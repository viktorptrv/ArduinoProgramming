int ledOne = 8;
int ledTwo = 7;

int buttonOne = 2;
int buttonTwo = 3;

int touchSensor = 13;

struct Leader{
  char party[50];
  char fName[25];
  char lName[25];
  int votes;
};

struct Leader arr[2] = {
  {"Idioacry", "Donald", "Trump", 0},
  {"DPS", "Delyan", "Prasov",0}
};

void incrementPartyRigth(){
  digitalWrite(ledOne, HIGH);
  arr[0].votes++;
  Serial.println("Vote for Donald has been accepted!");
  delay(100);
  digitalWrite(ledOne, LOW);
}

void incrementPartyLeft(){
  digitalWrite(ledTwo, HIGH);
  arr[1].votes++;
  Serial.println("Vote for Shishov has been accepted!");
  delay(100);
  digitalWrite(ledTwo, LOW);
}

void setup() {
  Serial.begin(9600);

  int startMachine = 0;
  // put your setup code here, to run once:
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(buttonOne, INPUT_PULLUP);
  pinMode(buttonTwo, INPUT_PULLUP);
  pinMode(touchSensor, INPUT);

  while (startMachine == 0){
    if (digitalRead(touchSensor) == 1){
      startMachine = 1;
      Serial.print("Voting machine is starting!");
    } 
  }
  
  attachInterrupt(digitalPinToInterrupt(buttonOne), incrementPartyRigth, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonTwo), incrementPartyLeft, RISING);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (arr[0].votes >= 10){
    Serial.println("Idioacracy won...");
  }
  else if (arr[1].votes >= 10){
    Serial.println("DPS won...");
  }
}
