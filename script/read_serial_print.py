#!/usr/bin/python

import serial

with serial.Serial('/dev/ttyUSB1', 115200, timeout=1) as ser:
    while True:
        line = ser.readline().strip()

        if line:
            line = line.split(' ')
            if len(line) == 2:
                print(line)
