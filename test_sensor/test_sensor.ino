void setup() 
{  
Serial.begin(9600);  
pinMode(13, INPUT);  
pinMode(10, OUTPUT);

}

void loop() {
  int rd  = digitalRead(13);
  Serial.print(rd);
  Serial.print("\n");
  delay(1000);
  if (rd == 1){
    digitalWrite(10,HIGH);
    delay(80);
    digitalWrite(10,LOW);
  }
}
  
