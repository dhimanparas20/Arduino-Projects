#ifndef CONFIG_H
#define CONFIG_H

// Wi-Fi credentials
const char* ssid = "";
const char* password = "";

// MQTT server configuration
#define MQTT_SERVER ""
#define MQTT_USER ""
#define MQTT_PASSWORD ""
#define MQTT_PORT 1883
#define WS_DEVICE_CLIENTID "/nodemcuwatertank"

// MQTT topics
const char* publishTopic = "watertank";
const char* subscribeTopicThreshold = "watertank/val";
const char* subscribeTopicDisplay = "watertank/display";

// Default threshold distance (in cm)
const int defaultThresholdDistance = 10;

// Display control flag (default state)
const bool defaultDisplayEnabled = true;

#endif // CONFIG_H
