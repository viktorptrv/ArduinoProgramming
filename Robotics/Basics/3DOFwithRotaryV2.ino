// Does not work well, can't find the reason, probably something wrong with the encoder

#include <math.h>
#include <Servo.h>

Servo servoOne, servoTwo, servoThree, servoFour, servoFive; 

double linkOne = 48.0;
double linkTwo = 120.0;
double linkThree = 100.0;
double x = 120.0;
double y = 120.0;
double z = 120.0;
double c, d, Zoffset, theta;
double alphaOne, alphaTwo, alphaFinal;
double beta;
int claw = 90;
int dt = 11;
int clk = 12;
int sw = 2;
volatile int selector = 1;
int currentStateCLK, lastStateCLK;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servoOne.attach(3);
  servoTwo.attach(5);
  servoThree.attach(6);
  servoFour.attach(9);
  servoFive.attach(10);
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT_PULLUP);
  attachInterrupt(2, increment, FALLING);
  lastStateCLK = digitalRead(clk);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentStateCLK = digitalRead(clk);
  if (currentStateCLK != lastStateCLK){
    if (digitalRead(dt) == currentStateCLK){
      if (selector == 1){
        x -=5;
      }
      else if (selector == 2){
        y -=5;
      }
      else if (selector == 3){
        z -=5;
      }
      else if (selector == 4){
        claw -=5;
      }
    }
    else{
      if (selector == 1){
        x +=5;
      }
      else if (selector == 2){
        y +=5;
      }
      else if (selector == 3){
        z +=5;
      }
      else if (selector == 4){
        claw +=5;
      }
    }
  }

  d = sqrt((x*x) + (y*y));
  theta = atan2(y,x)*(180/PI);
  Zoffset = (z - linkOne);
  c = sqrt((d*d) + (Zoffset*Zoffset));
  beta = acos((linkTwo*linkTwo + linkThree*linkThree - c*c) / (2 * linkTwo * linkThree)) * (180 / PI);
  alphaOne = acos(d/c);
  alphaTwo = acos((linkTwo * linkTwo + c*c - linkThree * linkThree)/(2*linkTwo*c));

  if (z > linkOne){
    alphaFinal = (alphaOne + alphaTwo) * (180/PI);
  }
  else if (z < linkOne){
    alphaFinal = (alphaTwo - alphaOne) * (180/PI);
  }

  Serial.print(";   Theta: ");
  Serial.print(theta);
  Serial.print(";   Alpha: ");
  Serial.print(alphaFinal);
  Serial.print(";   Beta: ");
  Serial.println(beta);
  delay(100);
  servoOne.write(theta);
  servoTwo.write(alphaFinal);
  servoThree.write(180-alphaFinal);
  servoFour.write(beta);
  servoFive.write(claw);
  lastStateCLK = currentStateCLK;
  delay(100);
}

void increment(void){
  selector++;
  if (selector == 5)
    selector = 1;
}
