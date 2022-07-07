#!/usr/bin/python

import RPi.GPIO as GPIO
from time import sleep

RED = 18
YELLOW = 40
GREEN = 36
ORANGE = 0
PIN32 = 32

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(RED, GPIO.OUT)
GPIO.setup(YELLOW, GPIO.OUT)
GPIO.setup(GREEN, GPIO.OUT)
GPIO.setup(PIN32, GPIO.OUT)

def setColor(COLOR, STATE):
    if COLOR == RED and STATE == 1:
        GPIO.output(RED, 0)
        GPIO.output(YELLOW, 1)
        GPIO.output(GREEN, 1)
    elif COLOR == YELLOW and STATE == 1:
        GPIO.output(RED, 1)
        GPIO.output(YELLOW, 0)
        GPIO.output(GREEN, 1)
    elif COLOR == ORANGE and STATE == 1:
        GPIO.output(RED, 0)
        GPIO.output(YELLOW, 0)
        GPIO.output(GREEN, 1)
    elif COLOR == GREEN and STATE == 1:
        GPIO.output(RED, 1)
        GPIO.output(YELLOW, 1)
        GPIO.output(GREEN, 0)
    elif STATE == 0:
        GPIO.output(RED, 1)
        GPIO.output(YELLOW, 1)
        GPIO.output(GREEN, 1)

while True:
    setColor(RED, 1)
    sleep(0.5)
    setColor(RED, 0)
    sleep(0.5)
#setColor(RED, 0)
#GPIO.output(PIN32, 1)