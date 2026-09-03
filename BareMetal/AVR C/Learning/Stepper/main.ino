// Controlling stepper motor through ULN2003 

#include <avr/io.h>
#include <util/delay.h>

#define half_step_mode 4095
#define full_step_mode 2047

const uint8_t motor_step_array_half_step_mode[8] = {
    (1 << PD2) | (1 << PD3) | (1 << PD4),
    (1 << PD3) | (1 << PD4),
    (1 << PD1) | (1 << PD3) | (1 << PD4),
    (1 << PD1) | (1 << PD4),
    (1 << PD1) | (1 << PD2) | (1 << PD4),
    (1 << PD1) | (1 << PD2),
    (1 << PD1) | (1 << PD2) | (1 << PD3),
    (1 << PD2) | (1 << PD3)
};

// One phased
const uint8_t motor_step_array_full_step_mode[4] = {      
    (1 << PD1),
    (1 << PD2),
    (1 << PD3),
    (1 << PD4)
};

// Two Phased full step
const uint8_t motor_step_array_full_step_mode2[4] = {      
    (1 << PD1 | (1 << PD2)),
    (1 << PD2 | (1 << PD3)),
    (1 << PD3 | (1 << PD4)),
    (1 << PD4 | (1 << PD1))
};

int main(void){
  int step_count = 0;
  uint8_t mode = 0;       // 0 for full one phase, 1 for 2 phase, 2 for half
  bool forward;
  int num ;

  DDRD = (1 << PD1) | (1 << PD2) | (1 << PD3) | (1 << PD4);
  while(1){
    if (mode == 0){
      if (step_count == half_step_mode ){
        forward = 0;
      }

      if (step_count == 0){
        forward = 1;
      }

      if (forward == 1){
        for(int i = 0; i < 8; i++){
          PORTD = motor_step_array_half_step_mode[i];
          _delay_ms(1);
          PORTD = 0;
          step_count ++;
          if (step_count == half_step_mode ){
            break;
          }
        }
      }
      else{
        for(int i = 7; i >= 0; i--){
          num = motor_step_array_half_step_mode[i];
          PORTD = num;
          _delay_ms(1);
          PORTD = 0;
          step_count --;
          if (step_count == 0){
            mode = 0;
            break;
          }
        }
      }
    }

    // Start one phased
    else if (mode == 1){
      Serial.println("Mode 1");
      if (step_count == full_step_mode ){
        forward = 0;
      }

      if (step_count == 0){
        forward = 1;
      }

      if (forward == 1){
        for(int i = 0; i < 4; i++){
          PORTD |= motor_step_array_full_step_mode[i];
          _delay_ms(1);
          PORTD = 0;
          step_count ++;
          if (step_count == full_step_mode ){
            break;
          }
        }
      }
      else{
        for(int i = 4; i >= 0; i--){
          PORTD |= motor_step_array_full_step_mode[i];
          _delay_ms(1);
          PORTD = 0;
          step_count --;
          if (step_count == 0){
            mode = 2;
            break;
          }
        }
      }
    }

    else if (mode == 2){
      Serial.println("Mode 2");
      if (step_count == full_step_mode ){
        forward = 0;
      }

      if (step_count == 0){
        forward = 1;
      }

      if (forward == 1){
        for(int i = 0; i < 4; i++){
          PORTD |= motor_step_array_full_step_mode[i];
          _delay_ms(1);
          PORTD = 0;
          step_count ++;
          if (step_count == full_step_mode ){
            break;
          }
        }
      }
      else{
        for(int i = 4; i >= 0; i--){
          PORTD |= motor_step_array_full_step_mode[i];
          _delay_ms(1);
          PORTD = 0;
          step_count --;
          if (step_count == 0){
            mode = 0;
            break;
          }
        }
      }
    } 
    
  }
}
