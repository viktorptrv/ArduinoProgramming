#include "Servo.h"
#include "math.h"

int servo_x_in = 9, servo_y_in = 10;
double pos_x = 0, pos_y = 0;
double length_b = 100, length_a = 100;

Servo servo_x;
Servo servo_y;

double calculate_theta_c(double x, double y);
double calculate_theta_a(double x, double y);

void setup(){
  servo_x.attach(servo_x_in);
  servo_y.attach(servo_y_in);
  Serial.begin(9600);

  // Always start each axis at 0;
  servo_x.write(125);
  servo_y.write(125);
}

void loop(){  
  pos_x = 150.0;
  pos_y = 160.0;
  double theta_A = calculate_theta_a(pos_x, pos_y);
  Serial.print("Theta A:");
  Serial.println(theta_A);
  double theta_C = calculate_theta_c(pos_x, pos_y);
  Serial.print("Theta C:");
  Serial.println(theta_C);
  servo_x.write(theta_A);
  servo_y.write(theta_C);
}

double calculate_theta_c(double x, double y){
  double dist2 = x*x + y*y;

  double term = (dist2 - length_a*length_a - length_b*length_b) /
                (-2.0 * length_a * length_b);

  // clamp for acos safety
  if (term > 1.0) term = 1.0;
  if (term < -1.0) term = -1.0;

  double result = acos(term);
  result = result * (180.0 / M_PI);

  return result;
}

double calculate_theta_a(double x, double y){
  double dist = sqrt(x*x + y*y);

  double term = (length_b - length_a*length_a - dist*dist) /
                (-2 * length_a * dist);

  // clamp to avoid acos domain errors
  if (term > 1) term = 1;
  if (term < -1) term = -1;

  double result = atan2(y, x) + acos(term);

  result = result * (180.0 / M_PI);

  return result;
  
}
