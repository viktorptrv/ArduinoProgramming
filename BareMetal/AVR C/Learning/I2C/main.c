#include <avr/io.h>
#include <util/delay.h>

void initI2C(void);
void i2cWaitForComplete(void);
void i2cStart(void);
void i2cStop(void);
void i2cSend(uint8_t data);
uint8_t i2cReadAck(void);
uint8_t i2cReadNock(void);

// Sets pullups and init bus speed to 100khz at fcpu == 8mhz
void initI2C(void){
  TWBR = 72;      // 100khz
  TWCR |= (1 << TWEN);    // Enable i2c
}

// waits until hardware sets the twint flag
void i2cWaitForComplete(void){
  loop_until_bit_is_set(TWCR, TWINT);
}

// sends a start condition
void i2cStart(void){
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  i2cWaitForComplete();
  if ((TWSR & 0xF8) != START){
    Serial.println("Error occured with i2cStart");
  }
}

// sends a stop condition
void i2cStop(void){
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

// loads data and sends it
void i2cSend(uint8_t data){
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  i2cWaitForComplete();
  if ((TWSR & 0xF8) != MT_DATA_ACK){
    Serial.println("Error occured with i2cSend");
  }
}

// read in from slave
uint8_t i2cReadAck(void){
  TWCR = (1 << TWINT) | ( 1 << TWEA) | (1 << TWEN);
  i2cWaitForComplete();
  return (TWDR);
}

// read in from slave
uint8_t i2cReadNock(void){
  TWCR = (1 << TWINT) | (1 << TWEN);
  i2cWaitForComplete();
  return (TWDR);
}

int main(void){
  Serial.begin(9600);
  initI2C();
}
