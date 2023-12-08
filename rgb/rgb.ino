void setup() {
  Serial.begin(9600);  // Enable UART for Debugging
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void glow(int a,int b,int c){
  analogWrite(2,a);
  analogWrite(3,b);
  analogWrite(4,c);
}

void loop() {
glow(0,255,200);
}


