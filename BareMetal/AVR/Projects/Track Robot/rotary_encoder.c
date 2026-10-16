// used for help this article
// https://www.instructables.com/Improved-Arduino-Rotary-Encoder-Reading/

#include <avr/io.h>
#include <util/delay.h>

#define ENC_IN_A    PD2       // INT0
#define ENC_IN_B    PD3       // INT1
#define MAX_SPD     100       // this is in %
#define MIN_SPD     0         // this is in %
#define PINS_HIGH   B00001100 
#define EXP_A       B00000100
#define EXP_B       B00001000

int8_t speed = MIN_SPD;
volatile int8_t aFlag = 0;
volatile int8_t bFlag = 0;
volatile int8_t encPos = 0;
volatile int8_t oldEncPos = 0;
volatile int8_t reading = 0;

void init_pins(void);
void init_interrupts(void);

void init_pins(void){
  DDRD &=~ (1 << ENC_IN_A) | (1 << ENC_IN_A);
  PORTD |= (1 << ENC_IN_A) | (1 << ENC_IN_A);
}

void init_interrupts(void){
  EICRA |= (1 << ISC11) | (1 << ISC10);
  EICRA |= (1 << ISC01) | (1 << ISC00);
  EIMSK |= (1 << INT1) | (1 << INT0);
  sei();
}

ISR(INT0_vect){
  reading = PIND & 0xC;
  if (reading == PINS_HIGH && aFlag){
    encPos--;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == B00000100)
    bFlag = 1;
}

ISR(INT1_vect){
  reading = PIND & 0xC;
  if (reading == PINS_HIGH && bFlag){
    encPos++;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == B00001000)
    aFlag = 1;
}

int main(void){
  Serial.begin(115200);
  init_pins();
  init_interrupts();

  while(1){
    Serial.print("EncPos = ");
    Serial.println(encPos);
    if (oldEncPos != encPos){
      Serial.println(encPos);
      oldEncPos = encPos;
    }
    _delay_ms(300);
  }
}
