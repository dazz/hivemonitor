# Hive Monitor

Monitoring beehives with lots of technologies.

Sensors => Node (Arduino) => Air => MQTT => Storage (InfluxDB, CouchDB) => Monitor

1. Arduino node reads sensor data and writes to serial port
1. Raspberry or $something_else publishes data to MQTT
1. Retrieve data from MQTT and write to storage
  1. InfluxDB (for monitoring and real-time joy)
  1. CouchDB (for doing long term sciency things)
1. Grafana shows dashboard with data from InfluxDB

## Arduino node

The sensors are attached to the Arduino. A ino-script retrieves the data and sends them to the serial port.

Find *.ino files in ./arduino

### General
#### Hardware
* Arduino
* SainSmart Sensor Shield http://www.sainsmart.com/sainsmart-sensor-shield-v5-4-arduino-apc220-bluetooth-analog-module-servo-motor-1.html

#### Setup
* install arduino IDE
* download library (in IDE): Adafruit_Sensors

### Humidity & Temperature
* Hardware: DHT22
* download library (in IDE): Adafruit_DHT


## Serial to MQTT

The data from the sensors are written to the serial port, they noe need to be published to a message broker.
MQTT is the best way to let interested parties know that something interesting has happened.

* http://iotf-beta.readthedocs.org/en/latest/reference/mqtt/index.html

> Note:
>
> This part will be replaced by "WiFi Module - ESP8266" and the data can be send directly from the Sensor Node (Arduino) to the Message Broker (MQTT).

### Setup

* copy `./read_serial_write_mqtt.py` on Raspberry Pi and edit config values
* optional: install supervisor to always run the script with `apt-get install supervisor` (http://supervisord.org/installing.html)
* add conf file to [supervisord](https://www.digitalocean.com/community/tutorials/how-to-install-and-manage-supervisor-on-ubuntu-and-debian-vps)

```
> cat  /etc/supervisor/conf.d/read_serial_write_mqtt.conf 
[program:read_serial_write_mqtt]
command=/home/user/read_serial_write_mqtt.py
autostart=true
autorestart=true
user=alarm
directory=/home/user
```

### Config

Edit config values in script

```
serial_device="/dev/ttyUSB0"
serial_baudrate=115200
mqtt_hostname="siri.visitor.congress.ccc.de"
mqtt_port=1883
```

### Run

If option with supervisor `supervisorctl reread` or `supervisorctl restart read_serial_write_mqtt`

If not, just run the script by calling it `/home/user/read_serial_write_mqtt.py`


## MQTT to InfluxDB



This script needs to run on a server which is always running and connected to the internet.
Best is to let it be managed by supervisord.

### Setup

* `apt-get install pip`
* `pip install -r requirements.txt`

Installs: 
* https://pypi.python.org/pypi/paho-mqtt/1.1
* https://pypi.python.org/pypi/influxdb

### Config

```
mqtt_subscribe = "/#"
mqtt_host = "siri.visitor.congress.ccc.de"
mqtt_port=1883

influxdb_host="gigawatt-hilldale-92.c.influxdb.com"
influxdb_port=8086
influxdb_user="32c3"
influxdb_password="3c23at32c3"
influxdb_database="32c3"
influxdb_ssl=True
influxdb_verify_ssl=True
```

### Run `./bin/read_mqtt_write_influx.py`
