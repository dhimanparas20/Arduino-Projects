#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TM1637Display.h>

// Define connection pins for TM1637
#define CLK 14  // D5
#define DIO 12  // D6

// WiFi credentials
const char* ssid = "MST Protocol";
const char* password = "Blackkaiser69";

// Initialize display
TM1637Display display(CLK, DIO);

// Define NTP Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Time offset for IST (GMT+5:30)
const long gmtOffset_sec = 19800;  // 5.5 hours in seconds

void setup() {
  Serial.begin(9600);
  
  // Set display brightness (0-7)
  display.setBrightness(4);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  
  // While connecting to WiFi, blink colon every 500ms
  while (WiFi.status() != WL_CONNECTED) {
    static bool colonState = false;
    display.showNumberDecEx(0000, colonState ? 0x40 : 0x00, true);
    colonState = !colonState;
    delay(500);
  }
  
  // Initialize NTP
  timeClient.begin();
  timeClient.setTimeOffset(gmtOffset_sec);
}

void loop() {
  timeClient.update();
  
  // Get current time
  int hours = timeClient.getHours();
  int minutes = timeClient.getMinutes();
  
  // Convert 24-hour format to 12-hour format
  if (hours > 12) {
    hours = hours - 12;
  }
  if (hours == 0) {
    hours = 12;
  }
  
  // Calculate display value (HHMM format)
  int displayValue = hours * 100 + minutes;
  
  // Toggle colon every second
  static bool colonState = false;
  colonState = !colonState;
  
  // Display time with blinking colon
  display.showNumberDecEx(displayValue, colonState ? 0x40 : 0x00, true);
  
  delay(1000);
}
