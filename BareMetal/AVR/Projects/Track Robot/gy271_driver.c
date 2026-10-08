#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>

#define GY_W            0x2C    // SLA+W
#define GY_R            0x2D    // SLA+R
#define QMC_REG_A       0x00
#define QMC_REG_B       0x01
#define QMC_MODE_REG    0x02
#define QMC_X_MSB       0x03
#define QMC_X_LSB       0x04
#define QMC_Z_MSB       0x05
#define QMC_Z_LSB       0x06
#define QMC_Y_MSB       0x07
#define QMC_Y_LSB       0x08
#define QMC_STAT        0x09

void check_bit(void);
uint8_t check_status(uint8_t bit);
void I2C_init(void);
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
  TWSR &=~ ((1 << TWPS1) | (1 << TWPS0));   // Set prescaler to 1
  TWBR = 72;                                // i2c is set to 100khz
  TWCR = (1 << TWEN);                       // Enable i2c
}

// Can be used as a repeated start too
uint8_t I2C_start(void){  
  uint8_t result;
  TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);
  check_bit();
  result = check_status(TW_START);
  if (result == 0){
    Serial.println("Could not send start signal!");
    Serial.flush();
  }
  return result;
}

uint8_t I2C_send_data_write(uint8_t data){
  uint8_t result;
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  check_bit();
  result = check_status(TW_MT_SLA_ACK);
  if (result == 0){
    Serial.println("Error sending data -> TW_MT_SLA_ACK");
    Serial.flush();
  }
  result = check_status(TW_MT_SLA_NACK);
  if (result == 0){
    Serial.println("Error sending data -> TW_MT_SLA_NACK");
    Serial.flush();
  }
  return result;
}

uint8_t I2C_send_data_read(uint8_t data){
  uint8_t result;
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  check_bit();
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
  return result;
}

uint8_t I2C_send_ack(void){
  TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);
  check_bit();
  return TWDR;
}

uint8_t I2C_send_nack(void){
  TWCR=(1<<TWEN) | (1<<TWINT);	
  check_bit();
  return TWDR;		
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
  uint8_t x_msb, x_lsb, y_msb, y_lsb, z_msb, z_lsb, gy_status;
  uint8_t i2c_status;
  _delay_ms(1000);
  inits();
  while(1){
    I2C_start();
    I2C_send_data_write(GY_W);
    I2C_send_data_write(QMC_X_MSB);
    I2C_start();
    I2C_send_data_read(GY_R);
    x_msb = I2C_send_ack();
    x_lsb = I2C_send_ack();
    z_msb = I2C_send_ack();
    z_lsb = I2C_send_ack();
    y_msb = I2C_send_ack();
    y_lsb = I2C_send_nack();
    I2C_stop();

    Serial.print("X MSB -> ");
    Serial.println(x_msb);
    Serial.print("X LSB -> ");
    Serial.println(x_lsb);
    Serial.print("Z MSB -> ");
    Serial.println(z_msb);
    Serial.print("Z LSB -> ");
    Serial.println(z_lsb);
    Serial.print("Y MSB -> ");
    Serial.println(y_msb);
    Serial.print("Y LSB -> ");
    Serial.println(y_lsb);
    Serial.flush();
  }
}
