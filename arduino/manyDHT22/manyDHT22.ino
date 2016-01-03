#include <DHT.h>

#define DHTPIN 3
#define DHTTYPE DHT22

DHT firstDht(3, DHTTYPE);
//DHT secondDht(7, DHTTYPE);
//DHT thirdDht(11, DHTTYPE);

DHT dhts[] = {firstDht};//, secondDht, thirdDht};
int dhtPins[] = {3};//, 7, 11};
int dhtCount = 1;

void setup() {
  Serial.begin(115200);
}

void loop() {
  //Serial.print("hallo\n");
  delay(4000);

  for (int i = 0; i < dhtCount; i = i + 1) {
    readDHT(dhts[i], dhtPins[i]);
  }
}

void readDHT(DHT &dht, int pin) {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  int temp = (int) (t * 100);
  int humi = (int) (h * 100);

  //Serial.print("/c-base/c-lab,sensor=dht22,");
  Serial.print("/32c3/halle4/c-base/dht22/pin");
  //Serial.print("pin=");
  if (pin <= 10) {
    Serial.print("0");
  }
  Serial.print(pin);
  Serial.print("/humidity ");
  Serial.print(humi);
  Serial.println("");


  Serial.print("/32c3/halle4/c-base/dht22/pin");
  //Serial.print("pin=");
  if (pin <= 10) {
    Serial.print("0");
  }
  Serial.print(pin);
  Serial.print("/temperature ");
  Serial.print(temp);
  Serial.println("");
}

