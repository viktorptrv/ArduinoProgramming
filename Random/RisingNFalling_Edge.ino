#define interrupt_pin 3
#define LED 9

void change_stat(void);

volatile int stat = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(interrupt_pin, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), change_stat, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (stat == 1){
    digitalWrite(LED, HIGH);
    delay(1000);
    stat = 0;
    digitalWrite(LED, LOW);
  }
  
}

void change_stat(void){
  stat = 1;
}

