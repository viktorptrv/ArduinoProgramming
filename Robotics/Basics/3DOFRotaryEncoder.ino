#include <Servo.h>

Servo servos[5];
int pins[] = {3,5,6,9,10};

int servoIndex=0;

byte s1 = 11;
byte s2 = 12;
byte sw = 2;

int pos1 = 90;
int pos2 = 90;
int pos3 = 90;
int pos5 = 90;
int pos4 = 180;
int counter = 0;
int currentStateCLK, lastStateCLK;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 5; i++) servos[i].attach(pins[i]);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(sw, INPUT_PULLUP);
  lastStateCLK = digitalRead(s1);
  attachInterrupt(digitalPinToInterrupt(sw), servo_func, FALLING);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentStateCLK = digitalRead(s1);
  if (currentStateCLK != lastStateCLK){
    if (digitalRead(s2) == currentStateCLK){
      pos1--;
    }
    else{
      pos1++;
    }
    if (pos1 > 180){
      pos1 = 180;
    }
    else if (pos1 <= 0){
      pos1 = 0;
    }

    if (servoIndex == 1 || servoIndex == 2){
      servos[1].write(45+pos1);
      servos[2].write(135 - pos1);
    }
    Serial.print("Current pose -> ");
    Serial.print(pos1);
    Serial.print("    Current servo -> ");
    Serial.println(servoIndex);
    servos[servoIndex].write(pos1);
  }
  

  lastStateCLK = currentStateCLK;

  delay(1);
}

void servo_func(void){
  servoIndex++;
  if (servoIndex > 5){
    servoIndex = 0;
  }
}

