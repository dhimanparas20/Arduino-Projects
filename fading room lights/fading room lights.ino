int i=0;
int del = 10;

void setup(){
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

void glow(char d0,char d1) {
  
  for (i;i<=255;i++){
    analogWrite(d0, i);
    analogWrite(d1, i);
    delay(del);
  }
  delay(50);
  for (i;i>=0;i--){
    analogWrite(d0, i);
    analogWrite(d1, i);
    delay(del);
  }
  delay(50);
}
 
void loop()
{
  glow(D0,D3);
  glow(D1,D4);
  glow(D2,D5); 
}

