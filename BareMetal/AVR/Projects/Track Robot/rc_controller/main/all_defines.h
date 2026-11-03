#define rxPin         10
#define txPin         11
#define LED_TX        6
#define LED_RX        0
#define LED_STATE_ERR 0
#define BTN_MID       PB0
#define BTN_RHT       PB2
#define BTN_LFT       PB2
#define BTN_DWN       0
#define BTN_UP        2
#define BTN_SPD       4   // must have interrupt  -> INT4
#define BTN_STEP      5   // must have interrupt  -> INT5
#define ENC_S1        PD0   // must have interrupt  -> INT0
#define ENC_S2        PD1   // must have interrupt  -> INT1
#define TIMER_INCREMENT 0.00001

// Defining vectors from vector table
#define TIMER3_COMPA        _VECTOR(32)   /* External Interrupt Request 0 */
#define INT2                2
#define INT3                3
#define INT4                4
#define INT5                5
#define INT4_vect           _VECTOR(5)
#define INT5_vect           _VECTOR(6)

// Defining OCR3A
#define OCR3A               _SFR_MEM16(0x98)
#define OCR3A_H             _SFR_MEM8(0x99)
#define OCR3A_L             _SFR_MEM8(0x98)
#define OCR3A_0             0
#define OCR3A_1             1
#define OCR3A_2             2
#define OCR3A_3             3
#define OCR3A_4             4
#define OCR3A_5             5
#define OCR3A_6             6
#define OCR3A_7             7
#define OCR3A_8             8
#define OCR3A_9             9
#define OCR3A_10            10
#define OCR3A_11            11
#define OCR3A_12            12
#define OCR3A_13            13
#define OCR3A_14            14
#define OCR3A_15            15

// Bit defines
#define WGM30               0
#define WGM31               1
#define WGM32               3
#define CS30                0
#define CS31                1
#define CS32                2
#define COM3A0              6
#define COM3A1              7
#define PRTIM3              3
#define OCIE3A              1
#define ISC21               5
#define ISC31               7
#define ISC41               1
#define ISC51               3

// Register defines
#define TCCR3A              _SFR_MEM8(0x90)
#define TCCR3B              _SFR_MEM8(0x91)
#define PRR1                _SFR_MEM8(0x65)
#define TIMSK3              _SFR_MEM8(0x71)
#define EICRB               _SFR_MEM8(0x6A)

// Ports defines and ddrs
#define PORTE               _SFR_MEM8(0x0E)
#define PORTL               _SFR_MEM8(0x10B)
#define PORTG               _SFR_MEM8(0x14)
#define DDRE                _SFR_MEM8(0x0D)
#define DDRL                _SFR_MEM8(0x10A)
#define DDRG                _SFR_MEM8(0x13)