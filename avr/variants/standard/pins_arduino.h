/***************************************************|
|            MIGHTYCORE STANDARD PINOUT             |
|       https://github.com/MCUdude/MightyCore       |
|                                                   |
| An Arduino core for:                              |
| ATmega1284/P                                      |
| ATmega644/A/P/PA                                  |
| ATmega324A/P/PA/PB                                |
| ATmega164A/P/PA                                   |
| ATmega32/A                                        |
| ATmega16/A                                        |
| ATmega8535                                        |
|                                                   |
|***************************************************/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#if defined(__AVR_ATmega644A__)
  #define __AVR_ATmega644__
#endif


// We're using the Standard pinout
#define STANDARD_PINOUT


// Digital pins
#if defined(__AVR_ATmega324PB__)
  #define NUM_DIGITAL_PINS          (39)
#else
  #define NUM_DIGITAL_PINS          (32)
#endif

// PWM pins
#if defined(__AVR_ATmega8535__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
  #define digitalPinHasPWM(p)       ((p) == 3 || (p) == 12 || (p) == 13 || (p) == 15)
#elif defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__)
  #define digitalPinHasPWM(p)       ((p) == 3 || (p) == 4 || (p) == 12 || (p) == 13 || (p) == 14 || (p) == 15)
#elif defined(__AVR_ATmega324PB__)
  #define digitalPinHasPWM(p)       ((p) == 3 || (p) == 4 || (p) == 6 || (p) == 7 || (p) == 12 || (p) == 13 || (p) == 14 || (p) == 15  || (p) == 20)
#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
  #define digitalPinHasPWM(p)       ((p) == 3 || (p) == 4 || (p) == 6 || (p) == 7 || (p) == 12 || (p) == 13 || (p) == 14 || (p) == 15)
#endif

// Builtin LED
#define LED_BUILTIN   (0)
static const uint8_t LED = LED_BUILTIN;

// Analog pins
#define PIN_A0 (24)
#define PIN_A1 (25)
#define PIN_A2 (26)
#define PIN_A3 (27)
#define PIN_A4 (28)
#define PIN_A5 (29)
#define PIN_A6 (30)
#define PIN_A7 (31)
static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;
#define NUM_ANALOG_INPUTS           (8)
#define analogInputToDigitalPin(p)  ((p < NUM_ANALOG_INPUTS) ? (p) + 24 : -1)
#define analogPinToChannel(p)       ((p) < NUM_ANALOG_INPUTS ? (p) : (p) >= 24 ? (p) - 24 : -1)

// SPI
#define PIN_SPI_SS    (4)
#define PIN_SPI_MOSI  (5)
#define PIN_SPI_MISO  (6)
#define PIN_SPI_SCK   (7)
static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;
#if defined(__AVR_ATmega324PB__)
  #define PIN_SPI_SS0   PIN_SPI_SS
  #define PIN_SPI_MOSI0 PIN_SPI_MOSI
  #define PIN_SPI_MISO0 PIN_SPI_MISO
  #define PIN_SPI_SCK0  PIN_SPI_SCK  
  #define PIN_SPI_SS1   (14)
  #define PIN_SPI_MOSI1 (35)
  #define PIN_SPI_MISO1 (34)
  #define PIN_SPI_SCK1  (15)
  static const uint8_t SS0   = PIN_SPI_SS0;
  static const uint8_t MOSI0 = PIN_SPI_MOSI0;
  static const uint8_t MISO0 = PIN_SPI_MISO0;
  static const uint8_t SCK0  = PIN_SPI_SCK0;
  static const uint8_t SS1   = PIN_SPI_SS1;
  static const uint8_t MOSI1 = PIN_SPI_MOSI1;
  static const uint8_t MISO1 = PIN_SPI_MISO1;
  static const uint8_t SCK1  = PIN_SPI_SCK1;
#endif

// i2c
#define PIN_WIRE_SDA  (17)
#define PIN_WIRE_SCL  (16)
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;
#if defined(__AVR_ATmega324PB__)
  #define PIN_WIRE_SDA0 PIN_WIRE_SDA
  #define PIN_WIRE_SCL0 PIN_WIRE_SCL
  #define PIN_WIRE_SDA1 (37)
  #define PIN_WIRE_SCL1 (38)
  static const uint8_t SDA0  = PIN_WIRE_SDA0;
  static const uint8_t SCL0  = PIN_WIRE_SCL0;
  static const uint8_t SDA1  = PIN_WIRE_SDA1;
  static const uint8_t SCL1  = PIN_WIRE_SCL1;
#endif

// Interrupts
#define EXTERNAL_NUM_INTERRUPTS     (3)
#define digitalPinToInterrupt(p)    ((p) == 2 ? 2 : ((p) == 10 ? 0 : ((p) == 11 ? 1 : NOT_AN_INTERRUPT)))

// PCINT
#if defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega324PB__) || \
defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284__) || \
defined(__AVR_ATmega1284P__)
#define digitalPinToPCMSKbit(p) ((p) % 8)
#define digitalPinToPCICR(p)    (((p) >= 0 && (p) < NUM_DIGITAL_PINS) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) ( (p) <= 7 ? 1 : (p) <= 15 ? 3 : (p) <= 23 ? 2 : 0 )
#if defined(__AVR_ATmega324PB__)
  #define digitalPinToPCMSK(p)  ((p) <= 7 ? &PCMSK1 : (p) <= 15 ? &PCMSK3 : (p) <= 23 ? &PCMSK2 : (p) <= 31 ? &PCMSK0 : &PCMSK4)
#else
  #define digitalPinToPCMSK(p)  ((p) <= 7 ? &PCMSK1 : (p) <= 15 ? &PCMSK3 : (p) <= 23 ? &PCMSK2 : &PCMSK0)
#endif
#endif

#ifdef ARDUINO_MAIN

#define PA 1
#define PB 2
#define PC 3
#define PD 4
#if defined(__AVR_ATmega324PB__)
  #define PE 5
#endif

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] =
{
  NOT_A_PORT,
  (uint16_t) &DDRA,
  (uint16_t) &DDRB,
  (uint16_t) &DDRC,
  (uint16_t) &DDRD,
  #if defined(__AVR_ATmega324PB__)
    (uint16_t) &DDRE,
  #endif
};

const uint16_t PROGMEM port_to_output_PGM[] =
{
  NOT_A_PORT,
  (uint16_t) &PORTA,
  (uint16_t) &PORTB,
  (uint16_t) &PORTC,
  (uint16_t) &PORTD,
  #if defined(__AVR_ATmega324PB__)
    (uint16_t) &PORTE,
  #endif
};

const uint16_t PROGMEM port_to_input_PGM[] =
{
  NOT_A_PORT,
  (uint16_t) &PINA,
  (uint16_t) &PINB,
  (uint16_t) &PINC,
  (uint16_t) &PIND,
  #if defined(__AVR_ATmega324PB__)
    (uint16_t) &PINE,
  #endif
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] =
{
  PB, /* D0 */
  PB,
  PB,
  PB,
  PB,
  PB,
  PB,
  PB,
  PD, /* D8 */
  PD,
  PD,
  PD,
  PD,
  PD,
  PD,
  PD,
  PC, /* D16 */
  PC,
  PC,
  PC,
  PC,
  PC,
  PC,
  PC,
  PA, /* D24 */
  PA,
  PA,
  PA,
  PA,
  PA,
  PA,
  PA,
  #if defined(__AVR_ATmega324PB__)
    PE, /* D32 */
    PE,
    PE,
    PE,
    PE,
    PE,
    PE,
  #endif
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] =
{
  _BV(0), /* D0, port B */
  _BV(1),
  _BV(2),
  _BV(3),
  _BV(4),
  _BV(5),
  _BV(6),
  _BV(7),
  _BV(0), /* D8, port D */
  _BV(1),
  _BV(2),
  _BV(3),
  _BV(4),
  _BV(5),
  _BV(6),
  _BV(7),
  _BV(0), /* D16, port C */
  _BV(1),
  _BV(2),
  _BV(3),
  _BV(4),
  _BV(5),
  _BV(6),
  _BV(7),
  _BV(0), /* D24, port A */
  _BV(1),
  _BV(2),
  _BV(3),
  _BV(4),
  _BV(5),
  _BV(6),
  _BV(7),
  #if defined(__AVR_ATmega324PB__)
    _BV(0), /* D32, port E */
    _BV(1),
    _BV(2),
    _BV(3),
    _BV(4),
    _BV(5),
    _BV(6),
  #endif
};

#if defined(__AVR_ATmega8535__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
  NOT_ON_TIMER,   /* D0  - PB0 */
  NOT_ON_TIMER,   /* D1  - PB1 */
  NOT_ON_TIMER,   /* D2  - PB2 */
  TIMER0A,        /* D3  - PB3 */
  NOT_ON_TIMER,   /* D4  - PB4 */
  NOT_ON_TIMER,   /* D5  - PB5 */
  NOT_ON_TIMER,   /* D6  - PB6 */
  NOT_ON_TIMER,   /* D7  - PB7 */
  NOT_ON_TIMER,   /* D8  - PD0 */
  NOT_ON_TIMER,   /* D9  - PD1 */
  NOT_ON_TIMER,   /* D10 - PD2 */
  NOT_ON_TIMER,   /* D11 - PD3 */
  TIMER1B,        /* D12 - PD4 */
  TIMER1A,        /* D13 - PD5 */
  NOT_ON_TIMER,   /* D14 - PD6 */
  TIMER2,         /* D15 - PD7 */
  NOT_ON_TIMER,   /* D16 - PC0 */
  NOT_ON_TIMER,   /* D17 - PC1 */
  NOT_ON_TIMER,   /* D18 - PC2 */
  NOT_ON_TIMER,   /* D19 - PC3 */
  NOT_ON_TIMER,   /* D20 - PC4 */
  NOT_ON_TIMER,   /* D21 - PC5 */
  NOT_ON_TIMER,   /* D22 - PC6 */
  NOT_ON_TIMER,   /* D23 - PC7 */
  NOT_ON_TIMER,   /* D24 - PA0 */
  NOT_ON_TIMER,   /* D25 - PA1 */
  NOT_ON_TIMER,   /* D26 - PA2 */
  NOT_ON_TIMER,   /* D27 - PA3 */
  NOT_ON_TIMER,   /* D28 - PA4 */
  NOT_ON_TIMER,   /* D29 - PA5 */
  NOT_ON_TIMER,   /* D30 - PA6 */
  NOT_ON_TIMER    /* D31 - PA7 */
};

#elif defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega644A__) || \
defined(__AVR_ATmega644P__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
  NOT_ON_TIMER,   /* D0  - PB0 */
  NOT_ON_TIMER,   /* D1  - PB1 */
  NOT_ON_TIMER,   /* D2  - PB2 */
  TIMER0A,        /* D3  - PB3 */
  TIMER0B,        /* D4  - PB4 */
  NOT_ON_TIMER,   /* D5  - PB5 */
  NOT_ON_TIMER,   /* D6  - PB6 */
  NOT_ON_TIMER,   /* D7  - PB7 */
  NOT_ON_TIMER,   /* D8  - PD0 */
  NOT_ON_TIMER,   /* D9  - PD1 */
  NOT_ON_TIMER,   /* D10 - PD2 */
  NOT_ON_TIMER,   /* D11 - PD3 */
  TIMER1B,        /* D12 - PD4 */
  TIMER1A,        /* D13 - PD5 */
  TIMER2B,        /* D14 - PD6 */
  TIMER2A,        /* D15 - PD7 */
  NOT_ON_TIMER,   /* D16 - PC0 */
  NOT_ON_TIMER,   /* D17 - PC1 */
  NOT_ON_TIMER,   /* D18 - PC2 */
  NOT_ON_TIMER,   /* D19 - PC3 */
  NOT_ON_TIMER,   /* D20 - PC4 */
  NOT_ON_TIMER,   /* D21 - PC5 */
  NOT_ON_TIMER,   /* D22 - PC6 */
  NOT_ON_TIMER,   /* D23 - PC7 */
  NOT_ON_TIMER,   /* D24 - PA0 */
  NOT_ON_TIMER,   /* D25 - PA1 */
  NOT_ON_TIMER,   /* D26 - PA2 */
  NOT_ON_TIMER,   /* D27 - PA3 */
  NOT_ON_TIMER,   /* D28 - PA4 */
  NOT_ON_TIMER,   /* D29 - PA5 */
  NOT_ON_TIMER,   /* D30 - PA6 */
  NOT_ON_TIMER    /* D31 - PA7 */
};

#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
  NOT_ON_TIMER,   /* D0  - PB0 */
  NOT_ON_TIMER,   /* D1  - PB1 */
  NOT_ON_TIMER,   /* D2  - PB2 */
  TIMER0A,        /* D3  - PB3 */
  TIMER0B,        /* D4  - PB4 */
  NOT_ON_TIMER,   /* D5  - PB5 */
  TIMER3A,        /* D6  - PB6 */
  TIMER3B,        /* D7  - PB7 */
  NOT_ON_TIMER,   /* D8  - PD0 */
  NOT_ON_TIMER,   /* D9  - PD1 */
  NOT_ON_TIMER,   /* D10 - PD2 */
  NOT_ON_TIMER,   /* D11 - PD3 */
  TIMER1B,        /* D12 - PD4 */
  TIMER1A,        /* D13 - PD5 */
  TIMER2B,        /* D14 - PD6 */
  TIMER2A,        /* D15 - PD7 */
  NOT_ON_TIMER,   /* D16 - PC0 */
  NOT_ON_TIMER,   /* D17 - PC1 */
  NOT_ON_TIMER,   /* D18 - PC2 */
  NOT_ON_TIMER,   /* D19 - PC3 */
  NOT_ON_TIMER,   /* D20 - PC4 */
  NOT_ON_TIMER,   /* D21 - PC5 */
  NOT_ON_TIMER,   /* D22 - PC6 */
  NOT_ON_TIMER,   /* D23 - PC7 */
  NOT_ON_TIMER,   /* D24 - PA0 */
  NOT_ON_TIMER,   /* D25 - PA1 */
  NOT_ON_TIMER,   /* D26 - PA2 */
  NOT_ON_TIMER,   /* D27 - PA3 */
  NOT_ON_TIMER,   /* D28 - PA4 */
  NOT_ON_TIMER,   /* D29 - PA5 */
  NOT_ON_TIMER,   /* D30 - PA6 */
  NOT_ON_TIMER    /* D31 - PA7 */
};

#elif defined(__AVR_ATmega324PB__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
  NOT_ON_TIMER,   /* D0  - PB0 */
  NOT_ON_TIMER,   /* D1  - PB1 */
  NOT_ON_TIMER,   /* D2  - PB2 */
  TIMER0A,        /* D3  - PB3 */
  TIMER0B,        /* D4  - PB4 */
  NOT_ON_TIMER,   /* D5  - PB5 */
  TIMER3A,        /* D6  - PB6 */
  TIMER3B,        /* D7  - PB7 */
  NOT_ON_TIMER,   /* D8  - PD0 */
  NOT_ON_TIMER,   /* D9  - PD1 */
  NOT_ON_TIMER,   /* D10 - PD2 */
  NOT_ON_TIMER,   /* D11 - PD3 */
  TIMER1B,        /* D12 - PD4 */
  TIMER1A,        /* D13 - PD5 */
  TIMER2B,        /* D14 - PD6 */
  TIMER2A,        /* D15 - PD7 */
  NOT_ON_TIMER,   /* D16 - PC0 */
  NOT_ON_TIMER,   /* D17 - PC1 */
  NOT_ON_TIMER,   /* D18 - PC2 */
  NOT_ON_TIMER,   /* D19 - PC3 */
  TIMER4A,        /* D20 - PC4 */
  NOT_ON_TIMER,   /* D21 - PC5 */
  NOT_ON_TIMER,   /* D22 - PC6 */
  NOT_ON_TIMER,   /* D23 - PC7 */
  NOT_ON_TIMER,   /* D24 - PA0 */
  NOT_ON_TIMER,   /* D25 - PA1 */
  NOT_ON_TIMER,   /* D26 - PA2 */
  NOT_ON_TIMER,   /* D27 - PA3 */
  NOT_ON_TIMER,   /* D28 - PA4 */
  NOT_ON_TIMER,   /* D29 - PA5 */
  NOT_ON_TIMER,   /* D30 - PA6 */
  NOT_ON_TIMER,   /* D31 - PA7 */
  NOT_ON_TIMER,   /* D32 - PE0 */
  NOT_ON_TIMER,   /* D33 - PE1 */
  NOT_ON_TIMER,   /* D34 - PE2 */
  NOT_ON_TIMER,   /* D35 - PE3 */
  NOT_ON_TIMER,   /* D36 - PE4 */
  NOT_ON_TIMER,   /* D37 - PE5 */
  NOT_ON_TIMER    /* D38 - PE6 */
};
#endif // Timer defs

#endif // ARDUINO_MAIN


// Missing definitions in iom164pa.h/iom324a.h/iom324p.h/iom324pa.h
#if defined(__AVR_ATmega164PA__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__)\
|| defined(__AVR_ATmega324PA__)
  #define SPSR SPSR0
  #define SPDR SPDR0
  #define SPCR SPCR0
  #define SPR0 SPR00
  #define SPR1 SPR10
  #define CPHA CPHA0
  #define CPOL CPOL0
  #define MSTR MSTR0
  #define DORD DORD0
  #define SPE  SPE0
  #define SPIE SPIE0
  #define SPI2X SPI2X0
  #define WCOL WCOL0
  #define SPIF SPIF0
#endif


// Missing definitions in iom324pb.h file + better backwards compatibility
#if defined(__AVR_ATmega324PB__)
  // USART
  #define MPCM0   MPCM
  #define U2X0    U2X
  #define UPE0    UPE
  #define DOR0    DOR
  #define FE0     FE
  #define UDRE0   UDRE
  #define TXC0    TXC
  #define RXC0    RXC
  #define TXB80   TXB8
  #define RXB80   RXB8
  #define UCSZ02  UCSZ2
  #define TXEN0   TXEN
  #define RXEN0   RXEN
  #define UDRIE0  UDRIE
  #define TXCIE0  TXCIE
  #define RXCIE0  RXCIE
  #define UCPOL0  UCPOL
  #define UCSZ00  UCSZ0
  #define UCSZ01  UCSZ1
  #define USBS0   USBS
  #define UPM00   UPM0
  #define UPM01   UPM1
  #define UMSEL00 UMSEL0
  #define UMSEL01 UMSEL1  
  #define MPCM1   MPCM
  #define U2X1    U2X
  #define UPE1    UPE
  #define DOR1    DOR
  #define FE1     FE
  #define UDRE1   UDRE
  #define TXC1    TXC
  #define RXC1    RXC
  #define TXB81   TXB8
  #define RXB81   RXB8
  #define UCSZ12  UCSZ2
  #define TXEN1   TXEN
  #define RXEN1   RXEN
  #define UDRIE1  UDRIE
  #define TXCIE1  TXCIE
  #define RXCIE1  RXCIE
  #define UCPOL1  UCPOL
  #define UCSZ10  UCSZ0
  #define UCSZ11  UCSZ1
  #define USBS1   USBS
  #define UPM10   UPM0
  #define UPM11   UPM1
  #define UMSEL10 UMSEL0
  #define UMSEL11 UMSEL1 
  #define MPCM2   MPCM
  #define U2X2    U2X
  #define UPE2    UPE
  #define DOR2    DOR
  #define FE2     FE
  #define UDRE2   UDRE
  #define TXC2    TXC
  #define RXC2    RXC
  #define TXB82   TXB8
  #define RXB82   RXB8
  #define UCSZ22  UCSZ2
  #define TXEN2   TXEN
  #define RXEN2   RXEN
  #define UDRIE2  UDRIE
  #define TXCIE2  TXCIE
  #define RXCIE2  RXCIE
  #define UCPOL2  UCPOL
  #define UCSZ20  UCSZ0
  #define UCSZ21  UCSZ1
  #define USBS2   USBS
  #define UPM20   UPM0
  #define UPM21   UPM1
  #define UMSEL20 UMSEL0
  #define UMSEL21 UMSEL1
  
  // i2c
  #define TWI_vect TWI0_vect
  #define TWI_vect_num TWI0_vect_num
  #define TWBR TWBR0
  #define TWSR TWSR0
  #define TWS3 TWS03
  #define TWS4 TWS04
  #define TWS5 TWS05
  #define TWS6 TWS06
  #define TWS7 TWS07
  #define TWAR TWAR0
  #define TWDR TWDR0
  #define TWD0 0
  #define TWD1 1
  #define TWD2 2
  #define TWD3 3
  #define TWD4 4
  #define TWD5 5
  #define TWD6 6
  #define TWD7 7
  #define TWCR  TWCR0
  #define TWAMR TWAMR0
  #define TWAM0 TWAM00
  #define TWAM1 TWAM01
  #define TWAM2 TWAM02
  #define TWAM3 TWAM03
  #define TWAM4 TWAM04
  #define TWAM5 TWAM05
  #define TWAM6 TWAM06

  // SPI
  #define SPI_STC_vect SPI0_STC_vect
  #define SPI_STC_vect_num SPI0_STC_vect_num
  #define SPCR SPCR0
  #define SPSR SPSR0
  #define SPDR SPDR0
  #define SPDRB0 0
  #define SPDRB1 1
  #define SPDRB2 2
  #define SPDRB3 3
  #define SPDRB4 4
  #define SPDRB5 5
  #define SPDRB6 6
  #define SPDRB7 7

#endif // 324PB defs

#endif // Pins_Arduino_h
