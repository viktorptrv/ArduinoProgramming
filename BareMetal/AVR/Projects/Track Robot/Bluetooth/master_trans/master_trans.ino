#include <SoftwareSerial.h>

const byte rxPin = 10;
const byte txPin = 11;

SoftwareSerial blSerial (rxPin, txPin);

int state = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  blSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (blSerial.available() > 0){    // check if data is coming
    state = blSerial.read();        // reads the data
  }

  blSerial.write(state); // write data to the port
  state++;
  if (state > 3)
    state = 0;
  delay(500);
}
