#ifndef CONFIG_H
#define CONFIG_H

// Wi-Fi credentials
const char* ssid = "MST Protocol";
const char* password = "Blackkaiser69";

// MQTT server configuration
#define MQTT_SERVER "mqtt.mstservices.tech"
#define MQTT_USER "mst"
#define MQTT_PASSWORD "1212"
#define MQTT_PORT 1883
#define WS_DEVICE_CLIENTID "9POWuKe/nodemcuwatertank"

// MQTT topics
const char* publishTopic = "watertank/percentage";
const char* subscribeTopicMinDist = "watertank/mindist";
const char* subscribeTopicMaxDist = "watertank/maxdist";
const char* subscribeTopicDisplay = "watertank/display";
const char* subscribeTopicBuzzer = "watertank/buzzer";

// Default threshold distance (in cm)
const int defaultThresholdDistance = 10;

// Variable to track the delay duration
int currentDelay = 5000; // Start with 5000 ms delay

// Display control flag (default state)
const bool defaultDisplayEnabled = true;
// Buzzer control flag (default state)
const bool defaultBuzzerSound = true;

#endif // CONFIG_H
