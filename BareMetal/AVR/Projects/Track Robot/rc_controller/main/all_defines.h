#define rxPin         10
#define txPin         11
#define LED_TX        PL6
#define LED_RX        PG0
#define LED_STATE_ERR PC0
#define BTN_MID       PB0
#define BTN_RHT       PB2
#define BTN_LFT       PB2
#define BTN_DWN       PL0
#define BTN_UP        PL2
#define BTN_SPD       PE4   // must have interrupt  -> INT4
#define BTN_STEP      PE5   // must have interrupt  -> INT5
#define ENC_S1        PD0   // must have interrupt  -> INT0
#define ENC_S2        PD1   // must have interrupt  -> INT1
#define TIMER3_COMPA        _VECTOR(32)   /* External Interrupt Request 0 */
#define TIMER_INCREMENT 0.00001
#define INT4_vect           _VECTOR(5)
#define INT5_vect           _VECTOR(6)