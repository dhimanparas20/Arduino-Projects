//-----------------------------------------------------------------
// Arduino code to make Equalizer using LED and Sound Sensor.     |
// Code by paras Dhiman Ken_kaneki_69 dhimanparas20               |
//-----------------------------------------------------------------

//===================================================================
// Pin configuration
// A0: Audio sensor, D1: Light1, D2: Light2, D3: Light3, D4: Light4 and so on till D8.
//===================================================================

// Configure your variables here:
/*
int r1 = 583;     // Starting threshold of Light1
int r2 = 586;     // Starting threshold of Light2
int r3 = 589;     // Starting threshold of Light3
int r4 = 592;     // Starting threshold of Light4
int r5 = 595;     // Starting threshold of Light5
int r6 = 598;     // Starting threshold of Light6
int r7 = 601;     // Starting threshold of Light7
int r8 = 604;     // Starting threshold of Light8
*/

//int arr[9] = {390,397,404,411,418,425,432,439};
int arr[9] = {390,396,402,408,414,420,426,432};

int t1 = 30 ;     // Time gap for second light to turn on.
int t2 = 30 ;     // Time gap for second light to turn off

void setup() {                // Defining pins
Serial.begin(9600);  
pinMode(A1, INPUT);
pinMode(2, OUTPUT); 
pinMode(3, OUTPUT);
pinMode(4, OUTPUT); 
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
}

//declaring functions
void l(int,int);
void light(int);


void loop() {                 // Drawing patterns
  int ard = analogRead(A1);   // Storing analog read values to a variable "ard".
  Serial.print(ard);          // Print read values on monitor
  Serial.print("\n");

  if(ard >=arr[0] && ard <arr[1]){
     light(2);
    ard = analogRead(A1);
  }
  else if(ard>=arr[1] && ard<arr[2]){
    light(3);
    ard = analogRead(A1);
  }
  else if (ard>=arr[2] && ard<arr[3]){
    light(4);
    ard = analogRead(A1);
  }
  else if(ard>=arr[3] && ard<arr[4]){
    light(5);
    ard = analogRead(A1);
  }
  else if(ard>=arr[4] && ard<arr[5]){
    light(6);
    ard = analogRead(A1);
  }
  else if (ard>=arr[5] && ard<arr[6]){
    light(7);
    ard = analogRead(A1);
  }
  else if(ard >=arr[6] && ard <arr[7]){
    light(8);
    ard = analogRead(A1);
  }
  else if(ard>=arr[7]){
    light(9);
    ard = analogRead(A1);
  }
  //ard = analogRead(A1);
  for(int i = 9;i>=2;i--){
      l(i,0);
      delay(t2);
  
  }
} 

// universal on/off control function.
void l(int p, int c){        //p stands for pin number and c stand for on or off command
  if (c == 1){
    digitalWrite(p,HIGH);     //on command
    //delay(t1);
  }
  else if (c == 0){  
    digitalWrite(p,LOW);      //off command
    //delay(t2);
  }
}

void light(int range){
  for(int i = 2;i<=range;i++){
    l(i,1);
    delay(t1);
  }
}