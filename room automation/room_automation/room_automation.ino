#include <IRremote.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLosDiardQ"
#define BLYNK_TEMPLATE_NAME "Room Automation No Sensor Input"
#define BLYNK_AUTH_TOKEN "ffSABDTkcCDoDV6j3rBSA2-xFMqaBSLj"
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "kek";         //Enter your WIFI name
char pass[] = "qwertyuiop";  //Enter your WIFI password


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


// Pin to variable declaration
#define IR_INPUT D0
#define ROOM_LIGHT D1
#define SPEAKER D2
#define FAN D3
#define RED_LED D4


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
  digitalWrite(ROOM_LIGHT, param.asInt());
}
BLYNK_WRITE(V2) {
  digitalWrite(SPEAKER, param.asInt());
}
BLYNK_WRITE(V3) {
  digitalWrite(FAN, param.asInt());
}

void setup() {
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Serial.begin(9600);
  IR.enableIRIn();
  pinMode(IR_INPUT, INPUT);     // IR remote input
  pinMode(ROOM_LIGHT, OUTPUT);  // Room Relay
  pinMode(SPEAKER, OUTPUT);     // Speaker
  pinMode(FAN, OUTPUT);         // FAn
  pinMode(RED_LED, OUTPUT);     // Red LEd

  digitalWrite(ROOM_LIGHT, LOW);  //default on
  digitalWrite(FAN, LOW);         //default fan  on
  /*pinMode(D4, OUTPUT);  
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  */
}

// on/off Modules
void on(int p) {
  digitalWrite(p, HIGH);
}

void off(int p) {
  digitalWrite(p, LOW);
}

// Main code
void loop() {
  Blynk.run();
  //Blynk.virtualWrite(V1, rd);

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

      case c0:  //Press 0 to turn off all appliances
        //Serial.println(" All Lights OFF");
        on(RED_LED);  // Turns on Red LED
        off(ROOM_LIGHT);
        off(SPEAKER);
        off(FAN);
        /*off(D5);
        off(D6);
        off(D7);
        off(D8);*/
    }
    IR.resume();
  }
}