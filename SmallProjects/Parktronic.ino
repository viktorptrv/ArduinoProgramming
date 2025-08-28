#define FarAway 10
#define Close 11
#define Closer 12
#define Alarming 13
#define Trig 4
#define Echo 5

int getdistance(void);
int getdistance(void){
  int duration, distance;
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = duration/58.1;
  return distance;
}

void setup(){
  pinMode(FarAway, OUTPUT);
  pinMode(Close, OUTPUT);
  pinMode(Closer, OUTPUT);
  pinMode(Alarming, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  Serial.begin(9600);
}

void loop(){
  int pin10Stat, pin11Stat, pin12Stat, pin13Stat;
  int distance;
Beginning:
  distance = getdistance();
  Serial.println(distance);
  if (distance > 25){
    digitalWrite(Alarming, LOW);
    delay(1000);
    digitalWrite(Closer, LOW);
    delay(1000);
    digitalWrite(Close, LOW);
    delay(1000);
    digitalWrite(FarAway, LOW);
    delay(1000);
    goto Beginning;
  }
  if (distance>=20 && distance <=25){
    digitalWrite(FarAway, HIGH);
    digitalWrite(Closer, LOW);
    digitalWrite(FarAway, LOW);
    digitalWrite(Close, LOW);
  }
  if (distance<20 && distance >= 15){
    digitalWrite(FarAway, HIGH);
    digitalWrite(Close, HIGH);
    digitalWrite(Closer, LOW);
    digitalWrite(FarAway, LOW);
  }
  if (distance < 15 && distance >6 ){
    digitalWrite(Closer, HIGH);
    digitalWrite(FarAway, HIGH);
    digitalWrite(Close, HIGH);
    digitalWrite(Alarming, LOW);
  }
  if (distance < 6){
    digitalWrite(Closer, HIGH);
    digitalWrite(FarAway, HIGH);
    digitalWrite(Close, HIGH);
    while (distance < 6){
      digitalWrite(Alarming, HIGH);
      delay(1000);
      digitalWrite(Alarming, LOW);
      delay(1000);
      distance = getdistance();
    }
  }
}
