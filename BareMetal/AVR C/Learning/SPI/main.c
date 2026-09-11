#include <avr/io.h>
#include <util/delay.h>

#define SCK           PB5
#define MISO          PB4
#define MOSI          PB3
#define SS            PB2 
#define SLAVESELECT   DDRB &=~ (1 << SS)
#define SLAVEDESELECT DDRB |= (1 << SS)

// Constants for EEPROM
#define EEPROM_READ   0x0003
#define EEPROM_WRITE  0x0002
#define EEPROM_WRDI   0x0004
#define EEPROM_WREN   0x0006
#define EEPROM_RDSR   0x0005
#define EEPROM_WRSR   0x0001

// Max EEPROM memory address
#define EEPROM_MEM_START      0x0000
#define EEPROM_MEM_END        0x7FFF
#define EEPROM_BYTE_PER_PAGE  64

// EEPROM status bits register to read from
#define EEPROM_WRITE_IN_PROGRESS  0
#define EEPROM_WRITE_ENABLE_LATCH 1
#define EEPROM_BLOCK_PROTECT_0    2
#define EEPROM_BLOCK_PROTECT_1    3

static inline void init_SPI(void);
static inline void SPI_tradeByte(uint8_t byte);
static inline void EEPROM_send16BitAddress(uint16_t address);
static inline uint8_t EEPROM_ReadStatus(void);
static inline void EEPROM_writeEnable(void);
uint8_t EEPROM_readByte(uint16_t address);
uint16_t EEPROM_readWord(uint16_t address);
void EEPROM_writeByte(uint16_t address, uint8_t byte);
void EEPROM_writeWord(uint16_t address, uint16_t byte);
void EEPROM_clearAll(void);

static inline void init_SPI(void){
  DDRB |= (1 << SS) | (1 << MOSI) | (1 << SCK);
  PORTB |= (1 << SS) | (1 << SCK);    // pull the slave pin high
  PORTD |= (1 << MISO);

  SPCR |= (1 << MSTR) | (1 <<SPR0);
  SPCR |= (1 << SPE);
}

static inline void SPI_tradeByte(uint8_t byte){
  SPDR = byte;
  while(!(SPSR & (1 << SPIF)));       // SPIF Will indicate successful transfer
}

static inline void EEPROM_send16BitAddress(uint16_t address){
  SPI_tradeByte((uint8_t) (address >> 8));      // shifting bits starts from most significant bit
  SPI_tradeByte((uint8_t) address);
}

static inline uint8_t EEPROM_ReadStatus(void){
  SLAVESELECT;
  SPI_tradeByte(EEPROM_RDSR);
  SPI_tradeByte(0);
  SLAVEDESELECT;
  return SPDR;
}

static inline void EEPROM_writeEnable(void){
  SLAVESELECT;
  SPI_tradeByte(EEPROM_WREN);
  SLAVEDESELECT;
  return;
}

uint8_t EEPROM_readByte(uint16_t address){
  SLAVESELECT;
  SPI_tradeByte(EEPROM_READ);
  EEPROM_send16BitAddress(address);
  SLAVEDESELECT;
  return SPDR;
} 

uint16_t EEPROM_readWord(uint16_t address){
  uint16_t word_result;
  SLAVESELECT;
  SPI_tradeByte(EEPROM_READ);
  EEPROM_send16BitAddress(address);
  SPI_tradeByte(0);
  word_result = (SPDR << 8);
  SPI_tradeByte(0);
  word_result |= SPDR;
  SLAVEDESELECT;
  return word_result;
}

void EEPROM_writeByte(uint16_t address, uint8_t byte){
  SLAVESELECT;
  SPI_tradeByte(EEPROM_WREN);
  SLAVEDESELECT;
  SLAVESELECT;
  SPI_tradeByte(EEPROM_WRITE);
  EEPROM_send16BitAddress(address);
  SPI_tradeByte(byte);
  SLAVEDESELECT;
  while(EEPROM_ReadStatus() & (1 << EEPROM_WRITE_IN_PROGRESS));
}

void EEPROM_writeWord(uint16_t address, uint16_t byte){
  SLAVESELECT;
  SPI_tradeByte(EEPROM_WREN);
  SLAVEDESELECT;
  SLAVESELECT;
  SPI_tradeByte(EEPROM_WRITE);
  EEPROM_send16BitAddress(address);
  SPI_tradeByte((uint8_t) (byte >> 8));
  SPI_tradeByte((uint8_t) byte);
  SLAVEDESELECT;
  while(EEPROM_ReadStatus() & (1 << EEPROM_WRITE_IN_PROGRESS));
}

void EEPROM_clearAll(void){
  uint8_t i;
  uint16_t pageAddress = 0;
  while(pageAddress <= EEPROM_MEM_END){
    EEPROM_writeEnable();
    SLAVESELECT;
    SPI_tradeByte(EEPROM_WRITE);
    EEPROM_send16BitAddress(pageAddress);
    for(i = 0; i < EEPROM_BYTE_PER_PAGE; i++){
      SPI_tradeByte(0);
    }
    SLAVEDESELECT;
    pageAddress += EEPROM_BYTE_PER_PAGE;
     while(EEPROM_ReadStatus() & (1 << EEPROM_WRITE_IN_PROGRESS));
  }
}

int main(void){
  init_SPI();
  Serial.begin(9600);

  while(1){

  }
}
