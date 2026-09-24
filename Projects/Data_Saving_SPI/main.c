#include <avr/io.h>
#include <util/delay.h>

#define CS_LED    PD2
#define READ_LED  PD3
#define WRITE_LED PD4
#define BUZZ      PD5
#define DHT22     PD6
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
#define SLAVE_DESELECT           POTRD |= (1 << CS_PIN)
#define TURN_ON_LED(led_pin)     PORTB |= (1 << led_pin)
#define TURN_OFF_LED(led_pin)    PORTB &=~(1 << led_pin)

static inline void SPI_Setup(void);
static inline void PORT_Setup(void);
static inline void eeprom_read_data(uint16_t address);
static inline void eeprom_write_data(uint16_t address, uint8_t data);
static inline void eeprom_write_latch_enable(void);
static inline void eeprom_write_latch_disable(void);

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

static inline void eeprom_read_data(uint16_t address){

}

static inline void eeprom_write_data(uint16_t address, uint8_t data){

}

static inline void eeprom_write_latch_enable(void){

}

static inline void eeprom_write_latch_disable(void){

}

int main(void){

}
