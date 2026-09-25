#include <avr/io.h>
#include <util/delay.h>
#include "DHT.h"

#define MAX_MEM_ADDRESS 0X7FFF
#define MIN_MEM_ADDRESS 0X0000
#define ERROR           101
#define EEROR_16BIT     404
#define DHTTYPE         DHT22

#define CS_LED    PD2
#define READ_LED  PD3
#define WRITE_LED PD4
#define BUZZ      PD5
#define DHTPIN    PD6
#define SCK_PIN   PB5
#define MISO_PIN  PB4
#define MOSI_PIN  PB3
#define CS_PIN    PB2

// Commands send to EEPROM  
#define EEPROM_WRSR   0x0001
#define EEPROM_WRITE  0x0002
#define EEPROM_READ   0x0003
#define EEPROM_WRDI   0x0004
#define EEPROM_RDSR   0x0005
#define EEPROM_WREN   0x0006

// EEPROM Status Register bits
#define EEPROM_STATUS_WIP  0    // Write in process status bit
#define EEPROM_STATUS_WEL  1    // Write Enable Latch status bit
#define EEPROM_STATUS_BP0  2
#define EEPROM_STATUS_BP1  3

#define WRITE_IN_PROGRESS    1
#define WRITE_ENABLED_LATCH  1

// Macros
#define SLAVE_SELECT             PORTD &=~(1 << CS_PIN)
#define SLAVE_DESELECT           PORTD |= (1 << CS_PIN)
#define TURN_ON_LED(led_pin)     PORTB |= (1 << led_pin)
#define TURN_OFF_LED(led_pin)    PORTB &=~(1 << led_pin)

DHT dht(DHTPIN, DHTTYPE);

static inline void SPI_Setup(void);
static inline void SPI_transmit(uint8_t data);
static inline void PORT_Setup(void);
static inline void eeprom_send_8bit(uint8_t data);
static inline void eeprom_send_16bit(uint16_t data);
static inline void eeprom_write_data(uint16_t address, uint8_t data);
static inline void eeprom_write_latch_enable(void);
static inline void eeprom_write_latch_disable(void);
static inline int  eeprom_read_status(void);
static inline int  eeprom_read_data(uint16_t address);

static inline void SPI_Setup(void){
  DDRB |= (1 << MOSI_PIN) | (1 << SCK_PIN);
  PORTB |= (1 << MISO_PIN);
  SPCR |= (1 << MSTR);
  SPCR |= (1 << SPR0);
  SPCR |= (1 << SPE);
}

static inline void PORT_Setup(void){
  DDRD |= (1 << CS_LED) | (1 << READ_LED) | (1 << WRITE_LED) | (1 << BUZZ);
}

static inline void SPI_transmit(uint8_t data){
  SPDR = data;
  while(!(SPSR & (1 << SPIF)));
}

static inline void eeprom_send_8bit(uint8_t data){
  if (data > 255){
    Serial.println("Data is too big!");
    data = ERROR;
  }
  SPI_transmit(data);
}

static inline void eeprom_send_16bit(uint16_t data){
  if (data > 65535){
    Serial.println("Data is too big!");
    data = EEROR_16BIT;
  }
  eeprom_send_8bit(data >> 8);
  eeprom_send_8bit(data);
}

static inline int eeprom_read_data(uint16_t address){
  TURN_ON_LED(READ_LED);
  SLAVE_SELECT;
  eeprom_send_8bit(EEPROM_READ);
  eeprom_send_16bit(address);
  eeprom_send_8bit(0);
  SLAVE_DESELECT;
  TURN_OFF_LED(READ_LED);
  return SPDR;
}

static inline void eeprom_write_data(uint16_t address, uint8_t data){
  if (address > MAX_MEM_ADDRESS || address < MIN_MEM_ADDRESS){
    Serial.println("Address cannot be used!");
    return;
  }
  TURN_ON_LED(WRITE_LED);
  SLAVE_SELECT;
  eeprom_write_latch_enable();
  SLAVE_DESELECT;
  SLAVE_SELECT;
  eeprom_send_8bit(EEPROM_WRITE);
  eeprom_send_16bit(address);
  eeprom_send_8bit(data);
  while(eeprom_read_status(EEPROM_STATUS_WIP) & WRITE_IN_PROGRESS);
  SLAVE_DESELECT;
  TURN_OFF_LED(WRITE_LED);
}

static inline void eeprom_write_latch_enable(void){
  eeprom_send_8bit(EEPROM_WREN);
}

static inline int eeprom_read_status(uint8_t bit){
  eeprom_send_8bit(EEPROM_RDSR);
  if (SPDR & bit){
    return 1;
  }
  else{
    return 0;
  }
}

int main(void){
  int iRes;
  SPI_Setup();
  dht.begin();
  Serial.begin(9600);
  
  while(1){
    iRes = eeprom_read_data(MIN_MEM_ADDRESS);
    Serial.println(iRes);
  }
}
