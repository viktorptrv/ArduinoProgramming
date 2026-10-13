#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define BT_UP      PD2
#define BT_DOWN    PD3
#define BT_LFT     PD4
#define BT_RGT     PD5
#define BT_MID     PD6
#define BT_SET     PD7
#define BT_RST     PB0      // Uses PORTB

uint8_t all_button_defines[7] = {BT_UP, BT_DOWN, 
                                 BT_LFT, BT_RGT, 
                                 BT_MID, BT_SET, BT_RST};

typedef struct button_track{
  uint8_t button_pin;
  uint8_t button_state;
  uint8_t last_button_state;
  unsigned long last_debounce_time;
} Button;

typedef struct _node{
  Button* button_node;
  struct _node *next;
  struct _node *prev;
}Node;

typedef struct _ll_circular{
  Node* head;
  Node* tail;
}LinkedList;

void init_buttons(void);
void init_list(LinkedList* ll);
void read_button(Button* btn);
void add_to_list(void);

void init_buttons(void){
  PORTB |= (1 << BT_RST);
  PORTD |= (1 << BT_UP) 
          | (1 << BT_DOWN) 
          | (1 << BT_LFT) 
          | (1 << BT_RGT) 
          | (1 << BT_MID) 
          | (1 << BT_SET) 
          | (1 << BT_RST);
}

void add_to_list(void){

}

void init_list(LinkedList* ll){
  for(int i = 0; i < 7; i++){
    add_to_list(LinkedList* ll,  all_button_defines[i]);
  }
}

void read_button(Button* btn){
  reading = PINB & (1 << BT_UP);
    if (reading != lastButtonState) {
        lastDebounceTime = millis(); // Record the time of this change
    }
     if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
        // Debounce time has passed, check if the state has stabilized
        if (reading != buttonState) {
            buttonState = reading; // Update the stable state

            if (buttonState == LOW) {
                // Button press is confirmed, take appropriate action
            }
        }
    }
}

int main(void){
  Serial.begin(9600);

  int reading;
  LinkedList* LL = (LinkedList*) malloc(sizeof(LinkedList));
  if (LL == NULL){
    Serial.println("Cannot allocate memory for linked list");
    return 0;
  }
  else{
    ll->head = NULL;
    ll->tail = NULL;
  }
  init_buttons();
  init_list(LinkedList* ll);
  Serial.println("Buttons initialised");
  while(1){
    
  }
}
