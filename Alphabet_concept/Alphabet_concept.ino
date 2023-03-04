// Alphabet concept ...
// Arduino Code written to Draw LEd Patterns.
// Code by Paras Dhiman @Ken_kaneki_69 @Dhimanparas20

// Defining of PINs 
void setup() 
{  
Serial.begin(9600);  
pinMode(D0, OUTPUT);  
pinMode(D1, OUTPUT);
pinMode(D2, OUTPUT);
pinMode(D3, OUTPUT);
pinMode(D4, OUTPUT);
pinMode(D5, OUTPUT);
pinMode(D6, OUTPUT);
pinMode(D7, OUTPUT);
pinMode(D8, OUTPUT);
}

//=============================================================================
// PIN schematic diagram.                                                     |
// (D1-top left)    (D2-top middle)    (D3-top right)                         |
// (D4-middle left) (D2-middle middle) (D6-middle right)                      |
// (D7-bottom left) (D8-bottom middle) (D0-bottom right)                      |
//=============================================================================


//--------------------------------------------------------------------
//  -------------------------------------                            
//  |  Configue pattern speed here      |                            
//  -------------------------------------                             
                                                                     
// Per LED on time(ms):                           
int pon = 150;                                    
                    
// Per LED off time(ms):                                             
int poff = 70;                                                        

// Full word on time(ms) (time for which a complete alphabet is visible):         
int on_stay = 400;                                                   

// Full word off time(ms) (time gap between 2 words):                
int off_stay = 250;  

// No. of time you want to repeat the blinking lEDs. They occur after all alphabets of a word have been printed.
int rpt = 2;
int ont = 170;  // Time(ms) for which all the leds will stay on.
int offt = 70;  // Time(ms) for which all the leds will stay off.
                                               
//------------------------------------------------------------------ 

//------------------------------------------------------------------ 
// Control(on/off) function for pins.
// DO NOT TOUCH, UNTILL YOU KNOW WHAT YOU ARE DOING.

void i(char d, int t1, int t2) {
  digitalWrite(d, HIGH);
  delay(t1);
  digitalWrite(d, LOW);
  delay(t2);
}

// Specific ON control for a pin.
void on (char d, int tm){
  digitalWrite(d, HIGH);
  delay(tm);
}

// Specific OFF control for a pin.
void off (char d, int tm){
  digitalWrite(d, LOW);
  delay(tm);
}

// Delay Function. (Just to shorten my code)
void d (int del){
  delay(del);
}
//------------------------------------------------------------------ 


//------------------------------------------------------------------
//----------------------
// Alphabets + Patterns 
//----------------------
// DO NOT TOUCH, UNTILL YOU KNOW WHAT YOU ARE DOING.

//Turn on all LEDs 
void BLINK(int t1,int t2){
  for(int j=1; j<=rpt; j++){
    on(D1,t1);
    on(D2,t1);
    on(D3,t1);
    on(D4,t1);
    on(D5,t1);
    on(D6,t1);
    on(D7,t1);
    on(D8,t1);
    on(D0,ont); 
    off(D0,t2);
    off(D8,t2);
    off(D7,t2);
    off(D6,t2);
    off(D5,t2);
    off(D4,t2);
    off(D3,t2);
    off(D2,t2);
    off(D1,offt);
  }
}

// Turn off all LEDs
void DED(int t){
  off(D1,0);
  off(D2,0);
  off(D3,0);
  off(D4,0);
  off(D5,0);
  off(D6,0);
  off(D7,0);
  off(D8,0);
  off(D0,t); 
}
void A(int t1,int t2){
  on(D7,t1);
  on(D4,t1);
  on(D2,t1);
  on(D6,t1);
  on(D0,on_stay);
  off(D7,t2);
  off(D4,t2);
  off(D2,t2);
  off(D6,t2);
  off(D0,off_stay);  
}

void B(int t1,int t2){
  on(D1,t1);
  on(D4,t1);
  on(D5,t1);
  on(D8,t1);
  on(D7,on_stay);
  off(D1,t2);
  off(D4,t2);
  off(D5,t2);
  off(D8,t2);
  off(D7,off_stay);
}

void C(int t1,int t2){
  on(D3,t1);
  on(D2,t1);
  on(D1,t1);
  on(D4,t1);
  on(D7,t1);
  on(D8,t1);
  on(D0,on_stay);
  off(D3,t2);
  off(D2,t2);
  off(D1,t2);
  off(D4,t2);
  off(D7,t2);
  off(D8,t2);
  off(D0,off_stay);
}

void D(int t1,int t2){
  on(D1,t1);
  on(D2,t1);
  on(D6,t1);
  on(D8,t1);
  on(D7,t1);
  on(D4,on_stay);
  
  off(D1,t2);
  off(D2,t2);
  off(D6,t2);
  off(D8,t2);
  off(D7,t2);
  off(D4,off_stay);
}

void E(int t1,int t2){
  on(D3,t1);
  on(D2,t1);
  on(D1,180);
  on(D5,t1);
  on(D7,t1);
  on(D8,t1);
  on(D0,on_stay);
  off(D3,t2);
  off(D2,300);
  off(D1,t2);
  off(D5,t2);
  off(D7,t2); 
  off(D8,t2);
  off(D0,off_stay); 
}

void f(int t1,int t2){
  on(D2,t1);
  on(D5,t1);
  on(D8,t1);
  on(D3,t1);
  on(D6,on_stay);
  off(D2,t2);
  off(D5,t2);
  off(D8,t2);
  off(D3,t2);
  off(D6,off_stay); 
}

void H(int t1,int t2){
  on(D1,t1);
  on(D4,t1);
  on(D7,t1);
  on(D5,t1);
  on(D3,t1);
  on(D6,t1);
  on(D0,on_stay);
  off(D1,t2);
  off(D4,t2);
  off(D7,t2);
  off(D5,t2);
  off(D3,t2);
  off(D6,t2);
  off(D0,off_stay);
}

void I(int t1,int t2){
  on(D2,t1);
  on(D5,t1);
  on(D8,on_stay);
  off(D2,t2);
  off(D5,t2);
  off(D8,off_stay);
}

void K(int t1,int t2){
  on(D1,t1);
  on(D4,t1);
  on(D7,t1);
  on(D2,t1);
  on(D3,t1);
  on(D8,t1);
  on(D0,on_stay);
  off(D1,t2);
  off(D4,t2);
  off(D7,t2);
  off(D2,t2);
  off(D3,t2);
  off(D8,t2);
  off(D0,off_stay);
}

void L(int t1,int t2){
  on(D1,t1);
  on(D4,t1);
  on(D7,t1);
  on(D8,t1);
  on(D0,on_stay);
  off(D1,t2);
  off(D4,t2);
  off(D7,t2);
  off(D8,t2);
  off(D0,off_stay);
}

void M(int t1,int t2){
  on(D7,t1);
  on(D4,t1);
  on(D1,t1);
  on(D5,t1);
  on(D3,t1);
  on(D6,t1);
  on(D0,on_stay);
  off(D7,t2);
  off(D4,t2);
  off(D1,t2);
  off(D5,t2);
  off(D3,t2);
  off(D6,t2);
  off(D0,off_stay);
}

void N(int t1,int t2){
  on(D7,t1);
  on(D4,t1);
  on(D1,t1);
  on(D5,t1);
  on(D0,t1);
  on(D6,t1);
  on(D3,on_stay);
  off(D7,t2);
  off(D4,t2);
  off(D1,t2);
  off(D5,t2);
  off(D0,t2);
  off(D6,t2);
  off(D3,off_stay);
}

void O(int t1,int t2){
  on(D1,t1);
  on(D2,t1);
  on(D3,t1);
  on(D6,t1);
  on(D0,t1);
  on(D8,t1);
  on(D7,t1);
  on(D4,on_stay);
  off(D1,t2);
  off(D2,t2);
  off(D3,t2);
  off(D6,t2);
  off(D0,t2);
  off(D8,t2);
  off(D7,t2);
  off(D4,off_stay);
}

void P(int t1,int t2){
  on(D7,t1);
  on(D4,t1);
  on(D1,t1);
  on(D2,t1);
  on(D3,t1);
  on(D6,t1);
  on(D5,on_stay);
  off(D7,t2);
  off(D4,t2);
  off(D1,t2);
  off(D2,t2);
  off(D3,t2);
  off(D6,t2);
  off(D5,off_stay);
}

void R(int t1,int t2){
  on(D7,t1);
  on(D4,t1);
  on(D1,t1);
  on(D2,t1);
  on(D3,t1);
  on(D6,t1);
  on(D5,t1);
  on(D0,on_stay);
  off(D7,t2);
  off(D4,t2);
  off(D1,t2);
  off(D2,t2);
  off(D3,t2);
  off(D6,t2);
  off(D5,t2);
  off(D0,off_stay);
}

void S(int t1,int t2){
  on(D3,t1);
  on(D2,t1);
  on(D5,t1);
  on(D8,t1);
  on(D7,on_stay);
  off(D3,t2);
  off(D2,t2);
  off(D5,t2);
  off(D8,t2);
  off(D7,off_stay); 
}

void T(int t1,int t2){
  on(D1,t1);
  on(D2,t1);
  on(D3,t1);
  on(D5,t1);
  on(D8,on_stay);
  off(D1,t2);
  off(D2,t2);
  off(D3,t2);
  off(D5,t2);
  off(D8,off_stay); 
}

void U(int t1,int t2){
  on(D1,t1);
  on(D4,t1);
  on(D7,t1);
  on(D8,t1);
  on(D0,t1);
  on(D6,t1);
  on(D3,on_stay);
  off(D1,t2);
  off(D4,t2);
  off(D7,t2);
  off(D8,t2);
  off(D0,t2);
  off(D6,t2);
  off(D3,off_stay);
}

void V(int t1,int t2){
  on(D1,t1);
  on(D4,t1);
  on(D8,t1);
  on(D6,t1);
  on(D3,on_stay);
  off(D1,t2);
  off(D4,t2);
  off(D8,t2);
  off(D6,t2);
  off(D3,off_stay);
}

void W(int t1,int t2){
  on(D1,t1);
  on(D4,t1);
  on(D7,t1);
  on(D5,t1);
  on(D0,t1);
  on(D6,t1);
  on(D3,on_stay);
  off(D1,t2);
  off(D4,t2);
  off(D7,t2);
  off(D5,t2);
  off(D0,t2);
  off(D6,t2);
  off(D3,off_stay);
}

void X(int t1,int t2){
  on(D1,t1);
  on(D5,t1);
  on(D0,t1);
  on(D3,t1);
  on(D7,on_stay);
  off(D1,t2);
  off(D5,t2);
  off(D0,t2);
  off(D3,t2);
  off(D7,off_stay);
}

void Y(int t1,int t2){
  on(D1,t1);
  on(D5,t1);
  on(D8,t1);
  on(D3,on_stay);
  off(D1,t2);
  off(D5,t2);
  off(D8,t2);
  off(D3,off_stay);
}

void Z(int t1,int t2){
  on(D1,t1);
  on(D2,t1);
  on(D3,t1);
  on(D5,t1);
  on(D7,t1);
  on(D8,t1);
  on(D0,on_stay);
  off(D1,t2);
  off(D2,t2);
  off(D3,t2);
  off(D4,t2);
  off(D7,t2);
  off(D8,t2);
  off(D0,off_stay);
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
//  -------------------------------------                            
//  |  Configue your words here         |                           
//  ------------------------------------- 

// Simply write your ALPHABET in capitals followed by "(pon,poff);"
void loop()
{ 
M(pon,poff);
I(pon,poff);
S(pon,poff);
S(pon,poff);
I(pon,poff);
O(pon,poff);
N(pon,poff);

BLINK(0,0); // Represents gap between 2 consecutive words

I(pon,poff);
S(pon,poff);
T(pon,poff);
A(pon,poff);
N(pon,poff);
B(pon,poff);
U(pon,poff);
L(pon,poff);

BLINK(0,0);

M(pon,poff);
S(pon,poff);
T(pon,poff);

//--------------------------------------------------------------------
DED(500);
}
