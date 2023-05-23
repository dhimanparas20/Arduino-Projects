// Including Libs.
#include <LiquidCrystal.h> // For LCD Display
#include "DHT.h"
#define DHTPIN D6     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

// LCD connection Diagram:
/*
* VSS to GND
* VDD to 5V
* V0 to Middle of 10K potentiometer(pm). Left of pm(red) to GND and Right of pm(yellow) to 5V.
* RS to D0
* RW to GND
* E to D1
* d4,d5,d6,d7 (display) to D2,D3,D4,D5 (node mcu) respectively
* A to 3.3V
* K to GND
*/

int h=12;
int m=0;
int s=-1;
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
  dht.begin();
  pinMode(D0, OUTPUT); 
  pinMode(D1, OUTPUT); 
  pinMode(D2, OUTPUT);    
  pinMode(D3, OUTPUT); 
  pinMode(D4, OUTPUT); 
  pinMode(D5, OUTPUT); 
  pinMode(DHTPIN, INPUT); 
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(A0, INPUT);
  pinMode(D9, INPUT); //RX pin
}

void loop()
{ 
  s = s+1;
  float hum = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float tmp = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(tmp, hum, false);
  
  lcd.setCursor(0, 0);        
  lcd.print(h);
  lcd.print(":");             
  lcd.print(m); 
  lcd.print(":");       
  lcd.print(s);    

  if(flag<12)  lcd.print(" ");
  //if(flag==12) lcd.print("'|");
  if(flag>=12) lcd.print("' ");

  lcd.print(hic);  
  lcd.print("C");

  if(flag==24) {flag=0; i += 1; dt += 1;}
  if (M == 1 | M ==3 |M ==5 |M ==7 |M ==8 |M ==10 |M ==12 ){  // Months having 31 days
      if (dt ==32) {dt=1;M+=1;}
  }
  else if (M == 1 |M ==4 |M ==6 |M ==9 |M ==11){  // Months having 30 days
    if (dt ==31) {dt=1;M+=1;}
  } 
  else if (M == 2){
    if (dt ==29) {dt=1;M+=1;}  // Feburary Month
  }
  //if (dt ==32) {dt=1; M+=1;}
  if (M ==13) M=1;
  if(i>8)i = 0;
 // s = s+1; 

  lcd.setCursor(0, 1);           
  lcd.print(dt);
  lcd.print("/");
  lcd.print(M);
  lcd.print(" "); 
  lcd.print(day[i]); 
  lcd.print(" |");
  lcd.print(hum);  
  lcd.print("%");
  delay(995); 
  lcd.clear();
       
  if (s == 59){
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
  //bM = digitalRead(D6);  // Button to change Minutes
  bm = digitalRead(D7);  // Button to change Hours
  bh = digitalRead(D8); // Button to change Date
  bdt = analogRead(A0);   // Button to change Month
  
  if (bm == 1 & bh == 1) {  // When both buttons pressed together the day changes.
    i += 1;
    if(i>8)i = 0;
  } 

  else if (bh == 1 & bdt == 1024) {  // When both buttons pressed together the day changes.
    M=M+1;
    if (M ==13) M=1;
  } 
  
  else if (bm == 1) {         // Minute Chnage 
    s=-1;
    m++;    
  }
  
  else if (bh == 1) {        //Hour Change
    h += 1;
    flag+=1;
    if(flag<12)  lcd.print(" ");
    //if(flag==12) lcd.print("'|");
    if(flag>=12) lcd.print("' ");
    if(flag==24) {flag=0;}
    if(h==13) h=1;    
  }
  
  else if (bdt == 1024) {    // Date change
    dt=dt+1;
    if (M == 1 | M ==3 |M ==5 |M ==7 |M ==8 |M ==10 |M ==12 ){  // Months having 31 days
      if (dt ==32) {dt=1;}
    }
    else if (M == 1 |M ==4 |M ==6 |M ==9 |M ==11){  // Months having 30 days
      if (dt ==31) {dt=1;}
    } 
    else if (M == 2){
      if (dt ==29) {dt=1;}  // Feburary Month
    }      
  } 
}


