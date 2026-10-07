#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>

#define GY_W  0x2C    // SLA+W
#define GY_R  0x2D    // SLA+R

void check_bit(void);
uint8_t check_status(uint8_t bit);
uint8_t I2C_init(void);
uint8_t I2C_start(void);
uint8_t I2C_send_data_write(uint8_t data);
uint8_t I2C_send_data_read(uint8_t data);
uint8_t I2C_send_ack(void);
uint8_t I2C_send_nack(void);
uint8_t I2C_stop(void);
void inits(void);

void check_bit(void){
  while (!(TWCR & (1<<TWINT)));
}

uint8_t check_status(uint8_t bit){
  if ((TWSR & 0xF8) != bit){
    return 0;
  }
  else{
    return 1;
  }
}

void I2C_init(void){
  TWSR &=~ ((1 << TWSP1) | (1 << TWSP0));   // Set prescaler to 1
  TWBR = 72;                                // i2c is set to 100khz
  TWCR = (1 << TWEN);                       // Enable i2c
}

// Can be used as a repeated start too
uint8_t I2C_start(void){  
  uint8_t result;
  TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);
  check_bit();
  result = check_status(TW_START);
  return result;
}

uint8_t I2C_send_data_write(uint8_t data){
  uint8_t;
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  result = check_status(TW_MT_SLA_ACK);
  if (result == 0){
    Serial.println("Error sending data -> TW_MT_SLA_ACK");
    Serual.flush();
  }
  result = check_status(TW_MT_SLA_NACK);
  if (result == 0){
    Serial.println("Error sending data -> TW_MT_SLA_NACK");
    Serual.flush();
  }
  result = check_status(TW_MT_ARB_LOST);
  if (result == 0){
    Serial.println("Error sending data -> TW_MT_ARB_LOST");
    Serual.flush();
  }
  return result;
}

uint8_t I2C_send_data_read(uint8_t data){
  uint8_t;
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  result = check_status(TW_MR_ARB_LOST);
  if (result == 0){
    Serial.println("Error receiving data -> TW_MR_ARB_LOST");
    Serial.flush();
  }
  result = check_status(TW_MR_SLA_ACK);
  if (result == 0){
    Serial.println("Error receiving data -> TW_MR_SLA_ACK");
    Serial.flush();
  }
  result = check_status(TW_MR_SLA_NACK);
  if (result == 0){
    Serial.println("Error receiving data -> TW_MR_ARB_LOST");
    Serial.flush();
  }
  return result;
}

uint8_t I2C_send_ack(void){
  uint8_t result;
  TWCR = (1 << TWINT) | (TWEN);
  check_bit();
  
}

uint8_t I2C_send_nack(void){

}

uint8_t I2C_stop(void){
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
  while (TWCR & (1 << TWSTO));
}

void inits(void){
  Serial.begin(9600);
  I2C_init();
  Serial.println("Finished Initialising");
}

int main(void){
  inits();
  while(1){

  }
}
