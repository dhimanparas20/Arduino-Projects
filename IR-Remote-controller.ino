//=======================================================================================================================
// Code to read IR signal froma a remote and respond accordingly.                                                      || 
// you can attach relay module to your output pins(D1,D2,D3) and use remote based controlling on electric appliances.  ||
// If you have enough knowledge you can edit my code and do alot more.                                                 ||
// IR-remote module link is given in initial commit.                                                                   ||
// Library Docs: "https://github.com/Arduino-IRremote/Arduino-IRremote?tab=readme-ov-file"
// Code by Paras Dhiman                                                                                                ||
//=======================================================================================================================

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
#define IR_RECEIVE_PIN D0

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN,ENABLE_LED_FEEDBACK); // Start the receiver
  pinMode(D0, INPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(9600);
}

void trgr(char pin){
  digitalWrite(pin, !digitalRead(pin));
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

// Main code
void loop(){
    if(IrReceiver.decode()){
    Serial.println(IrReceiver.decodedIRData.decodedRawData,DEC);  //Shows the read value on the monitor screen(if exisits).
    // IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    // IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    switch(IrReceiver.decodedIRData.decodedRawData) {
      case c1:     //press 1 to turn on/off 1st switch.
        trgr(D1);
        break;

      case c2:     //press 2 to turn on/off 2nd switch.
        trgr(D2);
        break;

      case c3:     //press 3 to turn on/off 3rd switch.
        trgr(D3);
        break; 
            
      case c0 : //Press 0 to turn off/off all appliances
        trgr(D1);
        trgr(D2);
        trgr(D3);
        trgr(D4);
    }
    IrReceiver.resume();
    }    
}
