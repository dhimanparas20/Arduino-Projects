#include <IRremote.h>
#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// Change Your Variables Here
char ssid[] = "192.168.1.42";
char pass[] = "Luffy@1414";
char appkey[] = "065cd449-3fed-4437-b355-9705596b1c40";
char appsec[] = "e43cc52f-59e0-4679-889b-d7609ddcb667-e7893776-fad8-445b-9459-11f69755aad3";

#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#include <Arduino.h>
#ifdef ESP8266 
       #include <ESP8266WiFi.h>
#endif 
#ifdef ESP32   
       #include <WiFi.h>
#endif

// Pin Layout for esp8266
#ifdef ESP8266
#define IR_INPUT D0
#define ROOM_LIGHT D1
#define SPEAKER D2
#define FAN D3
#define LAMP D4
#define RED_LED D5
#endif

#include <BlynkSimpleEsp8266.h>

// Place Blynk Variables Here
#define BLYNK_TEMPLATE_ID "TMPLosDiardQ"
#define BLYNK_TEMPLATE_NAME "Room Automation No Sensor Input"
#define BLYNK_AUTH_TOKEN "ffSABDTkcCDoDV6j3rBSA2-xFMqaBSLj"

//Do Not Touch
char auth[] = BLYNK_AUTH_TOKEN;

// Defining values to the signals received form the remote button.
#define c1 3125149440
#define c2 3108437760
#define c3 3091726080
#define c4 3141861120
#define c5 3208707840
#define c6 3158572800
#define c7 4161273600
#define c8 3927310080
#define c9 4127850240
#define c0 3860463360
#define cst 3910598400
#define chash 4061003520
#define cup 3877175040
#define cdown 2907897600
#define cleft 4144561920
#define cright 2774204160
#define cok 3810328320

// Define the input for the IR-receiver module
IRrecv IR(IR_INPUT);

//Get the button value for blynk
BLYNK_WRITE(V1) {
  digitalWrite(ROOM_LIGHT, param.asInt());}
BLYNK_WRITE(V2) {
  digitalWrite(SPEAKER, param.asInt());}
BLYNK_WRITE(V3) {
  digitalWrite(FAN, param.asInt());}
BLYNK_WRITE(V4) {
  digitalWrite(LAMP, param.asInt());}

/*****************
 * Configuration *
 *****************/
struct RelayInfo {
  String deviceId;
  String name;
  int pin;
};

// Declaring The Number of relays 
std::vector<RelayInfo> relays = {
    {"6443b1df918a3c911c862a54", "Relay 1", ROOM_LIGHT},
    {"6444043e312d40edc3f889be", "Relay 2", SPEAKER},
    {"6444042b918a3c911c8675a5", "Relay 3", FAN}
};

#define WIFI_SSID  ssid
#define WIFI_PASS  pass
#define APP_KEY    appkey
#define APP_SECRET appsec
#define BAUD_RATE  9600              // Change baudrate to your need

bool onPowerState(const String &deviceId, bool &state) {
  for (auto &relay : relays) {                                                            // for each relay configuration
    if (deviceId == relay.deviceId) {                                                       // check if deviceId matches
      Serial.printf("Device %s turned %s\r\n", relay.name.c_str(), state ? "on" : "off");     // print relay name and state to serial
      digitalWrite(relay.pin, state);                                                         // set state to digital pin / gpio
      return true;                                                                            // return with success true
    }
  }
  return false; // if no relay configuration was found, return false
}

void setupRelayPins() {
  for (auto &relay : relays) {    // for each relay configuration
    pinMode(relay.pin, OUTPUT);     // set pinMode to OUTPUT
  }
}

void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}

void setupSinricPro() {
  for (auto &relay : relays) {                             // for each relay configuration
    SinricProSwitch &mySwitch = SinricPro[relay.deviceId];   // create a new device with deviceId from relay configuration
    mySwitch.onPowerState(onPowerState);                     // attach onPowerState callback to the new device
  }

  SinricPro.onConnected([]() { Serial.printf("Connected to SinricPro\r\n"); });
  SinricPro.onDisconnected([]() { Serial.printf("Disconnected from SinricPro\r\n"); });

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  IR.enableIRIn();
  pinMode(IR_INPUT, INPUT);     // IR remote input
  pinMode(ROOM_LIGHT, OUTPUT);  // Room Relay
  pinMode(SPEAKER, OUTPUT);     // Speaker
  pinMode(FAN, OUTPUT);         // FAn
  pinMode(RED_LED, OUTPUT);     // Red LEd
  pinMode(LAMP, OUTPUT);     // Red LEd

  digitalWrite(ROOM_LIGHT, LOW);  //default on
  digitalWrite(FAN, LOW);         //default fan  on
  digitalWrite(LAMP, HIGH);         //default fan  on 

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Serial.begin(BAUD_RATE);
  setupRelayPins();
  setupWiFi();
  setupSinricPro();
  digitalWrite(LAMP, LOW);         //Turn the lamp off only after wifi gets connected
}

// on/off Modules
void on(int p) {
  digitalWrite(p, HIGH);}
void off(int p) {
  digitalWrite(p, LOW);}

void loop() {
  SinricPro.handle();
  Blynk.run();
  if (IR.decode()) {
    //Serial.println(IR.decodedIRData.decodedRawData, DEC);  //Shows the read value on the monitor screen(if exisits).
    switch (IR.decodedIRData.decodedRawData) {
      case c1:           //press 1 to turn on 1st switch.
                         // Serial.println(" Room Light ON");
        on(ROOM_LIGHT);  // Turns on Relay
        off(RED_LED);    // Turns off Red LED
        break;

      case c4:  //press 4 to turn off 1st switch.
        //Serial.println(" Room Light OFF");
        off(ROOM_LIGHT);  // Turns of Relay
        on(RED_LED);      // Turns on Red LED
        break;

      case c2:  //press 2 to turn on 2nd switch.
        //Serial.println(" BathRoom Light ON");
        on(SPEAKER);
        off(RED_LED);
        break;

      case c5:  //press 5 to turn off 2nd switch.
        //Serial.println(" BathRoom Light OFF");
        off(SPEAKER);
        on(RED_LED);
        break;

      case c3:
        on(FAN);
        off(RED_LED);
        break;

      case c6:
        off(FAN);
        on(RED_LED);
        break;

      case cst:
        on(LAMP);
        off(RED_LED);
        break;

      case chash:
        off(LAMP);
        on(RED_LED);
        break;  

      case c0:  //Press 0 to turn off all appliances
        //Serial.println(" All Lights OFF");
        on(RED_LED);  // Turns on Red LED
        off(ROOM_LIGHT);
        off(SPEAKER);
        off(FAN);
        off(LAMP);
        /*off(D5);
        off(D6);
        off(D7);
        off(D8);*/
    }
    IR.resume();
  }
}
