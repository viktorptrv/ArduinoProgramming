const byte Buzz = 10;
// LEDs
const byte LED1 = 2;
const byte LED2 = 3;
const byte LED3 = 4;
const byte LED4 = 5;

// Buttons
const byte IN1 = 6;
const byte IN2 = 7;
const byte IN3 = 8;
const byte IN4 = 9;

// Buzzer tones
const int WRONG = 2000;
const int CORRECT = 500;

int arrLed[] = { LED1, LED2, LED3, LED4 };
int arrButtons[] = { IN1, IN2, IN3, IN4 };

void callBuzzer(int result);
void callBuzzer(int result) {
  if (result == 1) {
    tone(Buzz, CORRECT);
    delay(500);
    noTone(Buzz);
  } else {
    tone(Buzz, WRONG);
    delay(500);
    noTone(Buzz);
  }
}

int checkInput(int pinInput, int generatedLedPin);
int checkInput(int pinInput, int generatedLedPin) {
  Serial.println("calling Buzz");
  if (pinInput == generatedLedPin) {
    callBuzzer(1);
    return 1;
  } 
  else {
    callBuzzer(0);
    return -1;
  }
}

void generateArray(int *generate, int *genNumbers);
void generateArray(int *generate, int *genNumbers) {
  int num;
  for (int i = 0; i < 4; i++) {
    num = random(0, 4);
    generate[i] = arrLed[num];
    genNumbers[i] = num;
  }
}

void turnOnLEDS(int *generated);
void turnOnLEDS(int *generated) {
  for (int i = 0; i < 4; i++) {
    Serial.println("Turning on LED");
    Serial.println(i);
    digitalWrite(generated[i], HIGH);
    delay(100);
    digitalWrite(generated[i], LOW);
    delay(30);
  }
}

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(arrLed[i], OUTPUT);
    pinMode(arrButtons[i], INPUT);
  }
  pinMode(Buzz, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  bool result = 0;
  int ledCount = 0;
  int count, pressed_button;
  int arrGenerated[4];
  int arrGeneratedNumbers[4];
  int *ptrArrGenerated = arrGenerated;
  int *ptrArrGeneratedNumbers = arrGeneratedNumbers;

  generateArray(ptrArrGenerated, arrGeneratedNumbers);
  Serial.println("Generated array");
  turnOnLEDS(ptrArrGenerated);
  Serial.println("Turned onn leds");

  for (int ledCount = 0; ledCount < 4; ){
    for (int i = 0; i < 4; i++) {
      pressed_button = digitalRead(arrButtons[i]);
      Serial.println("Pressed button:");
      Serial.println(pressed_button);
      if (pressed_button == 1) {
        result = checkInput(i, arrGeneratedNumbers[ledCount]);
        Serial.println(result);
        delay(1000);
        if (result == 1)
          ledCount++;
        else{
          Serial.println("Breaking");
          delay(1000);
          break;
        }
      }
    }
  }
}
