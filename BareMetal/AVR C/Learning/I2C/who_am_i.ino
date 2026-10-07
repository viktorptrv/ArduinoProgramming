#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>

void initI2C(void);
void initI2C(void){
  TWSR &= ~((1 << TWPS1) | (1 << TWPS0));
  TWBR = 72;
  TWCR = (1 << TWEN);
}

void check_bit(void);
void check_bit(void){
  while (!(TWCR & (1<<TWINT)));
}

int I2C_check_status_start(void);
int I2C_check_status_start(void){
  if ((TWSR & 0xF8) != TW_START){
    return 0;
  }
  else{
    return 1;
  }
}

int I2C_check_status_data(void);
int I2C_check_status_data(void){
  if ((TWSR & 0xF8) != TW_MT_SLA_ACK){
    return 0;
  }
  else{
    return 1;
  }
}


void I2C_start(void);
void I2C_start(void){
  uint8_t status;
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1 << TWEN);
  check_bit(); 
  status = I2C_check_status_start();
    if(status == 1){
      //Serial.println("Successfull start");
    }
    else{
      //Serial.println("Could not send start");
    }
}

int IC2_send_data(uint8_t data);
int IC2_send_data(uint8_t data){
  uint8_t status ;
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  check_bit();
  // Check the status of that data;
  status = I2C_check_status_data();
  if(status == 1){
    return 1;
  }
  return 0;
}

int I2C_check_status(uint8_t status_code);
int I2C_check_status(uint8_t status_code){
  
}

void I2C_stop(void);
void I2C_stop(void){
  TWCR = (1<<TWINT) | (1<<TWEN)| (1<<TWSTO); 
  while (TWCR & (1 << TWSTO));
}

int main(void){
  uint8_t address = 1;
  uint8_t status;
  Serial.begin(9600);
  _delay_ms(1000);
  initI2C();
  
    // First send start bit
  for (address = 1; address < 128; address++){
    I2C_start();

    // Then send SLA+W
    status = IC2_send_data(address << 1);
    if (status == 1){
      Serial.print("Address found!: ");
      Serial.println(address);
      Serial.flush();
      break;
    }
    I2C_stop();
  }  

  while(1);

  return 0;
}
