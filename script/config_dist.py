#!/usr/bin/python2

#
# Copy this to config.py
#

serial_device="/dev/ttyUSB0"
serial_baudrate=115200

mqtt_subscribe = "/#"
mqtt_host = "192.168.33.56"
mqtt_port=1883

influxdb_host="influxdb.com"
influxdb_port=8086
influxdb_user=""
influxdb_password=""
influxdb_database="test"
influxdb_ssl=True
influxdb_verify_ssl=True