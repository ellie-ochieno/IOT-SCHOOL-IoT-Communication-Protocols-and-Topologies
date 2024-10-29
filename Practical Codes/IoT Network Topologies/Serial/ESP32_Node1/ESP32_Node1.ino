#include <DHT.h>

#define DHTPIN 7       // DHT22 data pin
#define DHTTYPE DHT22  // DHT22 type
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);    // Serial for debugging
  Serial1.begin(9600);     // Serial1 for communication to second ESP32
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    String data = String(temperature) + "," + String(humidity);
    Serial.println("Sending data: " + data);  // Debugging
    Serial1.println(data);                    // Send data to Module 2
  } else {
    Serial.println("Failed to read from DHT sensor");
  }
  delay(10000);  // Send data every 10 seconds
}
