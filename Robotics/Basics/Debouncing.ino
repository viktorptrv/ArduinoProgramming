#define button_pin 2
#define debounce_time 50

byte buttonState = HIGH;
byte lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

void handleButtonPress(void){
  Serial.print("Button has been pressed! Last Debounce time: ");
  Serial.println(lastDebounceTime);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(button_pin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int currentState = digitalRead(button_pin);
  if (currentState != buttonState){
    lastDebounceTime = millis();
  }
  if((millis()-lastDebounceTime) > debounce_time){
    currentState = digitalRead(button_pin);
    if (currentState != buttonState){
      lastButtonState = currentState;
      Serial.println("Debounced");
    }
    else{
      lastButtonState = buttonState;
    }
  }
}

