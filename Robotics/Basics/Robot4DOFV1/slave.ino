// Does not work well, can't find the reason, probably something wrong with the encoder

#include <math.h>
#include <Servo.h>
#include <Wire.h>

#define SLAVE_ADDR 0x8

Servo servoOne, servoTwo, servoThree, servoFour, servoFive; 

double linkOne = 48.0;
double linkTwo = 120.0;
double linkThree = 100.0;
double x;
double y;
double z;
double c, d, Zoffset, theta;
double alphaOne, alphaTwo, alphaFinal;
double beta;

bool move = false;

char receive_string[20];

void setup() {
  // put your setup code here, to run once:
  Wire.begin(SLAVE_ADDR);
  Serial.begin(9600);
  servoOne.attach(3);
  servoTwo.attach(5);
  servoThree.attach(6);
  servoFour.attach(9);
  servoFive.attach(10);

  // Move Servos to initial;
  servoOne.write(90);
  servoTwo.write(90);
  servoThree.write(90);
  servoFour.write(180);

  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
}

void loop() {
  if (move == true){
    extract_values();

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
  delay(100);

  clean_string();
  move = false;
  }
}

void extract_values(void){
  sscanf(receive_string, "x=%d; y=%d; z=%d", &x, &y, &z);
}

void receiveEvent(void) {
  byte i = 0;
  while (Wire.available() && i < 19) {
    receive_string[i++] = Wire.read();
  }
  receive_string[i] = '\0';
  move = true; 
}

void clean_string(void){
  for(int i = 0; i < 20; i++){
    receive_string[i] = '\0';
  }
}
