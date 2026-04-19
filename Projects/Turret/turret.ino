#include "Servo.h"

int servoPin = 3;
int triggerPinSonic = 10;
int echoPinSonic = 2;
int servoPose = 0;

int backwardServo = 0x00;

Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
  pinMode(triggerPinSonic, OUTPUT);
  pinMode(echoPinSonic, INPUT);

  Serial.begin(9600);
  Serial.println("Initialising servo");
  delay(500);
  servo.write(servoPose);
  Serial.println("Servo is ready!");
}

void loop() {
  // put your main code here, to run repeatedly:
  float duration, distance;
  if (backwardServo & 1 == 1){
    servoPose -= 5;
    Serial.println("here 1");
  }
  else{
    servoPose += 5;
    Serial.println("here 2");
  }

  servo.write(servoPose);
  digitalWrite(triggerPinSonic, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPinSonic, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPinSonic, LOW);
  duration = pulseIn(echoPinSonic, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  if (servoPose > 180){
    backwardServo = 1;
    Serial.println("here 3");
  }
  else if (servoPose < 0){
    backwardServo = 0;
    Serial.println("here 4");
  }

}
