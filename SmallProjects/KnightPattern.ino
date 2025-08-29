// Knight Pattern More Optimised code

#define BUTTON 2
#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6
#define LED5 7
#define LED6 8
#define LED7 9
#define LED8 10
#define LED9 11
#define LED10 12
#define LED11 13

int ledArr[11] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11};

void knightPattern();
void knightPattern(){
  for (int i = 0; i <11; i++){
    digitalWrite(ledArr[i], HIGH);
    delay(50);
    digitalWrite(ledArr[i], LOW);
  }
  Serial.println("Go back");
  for (int i = 10; i >= 0; i--){
    digitalWrite(ledArr[i], HIGH);
    delay(50);
    digitalWrite(ledArr[i], LOW);
  }
}

void setup(){
  for (int i = 0; i < 11; i++){
    pinMode(ledArr[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop(){
  int mode = 0;
  digitalRead(BUTTON);
  Serial.println(BUTTON);
  knightPattern();

}
