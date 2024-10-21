//Tested on Node mcu, not working on wemos d1 r1
#include <Wire.h>               // Include Wire Library for I2C
#include <LiquidCrystal_I2C.h>   // Include LiquidCrystal_I2C library

// Set the LCD address to 0x27 for a 16 chars and 2-line display
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  // Start the I2C communication explicitly
  Wire.begin(D2, D1);    // SDA = D2 (GPIO 4), SCL = D1 (GPIO 5)

  lcd.init();        // Initialize the LCD
  lcd.clear();       // Clear the LCD screen
  lcd.backlight();   // Turn on the backlight

  // Print "Hello World" on the first line, starting from column 2
  lcd.setCursor(2, 0);    
  lcd.print("Hello World");

  // Print "JehanKandy" on the second line, starting from column 2
  lcd.setCursor(2, 1);    
  lcd.print("Dandi Bro");
}

void loop() {
  // No actions required in the loop for this example
}
