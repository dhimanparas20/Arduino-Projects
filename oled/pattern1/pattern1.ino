#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Initialize the OLED display
Adafruit_SSD1306 display(128, 32, &Wire, -1); // ACTUAL ARE 122 X 28

char txt[50] =  "GooD NighT";
int len =  strlen(txt);
int mid = (((20-len)/2)+3)*5;

void setup() {
  Serial.begin(9600);
  Wire.begin(D1, D2);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLUE;
}

void doo(){
  display.clearDisplay();
  display.display();
  for (int i=0;i<=122;i++){
    display.setCursor(i, 0);
    display.println("-");
    display.display();
  }
  for (int i=4;i<=28;i++){
    display.setCursor(122, i);
    display.println("|");
    display.display();
    delay(10);
  }
  for (int i=122;i>=0;i--){
    display.setCursor(i, 28);
    display.println("-");
    display.display();
  }
  for (int i=28;i>=4;i--){
    display.setCursor(0, i);
    display.println("|");
    display.display();
    delay(10);
  }
  
  display.setCursor(mid, 14);
  display.println(txt);
  display.display();

}

void loop() {
  doo();
  delay(1000);
}
