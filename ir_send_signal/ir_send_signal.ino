#include <IRremote.h>
IRsend irsend;

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  //Power//
  irsend.sendNEC(0x4027576064, D6); //Power Code
  Serial.println("Power");
  delay(1000);
}
