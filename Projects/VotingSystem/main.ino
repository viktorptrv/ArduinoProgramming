#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int ledOne = 8;
int ledTwo = 7;
int buttonOne = 2;
int buttonTwo = 3;
int touchSensor = 13;
int buttonPressedOne = 0x00;
int buttonPressedTwo = 0x00;
bool printMsg = false;

// init display library
LiquidCrystal_I2C lcd(0x27, 2, 16);

struct Leader{
  char party[50];
  char fName[25];
  char lName[25];
  int votes;
};

struct Leader arr[2] = {
  {"Idioacry", "Donald", "Trump", 0},
  {"DPS", "Delyan", "Prasov",0}
};

void printMessage(){
  if (printMsg == true){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Make your vote!");
    printMsg = false;
  }
}

void printChoice(){
  lcd.setCursor(0, 0);

  if (buttonPressedOne & 1){
    lcd.clear();
    lcd.print("Voted Donald!");
    digitalWrite(ledOne, HIGH);
    delay(400);
    digitalWrite(ledOne, LOW);
  }
  else if (buttonPressedTwo & 2){
    lcd.clear();
    lcd.print("Voted Shishi!");
    digitalWrite(ledTwo, HIGH);
    delay(400);
    digitalWrite(ledTwo, LOW);
  }
  buttonPressedOne = 0x00;
  buttonPressedTwo = 0x00;
  printMsg = true;
  delay(100);
}

void incrementPartyRigth(){
  digitalWrite(ledOne, HIGH);
  arr[0].votes++;
  buttonPressedOne = buttonPressedOne | 1;
}

void incrementPartyLeft(){
  digitalWrite(ledTwo, HIGH);
  arr[1].votes++;
  buttonPressedTwo = buttonPressedTwo | 2;
}

void setup() {
  Serial.begin(9600);

  int startMachine = 0;
  // put your setup code here, to run once:
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(buttonOne, INPUT_PULLUP);
  pinMode(buttonTwo, INPUT_PULLUP);
  pinMode(touchSensor, INPUT);

  // init display
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voting 2026 ");
  lcd.setCursor(0, 1);
  lcd.print("Press Sensor");

  while (startMachine == 0){
    if (digitalRead(touchSensor) == 1){
      startMachine = 1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Make your vote!");
    } 
  }
  
  attachInterrupt(digitalPinToInterrupt(buttonOne), incrementPartyRigth, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonTwo), incrementPartyLeft, RISING);

  lcd.setCursor(0, 0);
  lcd.print("Make your vote!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (arr[0].votes >= 10){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Idioacracy won...");
    delay(10000);
  }
  else if (arr[1].votes >= 10){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DPS won...");
    delay(10000);
  }
  printChoice();
  printMessage();
}
