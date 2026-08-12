#include <avr/io.h>
#include <util/delay.h>

void init_port(void);
void init_timer(void);

void init_port(void){
  DDRD |= (1 << 3);
  PORTD |= (1 << 4);
}

void init_timer(void){
  TCCR1B |= (1 << CS11) | (1 << CS10);
}


int main(void){
unsigned char sreg;     // Used to save global interrupt flag
uint8_t button_result, button_state;
uint8_t prev_state = 1;
long int time, last_debounce = 0;
  Serial.begin(115200);
  init_port();
  init_timer();

  while(1){
    TCNT1 = 0;
    PORTD |= (1 << 3);
    while(1){
      button_result = PIND & (1 << 4);
      //Serial.println("Button_result = ");
     // Serial.println(button_result);
      if (button_result != prev_state){
        //Serial.println("last_debounce is set");
        last_debounce = TCNT1;
      }

      if ((TCNT1 - last_debounce) > 500){
        //Serial.println("time is bigger");
        if (button_result != button_state){
          //Serial.println("button_state is different");
          button_state = button_result;
          if (button_state == 0){
            //Serial.println("button is 0");
            break;
          }
        }
      }
      prev_state = button_result;
    }

    sreg = SREG;
    cli();
    PORTD &= ~(1 << 3); 
    Serial.print("TCNT1 = ");
    Serial.print(TCNT1);
    Serial.print("Time Passed: ");
    Serial.println(0.000004 * TCNT1);
    _delay_ms(500);
    SREG = sreg;
  }

  return 0;
}
