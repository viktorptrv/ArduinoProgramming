char receivedChar;
bool newData = false;
char buffer[255];
int idxBuf = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  // put your main code here, to run repeatedly:
  recvOneChar();
  showNewData();
}

void recvOneChar(){
  if (Serial.available() > 0){
    receivedChar = Serial.read();
    buffer[idxBuf++] = receivedChar;
    buffer[idxBuf] = '\0';
    newData = true;
  }
}

void showNewData(){
  if (newData == true){
    Serial.print("This just in ... ");
    for(int i = 0; i < 255; i++){
      if (buffer[i] != '\0')
        Serial.print(buffer[i]);
    }
    Serial.println();
    newData = false;
  }
}
