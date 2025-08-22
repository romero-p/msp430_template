#!/usr/bin/env python3

import serial

DEVICE = '/dev/ttyACM1'
ser = serial.Serial(DEVICE, timeout=600)
# ser = serial.Serial()
# ser.port = DEVICE
# ser.baudrate = 115200
# ser.timeout = 600
# ser.rts = False
# ser.dtr = False

# ser.open()

while True:
    x = ser.readline()
    try:
        result = x.decode('utf-8')
    except UnicodeDecodeError:
        result = x
    print(result)
