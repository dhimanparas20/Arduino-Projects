#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Initialize the OLED display
Adafruit_SSD1306 display(128, 32, &Wire, -1);

void setup() {
  Serial.begin(9600);
  Wire.begin(D1, D2);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void disp(int col,int row,int del,String txt,int clr){
  display.setCursor(row, col);
  display.println(txt);
  display.display();
  delay(del);
  if (clr==1){
    display.clearDisplay();
    display.display();
    delay(del);
  }  
}

void loop() {
  disp(0,0,250,"HI",0);
  disp(8,15,250,"FUCK",0);
  disp(16,45,250,"YOU",1);
}
