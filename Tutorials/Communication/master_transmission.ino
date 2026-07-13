
#include <Wire.h>

void setup() {
  Wire.begin();               // join i2c bus (address optional for master)
  Serial.begin(9600);         // start serial for output
}

byte x = 0;

void loop() {
  Wire.beginTransmission(8);
  Wire.write("x is ");
  Wire.write(x);
  Wire.endTransmission();
  x++;
  delay(500);
}
