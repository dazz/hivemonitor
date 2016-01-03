# Data Structure of measurements

The goal is to create a generic enough data structure that suits all kinds of bee hacker projects and in that way helps us to build on work of others.

* interchange data between systems
* compare and correlate data
* reuse code and software
* protect privacy of beekeeper


### TOC

1. [Privacy vs. OpenData](#privacy-vs-opendata)
1. [Format](#format)
1. [Data point](#data-point)


## Privacy vs. OpenData

Every beekeeper should maintain anonymity if wished and also be able to conceal the location of the beehives.

At the same time the data should be made public so that a broader knowledgebase can be build and also correlations can be made.

To achieve this, all data points get a unique identifier.

## Format

The final format for storing the data is JSON.

Ids are generated and collisions are detected. Ids should be short to minimize the amount of data that needs to be send for each measurement.

## Data point

### Variant 1

* Use case: A sensor measures and sends one data point for each 
* Pro: Only one measurement value per data point
* Pro: Very flat structure
* Con: Need same structure for every measurement


```json
  {
    "hiveId": "h-GlaHquq0",
    "nodeId": "n-djrHauwd",
    "measurement": "temperature",
    "value": 23.42,
    "datetime": "2016-01-02T10:00:00.0Z",
    "sensor": "DHT22",
    "sensorId": "s-0agHRcNd",
    "sensorPos": "inside",
    "tags": [{"pin": 3}]
  }
```

All fields marked as optional do not need to be set. If not defined the property is required.

* `hiveId`: (Required, String) Identifier of the bee-hive. Unique per hive. The hive id consists of the word hive and a version 4 UUID. It is for querying and correlating data from different measurements.
* `nodeId`: (Optional, String) Identifier of the node, (Arduino, RaspberryPi, ...) that connects to the sensors
* `measurement`: (Required, String) Defines the type of measurement that was taken. Pick one:

    * `temperature`   in °C
    * `humidity`      in %
    * `acceleration`  in g
    * `weight`        in kg
    * `pressure`      in hPa
    * `light`         in lm
    * `flightcount`   as absolute
    * `wind-speed`    in km/h
    * `wind-gust`
    * `wind-deg`

    The type of the measurement also defines the unit of the `value`.
    
    All measurements are in metric units.
    **OR** there could be a `unit` field to specify.

* `value`: (Required, Float) The actual measured value.
* `datetime`: (Required, String)
* `sensor`: (Optional, String) Name of sensor, examples: `HIH4030`, `DHT22`, `ADXL345`
* `sensorId`: (Optional, String) Identifier of the sensor, sometimes more than one of the same sensor is connected to an node
* `sensorPos`: (Optional, String) Position of the sensor, "outside" or "inside"
* `tags`: (Optional, Object) Adding more meta information as key value pairs


### Variant 2

* Use case: a node sends multiple data points from possibly multi sensors at once.
* Con: Complex structure

```json
  {
    "hiveId": "h-GlaHquq0",
    "nodeId": "n-djrHauwd",
    "data": [
      {
        "sensor": "DHT22",
        "sensorId": "s-0agHRcNd",
        "sensorPos": "outside",
        "pin": 3,
        "temperature": 23.42,
        "humidity": 54.79
      },
      {
        "sensor": "DHT22",
        "sensorId": "s-GkKubcVG",
        "sensorPos": "inside",
        "pin": 7,
        "temperature": 10.42,
        "humidity": 40.10
      }
    ],
    "datetime": "2016-01-02T10:00:00.0Z"
  }
```

* `hiveId`: (Required, String) See above
* `nodeId`: (Required, String) See above
* `data`: (Required, array) List of Objects
  * `sensor`: (Optional, String) See above
  * `sensorId`: (Optional, String) See above
  * `sensorPos`: (Optional, String) See above
  * `pin`: (Optional, int) The pin number that the sensor is connected on the node
  * type: (Required, String) Pick options from measurement above
* `datetime`: (Required, String) See above
