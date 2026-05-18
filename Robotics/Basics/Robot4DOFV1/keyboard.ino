volatile bool sendPos = false;
volatile bool manualPos = false;
byte send_butt = 2;
byte mode_butt = 3;
byte NegativeZ = 4;
byte PositiveZ = 5;
byte NegativeY = 6;
byte PositiveY = 7;
byte NegativeX = 8;
byte PositiveX = 9;
int PosX = 0; int PosY = 0; int PosZ = 0;

byte allButtons[8] = {send_butt, mode_butt, NegativeZ,
                     PositiveZ, NegativeY, PositiveY,
                     NegativeX, PositiveX};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 8; i++){
    pinMode(allButtons[i], INPUT_PULLUP);
  }

  attachInterrupt(digitalPinToInterrupt(send_butt), send_command, FALLING);
  attachInterrupt(digitalPinToInterrupt(mode_butt), change_mod, FALLING);
  Serial.begin(9600);
  Serial.println("Arduino is starting");
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(NegativeZ) == LOW){
    if (PosZ > 0){
      PosZ--;
      Serial.print("Negative Z -> ");
      Serial.println(PosZ);
      delay(125);
    }
  }
  if (digitalRead(NegativeY) == LOW){
    if (PosY > 0){
      PosY--;
      Serial.print("Negative Y -> ");
      Serial.println(PosY);
      delay(125);
    }
  }
  if (digitalRead(NegativeX) == LOW){
    if (PosX > 0){
      PosX--;
      Serial.print("Negative X -> ");
      Serial.println(PosX);
      delay(125);
    }
  }
  if (digitalRead(PositiveZ) == LOW){
    if (PosZ < 180){
      PosZ++;
      Serial.print("Positive Z -> ");
      Serial.println(PosZ);
      delay(125);
    }
  }
  if (digitalRead(PositiveY) == LOW){
    if (PosY < 180){
      PosY++;
      Serial.print("Positive Y -> ");
      Serial.println(PosY);
      delay(125);
    }
  }
  if (digitalRead(PositiveX) == LOW){
    if (PosX < 180){
      PosX++;
      Serial.print("Positive X -> ");
      Serial.println(PosX);
      delay(125);
    }
  }

  if (sendPos == true || manualPos == true){
    send_position_to_robot();
    delay(200);
  }
}

void send_command(void){
  sendPos = !sendPos; // flip bool value
}

void change_mod(void){
  manualPos = !manualPos; // flip bool value
}

void send_position_to_robot(void){
  Serial.println("Robot Pos Function called");
  sendPos = !sendPos;
}
