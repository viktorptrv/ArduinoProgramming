// Simple Traffic lights simulator

#define ledPRed 11
#define ledPGreen 12
#define ledCRed 8
#define ledCYellow 9
#define ledCGreen 10
#define Button 2

void pedestrians();
void cars();
void carsStop();

int arrLeds[] = {ledPRed, ledPGreen, ledCRed, ledCYellow, ledCGreen};
int isCRed = 0; // Variable to keep track of the status of the cars traffic lights
int isPRed = 0; // Variable to keep track of the status of the pedestrian traffic lights

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 5; i++)
    pinMode(arrLeds[i], OUTPUT);
  pinMode(Button, INPUT);
  Serial.begin(9600);
}

void cars(){
  digitalWrite(ledCRed, HIGH);
  isCRed = 1;
  delay(1500);
  digitalWrite(ledCYellow, HIGH);
  delay(2000);
  digitalWrite(ledCRed, LOW);
  delay(500);
  digitalWrite(ledCYellow, LOW);
  digitalWrite(ledCGreen, HIGH);
  isCRed = 0;
  delay(5000);
  digitalWrite(ledCYellow, HIGH);
  delay(2000);
  digitalWrite(ledCGreen, LOW);
  digitalWrite(ledCYellow, LOW);
  digitalWrite(ledCRed, HIGH);
}

void pedestrians(){
  delay(1000);
  digitalWrite(ledPRed, LOW);
  digitalWrite(ledPGreen, HIGH);
  isPRed = 0;
  delay(10000);
  digitalWrite(ledPGreen, LOW);
  digitalWrite(ledPRed, HIGH);
  isPRed = 1;
}

void carsStop(){
  digitalWrite(ledCYellow, HIGH);
  delay(1);
  digitalWrite(ledCGreen, LOW);
  digitalWrite(ledCYellow, LOW);
  digitalWrite(ledCRed, HIGH);
  isPRed = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  int mode;
  digitalWrite(ledPRed, HIGH);
  cars();
  pedestrians();
}
