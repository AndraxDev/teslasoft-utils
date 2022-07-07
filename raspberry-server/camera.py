from picamera.array import PiRGBArray
from picamera import PiCamera
import numpy as np
import time
import argparse
import cv2
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
w = 640
h = 368
camera.resolution = (w, h)
camera.framerate = 24
rawCapture = PiRGBArray(camera, size=(w, h))
# allow the camera to warmup
time.sleep(1)
# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    # grab the raw NumPy array representing the image, then initialize the timestamp
    # and occupied/unoccupied text
    image = frame.array
    # show the frame
    cv2.imshow("Camera", image)
#     cv2.waitKey(0)
    key = cv2.waitKey(1) & 0xFF
    # clear the stream in preparation for the next frame
    rawCapture.truncate(0)
    # if the `q` key was pressed, break from the loop
    if key == ord("q"):
        break
