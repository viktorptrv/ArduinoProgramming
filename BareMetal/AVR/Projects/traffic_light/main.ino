// Simulating State machine

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

const uint8_t led_red = 0;      // PB0
const uint8_t led_yellow = 1;   // PB1
const uint8_t led_green = 2;    // PB2
const uint8_t red_state     = 0x0001;
const uint8_t green_state   = 0x0002;
const uint8_t yellow_state  = 0x0003;
volatile uint8_t current_state = red_state;
volatile uint8_t prev_state;      // variable is used to track previous state of traffic light
volatile long long int time_passed = 0;
volatile double past_change = 0.0;

static inline uint8_t change_state(void);
static inline uint8_t change_state(void){
  double current_time = get_time();
  if (current_state & red_state){
    Serial.println("Current state is red");
    if (current_time - past_change > 10){
      Serial.println("Turning off RED");
      past_change = get_time();
      prev_state = current_state;
      current_state = green_state;
      return 1;
    }
  }
  else if (current_state & green_state){
    Serial.println("Current state is GREEN");
    if (current_time - past_change > 10){
      Serial.println("Turning off GREEN");
      past_change = get_time();
      prev_state = current_state;
      current_state = red_state;
      return 1;
    }
  }
  return 0;
}

static inline void turn_on_yellow_led(void);
static inline void turn_on_yellow_led(void){
  PORTB = 0;
  _delay_ms(10);
  PORTB |= (1 << led_yellow);
  _delay_ms(100);
  PORTB = 0;
}

static inline void turn_on_led(uint8_t led);
static inline void turn_on_led(uint8_t led){
  PORTB = 0;
  _delay_ms(50);
  PORTB |= (1 << led);
}

static inline void turn_led(void);
static inline void turn_led(void){
  switch(current_state){
    case red_state:
      turn_on_led(led_red);
      break;
    case yellow_state:
      turn_on_yellow_led();
      break;
    case green_state:
      turn_on_led(led_green);
      break;
    default:
      break;
  }
}

static inline void init_io(void);
static inline void init_io(void){
  DDRB |= (1 << led_red) | (1 << led_yellow) | (1 << led_green);
  PORTB |= (1 << led_red) | (1 << led_yellow) | (1 << led_green); // Turn them on for a bit just to signal
  _delay_ms(100);
  PORTB = 0;
}

static inline void init_timer(void);
static inline void init_timer(void){
  TCCR0A |= (1 << WGM01);         // Set CTC Mode of timer;
  TCCR0B |= (1 << CS02) | (1 << CS00);    // Set prescaler to 1024
  TIMSK0 |= (1 << OCIE0A);        // Set timer interrupt match compare
  OCR0A = 255;
  sei();                          // turn on interrupts!!!
}

static inline double get_time(void){
  double result;
  long long int timer;
  char cSREG;
  cSREG = SREG;
  cli();
  timer = time_passed;
  SREG = cSREG;
  result = (double) timer / 1000000.0 ;
  Serial.print("Current timer: ");
  Serial.println(result);
  return result;
}

ISR(TIMER0_COMPA_vect){
  time_passed += 16384;
}

int main(void){
  uint8_t is_change_state = 0;    // Used to check if we have to change the state;
  // Initialising
  Serial.begin(9600);
  init_io();
  init_timer();

  // Start with red light:
  turn_on_led(led_red);

  // infinite while loop
  while(1){
    is_change_state = change_state();
    if (is_change_state == 1){
      turn_on_yellow_led();
      turn_led();
    }
  }
  return 0;
}
