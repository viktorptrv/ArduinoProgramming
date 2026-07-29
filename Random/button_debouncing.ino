#define button_pin 3
#define LED 9

void change_stat(void);
void readButton(void);

int turnLed = 0;
int state = 0;
unsigned long int timePassed = 0;
unsigned long int currentTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(button_pin), change_stat, RISING);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(button_pin) == LOW){
    state = 1;
  }
  if (state & 1){
    if(millis()-timePassed >=5){
      timePassed = millis();
    }
    if(digitalRead(button_pin) == LOW){
      turnLed = 1;
    }
    else{
      turnLed = 0;
      state = 0;
    }
  }
  if (turnLed == 1){
    digitalWrite(LED, HIGH);
    delay(10);
    digitalWrite(LED, LOW);
    turnLed = 0;
  }
}

void change_stat(void){
  state = !state;
}


