/*
README: Water Tank Monitoring System with Wi-Fi and MQTT Integration

This code is designed for a water tank monitoring system using an ultrasonic sensor, 
a TM1637 4-segment display, a buzzer, and an ESP8266 NodeMCU. The system measures 
the water level in a tank and provides alerts when the level is below a threshold. 
It also integrates with MQTT for remote monitoring and control.

---

**How the Code Works:**
1. The ultrasonic sensor measures the distance to the water surface.
2. The distance is displayed on a TM1637 4-segment display (if enabled via MQTT).
3. If the distance is below a threshold, the buzzer beeps to alert the user.
4. The system connects to Wi-Fi and publishes the water level to an MQTT topic.
5. The threshold distance can be updated dynamically via an MQTT topic (`watertank/val`).
6. The display can be toggled on/off via another MQTT topic (`watertank/display`).
7. If Wi-Fi is not available within 60 seconds of booting, the system enters offline mode 
   and continues to function locally without MQTT.

---

**Hardware Connections:**
1. **Ultrasonic Sensor (HC-SR04):**
   - Trig Pin: Connect to D1 (GPIO5)
   - Echo Pin: Connect to D2 (GPIO4)
   - VCC: Connect to 5V
   - GND: Connect to GND

2. **TM1637 4-Segment Display:**
   - CLK Pin: Connect to D5 (GPIO14)
   - DIO Pin: Connect to D6 (GPIO12)
   - VCC: Connect to 3.3V
   - GND: Connect to GND

3. **Buzzer:**
   - Positive Pin: Connect to D3 (GPIO0)
   - Negative Pin: Connect to GND

4. **Built-in LED:**
   - Used for status indication (Wi-Fi and MQTT connection).

---

**Wi-Fi and MQTT Configuration:**
- Update the following variables with your Wi-Fi and MQTT credentials:
  - `ssid`: Your Wi-Fi SSID
  - `password`: Your Wi-Fi password
  - `MQTT_SERVER`: Your MQTT broker address
  - `MQTT_USER`: Your MQTT username (leave empty if not required)
  - `MQTT_PASSWORD`: Your MQTT password (leave empty if not required)
  - `MQTT_PORT`: Your MQTT broker port (default is 1883)

---

**Variables:**
- `thresholdDistance`: Default threshold distance (in cm). Can be updated via MQTT.
- `publishTopic`: MQTT topic to publish water level (`watertank`).
- `subscribeTopicThreshold`: MQTT topic to subscribe for threshold updates (`watertank/val`).
- `subscribeTopicDisplay`: MQTT topic to subscribe for display control (`watertank/display`).
- `offlineMode`: Flag to indicate if the system is running in offline mode.
- `displayEnabled`: Flag to control whether the TM1637 display shows values (default is `1`).

---

**Features:**
1. **Wi-Fi Connection:**
   - Attempts to connect to Wi-Fi for 60 seconds. If unsuccessful, enters offline mode.

2. **MQTT Integration:**
   - Publishes water level to `watertank`.
   - Subscribes to `watertank/val` to dynamically update the threshold distance.
   - Subscribes to `watertank/display` to toggle the TM1637 display on/off.

3. **Offline Mode:**
   - If Wi-Fi is unavailable, the system continues to function locally.

4. **Buzzer Alert:**
   - Beeps when the water level is below the threshold.

5. **TM1637 Display:**
   - Displays the measured distance in cm (if enabled via MQTT).
   - Shows patterns during Wi-Fi and MQTT connection attempts.

---

**Usage:**
1. Connect the hardware as described above.
2. Update the Wi-Fi and MQTT credentials in the code.
3. Upload the code to the ESP8266 NodeMCU using the Arduino IDE.
4. Monitor the Serial Monitor for debug messages.
5. Use an MQTT client to publish a new threshold value to `watertank/val` or toggle the display via `watertank/display`.

---

**Dependencies:**
- TM1637Display Library
- ESP8266WiFi Library
- PubSubClient Library

---

**Author:**
- Paras Dhiman
- Date: 22/03/2025
*/

#include <TM1637Display.h> // Include the TM1637 library
#include <ESP8266WiFi.h>   // Include the ESP8266 Wi-Fi library
#include <PubSubClient.h>  // Include the PubSubClient library for MQTT

// Define pins for the ultrasonic sensor
const int trigPin = D1;  // Trig pin of ultrasonic sensor (GPIO5)
const int echoPin = D2;  // Echo pin of ultrasonic sensor (GPIO4)

// Define pins for the TM1637 display
const int CLK = D5;      // Clock pin of TM1637 (GPIO14)
const int DIO = D6;      // Data pin of TM1637 (GPIO12)

// Define the default threshold distance (in cm)
int thresholdDistance = 10; // Default value, can be updated via MQTT

// Create an instance of the TM1637Display class
TM1637Display display(CLK, DIO);

// Define the buzzer pin
const int buzzerPin = D3;   // Buzzer pin (GPIO0)

// Define the built-in LED pin
const int ledPin = LED_BUILTIN; // Built-in NodeMCU LED pin (usually GPIO2 or GPIO0)

// Variable to track the delay duration
int currentDelay = 1500; // Start with 2000 ms delay

// Wi-Fi credentials
const char* ssid = "";
const char* password = "";

// MQTT server configuration
#define MQTT_SERVER "mqtt.mstservices.tech"
#define MQTT_USER ""
#define MQTT_PASSWORD ""
#define MQTT_PORT 1883
#define WS_DEVICE_CLIENTID "/nodemcuwatertank"

// MQTT topics
const char* publishTopic = "watertank";
const char* subscribeTopicThreshold = "watertank/val";
const char* subscribeTopicDisplay = "watertank/display";

// Create Wi-Fi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

// Variable to store the previous distance value
int previousDistance = -1; // Initialize with an invalid value

// Offline mode flag
bool offlineMode = false; // Start in online mode by default

// Display control flag
bool displayEnabled = true; // Default to showing values on the display

// Function prototypes
void connectToWiFi();
void connectToMQTT();
long measureDistance();
void blinkLED(int frequency);
void mqttCallback(char* topic, byte* payload, unsigned int length);
void showConnectingPattern();

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
  displayEnabled = true;    // Default to showing values on the display

  // Attempt to connect to Wi-Fi
  connectToWiFi();

  // If not in offline mode, configure MQTT client
  if (!offlineMode) {
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(mqttCallback); // Set the callback function for incoming messages

    // Connect to MQTT broker
    connectToMQTT();
  }
}

void loop() {
  // If not in offline mode, ensure the MQTT client stays connected
  if (!offlineMode && !client.connected()) {
    connectToMQTT();
  }
  if (!offlineMode) {
    client.loop();
  }

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

    // Display the distance on the TM1637 4-segment display (if enabled)
    if (displayEnabled) {
      if (distance < 0 || distance > 6969) {
        // If the distance is out of range, display "----"
        display.showNumberDec(6969, false);
      } else {
        // Display the distance normally
        display.showNumberDec(distance, false);
      }
    } else {
      // Turn off the display
      display.clear();
    }

    // If not in offline mode, publish the water level to the MQTT topic
    if (!offlineMode) {
      char message[10];
      snprintf(message, sizeof(message), "%d", distance);
      client.publish(publishTopic, message, true); // Retain the message with QoS 1
    }
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
    currentDelay = 250;
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

  unsigned long startTime = millis(); // Record the start time
  while (WiFi.status() != WL_CONNECTED) {
    blinkLED(500); // Blink LED every 500ms while connecting to Wi-Fi
    showConnectingPattern(); // Show connecting pattern on the display
    Serial.print(".");

    // Check if 60 seconds have passed
    if (millis() - startTime > 60000) {
      Serial.println("\nFailed to connect to Wi-Fi within 60 seconds. Entering offline mode.");
      offlineMode = true; // Enable offline mode
      display.clear();    // Clear the display
      return;             // Exit the function
    }
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
    showConnectingPattern(); // Show connecting pattern on the display

    // Set Last Will and Testament (LWT) during the connect call
    if (client.connect(WS_DEVICE_CLIENTID, MQTT_USER, MQTT_PASSWORD, publishTopic, 1, true, "0")) {
      Serial.println("connected!");
      client.subscribe(subscribeTopicThreshold); // Subscribe to the topic to receive threshold updates
      client.subscribe(subscribeTopicDisplay);   // Subscribe to the topic to control the display
      Serial.print("Subscribed to topics: ");
      Serial.println(subscribeTopicThreshold);
      Serial.println(subscribeTopicDisplay);
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

// Function to show connecting pattern on the TM1637 display
void showConnectingPattern() {
  static int patternIndex = 0;
  int patterns[] = {0b00000000, 0b01010101, 0b10101010, 0b11111111}; // Example patterns
  display.setSegments((uint8_t*)&patterns[patternIndex], 4, 0);
  patternIndex = (patternIndex + 1) % 4; // Cycle through patterns
}

// Callback function to handle incoming MQTT messages
// Callback function to handle incoming MQTT messages
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);

  // Convert the payload to a null-terminated string
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0'; // Null-terminate the string

  // Display the received message temporarily on the TM1637 display
  int displayValue = atoi(message); // Convert the message to an integer
  if (displayValue >= 0 && displayValue <= 9999) {
    display.showNumberDec(displayValue, false); // Show the value on the display
    delay(1000); // Keep the value displayed for 2 seconds
  } else {
    // If the value is invalid, show "----" temporarily
    display.showNumberDecEx(0, 0b01000000, false); // Show "----"
    delay(1000);
  }

  // Handle threshold updates
  if (String(topic) == subscribeTopicThreshold) {
    int newThreshold = atoi(message); // Convert the message to an integer
    if (newThreshold > 0) { // Ensure the new threshold is valid
      thresholdDistance = newThreshold;
      Serial.print("Updated thresholdDistance to: ");
      Serial.println(thresholdDistance);
    } else {
      Serial.println("Invalid threshold value received.");
    }
  }

  // Handle display control
  if (String(topic) == subscribeTopicDisplay) {
    int newDisplayState = atoi(message); // Convert the message to an integer
    if (newDisplayState == 1) {
      displayEnabled = true;
      Serial.println("Display enabled.");
    } else if (newDisplayState == 0) {
      displayEnabled = false;
      display.clear(); // Turn off the display
      Serial.println("Display disabled.");
    } else {
      Serial.println("Invalid display state received.");
    }
  }
}
