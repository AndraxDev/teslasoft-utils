import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO_TRIGGER = 18
GPIO_ECHO = 24

GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
GPIO.setup(GPIO_ECHO, GPIO.IN)

GPIO.output(GPIO_TRIGGER, True)
    
time.sleep(0.00001)
GPIO.output(GPIO_TRIGGER, False)
    
StartTime = time.time()
StopTime = time.time()
    
while GPIO.input(GPIO_ECHO) == 0:
    StartTime = time.time()
    
while GPIO.input(GPIO_ECHO) == 1:
    StopTime = time.time()
        
TimeElapsed = StopTime - StartTime
distance = round((TimeElapsed * 17150), 2)
    
print("Distance: " + distance)

GPIO.cleanup()