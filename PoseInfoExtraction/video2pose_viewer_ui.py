from PyQt6 import QtCore, QtGui, QtWidgets

from video2pose_viewer_core import TCore


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(661, 636)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.panel = QtWidgets.QGraphicsView(self.centralwidget)
        self.panel.setObjectName("panel")
        self.gridLayout.addWidget(self.panel, 0, 0, 1, 1)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.button_play = QtWidgets.QPushButton(self.centralwidget)
        self.button_play.setObjectName("button_play")
        self.horizontalLayout.addWidget(self.button_play)
        self.label1 = QtWidgets.QLabel(self.centralwidget)
        self.label1.setObjectName("label1")
        self.horizontalLayout.addWidget(self.label1)
        self.button_export_pose = QtWidgets.QPushButton(self.centralwidget)
        self.button_export_pose.setObjectName("button_export_pose")
        self.horizontalLayout.addWidget(self.button_export_pose)
        self.button_export_ROI = QtWidgets.QPushButton(self.centralwidget)
        self.button_export_ROI.setObjectName("button_export_ROI")
        self.horizontalLayout.addWidget(self.button_export_ROI)
        self.gridLayout.addLayout(self.horizontalLayout, 2, 0, 1, 1)
        self.slider = QtWidgets.QSlider(self.centralwidget)
        self.slider.setOrientation(QtCore.Qt.Orientation.Horizontal)
        self.slider.setObjectName("slider")
        self.gridLayout.addWidget(self.slider, 1, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

        #以下 後から追加したevent listener
        self.tcore = TCore(self)
        self.slider.setObjectName("slider")
        self.button_play       .pressed.connect(self.tcore.btnpressed_play      )
        self.button_export_ROI .pressed.connect(self.tcore.btnpressed_exportroi )
        self.button_export_pose.pressed.connect(self.tcore.btnpressed_exportpose)
        self.slider.sliderMoved.connect(self.tcore.slider_moved)
        self.panel.mousePressEvent   = self.tcore.panelMousePress
        self.panel.mouseReleaseEvent = self.tcore.panelMouseRelease
        self.panel.mouseMoveEvent    = self.tcore.panelMouseMove
        #self.timer.valueChanged.connect(self.timer_step)


    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.button_play.setText(_translate("MainWindow", "Play ▶"))
        self.label1.setText(_translate("MainWindow", "TextLabel"))
        self.button_export_pose.setText(_translate("MainWindow", "Export Pose"))
        self.button_export_ROI.setText(_translate("MainWindow", "Export ROI"))

    # 以下 追加した関数
    def setVideoSize(self, width, height, num_frames):
        self.slider.setMaximum(num_frames)
        self.panel.setGeometry(0,0,width,height)
        self.panel.setAlignment(QtCore.Qt.AlignmentFlag.AlignTop | QtCore.Qt.AlignmentFlag.AlignLeft);
        self.panel.setScene(QtWidgets.QGraphicsScene(0, 0, width, height, self.panel))
        #self.panel.setSceneRect(0,0,width,height)

    def setButtonPlayText(self, text):
        self.button_play.setText(text)

    #frame numpy array
    def repaintPanel(self, frame):
        h, w, _ = frame.shape
        image = QtGui.QImage(frame.data, w, h, w*3, QtGui.QImage.Format.Format_RGB888)
        pixmap = QtGui.QPixmap.fromImage(image)
        self.panel.scene().clear()
        self.panel.scene().addPixmap(pixmap)



    def incrementSlider(self):
        self.slider.setValue(self.slider.value()+1)



if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec())
