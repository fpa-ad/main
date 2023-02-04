import sys
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtWidgets import QMainWindow, QLabel, QToolBar, QAction, QDialog, QDialogButtonBox, QGridLayout, QApplication, QWidget, QListWidget, QPushButton, QDoubleSpinBox, QComboBox, QFrame

class QHLine(QFrame):
    def __init__(self):
        super(QHLine, self).__init__()
        self.setFrameShape(QFrame.HLine)
        self.setFrameShadow(QFrame.Sunken)


class QVLine(QFrame):
    def __init__(self):
        super(QVLine, self).__init__()
        self.setFrameShape(QFrame.VLine)
        self.setFrameShadow(QFrame.Sunken)

class Window(QMainWindow):
    def __init__(self, parent=None):
        self.particles = []
        self.Lx = 1
        self.Ly = 1

        super().__init__(parent)
        self.setWindowIcon(QIcon('python/pic-logo.png'))
        self.setWindowTitle("PIC")
        self.resize(1000, 600)
        self.widget = QWidget()
        self.layout = QGridLayout()
        self.setCentralWidget(self.widget)
        self.widget.setLayout(self.layout)

        toolbar = QToolBar("Toolbar")
        self.addToolBar(toolbar)

        about_action = QAction("About", self)
        about_action.triggered.connect(self._aboutClicked)
        toolbar.addAction(about_action)

        help_action = QAction("Help", self)
        help_action.triggered.connect(self._helpClicked)
        toolbar.addAction(help_action)

        title = QLabel("Configurations")
        title.setStyleSheet("font: bold 24px;")
        self.layout.addWidget(title, 0, 0, 1, 1, Qt.AlignHCenter)

        particles_title = QLabel("Particles")
        self.layout.addWidget(particles_title, 1, 0, 1, 1, Qt.AlignHCenter)

        self.listwidget = QListWidget()
        self.listwidget.clicked.connect(self._particleClicked)
        self.layout.addWidget(self.listwidget, 2, 0, 1, 1)

        particles_button = QPushButton("New")
        particles_button.clicked.connect(self._newParticle)
        self.layout.addWidget(particles_button, 3, 0, 1, 1, Qt.AlignHCenter)

    def _newParticle(self):
        dlg = ParticleDialog("new", self.particles, self.Lx, self.Ly)
        if dlg.exec():
            # new particle needs to be added to the list
            self.listwidget.addItem(self._printParticle(-1))

    def _particleClicked(self, qmodelindex):
        item = self.listwidget.currentItem()
        dlg = ParticleDialog("edit", self.particles, self.Lx, self.Ly, qmodelindex.row())
        if dlg.exec():
            # particle was changed and needs to be updated
            item.setText(self._printParticle(qmodelindex.row()))

    def _printParticle(self, i):
        x_dist = self.particles[i][1][0]
        if x_dist == 0:
            x_dist_str = "random x dist."
        elif x_dist == 1:
            x_dist_str = f"step x dist. (s = {self.particles[i][1][1]})"
        else:
            x_dist_str = f"rectangular x dist. (s = {self.particles[i][1][1]}, e = {self.particles[i][1][2]})"
        y_dist = self.particles[i][2][0]
        if y_dist == 0:
            y_dist_str = "random y dist."
        elif y_dist == 1:
            y_dist_str = f"step y dist. (s = {self.particles[i][2][1]})"
        else:
            y_dist_str = f"rectangular y dist. (s = {self.particles[i][2][1]}, e = {self.particles[i][2][2]})"
        vx_dist = self.particles[i][3][0]
        if vx_dist == 0:
            vx_dist_str = f"maxwellian vx dist. (vp = {self.particles[i][3][1]})"
        else:
            vx_dist_str = f"bump-on-tail vx dist. (vp = {self.particles[i][3][1]}, v0 = {self.particles[i][3][2]}, s = {self.particles[i][3][3]})"
        vy_dist = self.particles[i][4][0]
        if vy_dist == 0:
            vy_dist_str = f"maxwellian vy dist. (vp = {self.particles[i][4][1]})"
        else:
            vy_dist_str = f"bump-on-tail vy dist. (vp = {self.particles[i][4][1]}, v0 = {self.particles[i][4][2]}, s = {self.particles[i][4][3]})"
        return f"ctm = {self.particles[i][0]}, {x_dist_str}, {y_dist_str},\n{vx_dist_str}, {vy_dist_str}"

    def _aboutClicked(self):
        dlg = CustomDialog("about")
        dlg.exec()

    def _helpClicked(self):
        dlg = CustomDialog("help")
        dlg.exec()

class CustomDialog(QDialog):
    def __init__(self, type):
        super().__init__()
        self.setWindowIcon(QIcon('python/pic-logo.png'))

        self.resize(600, 200)

        QBtn = QDialogButtonBox.Ok

        self.buttonBox = QDialogButtonBox(QBtn)
        self.buttonBox.accepted.connect(self.accept)

        self.layout = QGridLayout()

        bt = 1

        if type == "about":
            self.setWindowTitle("About")

            ist = QLabel(self)
            pixmap_ist = QPixmap('python/ist.png')
            ist.setPixmap(pixmap_ist.scaledToHeight(80))

            meft = QLabel(self)
            pixmap_meft = QPixmap('python/meft.png')
            meft.setPixmap(pixmap_meft.scaledToHeight(120))

            self.layout.addWidget(ist, 0, 0, 1, 1, Qt.AlignCenter)
            self.layout.addWidget(meft, 0, 1, 1, 1, Qt.AlignCenter)

            message = QLabel(
            '''This program was developed for the Advanced Plasma Physics 2022/23 class, as a final computational project.
    Developers:
        - Ana Sofia Sousa, ana.sofia.sousa@tecnico.ulisboa.pt
        - Diogo Simões, diogo.s.simoes@tecnico.ulisboa.pt''')
            message.setWordWrap(True)
            self.layout.addWidget(message, 1, 0, 1, 2)
            bt += 1

        elif type == "help":
            self.setWindowTitle("Help")

            message = QLabel('''
You have reached the help section.
Have you tried turning it off and on again?
            ''')

            self.layout.addWidget(message, 0, 0, 1, 2, Qt.AlignTop)

        self.layout.addWidget(self.buttonBox, bt, 0, 1, 2)
        self.setLayout(self.layout)

class ParticleDialog(QDialog):
    def __init__(self, type, particles, Lx, Ly, i=-1):
        super().__init__()
        self.setWindowIcon(QIcon('python/pic-logo.png'))
        self.setWindowTitle("Particle")

        self.resize(600, 800)

        if type == "new":
            QBtn = QDialogButtonBox.Ok | QDialogButtonBox.Cancel
        elif type == "edit":
            QBtn = QDialogButtonBox.Ok | QDialogButtonBox.Discard
        
        self.type = type
        self.particles = particles
        self.i = i

        self.buttonBox = QDialogButtonBox(QBtn)
        self.buttonBox.accepted.connect(self.accept)
        self.buttonBox.accepted.connect(self._save)
        self.buttonBox.rejected.connect(self.reject)

        self.layout = QGridLayout()

        title = QLabel("Particle configuration")
        title.setStyleSheet("font: bold;")
        self.layout.addWidget(title, 0, 0, 1, 2, Qt.AlignHCenter)

        ctm_label = QLabel("Charge to mass ratio")
        self.layout.addWidget(ctm_label, 1, 0, 1, 1, Qt.AlignLeft)

        self.ctm = QDoubleSpinBox()
        self.ctm.setMinimum(-10)
        self.ctm.setMaximum(10)
        self.ctm.setDecimals(4)
        self.ctm.setValue(-1)
        self.layout.addWidget(self.ctm, 1, 1, 1, 1, Qt.AlignHCenter)

        self.layout.addWidget(QHLine(), 2, 0, 1, 2)

        x_label = QLabel("x distribution function")
        self.layout.addWidget(x_label, 3, 0, 1, 1, Qt.AlignLeft)

        self.x = QComboBox()
        self.x.addItems(["Random", "Step", "Rectangular"])
        self.x.currentIndexChanged.connect(self._xChanged)
        self.layout.addWidget(self.x, 3, 1, 1, 1, Qt.AlignHCenter)

        self.x_grid_widget = QWidget()
        self.layout.addWidget(self.x_grid_widget, 4, 0, 1, 2)
        self.x_grid = QGridLayout()
        self.x_grid_widget.setLayout(self.x_grid)

        self.x_s_label = QLabel("Start")
        self.x_grid.addWidget(self.x_s_label, 0, 0, 1, 1, Qt.AlignLeft)

        self.x_s = QDoubleSpinBox()
        self.x_s.setMinimum(0)
        self.x_s.setMaximum(Lx)
        self.x_s.setValue(Lx/4)
        self.x_grid.addWidget(self.x_s, 0, 1, 1, 1, Qt.AlignHCenter)

        self.x_e_label = QLabel("End")
        self.x_grid.addWidget(self.x_e_label, 1, 0, 1, 1, Qt.AlignLeft)

        self.x_e = QDoubleSpinBox()
        self.x_e.setMinimum(0)
        self.x_e.setMaximum(Lx)
        self.x_e.setValue(3*Lx/4)
        self.x_grid.addWidget(self.x_e, 1, 1, 1, 1, Qt.AlignHCenter)

        self.layout.addWidget(QHLine(), 5, 0, 1, 2)

        y_label = QLabel("y distribution function")
        self.layout.addWidget(y_label, 6, 0, 1, 1, Qt.AlignLeft)

        self.y = QComboBox()
        self.y.addItems(["Random", "Step", "Rectangular"])
        self.y.currentIndexChanged.connect(self._yChanged)
        self.layout.addWidget(self.y, 6, 1, 1, 1, Qt.AlignHCenter)

        self.y_grid_widget = QWidget()
        self.layout.addWidget(self.y_grid_widget, 7, 0, 1, 2)
        self.y_grid = QGridLayout()
        self.y_grid_widget.setLayout(self.y_grid)

        self.y_s_label = QLabel("Start")
        self.y_grid.addWidget(self.y_s_label, 0, 0, 1, 1, Qt.AlignLeft)

        self.y_s = QDoubleSpinBox()
        self.y_s.setMinimum(0)
        self.y_s.setMaximum(Lx)
        self.y_s.setValue(Lx/4)
        self.y_grid.addWidget(self.y_s, 0, 1, 1, 1, Qt.AlignHCenter)

        self.y_e_label = QLabel("End")
        self.y_grid.addWidget(self.y_e_label, 1, 0, 1, 1, Qt.AlignLeft)

        self.y_e = QDoubleSpinBox()
        self.y_e.setMinimum(0)
        self.y_e.setMaximum(Lx)
        self.y_e.setValue(3*Lx/4)
        self.y_grid.addWidget(self.y_e, 1, 1, 1, 1, Qt.AlignHCenter)

        self.layout.addWidget(QHLine(), 8, 0, 1, 2)

        vx_label = QLabel("vx distribution function")
        self.layout.addWidget(vx_label, 9, 0, 1, 1, Qt.AlignLeft)

        self.vx = QComboBox()
        self.vx.addItems(["Maxwellian", "Bump-on-tail"])
        self.vx.currentIndexChanged.connect(self._vxChanged)
        self.layout.addWidget(self.vx, 9, 1, 1, 1, Qt.AlignHCenter)

        vx_grid_widget = QWidget()
        self.layout.addWidget(vx_grid_widget, 10, 0, 1, 2)
        vx_grid = QGridLayout()
        vx_grid_widget.setLayout(vx_grid)

        vx_vp_label = QLabel("Particle velocity")
        vx_grid.addWidget(vx_vp_label, 0, 0, 1, 1, Qt.AlignLeft)

        self.vx_vp = QDoubleSpinBox()
        self.vx_vp.setMinimum(0.001)
        self.vx_vp.setMaximum(10)
        self.vx_vp.setValue(1)
        self.vx_vp.setDecimals(3)
        vx_grid.addWidget(self.vx_vp, 0, 1, 1, 1, Qt.AlignHCenter)

        self.vx_v0_label = QLabel("Bump-on tail position")
        vx_grid.addWidget(self.vx_v0_label, 1, 0, 1, 1, Qt.AlignLeft)

        self.vx_v0 = QDoubleSpinBox()
        self.vx_v0.setMinimum(0.001)
        self.vx_v0.setMaximum(10)
        self.vx_v0.setValue(1)
        self.vx_v0.setDecimals(3)
        vx_grid.addWidget(self.vx_v0, 1, 1, 1, 1, Qt.AlignHCenter)

        self.vx_s_label = QLabel("Bump-on tail strength (b)")
        vx_grid.addWidget(self.vx_s_label, 2, 0, 1, 1, Qt.AlignLeft)

        self.vx_s = QDoubleSpinBox()
        self.vx_s.setMinimum(0.001)
        self.vx_s.setMaximum(1)
        self.vx_s.setValue(0.1)
        self.vx_s.setDecimals(4)
        vx_grid.addWidget(self.vx_s, 2, 1, 1, 1, Qt.AlignHCenter)

        self.layout.addWidget(QHLine(), 11, 0, 1, 2)

        vy_label = QLabel("vy distribution function")
        self.layout.addWidget(vy_label, 12, 0, 1, 1, Qt.AlignLeft)

        self.vy = QComboBox()
        self.vy.addItems(["Maxwellian", "Bump-on-tail"])
        self.vy.currentIndexChanged.connect(self._vyChanged)
        self.layout.addWidget(self.vy, 12, 1, 1, 1, Qt.AlignHCenter)

        vy_grid_widget = QWidget()
        self.layout.addWidget(vy_grid_widget, 13, 0, 1, 2)
        vy_grid = QGridLayout()
        vy_grid_widget.setLayout(vy_grid)

        vy_vp_label = QLabel("Particle velocity")
        vy_grid.addWidget(vy_vp_label, 0, 0, 1, 1, Qt.AlignLeft)

        self.vy_vp = QDoubleSpinBox()
        self.vy_vp.setMinimum(0.001)
        self.vy_vp.setMaximum(10)
        self.vy_vp.setValue(1)
        self.vy_vp.setDecimals(3)
        vy_grid.addWidget(self.vy_vp, 0, 1, 1, 1, Qt.AlignHCenter)

        self.vy_v0_label = QLabel("Bump-on tail position")
        vy_grid.addWidget(self.vy_v0_label, 1, 0, 1, 1, Qt.AlignLeft)

        self.vy_v0 = QDoubleSpinBox()
        self.vy_v0.setMinimum(0.001)
        self.vy_v0.setMaximum(10)
        self.vy_v0.setValue(1)
        self.vy_v0.setDecimals(3)
        vy_grid.addWidget(self.vy_v0, 1, 1, 1, 1, Qt.AlignHCenter)

        self.vy_s_label = QLabel("Bump-on tail strength (b)")
        vy_grid.addWidget(self.vy_s_label, 2, 0, 1, 1, Qt.AlignLeft)

        self.vy_s = QDoubleSpinBox()
        self.vy_s.setMinimum(0.001)
        self.vy_s.setMaximum(1)
        self.vy_s.setValue(0.1)
        self.vy_s.setDecimals(4)
        vy_grid.addWidget(self.vy_s, 2, 1, 1, 1, Qt.AlignHCenter)

        self.layout.addWidget(self.buttonBox, 14, 0, 1, 1)
        self.setLayout(self.layout)

        if type == "new":
            self._xChanged(0)
            self._yChanged(0)
            self._vxChanged(0)
            self._vyChanged(0)
        elif type == "edit":
            self.ctm.setValue(particles[i][0])

            x_dist = particles[i][1][0]
            self.x.setCurrentIndex(x_dist)
            if x_dist >= 1:
                self.x_s.setValue(particles[i][1][1])
                if x_dist == 2:
                    self.x_e.setValue(particles[i][1][2])

            y_dist = particles[i][2][0]
            self.y.setCurrentIndex(y_dist)
            if y_dist >= 1:
                self.y_s.setValue(particles[i][2][1])
                if y_dist == 2:
                    self.y_e.setValue(particles[i][2][2])

            vx_dist = particles[i][3][0]
            self.vx.setCurrentIndex(vx_dist)
            self.vx_vp.setValue(particles[i][3][1])
            if vx_dist == 1:
                self.vx_v0.setValue(particles[i][3][2])
                self.vx_s.setValue(particles[i][3][3])
            
            vy_dist = particles[i][4][0]
            self.vy.setCurrentIndex(vy_dist)
            self.vy_vp.setValue(particles[i][4][1])
            if vy_dist == 1:
                self.vy_v0.setValue(particles[i][4][2])
                self.vy_s.setValue(particles[i][4][3])

            self._xChanged(x_dist)
            self._yChanged(y_dist)
            self._vxChanged(vx_dist)
            self._vyChanged(vy_dist)

    def _save(self):
        new_particle = [self.ctm.value()]

        x_dist = self.x.currentIndex()
        x = [x_dist]
        if x_dist >= 1:
            x.append(self.x_s.value())
            if x_dist == 2:
                x.append(self.x_e.value())
        new_particle.append(x)

        y_dist = self.y.currentIndex()
        y = [y_dist]
        if y_dist >= 1:
            y.append(self.y_s.value())
            if y_dist == 2:
                y.append(self.y_e.value())
        new_particle.append(y)

        vx_dist = self.vx.currentIndex()
        vx = [vx_dist, self.vx_vp.value()]
        if vx_dist == 1:
            vx.append(self.vx_v0.value())
            vx.append(self.vx_s.value())
        new_particle.append(vx)

        vy_dist = self.vy.currentIndex()
        vy = [vy_dist, self.vy_vp.value()]
        if vy_dist == 1:
            vy.append(self.vy_v0.value())
            vy.append(self.vy_s.value())
        new_particle.append(vy)

        if self.type == "new":
            self.particles.append(new_particle)
        elif self.type == "edit":
            self.particles[self.i] = new_particle

    def _xChanged(self, index):
        if index == 0:
            self.x_grid_widget.hide()
        else:
            self.x_grid_widget.show()
            if index == 1:
                self.x_e_label.hide()
                self.x_e.hide()
            else:
                self.x_e_label.show()
                self.x_e.show()

    def _yChanged(self, index):
        if index == 0:
            self.y_grid_widget.hide()
        else:
            self.y_grid_widget.show()
            if index == 1:
                self.y_e_label.hide()
                self.y_e.hide()
            else:
                self.y_e_label.show()
                self.y_e.show()

    def _vxChanged(self, index):
        if index == 0:
            self.vx_v0_label.hide()
            self.vx_v0.hide()

            self.vx_s_label.hide()
            self.vx_s.hide()
        else:
            self.vx_v0_label.show()
            self.vx_v0.show()

            self.vx_s_label.show()
            self.vx_s.show()

    def _vyChanged(self, index):
        if index == 0:
            self.vy_v0_label.hide()
            self.vy_v0.hide()

            self.vy_s_label.hide()
            self.vy_s.hide()
        else:
            self.vy_v0_label.show()
            self.vy_v0.show()

            self.vy_s_label.show()
            self.vy_s.show()

app = QApplication(sys.argv)
app.setWindowIcon(QIcon('python/pic-logo.png'))
win = Window()
win.show()
sys.exit(app.exec_())