#ifndef MAIN_FUNCS_H
#define MAIN_FUNCS_H

#include <util/delay.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <avr/interrupt.h>
#include "all_defines.h"
#include <avr/io.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

extern int8_t volatile enc_mode;          // set speed by default;
extern int8_t volatile rx_robot;          // if rx == 1, then we know the robot successfully received the values
extern int8_t volatile aFlag;
extern int8_t volatile bFlag;
extern int8_t volatile encPos;
extern int8_t volatile enc_spd;           // speed
extern int8_t volatile old_enc_spd;
extern int8_t volatile enc_stp;           // step
extern int8_t volatile old_enc_stp;
extern int8_t volatile reading;

extern double timer;

typedef struct _control{
  int8_t speed;
  int8_t direction;
  int8_t step;                  // how many cycles we will do, it will be counted by a timer from robot part
  int8_t ready_to_send;
}Control;

typedef struct _btn{
  int8_t* ddr_addr;
  int8_t* port_addr;
  int8_t* inp_addr;
  int8_t btn;
}Btn;

typedef struct _ledBtns{
  Btn* tx_btn;
  Btn* rx_btn;
  Btn* bt_state;
}StateButtons;

extern SoftwareSerial bt_Serial;    // HC-05 is MASTER here
extern LiquidCrystal_I2C lcd;

int8_t inline received_from_robot(void);
uint8_t send_to_robot(int8_t val);
void init_pins(void);
void init_interrupts(void);
void init_clock(void);
void switch_enc_mode(void);
void turn_on_led(Btn* btn);
void turn_off_led(Btn* btn);
int8_t bt_listening(void);
int8_t bt_overflow(void);

#endif