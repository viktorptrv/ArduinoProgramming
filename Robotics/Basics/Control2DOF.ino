// Basic Control of 2DOF arm
// i am using 4 buttons with input PULLUP

#include "Servo.h"

int btn_x = 2, btn_y = 3;
int btn_x_neg = 5, btn_y_neg = 4;
int servo_x_in = 9, servo_y_in = 10;
int pos_x = 0, pos_y = 0;

Servo servo_x;
Servo servo_y;

void setup(){
  servo_x.attach(servo_x_in);
  servo_y.attach(servo_y_in);
  pinMode(btn_x, INPUT_PULLUP);
  pinMode(btn_y, INPUT_PULLUP);
  pinMode(btn_x_neg, INPUT_PULLUP);
  pinMode(btn_y_neg, INPUT_PULLUP);
  Serial.begin(9600);

  // Always start each axis at 0;
  servo_x.write(125);
  servo_y.write(125);
}

void loop(){
  int x, y, x_neg, y_neg;
  x = digitalRead(btn_x);
  y = digitalRead(btn_y);
  x_neg = digitalRead(btn_x_neg);
  y_neg = digitalRead(btn_y_neg);

  if(x == 0){
    Serial.print("Moving X Axis, current position of x: ");
    pos_x++;
    if (pos_x >= 180)
      pos_x = 0;
    servo_x.write(pos_x);
    Serial.println(pos_x);
  }
  else if(y == 0){
    Serial.print("Moving Y Axis, current position of y: ");
    pos_y++;
    if (pos_y >= 180)
      pos_y = 0;
    servo_y.write(pos_y);
    Serial.println(pos_y);
  }
  else if(x_neg == 0){
    Serial.print("Moving X Axis, current position of x: ");
    pos_x--;
    if (pos_x <= 0)
      pos_x = 15;
    servo_x.write(pos_x);
    Serial.println(pos_x);
  }
  else if(y_neg == 0){
    Serial.print("Moving Y Axis, current position of y: ");
    pos_y--;
    if (pos_y == 0)
      pos_y = 15;
    servo_y.write(pos_y);
    Serial.println(pos_y);
  }
}
