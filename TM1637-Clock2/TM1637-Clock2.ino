#include <TM1637Display.h>
#include <ESP8266WiFi.h>
#include "time.h"

#define BRIGHTNESS  3   //0-7
const char* ssid = "Kens Device";
const char* password = "asdfghjkl";
const int CLK_PIN = D2;
const int DIO_PIN = D3;
int colonShow = 0b01000000;
int colonHide = 0b00000000;
int colonStat,i=0;
bool colonVisible = true;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;   //Replace with your GMT offset (seconds)
const int   daylightOffset_sec = 0;  //Replace with your daylight offset (seconds)
String ab="";
TM1637Display display(CLK_PIN, DIO_PIN);


void setup()
{
  Serial.begin(9600);
  display.setBrightness(BRIGHTNESS); // Set display brightness
  display.clear();
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      display.showNumberDec(i, false);
      delay(1000);
      i++;
  }
  //Serial.println("CONNECTED to WIFI");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  printLocalTime();
}
void printLocalTime()
{
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);

  // Extract hour and minutes
  int hours = timeinfo->tm_hour;
  int minutes = timeinfo->tm_min;
  //const char* ampm = (hours < 12) ? "AM" : "PM";

  // Convert to 12-hour format
  if (hours > 12) {
    hours -= 12;
  }
  if (hours == 0) {
    hours = 12;
  }
  colonVisible = !colonVisible;
  if (colonVisible == true){
    colonStat= colonShow;
  }
  else if (colonVisible == false){
    colonStat= colonHide;
  }
  ab = (hours);
  ab +=  (minutes);
  int num = ab.toInt();
  display.showNumberDecEx(num,colonStat,true,4,0);   //true to show preceeding 0's,4 for no of digits, 0 for starting index

  //Serial.printf("Current time: %02d:%02d\n", hours, minutes);
  //Serial.println(asctime(timeinfo));
  delay(1000);
}
