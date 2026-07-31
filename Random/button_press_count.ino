// NOT WORKING FOR NOW

#define button_pin 3
#define LED1 9
#define LED2 8
#define LED3 7

int old_state;
int turnLed = 0;
int presses = 0;
int state = 0;
unsigned long int timePassed = 0;
unsigned long int timePassed_oldState = 0;

void turn_led(int led_pin);

void setup() {
  // put your setup code here, to run once:
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(button_pin), change_stat, RISING);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(button_pin) & LOW){
    state = 1;
  }

  if (millis() - timePassed >= 5){
    if (digitalRead(button_pin) == LOW){
      Serial.print("Incrementing presses = ");
      Serial.println(presses);
      presses++;
      turnLed = 1;
    }
    else{
      old_state = 0;
      timePassed_oldState = millis();
      state = 0;
    }
    timePassed = millis();
  }


  if (millis() - timePassed_oldState >= 10){
    if (turnLed == 1){
      if (presses == 1){
        turn_led(LED1);
      }
      else if(presses == 2){
        turn_led(LED2);
      }
      else if (presses == 3){
        turn_led(LED3);
      }
      turnLed = presses = 0;
    }
  }
  
}

void turn_led(int led_pin){
  digitalWrite(led_pin, HIGH);
  delay(100);
  digitalWrite(led_pin, LOW);
}


