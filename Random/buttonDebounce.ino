const int buttonPin = 3;
const int ledPin1 = 4;
const int ledPin2 = 5;
const int ledPin3 = 6;

int ledState = LOW;    // Current state of output pin
int buttonState;
int lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output 
int count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode (buttonPin, INPUT_PULLUP);
  pinMode (ledPin1, OUTPUT);
  pinMode (ledPin2, OUTPUT);
  pinMode (ledPin3, OUTPUT);

  digitalWrite(ledPin1, ledState);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState){
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay){
    if (reading != buttonState){
      buttonState = reading;
      if (buttonState == LOW){
        ledState = !ledState;
        count++;
      }
    }
  }

  if ((millis() - lastDebounceTime) > debounceDelay*3){
    if (count == 1){
      digitalWrite(ledPin1, ledState);
    }
    else if (count == 2){
      digitalWrite(ledPin2, ledState);
    }
    else if (count == 3){
      digitalWrite(ledPin3, ledState);
    }
    count = 0;
  }
  
  lastButtonState = reading;
}
