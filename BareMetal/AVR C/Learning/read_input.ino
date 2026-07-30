#include <avr/io.h>
#include <util/delay.h>

volatile byte* pind_addr = 0x29;
volatile byte* ddrd_addr = 0x2A;
volatile byte* portd_addr = 0x2B;

void setup() {
  // put your setup code here, to run once:
  *ddrd_addr &= ~(1<<3);
  *portd_addr |= (1<<3);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte iRes;
  iRes = *pind_addr & (1<<3);
  if (*pind_addr & (1<<3)){
    Serial.println("0");
  }
  else{
    Serial.println("1");
  }
}
