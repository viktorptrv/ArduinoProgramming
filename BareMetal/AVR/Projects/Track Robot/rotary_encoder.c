#include <avr/io.h>
#include <util/delay.h>

#define ENC_IN_A    PB1
#define ENC_IN_B    PB2
#define ENC_IN_BTN  PB3
#define MAX_SPD     100
#define MIN_SPD     10

int8_t speed = MIN_SPD;

int main(void){
  uint8_t resA, old_resA, resB;
  Serial.begin(9600);
  DDRB &=~ ((1 << ENC_IN_A) | (1 << ENC_IN_B) | (1 << ENC_IN_BTN));

  while(1){
    resA = PINB & (1 << ENC_IN_A) ? 1:0;
    Serial.print("ResA = ");
    Serial.println(resA);
    resB = PINB & (1 << ENC_IN_B) ? 1:0;
    if (resA != old_resA){
      
      Serial.print("resB = ");
      Serial.println(resB);
      if ((resA == 1) && (resB == 0)){
        speed++;
      }
      else if ((resA == 0) && (resB == 1)){
        speed--;
      }
    }
    if (speed >= 100)
      speed = 100;
    else if(speed <= 0)
      speed = 0;
    old_resA = resA;
    
    Serial.print("Speed == ");
    Serial.println(speed);
    //_delay_ms(50);
  }
}
