#!/usr/bin/python

# Run this script local to retrieve data from serial and write directly into influxDB

import serial
from influxdb import InfluxDBClient

client = InfluxDBClient('192.168.33.56', 8086, 'root', 'root', 'c-base/c-lab')
print(client.query("SHOW DATABASES"))

with serial.Serial('/dev/ttyACM4', 115200, timeout=1) as ser:
    while True:
        line = ser.readline().strip()

        if line:
            line = line.split(' ')
            if len(line) == 2:
                print(line)
                tags = line[0].split(',')
                data = line[1].split(',')
                humidity = data[0].split('=')
                temperature = data[1].split('=')

                #print(data)
                #print(humidity)
                #print(temperature)
                #print(tags)

                sensor = tags[1].split('=')
                #print(sensor)

                #print(tags)
                pin = tags[2].split('=')
                #print(pin)

                json_body = [
                    {
                        "measurement": "temperature",
                        "tags": {
                            sensor[0]: sensor[1],
                            pin[0]: int(pin[1])
                        },
                        "fields": {
                            "value": int(temperature[1])/100
                        }
                    },
                    {
                        "measurement": "humidity",
                        "tags": {
                            sensor[0]:sensor[1],
                            pin[0]: int(pin[1])
                        },
                        "fields": {
                            "value": int(humidity[1])/100
                        }
                    }
                ]
                #print(json_body)
                client.write_points(json_body)
                #result = client.query('select value from temperature;')
                #print("Result: {0}".format(result))