#include "DHT.h"
#define DHTPIN D2       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 22 (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0; // Stores the last time the temperature was checked
const unsigned long interval = 5000; // 5 seconds for testing, replace with 3600000 for 1 hour

void readDHTSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();        // Read temperature as Celsius
  float f = dht.readTemperature(true);    // Read temperature as Fahrenheit

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);         // Heat index in Fahrenheit
  float hic = dht.computeHeatIndex(t, h, false);  // Heat index in Celsius

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

void setup() {
  Serial.begin(9600);  // Start Serial communication FIRST!
  
  Serial.print(F("DHTxx Hourly Reading Test!"));
  dht.begin();

  // Read values immediately when the board starts
  delay(1500);
  Serial.println(F("Initial Reading:"));
  
  readDHTSensor();

  // Reset previousMillis to current time to start the interval tracking fresh
  previousMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  if (currentMillis - previousMillis >= interval) {
    Serial.println(F("Hourly Reading:"));
    previousMillis = currentMillis; // Update the previous time
    readDHTSensor(); // Call the function to read DHT11 sensor data
  }

  // Your other project code can be placed here
}
