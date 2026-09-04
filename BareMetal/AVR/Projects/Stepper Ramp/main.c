// Controlling stepper motor through ULN2003 

#include <avr/io.h>
#include <util/delay.h>

#define half_step_mode 4095
#define full_step_mode 2047
#define ramp_steps 10

volatile const uint8_t delay_fast = 1;
volatile const uint8_t delay_slow = 5;

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
volatile uint16_t step_counter = 0;
volatile uint16_t current_step = 0;

static inline void move_stepper(uint16_t num_of_steps, int delay);
static inline void move_stepper(uint16_t num_of_steps, int delay){
  while(num_of_steps != 0){
    if (current_step == 8)
      current_step = 0;
    PORTD |= motor_step_array_half_step_mode[current_step];
    if (delay == delay_fast)
      _delay_ms(1);
    else
      _delay_ms(5);
    PORTD = 0;
    current_step++;
    num_of_steps--;
    step_counter++;
  }
}

static inline void take_step(uint16_t num_of_steps);
static inline void take_step(uint16_t num_of_steps){
  uint8_t direction;
  uint16_t current_steps_taken =0 ;

  if (num_of_steps >= 0){
    direction = 1;
  }
  else{
    direction = 0;
    num_of_steps = -num_of_steps;
  }

  if (num_of_steps > ramp_steps){
    move_stepper(ramp_steps, delay_slow);
    current_steps_taken += ramp_steps;
  }

  move_stepper((num_of_steps - (ramp_steps * 2)), delay_fast);
  current_steps_taken += num_of_steps - (ramp_steps * 2);
  if (current_steps_taken < num_of_steps){
    move_stepper((num_of_steps - current_steps_taken), delay_slow);
  }
}

int main(void){
  int step_count = 0;
  uint8_t mode = 0;       // 0 for full one phase, 1 for 2 phase, 2 for half
  bool forward;
  int num ;

  DDRD = (1 << PD1) | (1 << PD2) | (1 << PD3) | (1 << PD4);
  while(1){ 
    take_step(100);
  }
}
