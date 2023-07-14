// Change Your Variables Here
char ssid[] = "Suvidha@2";
char pass[] = "Messi123@22";
char appkey[] = "065cd449-3fed-4437-b355-9705596b1c40";
char appsec[] = "e43cc52f-59e0-4679-889b-d7609ddcb667-e7893776-fad8-445b-9459-11f69755aad3";

// Place Blynk Variables Here
#define BLYNK_TEMPLATE_ID "TMPL3AFjO6q2Y"
#define BLYNK_TEMPLATE_NAME "Room Automation"
#define BLYNK_AUTH_TOKEN "g2-VR83SfRVfmPIMoTQLX0nCrWbJQ9kA"

#define WIFI_SSID  ssid
#define WIFI_PASS  pass
#define APP_KEY    appkey
#define APP_SECRET appsec
#define BAUD_RATE  115200              // Change baudrate to your need
#define WIFI_TIMEOUT 60000

#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #define IR_INPUT D2
  #define ROOM_LIGHT D3
  #define SPEAKER D4
  #define FAN D5
  #define LAMP D6
  #define RED_LED D7
#endif

#ifdef ESP32
  #include <WiFi.h>
#endif

#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#define C1 3125149440
#define C2 3108437760
#define C3 3091726080
#define C4 3141861120
#define C5 3208707840
#define C6 3158572800
#define C7 4161273600
#define C8 3927310080
#define C9 4127850240
#define C0 3860463360
#define CST 3910598400
#define CHASH 4061003520
#define CUP 3877175040
#define CDOWN 2907897600
#define CLEFT 4144561920
#define CRIGHT 2774204160
#define COK 3810328320