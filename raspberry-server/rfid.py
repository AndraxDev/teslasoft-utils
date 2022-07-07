#!/usr/bin/env python
import RPi.GPIO as GPIO
import mfrc522

GPIO.setwarnings(False)
reader = mfrc522.MFRC522()

while True:
    (status, TagType) = reader.MFRC522_Request(reader.PICC_REQIDL)
    ok = reader.MI_OK
    if status == reader.MI_OK:
        print("Card detected")
    
    (status, uid) = reader.MFRC522_Anticoll()
    
    if status == reader.MI_OK:
        print("Card UID: " + str(uid[0]) + "," + str(uid[1]) + "," + str(uid[2]) + "," + str(uid[3]) + "," + str(uid[4]))
        key = [0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF]
        
        reader.MFRC522_SelectTag(uid)
        
        auth_uid = [0, 0, 0, 0, 0]
        registery_1 = [98, 185, 10, 32, 241]
    