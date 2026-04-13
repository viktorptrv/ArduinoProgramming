#include <string.h>
#include <ctype.h>

#define LED 9
// 0 means short, 1 means long, null if there is no morse
int alphabet[][4] = {
  {0, 1, NULL, NULL}, //A
  {1, 0, 0, 0}, //B
  {1, 0, 1, 0}, //C
  {1, 0, 0, NULL}, //D
  {0, NULL, NULL, NULL}, //E
  {0, 0, 1, 0}, //F
  {1, 0, NULL, NULL}, //G
  {0, 0, 0, 0}, //H
  {0, 0, NULL, NULL}, //I
  {0, 1, 1, 1}, //J
  {1, 0, 1}, //K
  {0, 1, 0, 0}, //L
  {1, 1, NULL, NULL}, //M
  {1, 0, NULL, NULL}, //N
  {1, 1, 1, NULL}, //O
  {0, 1, 1, 0}, //P
  {1, 1, 0, 1}, //Q
  {0, 1, 0, NULL}, //R
  {0, 0, 0, NULL}, //S
  {1, NULL, NULL, NULL}, //T
  {0, 0, 1, NULL}, //U
  {0, 0, 0, 1}, //V
  {0, 1, 1, NULL}, //W
  {1, 0, 0, 1}, //X
  {1, 0, 1, 1}, //Y
  {1, 1, 0, 0}
};

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char str[] = "Hello World";
  for(int i = 0; i < strlen(str); i++){
    Serial.println(str[i]);
    for (int j = 0; j < 4; j++){
      Serial.println(j);
      if (alphabet[toupper(str[i])-65][j] & 1){
        digitalWrite(LED, HIGH);
        delay(300);
        digitalWrite(LED, LOW);
      }
      else if (alphabet[str[i]-65][j] == 0){
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
      }
      
      delay(300);
    }
  }
}
