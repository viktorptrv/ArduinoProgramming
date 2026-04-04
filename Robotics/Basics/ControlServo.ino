// Basic servo control using a potentiometer.
// Scalling function takes analog input from the potentiometer and scales it to make it into degrees.

#include "Servo.h"

float pot_max = 1023, movement_max = 180;

int pot_input = A0;
int temp;
int res = 0;

Servo servo;

int calculate_movement(int analog_in);
int calculate_movement(int analog_in){
  int result = 0;
  float scalling_factor;

  scalling_factor = pot_max/movement_max;
  Serial.print("Scalling factor: ");
  Serial.println(scalling_factor);
  result = analog_in / scalling_factor;
  return result;
}

void setup(){
  servo.attach(6);
  Serial.begin(9600);
}

void loop(){
  int pos;
  pos = analogRead(pot_input);
  Serial.print("Analog input value: ");
  Serial.println(pos);
  delay(100);

  res = calculate_movement(pos);
  Serial.print("Current pos to go ");
  Serial.println(res);
  servo.write(res);
  delay(100);
}
