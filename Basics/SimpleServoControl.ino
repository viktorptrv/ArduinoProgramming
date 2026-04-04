#include "Servo.h"
// Servo PWM Pin
Servo servo_one;
int btn_left, btn_right;
int pos = 0;

void setup(){
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  servo_one.attach(6);
  servo_one.write(0);
}

void loop(){
  btn_left = digitalRead(2);
  btn_right = digitalRead(4);
  if (btn_left == 0){
    Serial.println("Button 1 has been pressed.");
    pos -= 1;
    if (pos <= 0)
      pos = 45;
    servo_one.write(pos);
    delay(100);
  }
  else if(btn_right == 0){
    Serial.println("Button 2 has been pressed.");
    pos+=1;
    if (pos >= 180)
      pos = 45;
    servo_one.write(pos);
    delay(100);
  }
  Serial.println("Current pos: ");
  Serial.print(pos);
  delay(100);
}
