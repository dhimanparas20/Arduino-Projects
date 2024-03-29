#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "kek"
#define STAPSK  "qwertyuiop"
#endif

//#define BLYNK_TEMPLATE_ID "TMPLosDiardQ"
//#define BLYNK_TEMPLATE_NAME "Room Automation No Sensor Input"
//#define BLYNK_AUTH_TOKEN "ffSABDTkcCDoDV6j3rBSA2-xFMqaBSLj"
//char auth[] = BLYNK_AUTH_TOKEN;
//char ssid[] = "kek";         //Enter your WIFI name
//char pass[] = "qwertyuiop";  //Enter your WIFI password

const char* ssid = STASSID;
const char* password = STAPSK;



void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  pinMode(D1, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  digitalWrite(D1,HIGH);
  delay(500);
  digitalWrite(D1,LOW);
  delay(500);
}
