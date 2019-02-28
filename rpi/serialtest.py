#!/usr/bin/env python   
      
import time
import serial
               
ser = serial.Serial(            
    port='/dev/serial0',
    baudrate = 19200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)
         
while 1:
     ser.write('Hello\n')
     time.sleep(1)
