#include <avr/io.h>
#include <util/delay.h>

int set_bit_on(byte *addr, int bit);
int set_bit_off(byte *addr, int *bit);

volatile byte* ddrb_addr = 0x24;
volatile byte* ddrd_addr = 0x2A;
volatile byte* portb_addr = 0x25;
volatile byte* portd_addr = 0x2B;

const byte bitNumber[7] = {0,1,2,4,5,6,7};

void setup() {
  // put your setup code here, to run once:
  set_bit_on(ddrb_addr, 1 | (1<<1) | (1<<2));       // set bit on port B

  set_bit_on(ddrd_addr, (1<<4) | (1<<5) | (1<<6) | (1<<7));  // set bit on port D
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int* pvalue_for_off;
  int value_off, value_on;

  for(int i = 0; i < 7; i++){
    if (i < 3){
      set_bit_on(portb_addr, (1<<bitNumber[i]));
    }
    else{
      value_on= (1<<bitNumber[i]);
      set_bit_on(portd_addr, value_on);
    }
    delay(1000);
  }

  for (int i = 6; i > -1; i--){
    if (i < 3){
      Serial.println("Turning oFF portB");
      value_off = (1<<bitNumber[i]);
      pvalue_for_off = &value_off;
      set_bit_off(portb_addr, pvalue_for_off);
    }
    else{
      Serial.println("Turning oFF portD");
      value_off= (1<<bitNumber[i]);
      pvalue_for_off = &value_off;
      Serial.print("Value for off:");
      Serial.println(*pvalue_for_off);
      set_bit_off(portd_addr, pvalue_for_off);
    }
    Serial.print("OFF Cycle #");
    Serial.println(i);
    delay(1000);
  }
}

int set_bit_on(byte *addr, int bit){
  if (addr == NULL){
    return 0;
  }
  Serial.print("set_bit_on: bit = ");
  Serial.println(bit);
  *addr |= bit;
  Serial.print("set_bit_on: address is set as = ");
  Serial.println(*addr);
  return 1;
}

int set_bit_off(byte *addr, int *bit){
  if (addr == NULL){
    return 0;
  }

  if (bit == NULL){
    *addr &= 0;
    return 1;
  }

  *addr &= ~ (*bit);
}
