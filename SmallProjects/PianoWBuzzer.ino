#define BUT1 2
#define BUT2 3
#define BUT3 4
#define BUT4 5
#define BUT5 6
#define BUT6 7
#define BUT7 8
#define Buzz 10

int arrButtons[3] = {BUT1, BUT2, BUT3};
int arrSounds[3] = {100, 200, 400};

void sound(int Num);
void sound(int Num){
  int iRes = 1;
  while(iRes == 1){
    tone(Buzz, arrSounds[Num]);
    delay(1000);
    iRes = digitalRead(arrButtons[Num]);
  }
  noTone(Buzz);
}


void setup(){
  for (int i = 0; i < 3; i++)
    pinMode(arrButtons[i], INPUT);

  pinMode(Buzz, OUTPUT);
  digitalWrite(Buzz, LOW);
  Serial.begin(9600);
}

void loop(){
  int iRes;
  for (int i = 0; i < 3; i++){
    iRes = digitalRead(arrButtons[i]);
    Serial.println (iRes);
    Serial.print ("Button -> ");
    Serial.print (i);
    delay(1000);
    if (iRes == 1)
      sound(i);
  }
}
