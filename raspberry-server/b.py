#!/usr/bin/python

import RPi.GPIO as GPIO # Gpio library
from time import sleep # Time library required for sleep() method

RED = 36 # 36 - number of gpio pin (see gpio-datasheet.jpg)
YELLOW = 38
GREEN = 40

# Initialization for gpio library
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

# Initialization for gpio inputs
GPIO.setup(RED, GPIO.OUT)
GPIO.setup(YELLOW, GPIO.OUT)
GPIO.setup(GREEN, GPIO.OUT)

# Setting default values for pins
GPIO.output(RED, 1)
GPIO.output(YELLOW, 1)
GPIO.output(GREEN, 1)

# Main loop
while True:
    GPIO.output(YELLOW, 1)
    sleep(1)
    #GPIO.output(YELLOW, 0)
    #sleep(1)