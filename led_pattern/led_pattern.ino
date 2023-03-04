// Arduino Code written to Draw LEd Patterns.
// Code by Paras Dhiman

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

//===========================================================================================
// PIN schematic diagram.
// (D7-BLUE),(D5-BLUE),(D3-BLUE),(D1-BLUE),(D0-BLUE),(D2-BLUE),(D4-BLUE),(D6-BLUE),(D8-BLUE)
//===========================================================================================


// Control(on/off) function for pins.
void i(char d, int t1, int t2) {
  digitalWrite(d, HIGH);
  delay(t1);
  digitalWrite(d, LOW);
  delay(t2);
}

// Specific ON control for a pin.
void on (char d){
  digitalWrite(d, HIGH);
}

// Specific OFF control for a pin.
void off (char d){
  digitalWrite(d, LOW);
}

// Delay Function. (Just to shorten my code)
void d (int del){
  delay(del);
}

//  -------------------------------------
//  |  LED patterns Start from here     |
//  -------------------------------------

//-----------------
// Pattern 1 
//----------------
void p1(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    i(D7,t1,t2);
    i(D5,t1,t2);
    i(D3,t1,t2);
    i(D1,t1,t2);
    i(D0,t1,t2);
    i(D2,t1,t2);
    i(D4,t1,t2);
    i(D6,t1,t2);
    i(D8,t1,t2);
  }
}

//-----------------
// Pattern 2 (reverse of pattern 1)
//-----------------
void p2(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    i(D8,t1,t2);
    i(D6,t1,t2);
    i(D4,t1,t2);
    i(D2,t1,t2);
    i(D0,t1,t2);
    i(D1,t1,t2);
    i(D3,t1,t2);
    i(D5,t1,t2);
    i(D7,t1,t2);
  }
}

//-----------------
// Pattern 3
//-----------------
void p3(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    i(D0,t1,t2);
    on(D1);
    on(D2);
    d(t1);
    off(D1);
    off(D2);
    d(t2);

    on(D3);
    on(D4);
    d(t1);
    off(D3);
    off(D4);
    d(t2);

    on(D5);
    on(D6);
    d(t1);
    off(D5);
    off(D6);
    d(t2);

    on(D7);
    on(D8);
    d(t1);
    off(D7);
    off(D8);
    d(t2);
  }
}

//-----------------
// Pattern 4 (reverse of pattern 3)
//-----------------
void p4(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    on(D7);
    on(D8);
    d(t1);
    off(D7);
    off(D8);
    d(t2);

    on(D5);
    on(D6);
    d(t1);
    off(D5);
    off(D6);
    d(t2);

    on(D3);
    on(D4);
    d(t1);
    off(D3);
    off(D4);
    d(t2);

    on(D1);
    on(D2);
    d(t1);
    off(D1);
    off(D2);
    d(t2);
    i(D0,t1,t2);
  }
}

//-----------------
// Pattern 5
//-----------------
void p5(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    on(D0);
    d(t1);
    on(D1);
    on(D2);
    d(t1);
    on(D3);
    on(D4);
    d(t1);
    on(D5);
    on(D6);
    d(t1);
    on(D7);
    on(D8);
    d(800);

    off(D7);
    off(D8);
    d(t2);
    off(D5);
    off(D6);
    d(t2);
    off(D3);
    off(D4);
    d(t2);
    off(D1);
    off(D2);
    d(t2);
    off(D0);
    d(t2);
  }
} 

//-----------------
// Pattern 6
//-----------------
void p6(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    i(D0,t1,t2);
  }
  for(int j=1; j<=rep; j++){
    on(D1);
    on(D2);
    d(t1);
    off(D1);
    off(D2);
    d(t2);  
  }
  for(int j=1; j<=rep; j++){
    on(D3);
    on(D4);
    d(t1);
    off(D3);
    off(D4);
    d(t2);  
  }
  for(int j=1; j<=rep; j++){
    on(D5);
    on(D6);
    d(t1);
    off(D5);
    off(D6);
    d(t2);  
  }
  for(int j=1; j<=rep; j++){
    on(D7);
    on(D8);
    d(t1);
    off(D7);
    off(D8);
    d(t2);  
  }
}  

//-----------------
// Pattern 7 (reverse of pattern 6)
//-----------------  
void p7(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    on(D5);
    on(D6);
    d(t1);
    off(D5);
    off(D6);
    d(t2);
  }

  for(int j=1; j<=rep; j++){
    on(D3);
    on(D4);
    d(t1);
    off(D3);
    off(D4);
    d(t2);  
  }

  for(int j=1; j<=rep; j++){
    on(D1);
    on(D2);
    d(t1);
    off(D1);
    off(D2);
    d(t2);  
  }
  for(int j=1; j<=rep; j++){
    i(D0,t1,t2);
  }
  
}

//-----------------
// Pattern 8
//-----------------
void p8(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    i(D1,t1,t2);
    i(D2,t1,t2);
  }

  for(int j=1; j<=rep; j++){
    i(D3,t1,t2);
    i(D4,t1,t2);
  }

  for(int j=1; j<=rep; j++){
    i(D5,t1,t2);
    i(D6,t1,t2);
  }

  for(int j=1; j<=rep; j++){
    i(D7,t1,t2);
    i(D8,t1,t2);
  }

  for(int j=1; j<=rep; j++){
    i(D5,t1,t2);
    i(D6,t1,t2);
  }

  for(int j=1; j<=rep; j++){
    i(D3,t1,t2);
    i(D4,t1,t2);
  }

  for(int j=1; j<=rep; j++){
    i(D1,t1,t2);
    i(D2,t1,t2);
  }

}

//-----------------
// Pattern 9
//-----------------
void p9(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    on(D7);
    on(D0);
    d(t1);
    off(D7);
    off(D0);
    d(t2);

    on(D5);
    on(D2);
    d(t1);
    off(D5);
    off(D2);
    d(t2);

    on(D3);
    on(D4);
    d(t1);
    off(D3);
    off(D4);
    d(t2);

    on(D1);
    on(D6);
    d(t1);
    off(D1);
    off(D6);
    d(t2);

    on(D0);
    on(D8);
    d(t1);
    off(D0);
    off(D8);
    d(t2);

    on(D1);
    on(D6);
    d(t1);
    off(D1);
    off(D6);
    d(t2);

    on(D3);
    on(D4);
    d(t1);
    off(D3);
    off(D4);
    d(t2);

    on(D5);
    on(D2);
    d(t1);
    off(D5);
    off(D2);
    d(t2);

    on(D7);
    on(D0);
    d(t1);
    off(D7);
    off(D0);
    d(t2);

  }
    
}

//-----------------
// Pattern 10
//-----------------
void p10(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    on(D7);
    on(D3);
    d(t1);
    off(D7);
    off(D3);
    d(t2);

    on(D5);
    on(D1);
    d(t1);
    off(D5);
    off(D1);
    d(t2);

    on(D3);
    on(D0);
    d(t1);
    off(D3);
    off(D0);
    d(t2);

    on(D1);
    on(D2);
    d(t1);
    off(D1);
    off(D2);
    d(t2);

    on(D0);
    on(D4);
    d(t1);
    off(D0);
    off(D4);
    d(t2);

    on(D2);
    on(D6);
    d(t1);
    off(D2);
    off(D6);
    d(t2);

    on(D4);
    on(D8);
    d(t1);
    off(D4);
    off(D8);
    d(t2);

    on(D2);
    on(D6);
    d(t1);
    off(D2);
    off(D6);
    d(t2);

    on(D0);
    on(D4);
    d(t1);
    off(D0);
    off(D4);
    d(t2);

    on(D1);
    on(D2);
    d(t1);
    off(D1);
    off(D2);
    d(t2);

    on(D3);
    on(D0);
    d(t1);
    off(D3);
    off(D0);
    d(t2);

    on(D5);
    on(D1);
    d(t1);
    off(D5);
    off(D1);
    d(t2);

    on(D7);
    on(D3);
    d(t1);
    off(D7);
    off(D3);
    d(t2); 
      
  }
}

//-----------------
// Pattern 11
//-----------------
void p11(int rep, int t1, int t2){
  for(int j=1; j<=rep; j++){
    on(D7);
    d(t1);
    on(D5);
    d(t1);
    on(D3);
    d(t1);
    on(D1);
    d(t1);
    on(D0);
    d(t1);
    on(D2);
    d(150);
    on(D4);
    d(t1);
    on(D6);
    d(t1);
    on(D8);
    d(1000);
    off(D8);
    d(t2);
    off(D6);
    d(t2);
    off(D4);
    d(t2);
    off(D2);
    d(t2);
    off(D0);
    d(t2);
    off(D1);
    d(t2);
    off(D3);
    d(t2);
    off(D5);
    d(t2);
    off(D7);
    d(150);  

    on(D8);
    d(t1);  
    on(D6);
    d(t1);
    on(D4);
    d(t1);
    on(D2);
    d(t1);
    on(D0);
    d(t1);
    on(D1);
    d(t1);
    on(D3);
    d(t1);
    on(D5);
    d(t1);
    on(D7);
    d(1000);
    off(D7);
    d(t2);
    off(D5);
    d(t2);
    off(D3);
    d(t2);
    off(D1);
    d(t2);
    off(D0);
    d(t2);
    off(D2);
    d(t2);
    off(D4);
    d(t2);
    off(D6);
    d(t2);
    off(D8);
    d(200);
  }
}



//--------------------------------------------------------------------
// Looping code
// Repetition and on/off time can be controlled from here directly.
//--------------------------------------------------------------------

void loop() {
  p1(1,100,40);
  p2(1,100,40); 
  p1(1,100,40);
  p2(1,100,40); 
  p3(1,200,50); 
  p4(1,200,50);
  p3(1,200,50); 
  p4(1,200,50);
  p6(7,150,70);
  p5(2,300,100);
  p7(5,200,70);
  p10(2,200,50);
  p11(2,150,70);
}
