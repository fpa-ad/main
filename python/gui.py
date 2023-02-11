import sys
from PyQt5.QtCore import Qt, QObject, QThread, pyqtSignal
from PyQt5.QtGui import QIcon, QPixmap, QMovie
from PyQt5.QtWidgets import QMainWindow, QLabel, QToolBar, QAction, QDialog, QDialogButtonBox, QGridLayout, QApplication, QWidget, QListWidget, QPushButton, QDoubleSpinBox, QComboBox, QFrame, QSpinBox, QTextEdit, QMessageBox
import pyqtgraph as pg
import numpy as np
from plots import make_plots

import libFCpython as l

class QHLine(QFrame):
    """Simple horizontal line"""
    def __init__(self):
        super(QHLine, self).__init__()
        self.setFrameShape(QFrame.HLine)
        self.setFrameShadow(QFrame.Sunken)

class Plots(QObject):
    """Thread to run the simulation and handle the outputs"""
    finished = pyqtSignal(str)

    def __init__(self, Lx, Ly, dx, dy, dt, n, n_part, ctms, f, nFields, fields, T, sc, B, Bn):
        super(QObject, self).__init__()
        self.Lx = Lx
        self.Ly = Ly
        self.dx = dx
        self.dy = dy
        self.dt = dt
        self.n = n
        self.n_part = n_part
        self.ctms = ctms
        self.f = f
        self.nFields = nFields
        self.fields = fields
        self.T = T
        self.sc = sc
        self.B = B
        self.Bn = Bn

    def run(self):
        """Run the simulation, export the plots"""
        self.i = l.interface()
        self.name = self.i.create_simulation(self.Lx, self.Ly, self.dx, self.dy, self.dt, self.n, self.n_part, self.ctms, self.f, self.nFields, self.fields)
        self.i.run_simulation(self.T, self.sc)
        # the destructor should be called automatically, if not, call i.end_simulation()

        make_plots(self.name, self.B, self.Bn)

        self.finished.emit(self.name)

class Window(QMainWindow):
    """Main program window"""
    def __init__(self, parent=None):
        self.particles = []
        self.Lx = 1
        self.Ly = 1

        super().__init__(parent)
        self.setWindowIcon(QIcon('python/pic-logo.png'))
        self.setWindowTitle("PIC")
        self.resize(800, 600)
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
        self.layout.addWidget(title, 0, 0, 1, 6, Qt.AlignHCenter)

        particles_title = QLabel("Particles")
        particles_title.setStyleSheet("font: bold;")
        self.layout.addWidget(particles_title, 1, 0, 1, 6, Qt.AlignHCenter)

        self.listwidget = QListWidget()
        self.listwidget.clicked.connect(self._particleClicked)
        self.layout.addWidget(self.listwidget, 2, 0, 1, 6)

        particles_button = QPushButton("Add")
        particles_button.clicked.connect(self._newParticle)
        self.layout.addWidget(particles_button, 3, 0, 1, 3, Qt.AlignHCenter)

        particles_undo = QPushButton("Undo")
        particles_undo.clicked.connect(self._undoParticle)
        self.layout.addWidget(particles_undo, 3, 3, 1, 3, Qt.AlignHCenter)

        fields_title = QLabel("Background fields")
        fields_title.setStyleSheet("font: bold;")
        self.layout.addWidget(fields_title, 4, 0, 1, 6, Qt.AlignHCenter)

        Ex_label = QLabel("Ex")
        self.layout.addWidget(Ex_label, 5, 0, 1, 1, Qt.AlignLeft)

        self.Ex = QDoubleSpinBox()
        self.Ex.setMinimum(-10)
        self.Ex.setMaximum(10)
        self.Ex.setDecimals(3)
        self.Ex.setValue(0)
        self.layout.addWidget(self.Ex, 5, 1, 1, 1, Qt.AlignHCenter)

        Ey_label = QLabel("Ey")
        self.layout.addWidget(Ey_label, 5, 2, 1, 1, Qt.AlignLeft)

        self.Ey = QDoubleSpinBox()
        self.Ey.setMinimum(-10)
        self.Ey.setMaximum(10)
        self.Ey.setDecimals(3)
        self.Ey.setValue(0)
        self.layout.addWidget(self.Ey, 5, 3, 1, 1, Qt.AlignHCenter)

        Bz_label = QLabel("Bz")
        self.layout.addWidget(Bz_label, 5, 4, 1, 1, Qt.AlignLeft)

        self.Bz = QDoubleSpinBox()
        self.Bz.setMinimum(-10)
        self.Bz.setMaximum(10)
        self.Bz.setDecimals(3)
        self.Bz.setValue(0)
        self.layout.addWidget(self.Bz, 5, 5, 1, 1, Qt.AlignHCenter)

        box_title = QLabel("Box parameters")
        box_title.setStyleSheet("font: bold;")
        self.layout.addWidget(box_title, 6, 0, 1, 6, Qt.AlignHCenter)

        Lx_label = QLabel("Lx (x-direction box length)")
        self.layout.addWidget(Lx_label, 7, 0, 1, 1, Qt.AlignLeft)

        self.Lx_spin = QDoubleSpinBox()
        self.Lx_spin.setMinimum(0.1)
        self.Lx_spin.setMaximum(10)
        self.Lx_spin.setDecimals(2)
        self.Lx_spin.setValue(1)
        self.layout.addWidget(self.Lx_spin, 7, 1, 1, 1, Qt.AlignHCenter)

        Ly_label = QLabel("Ly (y-direction box length)")
        self.layout.addWidget(Ly_label, 7, 2, 1, 1, Qt.AlignLeft)

        self.Ly_spin = QDoubleSpinBox()
        self.Ly_spin.setMinimum(0.1)
        self.Ly_spin.setMaximum(10)
        self.Ly_spin.setDecimals(2)
        self.Ly_spin.setValue(1)
        self.layout.addWidget(self.Ly_spin, 7, 3, 1, 1, Qt.AlignHCenter)

        dx_label = QLabel("dx (x-direction grid size)")
        self.layout.addWidget(dx_label, 8, 0, 1, 1, Qt.AlignLeft)

        self.dx = QDoubleSpinBox()
        self.dx.setMinimum(0.1)
        self.dx.setMaximum(10)
        self.dx.setDecimals(2)
        self.layout.addWidget(self.dx, 8, 1, 1, 1, Qt.AlignHCenter)

        dy_label = QLabel("dy (y-direction grid size)")
        self.layout.addWidget(dy_label, 8, 2, 1, 1, Qt.AlignLeft)

        self.dy = QDoubleSpinBox()
        self.dy.setMinimum(0.1)
        self.dy.setMaximum(10)
        self.dy.setDecimals(2)
        self.layout.addWidget(self.dy, 8, 3, 1, 1, Qt.AlignHCenter)

        dt_label = QLabel("dt (time step)")
        self.layout.addWidget(dt_label, 7, 4, 2, 1, Qt.AlignLeft)

        self.dt = QDoubleSpinBox()
        self.dt.setMinimum(0.1)
        self.dt.setMaximum(1)
        self.dt.setDecimals(3)
        self.layout.addWidget(self.dt, 7, 5, 2, 1, Qt.AlignHCenter)

        sim_title = QLabel("Simulation")
        sim_title.setStyleSheet("font: bold;")
        self.layout.addWidget(sim_title, 9, 0, 1, 4, Qt.AlignHCenter)

        T_label = QLabel("Simulation time")
        self.layout.addWidget(T_label, 10, 0, 1, 1, Qt.AlignLeft)

        self.T = QDoubleSpinBox()
        self.T.setMinimum(0.1)
        self.T.setMaximum(600)
        self.T.setValue(10)
        self.T.setDecimals(3)
        self.layout.addWidget(self.T, 10, 1, 1, 1, Qt.AlignHCenter)

        sc_label = QLabel("Screenshot interval")
        self.layout.addWidget(sc_label, 10, 2, 1, 1, Qt.AlignLeft)

        self.sc = QDoubleSpinBox()
        self.sc.setMinimum(0.1)
        self.sc.setMaximum(10)
        self.sc.setValue(0.2)
        self.sc.setDecimals(3)
        self.layout.addWidget(self.sc, 10, 3, 1, 1, Qt.AlignHCenter)

        plots_title = QLabel("Plots")
        plots_title.setStyleSheet("font: bold;")
        self.layout.addWidget(plots_title, 11, 0, 1, 4, Qt.AlignHCenter)

        B_label = QLabel("Bin start/end")
        self.layout.addWidget(B_label, 12, 0, 1, 1, Qt.AlignLeft)

        self.B = QDoubleSpinBox()
        self.B.setMinimum(0.1)
        self.B.setMaximum(1000)
        self.B.setValue(100)
        self.B.setDecimals(1)
        self.layout.addWidget(self.B, 12, 1, 1, 1, Qt.AlignHCenter)

        Bn_label = QLabel("Bin number")
        self.layout.addWidget(Bn_label, 12, 2, 1, 1, Qt.AlignLeft)

        self.Bn = QSpinBox()
        self.Bn.setMinimum(10)
        self.Bn.setMaximum(200)
        self.Bn.setValue(50)
        self.layout.addWidget(self.Bn, 12, 3, 1, 1, Qt.AlignHCenter)

        self.sim = QPushButton("Start")
        self.sim.setFixedSize(80, 80)
        self.sim.setStyleSheet("border-radius: 40; border: 2px solid black; background-color:red; font: 16pt bold; color: black")
        self.sim.clicked.connect(self._simClicked)
        self.layout.addWidget(self.sim, 10, 4, 4, 2, Qt.AlignHCenter)

    def _newParticle(self):
        """Handler for the new particle button"""
        dlg = ParticleDialog("new", self.particles, self.Lx, self.Ly)
        if dlg.exec():
            # new particle needs to be added to the list
            self.listwidget.addItem(self._printParticle(-1))

    def _undoParticle(self):
        """Handler for the undo button"""
        if self.particles:
            self.listwidget.takeItem(len(self.particles)-1)
            self.particles.pop()

    def _particleClicked(self, qmodelindex):
        """Handler for the listwidget, when an item is clicked
        @param qmodelindex QModelIndex clicked"""
        item = self.listwidget.currentItem()
        dlg = ParticleDialog("edit", self.particles, self.Lx, self.Ly, qmodelindex.row())
        if dlg.exec():
            # particle was changed and needs to be updated
            item.setText(self._printParticle(qmodelindex.row()))

    def _printParticle(self, i):
        """Print a given particle as a string
        @param i particle's index"""
        x_dist = self.particles[i][2][0]
        if x_dist == 0:
            x_dist_str = "random x dist."
        elif x_dist == 1:
            x_dist_str = f"step x dist. (s = {self.particles[i][2][1]})"
        else:
            x_dist_str = f"rectangular x dist. (s = {self.particles[i][2][1]}, e = {self.particles[i][2][2]})"
        y_dist = self.particles[i][3][0]
        if y_dist == 0:
            y_dist_str = "random y dist."
        elif y_dist == 1:
            y_dist_str = f"step y dist. (s = {self.particles[i][3][1]})"
        else:
            y_dist_str = f"rectangular y dist. (s = {self.particles[i][3][1]}, e = {self.particles[i][3][2]})"
        vx_dist = self.particles[i][4][0]
        if vx_dist == 0:
            vx_dist_str = f"maxwellian vx dist. (vp = {self.particles[i][4][1]}, v0 = {self.particles[i][4][2]})"
        else:
            vx_dist_str = f"bump-on-tail vx dist. (vp = {self.particles[i][4][1]}, v0 = {self.particles[i][4][2]}, s = {self.particles[i][4][3]})"
        vy_dist = self.particles[i][5][0]
        if vy_dist == 0:
            vy_dist_str = f"maxwellian vy dist. (vp = {self.particles[i][5][1]}, v0 = {self.particles[i][5][2]})"
        else:
            vy_dist_str = f"bump-on-tail vy dist. (vp = {self.particles[i][5][1]}, v0 = {self.particles[i][5][2]}, s = {self.particles[i][5][3]})"
        return f"{self.particles[i][0]} particle(s) with ctm = {self.particles[i][1]}, {x_dist_str}, {y_dist_str},\n{vx_dist_str}, {vy_dist_str}"

    def _simClicked(self):
        """Handler for the simulation button, runs the Plots thread"""

        if not self.particles:
            QMessageBox.critical(self, "Error", "Unable to start simulation! Define some particles first...")
            return

        n_particles = []
        ctms = []
        f = []
        for i in range(len(self.particles)):
            n_particles.append(self.particles[i][0])
            ctms.append(self.particles[i][1])
            f.append([self.particles[i][2], self.particles[i][3], self.particles[i][4], self.particles[i][5]])
        nFields = 1
        fields = [[self.Ex.value(), self.Ey.value(), 0]]
        if self.Bz.value() != 0:
            nFields = 2
            fields.append([0, 0, self.Bz.value()])

        self.thread = QThread()
        self.worker = Plots(self.Lx_spin.value(), self.Ly_spin.value(), self.dx.value(), self.dy.value(), self.dt.value(), len(self.particles), n_particles, ctms, f, nFields, fields, self.T.value(), self.sc.value(), self.B.value(), self.Bn.value())
        self.worker.moveToThread(self.thread)
        self.thread.started.connect(self.worker.run)
        self.worker.finished.connect(self.thread.quit)
        self.worker.finished.connect(self.worker.deleteLater)
        self.thread.finished.connect(self.thread.deleteLater)
        self.thread.start()

        self.sim.setEnabled(False)
        self.thread.finished.connect(
            lambda : self.sim.setEnabled(True)
        )
        self.worker.finished.connect(self._showResults)

    def _showResults(self, name):
        """Show results handler, called when the Plots thread is done
        @param name name of the simulation"""
        dlg = ResultsDialog(name)
        dlg.exec()

    def _aboutClicked(self):
        """Handler for the about button"""
        dlg = CustomDialog("about")
        dlg.exec()

    def _helpClicked(self):
        """Handler for the help button"""
        dlg = CustomDialog("help")
        dlg.exec()

class CustomDialog(QDialog):
    """Custom dialog, used for specific situations
    @param type ("about" or "help")"""
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

            message = QTextEdit()

            message.setPlainText('''---- FAQ
1. The program crashed! Where are my results? Did I lose everything?
No. As the simulation progresses, its results are saved in a timestamped folder on the "output" folder in your main directory. You should be able to recover most of your results.

2. The program is having weird glitches...
Have you tried recompiling the library from scratch?

3. The program is taking a reaaaaaally long time to produce my gifs. Is this normal?
If you have selected a very high frequency of snapshots or a very lengthy simulation, that can happen. Consider changing your parameters.
The plots program is fully optimised, so if the simulation runs smoothly, and quickly, the problem is there are too many snapshots to handle. It's a waiting game...

4. The program will not let me select the parameters I want for the positions distribution functions!
Have you checked if they are in compliance with the Lx and Ly you have selected? Try increasing these first.

5. The boxes will not let me input the parameters I want!
Assume the limitations are there for a reason OR try using the library directly instead.

6. I am getting really funky results.
Check the Physics. The GUI only does very light validation of the parameters, there may be something weird with them.
            ''')
            message.setReadOnly(True)

            self.layout.addWidget(message, 0, 0, 1, 2, Qt.AlignTop)

        self.layout.addWidget(self.buttonBox, bt, 0, 1, 2)
        self.setLayout(self.layout)

class ParticleDialog(QDialog):
    """Dialog to enter a new particle type
    @param type whether this is a new particle or an edit
    @param particles particle list
    @param Lx x length of the box
    @param Ly y length of the box
    @param i index of the particle clicked, if editing (-1 otherwise)"""
    def __init__(self, type, particles, Lx, Ly, i=-1):
        super().__init__()
        self.setWindowIcon(QIcon('python/pic-logo.png'))
        self.setWindowTitle("Particle")

        self.resize(1000, 800)

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
        self.layout.addWidget(title, 0, 0, 1, 3, Qt.AlignHCenter)

        n_label = QLabel("Number of particles")
        self.layout.addWidget(n_label, 1, 0, 1, 1, Qt.AlignLeft)

        self.n = QSpinBox()
        self.n.setMinimum(1)
        self.n.setMaximum(100)
        self.layout.addWidget(self.n, 1, 1, 1, 1, Qt.AlignCenter)

        self.layout.addWidget(QHLine(), 2, 0, 1, 2)

        ctm_label = QLabel("Charge to mass ratio")
        self.layout.addWidget(ctm_label, 3, 0, 1, 1, Qt.AlignLeft)

        self.ctm = QDoubleSpinBox()
        self.ctm.setMinimum(-10)
        self.ctm.setMaximum(10)
        self.ctm.setDecimals(4)
        self.ctm.setValue(-1)
        self.layout.addWidget(self.ctm, 3, 1, 1, 1, Qt.AlignHCenter)

        self.layout.addWidget(QHLine(), 4, 0, 1, 2)

        x_label = QLabel("x distribution function")
        self.layout.addWidget(x_label, 5, 0, 1, 1, Qt.AlignLeft)

        self.x = QComboBox()
        self.x.addItems(["Random", "Step", "Rectangular"])
        self.x.currentIndexChanged.connect(self._xChanged)
        self.layout.addWidget(self.x, 5, 1, 1, 1, Qt.AlignHCenter)

        self.x_grid_widget = QWidget()
        self.layout.addWidget(self.x_grid_widget, 6, 0, 1, 2)
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

        self.layout.addWidget(QHLine(), 7, 0, 1, 2)

        y_label = QLabel("y distribution function")
        self.layout.addWidget(y_label, 8, 0, 1, 1, Qt.AlignLeft)

        self.y = QComboBox()
        self.y.addItems(["Random", "Step", "Rectangular"])
        self.y.currentIndexChanged.connect(self._yChanged)
        self.layout.addWidget(self.y, 8, 1, 1, 1, Qt.AlignHCenter)

        self.y_grid_widget = QWidget()
        self.layout.addWidget(self.y_grid_widget, 9, 0, 1, 2)
        self.y_grid = QGridLayout()
        self.y_grid_widget.setLayout(self.y_grid)

        self.y_s_label = QLabel("Start")
        self.y_grid.addWidget(self.y_s_label, 0, 0, 1, 1, Qt.AlignLeft)

        self.y_s = QDoubleSpinBox()
        self.y_s.setMinimum(0)
        self.y_s.setMaximum(Ly)
        self.y_s.setValue(Ly/4)
        self.y_grid.addWidget(self.y_s, 0, 1, 1, 1, Qt.AlignHCenter)

        self.y_e_label = QLabel("End")
        self.y_grid.addWidget(self.y_e_label, 1, 0, 1, 1, Qt.AlignLeft)

        self.y_e = QDoubleSpinBox()
        self.y_e.setMinimum(0)
        self.y_e.setMaximum(Ly)
        self.y_e.setValue(3*Ly/4)
        self.y_grid.addWidget(self.y_e, 1, 1, 1, 1, Qt.AlignHCenter)

        self.layout.addWidget(QHLine(), 10, 0, 1, 2)

        vx_label = QLabel("vx distribution function")
        self.layout.addWidget(vx_label, 11, 0, 1, 1, Qt.AlignLeft)

        self.vx = QComboBox()
        self.vx.addItems(["Maxwellian", "Bump-on-tail"])
        self.vx.currentIndexChanged.connect(self._vxChanged)
        self.layout.addWidget(self.vx, 11, 1, 1, 1, Qt.AlignHCenter)

        vx_grid_widget = QWidget()
        self.layout.addWidget(vx_grid_widget, 12, 0, 1, 2)
        vx_grid = QGridLayout()
        vx_grid_widget.setLayout(vx_grid)

        vx_vp_label = QLabel("Particle velocity")
        vx_grid.addWidget(vx_vp_label, 0, 0, 1, 1, Qt.AlignLeft)

        self.vx_vp = QDoubleSpinBox()
        self.vx_vp.setMinimum(0.001)
        self.vx_vp.setMaximum(10)
        self.vx_vp.setValue(1)
        self.vx_vp.setDecimals(3)
        self.vx_vp.valueChanged.connect(self._updatePlot)
        vx_grid.addWidget(self.vx_vp, 0, 1, 1, 1, Qt.AlignHCenter)

        self.vx_v0_label = QLabel("Position")
        vx_grid.addWidget(self.vx_v0_label, 1, 0, 1, 1, Qt.AlignLeft)

        self.vx_v0 = QDoubleSpinBox()
        self.vx_v0.setMinimum(-10)
        self.vx_v0.setSingleStep(0.1)
        self.vx_v0.setMaximum(10)
        self.vx_v0.setValue(0)
        self.vx_v0.setDecimals(3)
        self.vx_v0.valueChanged.connect(self._updatePlot)
        vx_grid.addWidget(self.vx_v0, 1, 1, 1, 1, Qt.AlignHCenter)

        self.vx_s_label = QLabel("Bump-on tail strength (b)")
        vx_grid.addWidget(self.vx_s_label, 2, 0, 1, 1, Qt.AlignLeft)

        self.vx_s = QDoubleSpinBox()
        self.vx_s.setMinimum(0.001)
        self.vx_s.setMaximum(1)
        self.vx_s.setValue(0.1)
        self.vx_s.setDecimals(4)
        self.vx_s.valueChanged.connect(self._updatePlot)
        vx_grid.addWidget(self.vx_s, 2, 1, 1, 1, Qt.AlignHCenter)

        self.layout.addWidget(QHLine(), 13, 0, 1, 2)

        vy_label = QLabel("vy distribution function")
        self.layout.addWidget(vy_label, 14, 0, 1, 1, Qt.AlignLeft)

        self.vy = QComboBox()
        self.vy.addItems(["Maxwellian", "Bump-on-tail"])
        self.vy.currentIndexChanged.connect(self._vyChanged)
        self.layout.addWidget(self.vy, 14, 1, 1, 1, Qt.AlignHCenter)

        vy_grid_widget = QWidget()
        self.layout.addWidget(vy_grid_widget, 15, 0, 1, 2)
        vy_grid = QGridLayout()
        vy_grid_widget.setLayout(vy_grid)

        vy_vp_label = QLabel("Particle velocity")
        vy_grid.addWidget(vy_vp_label, 0, 0, 1, 1, Qt.AlignLeft)

        self.vy_vp = QDoubleSpinBox()
        self.vy_vp.setMinimum(0.001)
        self.vy_vp.setMaximum(10)
        self.vy_vp.setValue(1)
        self.vy_vp.setDecimals(3)
        self.vy_vp.valueChanged.connect(self._updatePlot)
        vy_grid.addWidget(self.vy_vp, 0, 1, 1, 1, Qt.AlignHCenter)

        self.vy_v0_label = QLabel("Position")
        vy_grid.addWidget(self.vy_v0_label, 1, 0, 1, 1, Qt.AlignLeft)

        self.vy_v0 = QDoubleSpinBox()
        self.vy_v0.setMinimum(-10)
        self.vy_v0.setSingleStep(0.1)
        self.vy_v0.setMaximum(10)
        self.vy_v0.setValue(0)
        self.vy_v0.setDecimals(3)
        self.vy_v0.valueChanged.connect(self._updatePlot)
        vy_grid.addWidget(self.vy_v0, 1, 1, 1, 1, Qt.AlignHCenter)

        self.vy_s_label = QLabel("Bump-on tail strength (b)")
        vy_grid.addWidget(self.vy_s_label, 2, 0, 1, 1, Qt.AlignLeft)

        self.vy_s = QDoubleSpinBox()
        self.vy_s.setMinimum(0.001)
        self.vy_s.setMaximum(1)
        self.vy_s.setValue(0.1)
        self.vy_s.setDecimals(4)
        self.vy_s.valueChanged.connect(self._updatePlot)
        vy_grid.addWidget(self.vy_s, 2, 1, 1, 1, Qt.AlignHCenter)

        self.graphWidget = pg.PlotWidget()
        self.layout.addWidget(self.graphWidget, 1, 2, 15, 1)
        self.graphWidget.setBackground('w')

        self.layout.addWidget(self.buttonBox, 16, 0, 1, 3)
        self.setLayout(self.layout)

        if type == "new":
            self._xChanged(0)
            self._yChanged(0)
            self._vxChanged(0)
            self._vyChanged(0)
        elif type == "edit":
            self.n.setValue(particles[i][0])

            self.ctm.setValue(particles[i][1])

            x_dist = particles[i][2][0]
            self.x.setCurrentIndex(x_dist)
            if x_dist >= 1:
                self.x_s.setValue(particles[i][1][1])
                if x_dist == 2:
                    self.x_e.setValue(particles[i][1][2])

            y_dist = particles[i][3][0]
            self.y.setCurrentIndex(y_dist)
            if y_dist >= 1:
                self.y_s.setValue(particles[i][2][1])
                if y_dist == 2:
                    self.y_e.setValue(particles[i][2][2])

            vx_dist = particles[i][4][0]
            self.vx.setCurrentIndex(vx_dist)
            self.vx_vp.setValue(particles[i][3][1])
            self.vx_v0.setValue(particles[i][3][2])
            if vx_dist == 1:
                self.vx_s.setValue(particles[i][3][3])
            
            vy_dist = particles[i][5][0]
            self.vy.setCurrentIndex(vy_dist)
            self.vy_vp.setValue(particles[i][4][1])
            self.vy_v0.setValue(particles[i][4][2])
            if vy_dist == 1:
                self.vy_s.setValue(particles[i][4][3])

            self._xChanged(x_dist)
            self._yChanged(y_dist)
            self._vxChanged(vx_dist)
            self._vyChanged(vy_dist)
        self._updatePlot()

    def _save(self):
        """Save the particle created/edited"""
        new_particle = [self.n.value(), self.ctm.value()]

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
        vx = [vx_dist, self.vx_vp.value(), self.vx_v0.value()]
        if vx_dist == 1:
            vx.append(self.vx_s.value())
        new_particle.append(vx)

        vy_dist = self.vy.currentIndex()
        vy = [vy_dist, self.vy_vp.value(), self.vy_v0.value()]
        if vy_dist == 1:
            vy.append(self.vy_s.value())
        new_particle.append(vy)

        if self.type == "new":
            self.particles.append(new_particle)
        elif self.type == "edit":
            self.particles[self.i] = new_particle

    def _xChanged(self, index):
        """Handler for the x distribution combo - changed
        @param index index selected"""
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
        """Handler for the y distribution combo - changed
        @param index index selected"""
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
        """Handler for the vx distribution combo - changed
        @param index index selected"""
        if index == 0:
            self.vx_s_label.hide()
            self.vx_s.hide()
        else:
            self.vx_s_label.show()
            self.vx_s.show()
        self._updatePlot()

    def _vyChanged(self, index):
        """Handler for the vy distribution combo - changed
        @param index index selected"""
        if index == 0:
            self.vy_s_label.hide()
            self.vy_s.hide()
        else:
            self.vy_s_label.show()
            self.vy_s.show()
        self._updatePlot()

    def _updatePlot(self):
        """Update the plot of the distribution functions"""
        self.graphWidget.clear()

        points = np.arange(-10, 20, 0.1)

        vx_dist = self.vx.currentIndex()
        vp = self.vx_vp.value()
        if vx_dist == 0:
            fx = lambda v, vp=vp, v0=self.vx_v0.value(): 1/(vp*np.pi) * np.exp(-(v-v0)*(v-v0)/(vp*vp))
        else:
            fx = lambda v, vp=vp, v0=self.vx_v0.value(), b=self.vx_s.value(): 1/(vp*np.pi) * ((1-b)*np.exp(-v*v/(vp*vp)) + b*np.exp(-(v-v0)*(v-v0)/(vp*vp)))

        vy_dist = self.vy.currentIndex()
        vp = self.vy_vp.value()
        if vy_dist == 0:
            fy = lambda v, vp=vp, v0=self.vy_v0.value(): 1/(vp*np.pi) * np.exp(-(v-v0)*(v-v0)/(vp*vp))
        else:
            fy = lambda v, vp=vp, v0=self.vy_v0.value(), b=self.vy_s.value(): 1/(vp*np.pi) * ((1-b)*np.exp(-v*v/(vp*vp)) + b*np.exp(-(v-v0)*(v-v0)/(vp*vp)))

        self.graphWidget.setTitle("Velocity distributions")
        pen1 = pg.mkPen(color=(255, 0, 0), width=4)
        self.graphWidget.plot(points, fx(points), name="vx", pen=pen1)
        pen2 = pg.mkPen(color=(0, 0, 255), width=4)
        self.graphWidget.plot(points, fy(points), name="vy", pen=pen2)
        self.graphWidget.setXRange(-5, 10, padding=0)
        self.graphWidget.addLegend()

class ResultsDialog(QDialog):
    """Dialog with the resulting gifs"""
    def __init__(self, name):
        super().__init__()
        self.setWindowIcon(QIcon('python/pic-logo.png'))

        QBtn = QDialogButtonBox.Ok

        self.buttonBox = QDialogButtonBox(QBtn)
        self.buttonBox.accepted.connect(self.accept)

        self.layout = QGridLayout()

        self.plot_label = QLabel()
        self.plot_movie = QMovie("output/"+name+"/sim.gif")
        self.plot_label.setMovie(self.plot_movie)
        self.layout.addWidget(self.plot_label, 0, 0, 1, 1)

        self.hist_label = QLabel()
        self.hist_movie = QMovie("output/"+name+"/sim_hist.gif")
        self.hist_label.setMovie(self.hist_movie)
        self.layout.addWidget(self.hist_label, 0, 1, 1, 1)

        self.plot_movie.start()
        self.hist_movie.start()

        self.layout.addWidget(self.buttonBox, 1, 0, 1, 2)
        self.setLayout(self.layout)

app = QApplication(sys.argv)
app.setWindowIcon(QIcon('python/pic-logo.png'))
win = Window()
win.show()
sys.exit(app.exec_())
