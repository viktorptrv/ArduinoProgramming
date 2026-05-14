// TO DO
// 1. Add Serial communication for testing
// 2. Add Bluetooth connection to raspberry pi gui
// 3. Add once a command returns successfully to set finished bit


#include <Servo.h>

//basic commands
#define   MTL     0x4d5456              // Move to the left
#define   MTR     0x4d5452              // Move to the right
#define   MTB     0x4d5442              // Move backwards
#define   MTF     0x4d5446              // Move frontwards
#define   MTRel   0x4d5452656c          // Move Relative position
#define   MTAbs   0x4d54416273          // Move Absolute position
#define   MON     0x4d4f4e              // Motor ON
#define   MOF     0x4d4f46              // Motor OFF
#define   OUTP    0x4f555450            // Turn on/off outputs
#define   INP     0x494e50              // Check on inputs

// Return codes
#define   accepted    0x0001
#define   finished    0x0002
#define   error       0x0003  
#define   denied      0x0004

// Random variables
#define   MaxFreePin    13
#define   MinFreePin    3

// Function definitions;
uint8_t MTL(int step);
uint8_t MTR(int step);
uint8_t MTB(int step);
uint8_t MTF(int step);
uint8_t MTRel(int step);
uint8_t MTAbs(int step);
uint8_t MON(byte motor);
uint8_t MOF(byte motor);
uint8_t OUTP(byte pin, byte mode);
uint16_t INP(byte pin);

uint8_t global_status = 0x0000;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

// functions declaration
uint8_t MTL(int step){

}

uint8_t MTR(int step){

}

uint8_t MTB(int step){

}

uint8_t MTF(int step){

}

uint8_t MTRel(int step){

}

uint8_t MTAbs(int step){

}

uint8_t MON(byte motor){

}

uint8_t MOF(byte motor){

}

uint8_t OUTP(byte pin, byte mode){
  if (pin > MaxFreePin || pin < MinFreePin){
    global_status = global_status | error;
    return error;
  }

  if (mode & 2){
    if (pin == 3){
      Serial.print()
    }
  }

}

uint16_t INP(byte pin){
  if (pin > 5){
    global_status = global_status | error;
    return error;
  }
  global_status = global_status >> 4 | accepted;
  int result;

  if (pin == 0){
    result = analogRead(A0);
  }
  else if (pin == 1){
    result = analogRead(A1);
  }
  else if (pin == 2){
    result = analogRead(A2);
  }
  else if (pin == 3){
    result = analogRead(A3);
  }
  else if (pin == 4){
    result = analogRead(A4);
  }
  else if (pin == 5){
    result = analogRead(A5);
  }

  return result;
}
