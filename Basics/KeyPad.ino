#include <Key.h>
#include <Keypad.h>

char hexaKeys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[4] = {6,7,8,9};
byte colPins[4] = {2,3,4,5};

Keypad ckeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, 4, 4);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  char ch = ckeypad.getKey();
  Serial.print(ch);
  delay(1000);
}
