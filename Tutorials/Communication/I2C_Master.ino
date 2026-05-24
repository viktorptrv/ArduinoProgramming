#include <Wire.h>

#define SLAVE_ADDR 0x8
#define ANSWER_SIZE 5

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  delay(50);

  Serial.println("Write data to slave");

  // Write to slave
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0);
  Wire.endTransmission();

  Serial.println("Receive data:");

  // Read Response from slave
  Wire.requestFrom(SLAVE_ADDR, ANSWER_SIZE);

  // Add chars to string;
  String response = "";
  while(Wire.available()){
    char b = Wire.read();
    response += b;
  }

  Serial.println(response);
}
