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
  recvWithEndMarker();
  showNewData();
}

void recvWithEndMarker(){
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while(Serial.available() > 0 && newData == false){
    rc = Serial.read();
    if (rc != endMarker){
      buffer[ndx] = rc;
      ndx++;
      if (ndx >= 255){
        ndx = 254;
      }
    }
    else{
      buffer[ndx] = '\0';
      ndx = 0;
      newData = true;
    }
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
