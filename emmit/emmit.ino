#include <IRremote.h>
IRsend irsend;

void setup() {
  Serial.begin(9600);
  // pinMode(D3, OUTPUT);  // IR remote input

}

void loop() {
  irsend.sendNEC(0xFF02FD, 32); //Power Code

  Serial.println("Power");
  delay(1000);
}


// #include <Arduino.h>
// #include <IRremoteESP8266.h>
// #include <IRsend.h>

// const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

// IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.


// void setup() {
//   irsend.begin();
//   Serial.begin(9600);

// }

// void loop() {
//   Serial.println("Send");
//   // irsend.sendSony(0xa8305E8, 24, 1);  // 12 bits & 2 repeats
//   irsend.sendNEC(0xFF02FD, 32); //Power Code
//   delay(1500);
//   // 3810328320
// }
