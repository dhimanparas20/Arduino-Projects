// Including Libs.
#include <Servo.h> 
#include <IRremote.h>
#include <LiquidCrystal.h>

/*LCD connection Diagram:
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

// Defining values to the signals received form the remote button.
#define c1 3125149440
#define c2 3108437760
#define c3 3091726080
#define c4 3141861120
#define c5 3208707840
#define c6 3158572800
#define c7 4161273600
#define c8 3927310080 
#define c9 4127850240
#define c0 3860463360
#define cst 3910598400
#define chash 4061003520
#define cup 3877175040
#define cdown 2907897600
#define cleft 4144561920
#define cright 2774204160
#define cok 3810328320

Servo Servo;
IRrecv IR(12);
String str = "WELCM TO ABVGIET";
int len = str.length();
int i=0,h=0,m=0,s=0;

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() { 
  Serial.begin(9600);
  IR.enableIRIn();
  Servo.attach(11);
  lcd.begin(16, 2);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);    // Blue LED
  pinMode(9, OUTPUT);    // Green LED
  pinMode(10, OUTPUT);   // Buzzer 
  pinMode(11, OUTPUT);   // Servo
  pinMode(12, INPUT);    // IR Remote Input 
  pinMode(13, INPUT);    // IR Sensor input
}

void loop(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(str);
  int rd  = digitalRead(13);
  Serial.println("object there ");
  delay(300);

  while (rd == 1){
    lcd.setCursor(0, 0);
    lcd.print(str);
    lcd.setCursor(4, 1);
    lcd.print("NO OBJECT");
    Serial.println("no object ");
    delay(300);
    rd  = digitalRead(13);
  }
  if(IR.decode()){
    Serial.println(IR.decodedIRData.decodedRawData,DEC);  //Shows the read value on the monitor screen(if exisits).
    switch(IR.decodedIRData.decodedRawData) {
      case c1:
        lcd.setCursor(0, 1);
        lcd.print("Opening Gate");
        for (int i = 0;i<=90;i++){
          digitalWrite(10, HIGH);
          digitalWrite(9, HIGH);
          Servo.write(i); 
          delay(15);  
        }
        break;
      case c2:
        lcd.setCursor(0, 1);
        lcd.print("Closing Gate");
        for (int i = 90;i>=0;i--){
          digitalWrite(10, HIGH);
          digitalWrite(8, HIGH);
          Servo.write(i); 
          delay(15);  
        }
        break;
          }       
    digitalWrite(8, LOW); 
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    //lcd.clear();
    IR.resume();
    }}
