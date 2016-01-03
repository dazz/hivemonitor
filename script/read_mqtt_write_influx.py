#!/usr/bin/env python2

import paho.mqtt.client as mqtt
from influxdb import InfluxDBClient

# Configure
mqtt_subscribe = "/#"
mqtt_host = ""
mqtt_port=1883

influxdb_host=""
influxdb_port=8086
influxdb_user="32c3"
influxdb_password="3c23at32c3"
influxdb_database="32c3"
influxdb_ssl=True
influxdb_verify_ssl=True


# influxdbc = InfluxDBClient('192.168.33.56', 8086, 'root', 'root', 'c-base/c-lab')
influxdbc = InfluxDBClient(influxdb_host, influxdb_port, influxdb_user, influxdb_password, influxdb_database, influxdb_ssl, influxdb_verify_ssl)

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(mqtt_subscribe)

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    write_influx(msg.topic, msg.payload)

# Write data to influxdb
def write_influx(topic, payload):

    print(topic+" "+str(payload))
    # /32c3/halle4/c-base/dht22/pin03/temperature 2380
    topic_parts = topic.split("/")
    # ['', '32c3', 'halle4', 'c-base', 'dht22', 'pin03', 'temperature']
    #print(topic_parts)

    json_body = [
        {
            "measurement": str(topic_parts[6]),
            "tags": {
                "sensor": topic_parts[4],
                "pin": str(topic_parts[5])
            },
            "fields": {
                "value": int(payload)/100.0
            }
        }
    ]
    #print(json_body)
    influxdbc.write_points(json_body)



def main():
    mqttc = mqtt.Client()
    mqttc.on_connect = on_connect
    mqttc.on_message = on_message

    mqttc.connect(mqtt_host, mqtt_port, 60)

    # Blocking call that processes network traffic, dispatches callbacks and
    # handles reconnecting.
    # Other loop*() functions are available that give a threaded interface and a
    # manual interface.
    mqttc.loop_forever()

if __name__ == "__main__":
    main()



