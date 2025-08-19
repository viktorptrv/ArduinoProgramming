void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode( 2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 2; i < 7; i++){
    if (i % 2 == 0){
      digitalWrite(2, HIGH);
      Serial.println("High");
      delay(1000);
      continue;
    }
    else {
      digitalWrite(2, LOW);
      Serial.println("LOW");
      delay(1000);
      continue;
    }
  }
  digitalWrite(2, LOW);
  delay(3000);

  for (int i = 2; i < 7; i++){
    if (i % 2 == 0){
      digitalWrite(2, HIGH);
      Serial.println("High");
      delay(3000);
      continue;
    }
    else{
      digitalWrite(2, LOW);
      Serial.println("LOW");
      delay(1000);
      continue;
    }
  }
  digitalWrite(2, LOW);
  delay(1000);

  for (int i = 2; i < 7; i++){
    if (i % 2 == 0){
      digitalWrite(2, HIGH);
      Serial.println("High");
      delay(1000);
      continue;
    }
    else {
      digitalWrite(2, LOW);
      Serial.println("LOW");
      delay(1000);
      continue;
    }
  }
  digitalWrite(2, LOW);
  Serial.println("End of SOS");
}
