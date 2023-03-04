//Include the library files
//#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPL8izfDkJk"
#define BLYNK_TEMPLATE_NAME "Room Control"
#define BLYNK_AUTH_TOKEN "zfBdXLRsHuZ-YRclb6GDdz7hXd2DLy4H"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "kek";//Enter your WIFI name
char pass[] = "asdfghjkl";//Enter your WIFI password

//Get the button value
BLYNK_WRITE(V0) {
  digitalWrite(D0, param.asInt());
  
}
/*
BLYNK_READ(V0) {
  digitalRead(D0);
}
*/


void setup() {
  //Set the LED pin as an output pin
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  //pinMode(D1, OUTPUT);
  
  //Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  //Run the Blynk library
  Blynk.run();   
}