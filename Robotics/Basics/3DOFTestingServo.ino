#include <Servo.h>

Servo servo1, servo2, servo3, servo4, servo5;
int pos;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  servo5.attach(10);

  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(180);
  servo5.write(90);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (pos = 0; pos <= 90; pos++){
    servo1.write(pos);
    delay(50);
  }

  for(pos = 90; pos >= 0; pos--){
    servo1.write(pos);
    delay(50);
  }

  for(pos = 0; pos <= 90; pos++){
    servo2.write(45+pos);
    servo3.write(135-pos);
    delay(50);
  }

  for(pos = 0; pos <= 90; pos++){
    servo2.write(135-pos);
    servo3.write(45+pos);
    delay(50);
  }

  for(pos = 0; pos <= 90; pos++){
    servo4.write(pos);
    delay(50);
  }

  for(pos = 90; pos >= 0; pos--){
    servo4.write(pos);
    delay(50);
  }

  for(pos = 45; pos <= 135; pos++){
    servo5.write(pos);
    delay(50);
  }

  for(pos = 135; pos >= 45; pos--){
    servo5.write(pos);
    delay(50);
  }

}
