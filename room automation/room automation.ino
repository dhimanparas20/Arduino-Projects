#include <IRremote.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

/*
#define BLYNK_TEMPLATE_ID "TMPLTzxHlKNo"
#define BLYNK_TEMPLATE_NAME "Room Control"
#define BLYNK_AUTH_TOKEN "v-E2EQkF96PsHSDX4DlStKOgiVsdbkpb"
*/
#define BLYNK_TEMPLATE_ID "TMPLTzxHlKNo"
#define BLYNK_TEMPLATE_NAME "Room Control"
#define BLYNK_AUTH_TOKEN "vUo-0e3XLRVHTLJmLU_qL4ELYCjI5dhL"

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
#define PIR D1  //Pin for PIR sensor Digitail Input

// Define the input for the IR-receiver module
IRrecv IR(D0);

//Get the button value for blynk
/*BLYNK_READ(V0) {
  digitalWrite(D0, param.asInt());
}
BLYNK_READ(V1) {
  digitalWrite(D1, param.asInt());
}
*/
BLYNK_WRITE(V2) {
  digitalWrite(D2, param.asInt());
}
BLYNK_WRITE(V3) {
  digitalWrite(D3, param.asInt());
}


void setup() {
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Serial.begin(9600);
  digitalWrite(D3, LOW);
  IR.enableIRIn();
  pinMode(D0, INPUT);   // IR remote input
  pinMode(D1, INPUT);   // PIR input
  pinMode(D2, OUTPUT);  // Room Relay
  pinMode(D3, OUTPUT);  // Bathroom Relay
  pinMode(D4, OUTPUT);  // Red LEd
  /*pinMode(D5, OUTPUT);
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
  int rd = digitalRead(PIR);  // Reads ir value and stores in var rd
  Blynk.virtualWrite(V1, rd); 
  //Serial.println(rd);

  while (rd == HIGH) {
    //Serial.println(" BathRoom Light ON");
    Blynk.virtualWrite(V1, rd); 
    on(D3);
    off(D4);
    rd = digitalRead(PIR);
    if (rd == LOW) {
      Blynk.virtualWrite(V1, rd); 
      off(D3);
      on(D4);
    }
  }

  if (IR.decode()) {
    //Serial.println(IR.decodedIRData.decodedRawData, DEC);  //Shows the read value on the monitor screen(if exisits).
    switch (IR.decodedIRData.decodedRawData) {
      case c1:  //press 1 to turn on 1st switch.
       // Serial.println(" Room Light ON");
        on(D2);   // Turns on Relay
        off(D4);  // Turns off Red LED
        break;

      case c4:  //press 4 to turn off 1st switch.
        //Serial.println(" Room Light OFF");
        off(D2);  // Turns of Relay
        on(D4);   // Turns on Red LED
        break;

      case c2:  //press 2 to turn on 2nd switch.
        //Serial.println(" BathRoom Light ON");
        on(D3);
        off(D4);
        break;

      case c5:  //press 5 to turn off 2nd switch.
        //Serial.println(" BathRoom Light OFF");
        off(D3);
        on(D4);
        break;

      case c0:  //Press 0 to turn off all appliances
        //off(D1);
        //Serial.println(" All Lights OFF");
        on(D4);  // Turns on Red LED
        off(D2);
        off(D3);
        off(D4);
        /*off(D5);
        off(D6);
        off(D7);
        off(D8);*/
    }
    IR.resume();
  }
}
