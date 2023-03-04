// Including Libs.
#include <LiquidCrystal.h> // For LCD Display

// LCD connection Diagram:
/*
* VSS to GND
* VDD to 5V
* V0 to Middle of 10K potentiometer(pm). Left of pm(red) to GND and Right of pm(yellow) to 5V.
* RS to D0
* RW to GND
* E to D1
* d4,d5,d6,d7 to D2,D3,D4,D5 respectively
* A to 3.3V
* K to GND
*/

int h=12;
int m;
int s;
int flag;
String day[7] = {"SU","MO","TU","WE","TH","FR","SA"};
int i=0;
int M = 1;
int dt = 1; 
int bm=0,bh=0,bdt=0,bM=0,bd=0;

const int rs = D0, en = D1, d4 = D2, d5 = D3, d6 = D4, d7 = D5;  // PiN's for LCD Display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup(){
  Serial.begin(9600);          // Enable UART for Debugging
  lcd.begin(16, 2);            // Defins the Dimens of LCD
  pinMode(D0, OUTPUT); 
  pinMode(D1, OUTPUT); 
  pinMode(D2, OUTPUT);    
  pinMode(D3, OUTPUT); 
  pinMode(D4, OUTPUT); 
  pinMode(D5, OUTPUT); 
  pinMode(D6, INPUT); 
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(A0, INPUT);
  pinMode(D9, INPUT); //RX pin
}

void loop()
{ 
  lcd.setCursor(0, 0);       
  lcd.print("Time"); 
  lcd.setCursor(5, 0);    
  lcd.print(h);
  lcd.print(":");             
  lcd.print(m); 
  lcd.print(":");       
  lcd.print(s);       
  if(flag<12)  lcd.print(" AM");
  if(flag==12) lcd.print(" PM");
  if(flag>=12) lcd.print(" PM");

  if(flag==24) {flag=0; i += 1; dt += 1;}
  if (dt ==32) {dt=1; M+=1;}
  if (M ==13) M=1;
  if(i>8)i = 0;
  s = s+1; 

  lcd.setCursor(0, 1);       
  lcd.print("Date");
  lcd.setCursor(5, 1);      
  lcd.print(dt);
  lcd.print(":");
  lcd.print(M);
  lcd.print(":22 "); 
  lcd.print(day[i]); 
  delay(1000);
  lcd.clear();
       
  if (s == 60){
    s = 0;
    m = m+1;
  }
  if (m == 60){
    m = 0;
    h = h+1;
    flag=flag+1;
  }
  if (h==13){
    h = 1;
  }

  //Reading Button Values 
  bm = digitalRead(D6);  // Button to change Minutes
  bh = digitalRead(D7);  // Button to change Hours
  bdt = digitalRead(D8); // Button to change Date
  bM = analogRead(A0);   // Button to change Month

  if (bm == 1 & bh == 1) {  // When both buttons pressed together the day changes.
    i += 1;
    if(i>8)i = 0;
  } 
  
  else if (bm == 1) {         // Minute Chnage 
    s=0;
    m=m+1;
  }
  
  else if (bh == 1) {        //Hour Change
    h += 1;
    flag+=1;
    if(flag<12)  lcd.print(" AM");
    if(flag==12) lcd.print(" PM");
    if(flag>=12) lcd.print(" PM");
    if(flag==24) {flag=0; i += 1; dt += 1;}
    if (dt ==32) {dt=1; M+=1;}
    if (M ==13) M=1;
    if(i>8)i = 0;
    if(h==13) h=1;    
  }
  
  else if (bdt == 1) {    // Date change
    dt=dt+1;
    i += 1;
    if(i>6)i = 0;
    if (dt ==32) {dt=1; M+=1;}
    if (M ==13) M=1;
  } 
   
  else if (bM == 1024) {  //Month Change
    M=M+1;
    if (M ==13) M=1;
  } 

}


