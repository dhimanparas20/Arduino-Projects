#include <IRremote.h>
#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

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

#ifdef ESP8266
//#define RELAYPIN_1 D1
//#define RELAYPIN_2 D2
//#define RELAYPIN_3 D3
#define IR_INPUT D0
#define LIGHT D1
#define FAN D2
#endif

#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPL3AbDGV6If"
#define BLYNK_TEMPLATE_NAME "Cabin"
#define BLYNK_AUTH_TOKEN "CN6QSsEG3ZOzeqMc1tEvt-CHGgy826yB"
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "CSE_1";         //Enter your WIFI name
char pass[] = "";  //Enter your WIFI password
//char ssid[] = "9816999530";         //Enter your WIFI name
//char pass[] = "server@123";  //Enter your WIFI password

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
/*BLYNK_READ(V0) {
  digitalWrite(D0, param.asInt());
}
BLYNK_READ(V1) {
  digitalWrite(D1, param.asInt());
}
*/
BLYNK_WRITE(V1) {
  digitalWrite(LIGHT, param.asInt());
}
BLYNK_WRITE(V2) {
  digitalWrite(FAN, param.asInt());
}


/*****************
 * Configuration *
 *****************/

struct RelayInfo {
  String deviceId;
  String name;
  int pin;
};

std::vector<RelayInfo> relays = {
    {"64524d4f743f9120700f25c6", "Relay 1", LIGHT},
    {"64525191743f9120700f2927", "Relay 2", FAN},
};

#define WIFI_SSID  "CSE_1"
#define WIFI_PASS  ""
//#define WIFI_SSID  "9816999530"
//#define WIFI_PASS  "server@123"
#define APP_KEY    "a13aedbc-0efa-4910-aefa-e53845c2daf7"    // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET "4a491d3a-e4ae-43c0-b33e-6d235396afd1-f1dc6601-3008-4146-913c-cc246cd1b419" // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

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
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Serial.begin(BAUD_RATE);
  setupRelayPins();
  setupWiFi();
  setupSinricPro();

  IR.enableIRIn();
  pinMode(IR_INPUT, INPUT);     // IR remote input
  pinMode(LIGHT, OUTPUT);  // Room Relay
  pinMode(FAN, OUTPUT);         // FAn

  digitalWrite(LIGHT, LOW);  //default on
  digitalWrite(FAN, LOW); 
}

// on/off Modules
void on(int p) {
  digitalWrite(p, HIGH);
}

void off(int p) {
  digitalWrite(p, LOW);
}

void loop() {
  SinricPro.handle();
  Blynk.run();
  if (IR.decode()) {
    Serial.println(IR.decodedIRData.decodedRawData, DEC);  //Shows the read value on the monitor screen(if exisits).
    switch (IR.decodedIRData.decodedRawData) {
      case c1:           //press 1 to turn on 1st switch.
                         // Serial.println(" Room Light ON");
        on(LIGHT);  // Turns on Relay
        break;

      case c4:  //press 4 to turn off 1st switch.
        //Serial.println(" Room Light OFF");
        off(LIGHT);  // Turns of Relay
        break;

      case c2:  //press 2 to turn on 2nd switch.
        //Serial.println(" BathRoom Light ON");
        on(FAN);
        break;

      case c5:  //press 5 to turn off 2nd switch.
        //Serial.println(" BathRoom Light OFF");
        off(FAN);
        break;

      case c0:  //Press 0 to turn off all appliances
        //Serial.println(" All Lights OFF");
        off(LIGHT);
        off(FAN);
        /*off(D5);
        off(D6);
        off(D7);
        off(D8);*/
    }
    IR.resume();
  }
}
