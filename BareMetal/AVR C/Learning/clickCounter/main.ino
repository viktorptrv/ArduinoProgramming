#include <avr/io.h>
#include <util/delay.h>

#define PIN3 (1 << 3)

int clickCount = 0;
byte currentState, prevState = 0;
long long int timePassed, currentTime;
const byte LED_PIN = 4;
volatile int* addr_DDRD = 0x2A;
volatile int* addr_PORTD = 0x2B;
volatile int* addr_PIND = 0x29;

void setup_pins(void){
  *addr_DDRD |= (1 << 4);
  *addr_PORTD |= PIN3; // configure pin 3 to be a pull up
}

int main(void){
  // variables
  Serial.begin(9600);
  // setup pins;
  setup_pins();

  // main loop
  while(1){
    currentState = *addr_PIND & PIN3;
    Serial.print("Debug Message: currentState = ");
    Serial.println(currentState);
    currentTime = millis();
    if (currentState == 0){
      if ((millis() - currentTime) > 50){
        currentState = *addr_PIND & PIN3;
        Serial.println("Debounced time passed");
        if (currentState == prevState){
          clickCount += 1;
          timePassed = millis();
        } 
        else{
          clickCount = 0;
        }
      }
    }

    if (clickCount == 3){
      *addr_PORTD |= (1 << LED_PIN);
      _delay_ms(150);
      *addr_PORTD &= 0;
    }
  }

  return 0;
}
