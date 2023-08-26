#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TM1637Display.h>

const char* ssid = "MST";
const char* password = "Mst@2069";
const int CLK_PIN = D2;
const int DIO_PIN = D3;
int hours=0,minutes=0,seconds=0;
int colonShow = 0b01000000;
int colonHide = 0b00000000;
int colonStat,i=0;
String ab;
bool colonVisible = true; 


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800); // GMT +5:30
TM1637Display display(CLK_PIN, DIO_PIN);

void setup() {
    Serial.begin(115200);
    display.setBrightness(7); // Set display brightness
    display.clear();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        i++;
        display.showNumberDec(i, false);
        delay(1000);
        //Serial.print("-_-");
    }
    timeClient.begin();
}

void loop() {
    ab = "";
    if (WiFi.status() == WL_CONNECTED){
          timeClient.update(); // Fetch the time
          hours = timeClient.getHours();
          minutes = timeClient.getMinutes();
          seconds = timeClient.getSeconds();
    }
    else{
        if (seconds>59){
          seconds = 0;
          minutes ++;
          if (minutes>59){
            minutes = 0;
            hours++;
          }
          if (hours>23){
              hours = 0;
          }
        }
        seconds++;
    }    
    // Convert to 12-hour format
    bool isPM = hours >= 12;
    if (isPM) {
        hours = hours % 12;
    }
    if (hours == 0) {
        hours = 12; // Display 12 instead of 0 for 12:00 AM/PM
    }

    // Blink colon every second
    colonVisible = !colonVisible;
    if (colonVisible == true){
      colonStat= colonShow;
    }
    else if (colonVisible == false){
      colonStat= colonHide;
    }

    ab = (hours/10);
    ab += (hours%10);
    ab +=  (minutes/10);
    ab += (minutes%10);
    //ab += (seconds);
    int num = ab.toInt();
    display.showNumberDecEx(num,colonStat);
    delay(1000);
}
