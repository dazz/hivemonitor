#include <DHT.h>

#define DHTPIN 3
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(4000);

  float h = dht.readHumidity();

  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  int temp = (int) t * 100;
  int humi = (int) h * 100;

  Serial.print("/home/kitchen,sensor=dht22 h=");
  Serial.print(humi);
  Serial.print(",t=");
  Serial.print(temp);

  Serial.println("");
}
