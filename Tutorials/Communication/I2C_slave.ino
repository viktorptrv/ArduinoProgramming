#include <Wire.h>

#define SLAVE_ADDR 0x8

#define ANSWER_SIZE 5

String answer = "Hello";

void setup() {
  Wire.begin(SLAVE_ADDR);

  // Function to run when data requested from master
  Wire.onRequest(requestEvent);

  // Function to run when data received from master
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
}

void receiveEvent(){
  while(0 < Wire.available()){
    byte x = Wire.read();
  }
}

void requestEvent() {
  // Setup byte variable in the correct size
  byte response[ANSWER_SIZE];
  
  // Format answer as array
  for (byte i=0;i<ANSWER_SIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  
  // Send response back to Master
  Wire.write(response,sizeof(response));
  
  // Print to Serial Monitor
  Serial.println("Request event");
}
 

void loop() {
  delay(50);
}
