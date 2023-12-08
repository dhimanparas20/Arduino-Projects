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
* d4,d5,d6,d7 (display) to D2,D3,D4,D5 (node mcu) respectively
* A to 3.3V
* K to GND
*/

#define p6 D6
#define p7 D7
#define p8 D8
#define p9 A0

int b6=0,b7=0,b8=0,b9=0;
int x=0,y=0,z=0,i=0;
int lst[5] = {0,1,2,3,4};
int op = 0;

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
  pinMode(p6, INPUT); 
  pinMode(p7, INPUT);
  pinMode(p8, INPUT);
  pinMode(p9, INPUT);
}

void loop()
{ 
  lcd.setCursor(0, 0);       
  lcd.print("Operand: "); 
  lcd.setCursor(9, 0); 
  switch(op){
    case 0:
      lcd.print("+");
      break;
    case 1:
      lcd.print("-");
      break;
    case 2:
      lcd.print("/");
      break;
    case 3:
      lcd.print("*");
      break;  
    case 4:
      lcd.print("%"); 
      break;       
  }      
  lcd.setCursor(0, 1);       
  lcd.print(x); 
  switch(op){
    case 0:
      lcd.print("+");
      break;
    case 1:
      lcd.print("-");
      break;
    case 2:
      lcd.print("/");
      break;
    case 3:
      lcd.print("*");
      break;  
    case 4:
      lcd.print("%"); 
      break;     
  }   
  lcd.print(y);   
  lcd.print(" = ");
  lcd.print(z);
  //lcd.clear();


  //Reading Button Values 
  b6 = digitalRead(p6); 
  b7 = digitalRead(p7); 
  b8 = digitalRead(p8);
  b9 = analogRead(p9);   // high = 1024
  

  if (b9==1024){
    i +=1;
    if (i==5){
    i=0;
    }
    op = lst[i];
    lcd.clear(); 
  }

  if (b6==1 & b7==0){
    x += 1;
    if (x==100){
    x=0;
    }
    lcd.clear(); 
  }
  if (b7==1 & b6==0){
    y += 1;
    if (y==100){
    y=0;
    }
    lcd.clear(); 
  }
  else if (b8==1){
    x = 0 ;
    y = 0 ;
    z = 0 ;
    lcd.clear(); 
  }
  switch(op){
    case 0:
      z = x+y;
      break;
    case 1:
      z = x-y;
      break;
    case 2:
      z = x/y;
      break;
    case 3:
      z = x*y;
      break;  
    case 4:
      z = x%y;
      break;      
  }
  delay(150);
}