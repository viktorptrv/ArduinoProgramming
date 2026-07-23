#define DDRB_Address 0x24
#define PORTB_Address 0x25

#define DDRB_Access *((volatile byte*) DDRB_Address)
#define PORTB_Access *((volatile byte*) PORTB_Address)

void setup() {
  // put your setup code here, to run once:
  DDRB_Access |= 0x20;
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB_Access |= 0x20;
  delay(1000);
  PORTB_Access &= 0;
  delay(1000);
}
