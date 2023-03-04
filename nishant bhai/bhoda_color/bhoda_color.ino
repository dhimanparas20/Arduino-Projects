// Including Libs.
#include <Servo.h> // Controls the Servo Motor
#include <LiquidCrystal.h> // For LCD Display

// LCD connection Diagram:
/*
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

Servo Servo;                      // Creating Servo object of class Servo
String str = " WLCM TO ABVGIET";  // 
int len = str.length();           //
int GREEN =  90;                  //Green Density read by the color sensor.
int count = 0;                    //Set count limit for car 
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  // PiN's for LCD Display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// PINS For Color Sensor
#define SERVO A0   // Servo
#define LED A1     // Green led + buzzer
#define BLED A2    // Blue LED
#define S0_PIN 8  
#define S1_PIN 9  
#define S2_PIN 10 
#define S3_PIN 11 
#define OUT_PIN 12
#define IR 13      // IR
#define IR2 1      // IR 2

void setup(){
  Serial.begin(9600);          // Enable UART for Debugging
  Servo.attach(SERVO);         // Attach the servo to the pin of UNO
  lcd.begin(16, 2);            // Defins the Dimens of LCD
  // IR sensor Inputs
  pinMode(IR, INPUT);          // Ir sensor input 
  pinMode(IR2, INPUT);         // IR sensor 2 Input 
  // Analog PIN's
  pinMode(LED, OUTPUT);        // Buzzer + Green LED OUTPUT
  pinMode(SERVO, OUTPUT);      // Servo Fucker 
  pinMode(BLED, OUTPUT);       // BLUE LED OUTPUT
  // Digital PIN's 
  pinMode(2, OUTPUT);    
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT);
  // Sensor Pins 
  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  pinMode(OUT_PIN, INPUT);   //Set OUT_PIN as Input

  // Set Pulse Width scaling to 20%
  digitalWrite(S0_PIN, HIGH);
  digitalWrite(S1_PIN, LOW);
}

void loop()
{
  lcd.setCursor(0, 0);        // Defines the Column and row of LCD
  lcd.print(str);             // Prints Text on LCD
  int rd  = digitalRead(IR);  // Reads ir value and stores in var rd
  int rd2  = digitalRead(IR); // Reads value from sensor 2
  Serial.println(rd);         // Prints the IR sensor reading on Serial Monitor
 
  if (rd == 0){               // If IR sensor detects an Object
    Serial.println(" Object Detected");
    lcd.setCursor(0, 1);
    lcd.print("OBJECT DETECTED");   //Display or LCD
    int r, g, b;      

    g = process_green_value();      //Processing GREEN Color
    delay(200);
    Serial.print("g = ");
    Serial.print(g);
    /*
    r = process_red_value();        //Processing RED Color
    delay(200);
    b = process_blue_value();       //Processing BLUE Color
    delay(200);
    Serial.print("r = ");
    Serial.print(r);
    Serial.print(" ");
    Serial.print(" ");
    Serial.print("b = ");
    Serial.print(b);
    Serial.print(" ");
    */    
    Serial.println();                        
    if (g < GREEN){                 //If Green Color is detected by the Sensor   
      Serial.println("  Colour Green  ");
      lcd.setCursor(0, 1);
      lcd.print("  OPENING GATE  ");
      digitalWrite(LED, HIGH);      // TUrn on the buzzer and Green LED
      digitalWrite(BLED, LOW);      // TURN OFF blue LED 
      Servo.write(+90);             // Rotate the Servo
      count++;                      // Increments counts for each car     
      delay(3500);                  // Hold
      lcd.clear();
    }
    else if (count == 3){           // If parking reaches its limit
      Serial.println("  Parking Full ");      
      lcd.setCursor(0, 1);
      lcd.print("  Parking FUll  ");
    }
    else{
       delay(150);                  //Just INCASE
    }
  }

  else{
    digitalWrite(LED, LOW);    // TUrn of the buzzer and GREEN LED
    digitalWrite(BLED, HIGH);  // TURN ON blue LED
    lcd.setCursor(0, 1);
    lcd.print("    NO OBJECT");
    Servo.write(-90);          // Rotate back the Servo 
    if (rd2 == 0){
      Servo.write(+90);         // opens the gate for outgoing car
      count --; // Reduce the count 
      Serial.println(" reducing count ");
      lcd.setCursor(0, 1);
      lcd.print(count);
      delay(5000);      
    }
  }
}

//------------------------------------------------------------------------
// Processing Colors 
//------------------------------------------------------------------------
int process_red_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, LOW);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}
int process_green_value()
{
  digitalWrite(S2_PIN, HIGH);
  digitalWrite(S3_PIN, HIGH);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}
int process_blue_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, HIGH);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}
//----------------------------------------------------------------------------
