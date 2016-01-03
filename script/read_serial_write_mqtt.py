#!/usr/bin/python2

import serial
import paho.mqtt.publish as publish

# config
serial_device="/dev/ttyUSB0"
serial_baudrate=115200
mqtt_hostname="siri.visitor.congress.ccc.de"
mqtt_port=1883


# read from serial
with serial.Serial(serial_device, serial_baudrate, timeout=1) as ser:
    while True:
        line = ser.readline().strip()

        if line:
            # print(line)
            # expected format:
            # /32c3/halle4/c-base/dht22/pin03/humidity 3180
            # /32c3/halle4/c-base/dht22/pin03/temperature 2330

            line = line.split(' ')
            if len(line) == 2:
                #print(line)
                subject = str(line[0])
                payload = int(line[1])
                publish.single(subject, payload, mqtt_hostname, mqtt_port)