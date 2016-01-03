#!/usr/bin/python2

import paho.mqtt.publish as publish
import paho.mqtt.client as mqtt
import time

# config
mqtt_hostname="192.168.33.56"
mqtt_port=1883

topic = "/this/is/a/test/subject"
payload = 5

while True:
    publish.single(topic, payload, qos=0, retain=False, hostname=mqtt_hostname, port=mqtt_port, client_id="test_publisher", keepalive=60, will=None, auth=None, tls=None, protocol=mqtt.MQTTv31)

    time.sleep(3)  # Delay for 3 seconds