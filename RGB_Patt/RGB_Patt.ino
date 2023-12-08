const int redPin = D1;   // Red LED pin is connected to D3
const int greenPin = D2; // Green LED pin is connected to D4
const int bluePin = D3;  // Blue LED pin is connected to D5
int rate = 5;
int del = 50;

void rgb(int r,int g,int b){
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  delay(50);
}

void pat(String C,int type){
  int color;
  if (C == "r"){color=redPin;}
  if (C == "g"){color=greenPin;}
  if (C == "b"){color=bluePin;}

  if (type==1){
    for (int i = 0; i < 255; i+=rate) {
      analogWrite(color, i);
      delay(del);   
    }
  }
  else if(type==0){
    for (int i = 255; i > 0; i-=rate) {
      analogWrite(color, i); 
      delay(del);  
    }
  }
}

void loopAll(){
  for (int r = 0; r < 255; r+=rate) {
    for (int g = 0; g < 255; g+=rate) {
      for (int b = 50; b < 255; b+=rate) {
        analogWrite(redPin, b);
        analogWrite(greenPin, g);
        analogWrite(bluePin, r);
        delay(del);
      }
    }
  }   
}

void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  loopAll();

  pat("r",1);
  pat("g",1);
  pat("b",1);
  pat("r",0);
  pat("g",0);
  pat("b",0);

  pat("r",1);
  pat("g",1);
  pat("b",1);
  pat("g",0);
  pat("b",0);
  pat("r",0);

  pat("r",1);
  pat("g",1);
  pat("b",1);
  pat("b",0);
  pat("g",0);
  pat("r",0);

  pat("g",1);
  pat("b",1);
  pat("r",1);
  pat("g",0);
  pat("b",0);
  pat("r",0);

  pat("g",1);
  pat("b",1);
  pat("r",1);
  pat("b",0);
  pat("r",0);
  pat("g",0);

  pat("g",1);
  pat("b",1);
  pat("r",1);
  pat("r",0);
  pat("g",0);
  pat("b",0);

  pat("b",1);
  pat("g",1);
  pat("r",1);
  pat("b",0);
  pat("g",0);
  pat("r",0);

  pat("b",1);
  pat("g",1);
  pat("r",1);
  pat("g",0);
  pat("r",0);
  pat("b",0);

  pat("b",1);
  pat("g",1);
  pat("r",1);
  pat("r",0);
  pat("b",0);
  pat("g",0);

}    