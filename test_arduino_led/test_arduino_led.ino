#define pin 12
void setup() 
{  
Serial.begin(9600);  
pinMode(pin, OUTPUT); 
}
void loop() {
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
  delay(100);
}
