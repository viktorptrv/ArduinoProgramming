#include <Servo.h>

#define ServoPIN 8

Servo servo;

int curPose = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(ServoPIN);
  servo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sens1 = analogRead(A3);
  int sens2 = analogRead(A4);
  int sens3 = analogRead(A5); 

  if (sens1 < 555 && sens2 < 555 && sens3 < 555){
    servo.write(90-curPose);
    curPose = 90;
  }
  else{
    if (sens1 < 555 && sens2 < 555){
      curPose+=20;
      servo.write(curPose);
      
    }
    else if (sens2 < 555 && sens3 < 555){
      curPose+=20;
      servo.write(120-curPose);
    }
    else if (sens1 < 555 && sens2 > 555 && sens3 > 555){
      curPose-=10;
      servo.write(0);
      curPose = 0;
    }
    else if (sens1 > 555 && sens2 < 555 && sens3 > 555){
      curPose-=10;
      servo.write(90-curPose);
      curPose = 90;
    }
    else if (sens1 > 555 && sens2 > 555 && sens3 < 555){
      servo.write(180);
      curPose = 180;
    }
  }



  delay(1000);
}
