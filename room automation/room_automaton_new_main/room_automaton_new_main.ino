#include "constants.h"
#include <IRremote.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <Arduino.h>
#include <WiFiClientSecure.h>

#ifdef ESP8266
  #include <BlynkSimpleEsp8266.h>
#endif

//Do Not Touch
char auth[] = BLYNK_AUTH_TOKEN;
IRrecv IR(IR_INPUT);
bool Trigger = false;

//Get the button value for blynk
BLYNK_WRITE(V1) {
  digitalWrite(ROOM_LIGHT, param.asInt());}
BLYNK_WRITE(V2) {
  digitalWrite(SPEAKER, param.asInt());}
BLYNK_WRITE(V3) {
  digitalWrite(FAN, param.asInt());}
BLYNK_WRITE(V4) {
  digitalWrite(LAMP, param.asInt());}

// Structure of Relay Info
struct RelayInfo {
  String deviceId;
  String name;
  int pin;
};

// Declaring The Number of relays for siniric pro
std::vector<RelayInfo> relays = {
    {"64b123092ac6a1822a87bb5f", "Relay 1", ROOM_LIGHT},
    {"6444043e312d40edc3f889be", "Relay 2", SPEAKER},
    {"6444042b918a3c911c8675a5", "Relay 3", FAN}
};

// Function Declaration
void setupWiFi();
void setupRelayPins();
void setupSinricPro();
void on(int);
void off(int);
bool onPowerState(const String &deviceId, bool &state);

//=====================================================================
// Void Setup
//=====================================================================
void setup() {
  IR.enableIRIn();
  pinMode(IR_INPUT, INPUT);     // IR remote input
  pinMode(ROOM_LIGHT, OUTPUT);  // Room Light
  pinMode(SPEAKER, OUTPUT);     // Speaker
  pinMode(FAN, OUTPUT);         // FAn
  pinMode(LAMP, OUTPUT);     // Red LEd
  digitalWrite(ROOM_LIGHT, LOW);
  digitalWrite(FAN, LOW);   
  digitalWrite(LAMP, HIGH);

  setupRelayPins();       
  setupSinricPro();

  Serial.begin(BAUD_RATE);
  setupWiFi();
  if (WiFi.status() == WL_CONNECTED) {
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  digitalWrite(LAMP, LOW);
  }
  else{
  digitalWrite(LAMP, LOW);
  Trigger = true;
  //Serial.println("No wofi Found");}
 }
} 

//=====================================================================
// Void Loop
//=====================================================================
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
  if (Trigger == true){
      Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
      //Serial.println("Trigger Section");
      Trigger = false;
      return;
    }  
  Blynk.run();
  SinricPro.handle();
  if (IR.decode()) {
    handleIR();
   }
  }
  else{
    if (IR.decode()) {
    handleIR();
    }
  }
}

//---------------------------------------------------------------------
// Alll The aBOVE CALLED functiona are here
//---------------------------------------------------------------------

void setupWiFi() {
  Serial.println("\r\n[Wifi]: Connecting...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long startTime = millis();
  const unsigned long timeout = WIFI_TIMEOUT;  // Timeout set to 10 seconds (10,000 milliseconds)

  while (WiFi.status() != WL_CONNECTED) {
    if (IR.decode()) {
    handleIR();
    }
    if (millis() - startTime >= timeout) {
      Serial.println("\r\n[Wifi]: Connection timed out");
      return;  // Exit the function if timeout is reached
    }
    Serial.print(".");
    delay(500);
  }

  //wifiConnected = true;  // Set flag to true if Wi-Fi connection is established
  Serial.printf("\r\n[Wifi]: Connected\r\n[Wifi]: SSID --> %s\r\n[Wifi]: IP-Address --> %s\r\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
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

bool onPowerState(const String &deviceId, bool &state) {
  for (auto &relay : relays) {                                                            // for each relay configuration
    if (deviceId == relay.deviceId) {                                                       // check if deviceId matches
      //Serial.printf("Device %s turned %s\r\n", relay.name.c_str(), state ? "on" : "off");     // print relay name and state to serial
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

void handleIR(){
  //Serial.println(IR.decodedIRData.decodedRawData, DEC);  //Shows the read value on the monitor screen(if exisits).
    switch (IR.decodedIRData.decodedRawData) {
      case C1:
        on(ROOM_LIGHT);
        break;

      case C4:
        off(ROOM_LIGHT);
        break;

      case C2:
        on(SPEAKER);
        break;

      case C5: 
        off(SPEAKER);
        break;

      case C3:
        on(FAN);
        break;

      case C6:
        off(FAN);
        break;

      case CST:
        on(LAMP);
        break;

      case CHASH:
        off(LAMP);
        break;  

      case C0:  //Press 0 to turn off all appliances
        off(ROOM_LIGHT);
        off(SPEAKER);
        off(FAN);
        off(LAMP);
    }
    IR.resume();
   }

// on/off Modules
void on(int p) {
  digitalWrite(p, HIGH);}
void off(int p) {
  digitalWrite(p, LOW);}
