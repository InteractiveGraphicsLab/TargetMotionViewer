from PyQt6 import QtCore
from PyQt6.QtWidgets import QFileDialog

import cv2
import numpy as np
import sys

import mediapipe as mp
mp_drawing = mp.solutions.drawing_utils
mp_pose = mp.solutions.pose
mp_holistic = mp.solutions.holistic

from mp_params import POINT_NAME, COLORs

class TCore():

    def __init__(self, mainwindow):
        self.mainwindow = mainwindow
        self.timer = QtCore.QTimeLine()
        self.timer.valueChanged.connect(self.timer_step)
        self.timer.finished    .connect(self.timer_runout)
        self.timer.setUpdateInterval(33) #100ms
        self.roi = np.array([0,0,10,10])
        self.mouse_p0 = np.array([0,0])
        self.video_whf = np.array([0,0,0]) # width, height, frame
        # loa video
        if len(sys.argv) > 1:
            fname = sys.argv1[1]
        else:
            fname = QFileDialog.getOpenFileName(None, 'Open file', "./")[0]
        if fname == None or fname == "":
            exit()
        self.cap = None
        self.load_video(fname)
        self.timer.start()
        self.pose = mp_pose.Pose(min_detection_confidence=0.5,min_tracking_confidence=0.5)


    def load_video(self, fname):
        if self.cap != None :
            self.cap.release()

        self.cap = cv2.VideoCapture(fname)
        num_frame = int(self.cap.get(cv2.CAP_PROP_FRAME_COUNT))
        width     = int(self.cap.get(cv2.CAP_PROP_FRAME_WIDTH))
        height    = int(self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
        if num_frame == 0 :
            self.cap = None
            return
        time_per_frame = 1000.0 / self.cap.get(cv2.CAP_PROP_FPS)

        self.timer.setDuration(10000000)
        self.timer.setUpdateInterval(int(time_per_frame))
        self.mainwindow.setVideoSize(width, height, num_frame)
        self.video_whf = np.array([width, height, num_frame])
        self.roi = np.array([0,0,width,height])


    def release_mediapipe(self):
        self.pose.close()


    def btnpressed_play(self):
        if self.timer.state() == QtCore.QTimeLine.State.Running :
            self.timer.stop()
            self.mainwindow.setButtonPlayText("Start ▶")
        else :
            self.timer.start()
            self.mainwindow.setButtonPlayText("Stop ■")


    #Timer event handler
    def timer_runout(self):
        self.timer.setCurrentTime(0)
        self.timer.start()
        return


    def timer_step(self):
        self.__RepaintPanel(True, True)


    def slider_moved(self, value):
        self.cap.set(cv2.CAP_PROP_POS_FRAMES, value)
        self.__RepaintPanel(True, False)


    def __RepaintPanel(self, b_readframe, b_incrementslider ):
        if b_readframe :
            ret, frame = self.cap.read()
            if not ret:
                return
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            self.__DetectAndDrawLandmark(frame)
            self.prev_frame = frame.copy()
        else:
            if self.prev_frame is None : return
            frame = self.prev_frame.copy()
        self.__DrawRoiRect(frame)
        self.mainwindow.repaintPanel(frame)

        if b_incrementslider:
            self.mainwindow.incrementSlider()


    def __DetectAndDrawLandmark(self, img):
        img_trgt = img[self.roi[1]:self.roi[3], self.roi[0]:self.roi[2]]
        h, w, _ = img_trgt.shape
        if h < 10 or w < 10 :
            return

        results = self.pose.process(img_trgt)
        if results.pose_landmarks is None:
            return

        for i, id in enumerate(POINT_NAME):
            x = int(results.pose_landmarks.landmark[id].x * w) + self.roi[0]
            y = int(results.pose_landmarks.landmark[id].y * h) + self.roi[1]
            z = results.pose_landmarks.landmark[id].z
            v = results.pose_landmarks.landmark[id].visibility
            cv2.circle(img, (x,y), 5, COLORs[i], thickness=2, lineType=cv2.LINE_8)


    def __DrawRoiRect(self, img):
        cv2.rectangle(img, (self.roi[0], self.roi[1]), (self.roi[2], self.roi[3]),
                      color=(255, 255, 0), thickness=2)


    def panelMousePress(self, e):
        self.mouse_p0[0] = int(e.position().x())
        self.mouse_p0[1] = int(e.position().y())


    def panelMouseRelease(self, e):
        pass


    def panelMouseMove(self, e):
        x = int(e.position().x())
        y = int(e.position().y())
        self.roi[0] = min(x, self.mouse_p0[0])
        self.roi[1] = min(y, self.mouse_p0[1])
        self.roi[2] = max(x, self.mouse_p0[0])
        self.roi[3] = max(y, self.mouse_p0[1])
        self.__RepaintPanel(False, False)


    def btnpressed_exportroi(self):
        print("btnpressed_exportroi")


    def btnpressed_exportpose(self):

        self.timer.stop()
        self.mainwindow.setButtonPlayText("Start ▶")

        self.cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
        num_frame = self.video_whf[2]
        roi = self.roi
        h = roi[3] - roi[1]
        w = roi[2] - roi[0]
        if h < 10 or w < 10 :
            print("roi size is too small")
            return

        fname = QFileDialog.getSaveFileName(None, 'Save file', 'posedata.txt', 'text (*.txt)')[0]
        fp = open(fname, 'w')

        for id in POINT_NAME: fp.write(str(id) + " ")
        fp.write("\n")

        for i in range(num_frame):
            ret, frame = self.cap.read()
            if not ret : continue
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            results = self.pose.process(frame[roi[1]:roi[3], roi[0]:roi[2]])

            fp.write(str(i))
            for id in POINT_NAME:
                if results.pose_landmarks is None:
                    x, y = 0,0
                else :
                    x = int(results.pose_landmarks.landmark[id].x * w) + roi[0]
                    y = int(results.pose_landmarks.landmark[id].y * h) + roi[1]
                fp.write(" " + str(x) + " " +  str(y))
            fp.write("\n")

            if i % 100 == 0:
                print(i, "/", num_frame, "done")

        fp.close()

        print("btnpressed_exportpose")
