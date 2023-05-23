#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 display(OLED_RESET);
Adafruit_SSD1306 display(128, 32, &Wire, -1);

void setup() {
  Serial.begin(9600);
  Wire.begin(D1, D2); // Initialize I2C communication on pins D1 (SDA) and D2 (SCL)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize OLED display with I2C address 0x3C
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
}

void loop() {
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.display();
}
