#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);                    // Set address of 8
  Wire.onReceive(receiveEvent);     // interrupt request event
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void receiveEvent(int howMany){
  while(1 < Wire.available())   // loop through all but last
  {
    char c = Wire.read();
    Serial.println(c);
  }

  int x = Wire.read()   ;
  Serial.println(x);
}
