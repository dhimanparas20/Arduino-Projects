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
int i;

#include <LiquidCrystal.h>
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
}
void loop() {
  lcd.setCursor(1, 0);
  for (i=0;i<=len-1;i++){
    lcd.print(h[i]);
    delay(100);
  }
  lcd.setCursor(0, 1);
  lcd.print("Have a great Day");
  delay(3000);
  lcd.clear();
  delay(400);
  //lcd.print(millis() / 1000); 

  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  // Turn on the display:
  lcd.display();
  delay(500);
}

