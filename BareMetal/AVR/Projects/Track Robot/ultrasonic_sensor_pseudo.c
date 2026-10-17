// HC SR04 
#define TRG_PIN 7
#define ECHO_PIN 8

void setup() {
  // put your setup code here, to run once:
  pinMode(TRG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t timer_start;
  uint32_t timer_end;
  uint32_t total_time;
  uint16_t dist;

  Serial.println("Starting measurement");
  digitalWrite(TRG_PIN, LOW);
  delayMicroseconds(20);
  digitalWrite(TRG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRG_PIN, LOW);
  while(digitalRead(ECHO_PIN) == 0);
  timer_start = micros();
  Serial.print("Timer start at = ");
  Serial.println(timer_start);
  while(digitalRead(ECHO_PIN) & 1);
  timer_end = micros();
  Serial.print("Timer end at = ");
  Serial.println(timer_end);
  dist = timer_end - timer_start;
  Serial.print("DistA = ");
  Serial.println(dist);
  //dist = pulseIn(ECHO_PIN, HIGH);
  // Calculate the distance:
  dist = dist * 0.034 / 2;

  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("Distance = ");
  Serial.print(dist);
  Serial.println(" cm");
  delay(100);
}
