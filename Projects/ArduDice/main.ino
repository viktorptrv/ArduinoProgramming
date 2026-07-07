#include <FastLED.h>
#include <stdio.h>

#define NUM_LEDS 64
#define LED_PIN 3

const int careful[64]       = {0,0,0,1,1,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,1,1,0,0,0};
const int matrix_one[64]    = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
const int matrix_two[64]    = {1,1,0,0,0,0,0,0, 1,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,1, 0,0,0,0,0,0,1,1};
const int matrix_three[64]  = {1,1,0,0,0,0,0,0, 1,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,1, 0,0,0,0,0,0,1,1};
const int matrix_four[64]   = {1,1,0,0,0,0,1,1, 1,1,0,0,0,0,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,0,0,0,0,1,1, 1,1,0,0,0,0,1,1};
const int matrix_five[64]   = {1,1,0,0,0,0,1,1, 1,1,0,0,0,0,1,1, 0,0,0,0,0,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,0,0,0,0,0, 1,1,0,0,0,0,1,1, 1,1,0,0,0,0,1,1};
const int matrix_six[64]    = {1,1,0,0,0,0,1,1, 1,1,0,0,0,0,1,1, 0,0,0,0,0,0,0,0, 1,1,0,0,0,0,1,1, 1,1,0,0,0,0,1,1, 0,0,0,0,0,0,0,0, 1,1,0,0,0,0,1,1, 1,1,0,0,0,0,1,1};

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  turn_leds(NULL);
  turn_leds(matrix_one);
  turn_leds(matrix_two);
  turn_leds(matrix_three);
  turn_leds(matrix_four);
  turn_leds(matrix_five);
  turn_leds(matrix_six);
}

void turn_leds(int *arr){
CRGB colour;
  if (arr == NULL){
    Serial.println("Careful");
    arr = careful;
    colour = CRGB::Red;
  }
  else{
    colour = CRGB::Blue;
  }

  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = arr[i] ? colour : CRGB::Black;
  }
  FastLED.show();
  delay(500);
  FastLED.clear();
  FastLED.show();
  delay(100);
}
