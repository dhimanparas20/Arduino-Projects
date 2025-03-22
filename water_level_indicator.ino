#include <TM1637Display.h> // Include the TM1637 library
#include <ESP8266WiFi.h>   // Include the ESP8266 Wi-Fi library
#include <PubSubClient.h>  // Include the PubSubClient library for MQTT

// Define pins for the ultrasonic sensor
const int trigPin = D1;  // Trig pin of ultrasonic sensor (GPIO5)
const int echoPin = D2;  // Echo pin of ultrasonic sensor (GPIO4)

// Define pins for the TM1637 display
const int CLK = D5;      // Clock pin of TM1637 (GPIO14)
const int DIO = D6;      // Data pin of TM1637 (GPIO12)

// Define the threshold distance (in cm)
const int thresholdDistance = 10; // Adjust this value based on your tank's dimensions

// Create an instance of the TM1637Display class
TM1637Display display(CLK, DIO);

// Define the buzzer pin
const int buzzerPin = D3;   // Buzzer pin (GPIO0)

// Define the built-in LED pin
const int ledPin = LED_BUILTIN; // Built-in NodeMCU LED pin (usually GPIO2 or GPIO0)

// Variable to track the delay duration
int currentDelay = 2000; // Start with 2000 ms delay

// Wi-Fi credentials
const char* ssid = "";
const char* password = "";

// MQTT server configuration
#define MQTT_SERVER "mqtt.mstservices.tech"
#define MQTT_USER ""
#define MQTT_PASSWORD ""
#define MQTT_PORT 1883
#define WS_DEVICE_CLIENTID "/nodemcuwatertank"

// MQTT topic
const char* topic = "watertank";

// Create Wi-Fi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

// Variable to store the previous distance value
int previousDistance = -1; // Initialize with an invalid value

// Function prototypes
void connectToWiFi();
void connectToMQTT();
long measureDistance();
void blinkLED(int frequency);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set pin modes for ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set pin mode for the buzzer
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH); // Turn off the buzzer initially

  // Set pin mode for the built-in LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // Turn off the LED initially

  // Initialize the TM1637 display
  display.setBrightness(1); // Set brightness (0-7, 7 is max)

  // Connect to Wi-Fi
  connectToWiFi();

  // Configure MQTT client
  client.setServer(MQTT_SERVER, MQTT_PORT);

  // Connect to MQTT broker
  connectToMQTT();
}

void loop() {
  // Ensure the MQTT client stays connected
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

  // Measure the distance
  long duration = measureDistance();
  int distance = duration * 0.034 / 2; // Convert duration to distance in cm

  // Only proceed if the distance has changed
  if (distance != previousDistance) {
    // Update the previous distance
    previousDistance = distance;

    // Print the distance to the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Display the distance on the TM1637 4-segment display
    if (distance < 0 || distance > 6969) {
      // If the distance is out of range, display "----"
      display.showNumberDec(6969, false);
    } else {
      // Display the distance normally
      display.showNumberDec(distance, false);
    }

    // Publish the water level to the MQTT topic
    char message[10];
    snprintf(message, sizeof(message), "%d", distance);
    client.publish(topic, message, true); // Retain the message with QoS 1
  }

  // Check if the distance is below the threshold
  if (distance <= thresholdDistance) {
    // Make the buzzer beep
    for (int i = 0; i < 3; i++) { // Beep 3 times
      digitalWrite(buzzerPin, LOW); // Turn on the buzzer
      delay(150);                   // Buzzer on for 150ms
      digitalWrite(buzzerPin, HIGH); // Turn off the buzzer
      delay(150);                   // Buzzer off for 150ms
    }
    // Reduce the delay to 500 ms while the buzzer is active
    currentDelay = 50;
  } else {
    // Ensure the buzzer is off
    digitalWrite(buzzerPin, HIGH);
    // Restore the delay to 2000 ms when the distance is above the threshold
    currentDelay = 1500;
  }

  // Wait for the current delay duration before the next measurement
  delay(currentDelay);
}

// Function to measure distance using the ultrasonic sensor
long measureDistance() {
  // Send a 10-microsecond pulse to the Trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the Echo pin and calculate the duration
  return pulseIn(echoPin, HIGH);
}

// Function to connect to Wi-Fi
void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  WiFi.setSleepMode(WIFI_LIGHT_SLEEP);

  while (WiFi.status() != WL_CONNECTED) {
    blinkLED(500); // Blink LED every 500ms while connecting to Wi-Fi
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(ledPin, HIGH); // Turn off the LED after connection
}

// Function to connect to the MQTT broker
void connectToMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    // Blink LED every 200ms while connecting to MQTT
    blinkLED(200);

    // Set Last Will and Testament (LWT) during the connect call
    if (client.connect(WS_DEVICE_CLIENTID, MQTT_USER, MQTT_PASSWORD, topic, 1, true, "0")) {
      Serial.println("connected!");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
  digitalWrite(ledPin, HIGH); // Turn off the LED after connection
}

// Function to blink the LED at a specified frequency
void blinkLED(int frequency) {
  digitalWrite(ledPin, LOW); // Turn on the LED
  delay(frequency / 2);      // Wait for half the frequency duration
  digitalWrite(ledPin, HIGH); // Turn off the LED
  delay(frequency / 2);      // Wait for the other half
}
