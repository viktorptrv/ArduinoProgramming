int ledOne = 8;
int ledTwo = 7;

int buttonOne = 2;
int buttonTwo = 3;

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
  // put your setup code here, to run once:
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(buttonOne, INPUT_PULLUP);
  pinMode(buttonTwo, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonOne), incrementPartyRigth, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonTwo), incrementPartyLeft, RISING);
  Serial.begin(9600);
  Serial.println('Voting machine is starting!');
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
