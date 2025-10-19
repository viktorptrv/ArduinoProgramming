#include <Encoder.h>

// Defining pins
const byte redPin = 6;
const byte bluePin = 7;
const byte greenPin = 8;
const byte S1 = 2;
const byte S2 = 3;
const byte button = 4;
long oldPosition  = -999;

// Defining color values
int valRed = 0;
int valBlue = 0;
int valGreen = 0;
int currColor = 0;

int colors[] = {redPin, bluePin, greenPin};
int colorValues[] = {valRed, valBlue, valGreen};

Encoder myEnc(S1, S2);

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.println(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int butRes = digitalRead(button);
  
  if (currColor == 2 && butRes == 0)
    currColor = 0;
  else if (currColor < 2 && butRes == 0)
    currColor++;

  long position = myEnc.read();
  if (position != oldPosition){
    oldPosition = position;
      if (colorValues[currColor] == 255)
        colorValues[currColor] = 0;
    colorValues[currColor]++;
    analogWrite(colors[currColor], colorValues[currColor]);
  }
}
