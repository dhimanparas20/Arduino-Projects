// Arduino Code written to Draw LEd Patterns using remote control.
// Code by Paras Dhiman

// Include the IRremote library
#include <IRremote.h>

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

// Define the input for the IR-receiver module
IRrecv IR(D0);

// Defining of PINs 
void setup() {
IR.enableIRIn();  
pinMode(D0, INPUT);  
pinMode(D1, OUTPUT);
pinMode(D2, OUTPUT);
pinMode(D3, OUTPUT);
pinMode(D4, OUTPUT);
pinMode(D5, OUTPUT);
pinMode(D6, OUTPUT);
pinMode(D7, OUTPUT);
pinMode(D8, OUTPUT);
Serial.begin(9600);
}

// on/off Modules
void on(char p){
  digitalWrite(p, HIGH);
}

void off(char p){
  digitalWrite(p, LOW);
}

void c(char p,int t1, int t2){
  digitalWrite(p, HIGH);
  delay(t1);
  digitalWrite(p, LOW);
  delay(t2);
}

#define t1 150
#define t2 50

// Main code
void loop(){
    if(IR.decode()){
    Serial.println(IR.decodedIRData.decodedRawData,DEC);  //Shows the read value on the monitor screen(if exisits).
    switch(IR.decodedIRData.decodedRawData) {
      
      case c1:     //press 1 to turn on 1st switch.
        on(D1);
        on(D4);
        break;

      case c2:     //press 2 to turn on 2nd switch.
        on(D2);
        on(D5);
        break;

      case c3:     //press 3 to turn on 3rd switch.
        on(D3);
        on(D6);
        break;

      case c4:     //press 4 to turn off 1st switch.    
        off(D1);
        off(D4);
        break;

      case c5:     //press 5 to turn off 2nd switch.
        off(D2);
        off(D5);
        break;

      case c6:     //press 6 to turn off 3rd switch.
        off(D3);
        off(D6);
        break;

      case c7:     //press 7 to turn on 4th switch.
        off(D8);
        break;

      case c8:     //press 8 to turn off 4th switch.    
        on(D8);
        break;  

      case c9:   
        on(D1);
        on(D2);
        on(D3);
        on(D4);
        on(D5);
        on(D6);
        break;

      case cst:     //turns on relay
        on(D3);
        on(D6);
        delay(200);
        off(D3);
        off(D6);
        delay(200);
        on(D3);
        on(D6);
        delay(200);
        off(D3);
        off(D6);
        delay(200);
        c(D1,t1,t2);
        c(D2,t1,t2);
        c(D3,t1,t2);
        c(D4,t1,t2);
        c(D5,t1,t2);
        c(D6,t1,t2);
        on(D7);
        break;    

      case chash:     //turns off relay
        on(D2);
        on(D5);
        delay(200);
        off(D2);
        off(D5);
        delay(200);
        on(D2);
        on(D5);
        delay(200);
        off(D2);
        off(D5);
        delay(200);
        off(D7);
        delay(150);
        c(D6,t1,t2);
        c(D5,t1,t2);
        c(D4,t1,t2);
        c(D3,t1,t2);
        c(D2,t1,t2);
        c(D1,t1,t2);
        break;        
            
      case c0 : //Press 0 to turn off all appliances
        off(D1);
        off(D2);
        off(D3);
        off(D4);
        off(D5);
        off(D6);
        off(D7);
        off(D8);
        break;
    }
    IR.resume();
    }    
}
