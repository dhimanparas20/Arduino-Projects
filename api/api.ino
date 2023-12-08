//#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>


#define BLYNK_AUTH_TOKEN ""
#define USE_SERIAL Serial

const char* ssid = "";
const char* pass = "";

void setup() {
  USE_SERIAL.begin(9600);
  
  int numberOfNetworks = WiFi.scanNetworks();
 
  for (int i = 0; i < numberOfNetworks; i++) {
    USE_SERIAL.print("Network name: ");
    USE_SERIAL.println(WiFi.SSID(i));
    USE_SERIAL.print("Signal strength: ");
    USE_SERIAL.println(WiFi.RSSI(i));
    USE_SERIAL.println("-----------------------");
  }

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) { 
    USE_SERIAL.print("."); 
    delay(500);
  } 

  USE_SERIAL.println(""); 
  USE_SERIAL.println("Wi-Fi connected"); 
  USE_SERIAL.print("IP Address: ");
  USE_SERIAL.println(WiFi.localIP()); 
  restoreState();
  
}

void loop() {
  httpGET();
  delay(3000);
}

/*
void httpGet() {
  HTTPClient http;
  WiFiClient client; // Create a WiFiClient object

  //const char* url = "http://blr1.blynk.cloud/external/api/get?token=I1mwrVRgLtqBQ8b5m3GZ9quXlh4J-B0b&V1&V2&V3&V4"; // Updated to const char*
  const char* url = "http://blr1.blynk.cloud/external/api/update?token=I1mwrVRgLtqBQ8b5m3GZ9quXlh4J-B0b&V2=1";

  http.begin(client, url); // Use client argument in begin method
  int resCode = http.GET();

  USE_SERIAL.println(resCode);
  
  String res = http.getString();
  USE_SERIAL.println(res);
  parserMessage(res);

  http.end();
}

void httpsGet() {
  HTTPClient http;
  WiFiClientSecure client; // Use WiFiClientSecure for HTTPS

  const char* url = "https://blr1.blynk.cloud/external/api/get?token=I1mwrVRgLtqBQ8b5m3GZ9quXlh4J-B0b&V1&V2&V3&V4"; // Updated to const char*

  http.begin(client, url); // Use client argument in begin method
  int resCode = http.GET();

  USE_SERIAL.println(resCode);
  
  String res = http.getString();
  USE_SERIAL.println(res);

  parserMessage(res);

  http.end();
}
*/

void httpPOST(const char* pin,int pin_value){
  HTTPClient http;
  WiFiClient client; // Create a WiFiClient object
  String url = "http://blr1.blynk.cloud/external/api/update?token=";
  url += BLYNK_AUTH_TOKEN;
  url += "&";
  url += pin;
  url += "=";
  url += pin_value;
  http.begin(client, url); // Use client argument in begin method
  int resCode = http.GET();
  Serial.println(resCode);
  String res = http.getString();
  Serial.println(res);
  //parserMessage(res);
  http.end();
}

void restoreState(){
  HTTPClient http;
  WiFiClient client; // Create a WiFiClient object
  String url = "http://blr1.blynk.cloud/external/api/get?token=";
  url += BLYNK_AUTH_TOKEN;
  url += "&V1&V2&V3&V4";
  http.begin(client, url); // Use client argument in begin method
  int resCode = http.GET();
  Serial.println(resCode);
  String res = http.getString();
  Serial.println(res);
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, res);

  int valueV1 = doc["V1"];
  int valueV2 = doc["V2"];
  int valueV3 = doc["V3"];
  int valueV4 = doc["V4"];
  valueV1 == 1 ? httpPOST("V1", 1) : httpPOST("V1", 0);
  valueV2 == 1 ? httpPOST("V2", 1) : httpPOST("V2", 0);
  valueV3 == 1 ? httpPOST("V3", 1) : httpPOST("V3", 0);
  valueV4 == 1 ? httpPOST("V4", 1) : httpPOST("V4", 0);
  http.end();
}


void httpGET() {
  HTTPClient http;
  WiFiClient client; // Create a WiFiClient object
  String url = "http://blr1.blynk.cloud/external/api/get?token=";
  url += BLYNK_AUTH_TOKEN;
  url += "&V1&V2&V3&V4";
  http.begin(client, url); // Use client argument in begin method
  int resCode = http.GET();
  Serial.println(resCode);
  String res = http.getString();
  Serial.println(res);
}
