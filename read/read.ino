#include <IRremote.h>
// const int RECV_PIN = 4;
// // Define variable to store last code received
// unsigned long lastCode; 
 
// // Define IR Receiver and Results Objects
// IRrecv irrecv(RECV_PIN);
// decode_results results;
 
// void setup()
// {
//   Serial.begin(9600);
//   irrecv.enableIRIn();
//   pinMode(RECV_PIN, INPUT);
// }
 
// void loop() {
//         // Serial.println("FFFFFFF");     

// if(irrecv.decode(&results)) //this checks to see if a code has been received
// {
//   Serial.println(results.value, HEX);
 
//     if(results.value == 0xFFFFFFFF)   
//     {
//        // If Repeat then use last code received
//        results.value = lastCode;      
//         Serial.println("Repeat");     

//     }
 
//     if(results.value == 0xFF22DD)    
//     {
//         // Left Button Pressed
//         lastCode = results.value;
//         Serial.println("Left Print");     
//     }
      
//     if(results.value == 0xFFC23D)     
//     {
//        // Right Button Pressed
//        lastCode = results.value;
//         Serial.println("Right Print");     
    
//     }
 
//    if(results.value == 0xFF02FD)     
//     {
//        // Center Button Pressed
//        lastCode = results.value;
//         Serial.println("Center Print");     
    
//     }
 
//     // Add delay to prevent false readings
//     delay(30); 
//     //receive the next value  
//     irrecv.resume(); 
// }   
// }
//  #include <IRremote.h>

// const int IR_RECEIVER_PIN = 4;  // Pin connected to the IR receiver module

// IRrecv irrecv(IR_RECEIVER_PIN);

// decode_results results;  // Variable to store the decoded IR signal

// void setup() {
//   Serial.begin(9600);
//   irrecv.enableIRIn();  // Start the IR receiver
// }

// void loop() {
//   if (irrecv.decode(&results)) {
//     // Print the raw IR signal data
//     Serial.print("Raw IR Signal Data: ");
//     Serial.println(results.value, DEC);
    
//     // Decode and print the protocol and value of the received IR signal
//     if (results.decode_type != UNKNOWN) {
//       Serial.print("Protocol: ");
//       Serial.print(results.decode_type);
//       Serial.print(", Value: ");
//       Serial.println(results.value, HEX);
//     }
    
//     irrecv.resume();  // Continue to receive IR signals
//   }
// }



#define irpin D0

IRrecv IR(irpin);


void setup() {
  Serial.begin(9600);
  IR.enableIRIn();
  pinMode(irpin, INPUT);  // IR remote input
}

// 3810328320
// Main code
void loop(){ 
  if(IR.decode()){
    Serial.println(IR.decodedIRData.decodedRawData,DEC);  //Shows the read value on the monitor screen(if exisits).
    IR.resume();
  }}