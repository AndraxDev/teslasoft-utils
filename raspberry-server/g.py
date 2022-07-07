#!/usr/bin/python

import RPi.GPIO as GPIO # Gpio library
from time import sleep # Time library required for sleep() method

PORT_A = 36 # 36 - number of gpio pin (see gpio-datasheet.jpg)

# Initialization for gpio library
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

# Initialization for gpio inputs
GPIO.setup(PORT_A, GPIO.OUT)

# Setting default values for pins
GPIO.output(PORT_A, 0)


while True:
    GPIO.output(PORT_A, 1) # Start signal for pin #36
    #print("1")
    sleep(0.5)
    GPIO.output(PORT_A, 0) # Stop signal for pin #36
    #print("0")
    sleep(0.5)
