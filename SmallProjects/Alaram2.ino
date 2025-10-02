/*Using a sound recognition module with arduino for making an alarm.*/

#define BUZZ 3
#define LED 6
#define sensIn 4

void setup(){
  pinMode(BUZZ, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(sensIn, INPUT);
  Serial.begin(115200);
}

void loop(){
  int count = 0;
  int sensRes;
  sensRes = digitalRead(sensIn);
  Serial.println(sensRes);
  if (sensRes == 1){
    while(count < 10){
      digitalWrite(LED, HIGH);
      tone(BUZZ, 2000);
      delay(150);
      digitalWrite(LED, LOW);
      noTone(BUZZ);
      delay(50);
      count++;
    }
  }
}
