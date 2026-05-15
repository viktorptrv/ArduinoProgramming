#include <math.h>
#include <Servo.h>

Servo servo1, servo2;

int x_max = 100;
int y_max = 180;

double x;
double y;
double linkOne = 100.0, linkTwo = 100.0;
double alphaOne, alphaTwo, alphaFinal;
double betaOne, betaTwo, betaFinal;
double c, d = 60.0, e;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(3);
  servo2.attach(5);
}

void loop() {
  int xRead, yRead;

  xRead = analogRead(A0);
  yRead = analogRead(A2);

  x = map(xRead, 0, 1023, 0, x_max);
  y = map(yRead, 0, 1023, 0, y_max);
  
  // put your main code here, to run repeatedly:
  c = sqrt((x*x) + (y*y));
  e = sqrt(((d-x) * (d-x)) + (y*y));

  alphaOne = atan(y/x) * (180/PI);
  alphaTwo = acos(((linkTwo * linkTwo) - (c*c) - (linkOne * linkOne)) / (-2 * linkOne * c)) * (180/PI);
  betaOne  = atan(y/(d-x)) * (180/PI);
  betaTwo  = acos(((linkTwo * linkTwo) - (e*e) - (linkOne * linkOne)) / (-2 * linkOne * e)) * (180 / PI);
  
  if (x < 0){
    alphaFinal = 180 + ((alphaOne) + (alphaTwo));
    betaFinal = 180 - (betaOne + betaTwo);
  }
  else if (x > d){
    alphaFinal = alphaOne + alphaTwo;
    betaFinal = -1 * (betaOne + betaTwo);
  }
  else{
    alphaFinal = alphaOne + alphaTwo;
    betaFinal = 180 - (betaOne + betaTwo);
  }

  Serial.print("alpha one -> ");
  Serial.println(alphaOne);

  Serial.print("alpha two -> ");
  Serial.println(alphaTwo);

  Serial.print("alpha final -> ");
  Serial.println(alphaFinal);

  Serial.print("Beta one -> ");
  Serial.println(betaOne);

  Serial.print("Beta Two -> ");
  Serial.println(betaTwo);

  Serial.print("Beta final -> ");
  Serial.println(betaFinal);

  Serial.print("alpha one -> ");
  Serial.println(alphaOne);

  servo2.write(alphaFinal);
  servo1.write(betaFinal);
}
