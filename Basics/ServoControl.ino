#include <Servo.h>

unsigned long time_passed;
unsigned long timestep = 4000 / 90; // necessary period to reach 4s in 90 steps
Servo myservo;
int pos = 0;

void setup() {
  myservo.attach(9);
}
void loop() {
  time_passed = millis();
  for (pos = 0; pos <= 180; pos += 10) {
    myservo.write(pos);
    while ( millis() - time_passed < timestep) {
    }
    time_passed = time_passed + timestep; // this was time_passed = millis(); at testing, but this should be even more accurate. Hope I made no mistake, since I tested only the previous Version ;-)

  }

  for (pos = 180; pos >= 0; pos -= 10) {
    myservo.write(pos);
    while ( millis() - time_passed < timestep) {
    }
    time_passed = time_passed + timestep; // this was time_passed = millis(); at testing, but this should be even more accurate. Hope I made no mistake, since I tested only the previous Version ;-)
  }
}
