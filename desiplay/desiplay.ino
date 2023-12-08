/* LCD connection Diagram:
* VSS to GND
* VDD to 5V
* V0 to Middle of 10K potentiometer(pm). Left of pm(red) to GND and Right of pm(yellow) to 5V.
* RS to 7
* RW to GND
* E to 6
* D4,D5,D6,D7 to 5,4,3,2 respectively
* A to 3.3V
* K to GND
*/
#include <LiquidCrystal.h>

String h = "Hello Abhishek";
int len = h.length();
int i=0;

#include <LiquidCrystal.h>
const int rs = D0, en = D1, d4 = D2, d5 = D3, d6 = D4, d7 = D5;  // PiN's for LCD Display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
}
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Have a great Day");
  lcd.setCursor(0, 1);
  lcd.print(i);
  delay(500);
  i += 1;
  lcd.clear();
  //lcd.print(millis() / 1000); 

/*
  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  // Turn on the display:
  lcd.display();
  delay(500);
*/  
}

