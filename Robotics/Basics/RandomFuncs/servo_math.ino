// DS3240 -> degree * 7.407407407407407 + 500 ; 500us = 0d, 1500us = 90d, 2500us = 270d
// MG996R -> degree * 11.11111111111111 + 500 ;500us = 0d, 1500us = 90d, 2500us = 180d

#include <Servo.h>

const float DSservo_us_per_degree = 7.407407407407407;
const float MGservo_us_per_degree = 11.11111111111111;

Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(10);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 270; i+= 5){
    float result = i * dsservo_us_per_degree + 500;
    Serial.print("Servo Microseconds -> ");
    Serial.println(result);
    servo.writeMicroseconds(result);
    if (result == 500 && result < 520)
      delay(1500);
    else
      delay(40);
  }
}
