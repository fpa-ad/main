import sys
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtWidgets import QMainWindow, QLabel, QToolBar, QAction, QDialog, QDialogButtonBox, QGridLayout, QApplication

class Window(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowIcon(QIcon('python/pic-logo.png'))
        self.setWindowTitle("PIC")
        self.resize(800, 600)
        self.centralWidget = QLabel("Hello, World")
        self.centralWidget.setAlignment(Qt.AlignHCenter | Qt.AlignVCenter)
        self.setCentralWidget(self.centralWidget)

        toolbar = QToolBar("Toolbar")
        self.addToolBar(toolbar)

        about_action = QAction("About", self)
        about_action.triggered.connect(self._aboutClicked)
        toolbar.addAction(about_action)

        help_action = QAction("Help", self)
        help_action.triggered.connect(self._helpClicked)
        toolbar.addAction(help_action)

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

app = QApplication(sys.argv)
app.setWindowIcon(QIcon('python/pic-logo.png'))
win = Window()
win.show()
sys.exit(app.exec_())