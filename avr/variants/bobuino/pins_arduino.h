/***************************************************|
|            MIGHTYCORE BOBUINO PINOUT              |
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


// We're using the Bobuino pinout
#define BOBUINO_PINOUT


// Digital pins
#if defined(__AVR_ATmega324PB__)
  #define NUM_DIGITAL_PINS          (39)
#else
  #define NUM_DIGITAL_PINS          (32)
#endif

// PWM pins
#if defined(__AVR_ATmega8535__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
  #define digitalPinHasPWM(p)       ((p) == 7 || (p) == 8 || (p) == 30 || (p) == 31)
#elif defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__)
  #define digitalPinHasPWM(p)       ((p) == 7 || (p) == 8 || (p) == 9 || (p) == 10 || (p) == 30 || (p) == 31)
#elif defined(__AVR_ATmega324PB__)
  #define digitalPinHasPWM(p)       ((p) == 7 || (p) == 8 || (p) == 9 || (p) == 10 || (p) == 12 || (p) == 13 || (p) == 26 || (p) == 30 || (p) == 31)
#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
  #define digitalPinHasPWM(p)       ((p) == 7 || (p) == 8 || (p) == 9 || (p) == 10 || (p) == 12 || (p) == 13 || (p) == 30 || (p) == 31)
#endif

// Builtin LED
#define LED_BUILTIN   (13)
static const uint8_t LED = LED_BUILTIN;

// Analog pins
#define PIN_A0 (14)
#define PIN_A1 (15)
#define PIN_A2 (16)
#define PIN_A3 (17)
#define PIN_A4 (18)
#define PIN_A5 (19)
#define PIN_A6 (20)
#define PIN_A7 (21)
static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;
#define NUM_ANALOG_INPUTS           (8)
#define analogInputToDigitalPin(p)  ((p < NUM_ANALOG_INPUTS) ? (p) + 14 : -1)
#define analogPinToChannel(p)       ((p) < NUM_ANALOG_INPUTS) ? (7 - (p)) : ((p)  >=  14 && (p) <= 21) ? (21 - (p)) : -1

// SPI
#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)
static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;
#if defined(__AVR_ATmega324PB__)
  #define PIN_SPI_SS0   PIN_SPI_SS
  #define PIN_SPI_MOSI0 PIN_SPI_MOSI
  #define PIN_SPI_MISO0 PIN_SPI_MISO
  #define PIN_SPI_SCK0  PIN_SPI_SCK
  #define PIN_SPI_SS1   (9)
  #define PIN_SPI_MOSI1 (35)
  #define PIN_SPI_MISO1 (34)
  #define PIN_SPI_SCK1  (31)
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
#define PIN_WIRE_SDA  (23)
#define PIN_WIRE_SCL  (22)
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
#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 3 ? 1 : ((p) == 6 ? 2 : NOT_AN_INTERRUPT)))

// PCINT
#if defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega324PB__) || \
defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284__) || \
defined(__AVR_ATmega1284P__)
#if defined(__AVR_ATmega324PB__)
#define PORT_NDX_TO_PCMSK(x) ((x) == 0 ? &PCMSK0 : ((x) == 1 ? &PCMSK1 : ((x) == 2 ? &PCMSK2 : ((x) == 3 ? &PCMSK3 : ((x) == 4 ? &PCMSK4 : (uint8_t )0)))))
#else
#define PORT_NDX_TO_PCMSK(x) ((x) == 0 ? &PCMSK0 : ((x) == 1 ? &PCMSK1 : ((x) == 2 ? &PCMSK2 : ((x) == 3 ? &PCMSK3 : (uint8_t )0))))
#endif
#define ifpin(p,what,ifnot)         (((p) >= 0 && (p) < NUM_DIGITAL_PINS) ? (what) : (ifnot))
#define digitalPinToPCICR(p)    ifpin(p,&PCICR,(uint8_t *)0)
#define digitalPinToPCICRbit(p) ifpin(p,digital_pin_to_pcint[p] >> 3,0)
#define digitalPinToPCMSK(p)    ifpin(p,(uint8_t *)PORT_NDX_TO_PCMSK(digital_pin_to_pcint[p] >> 3),(uint8_t *)0)
#define digitalPinToPCMSKbit(p) ifpin(p,digital_pin_to_pcint[p] & 0x7,0)


#ifndef ARDUINO_MAIN
extern const uint8_t digital_pin_to_pcint[];
#else
const uint8_t digital_pin_to_pcint[NUM_DIGITAL_PINS] =
{
  24, // D0 - PD0
  25, // D1 - PD1
  26, // D2 - PD2
  27, // D3 - PD3
  8,  // D4 - PB0
  9,  // D5 - PB1
  10, // D6 - PB2
  11, // D7 - PB3
  29, // D8 - PD5
  30, // D9 - PD6
  12, // D10 - PB4
  13, // D11 - PB5
  14, // D12 - PB6
  15, // D13 - PB7
  7,  // D14 - PA7
  6,  // D15 - PA6
  5,  // D16 - PA5
  4,  // D17 - PA4
  3,  // D18 - PA3
  2,  // D19 - PA2
  1,  // D20 - PA1
  0,  // D21 - PA0
  16, // D22 - PC0
  17, // D23 - PC1
  18, // D24 - PC2
  19, // D25 - PC3
  20, // D26 - PC4
  21, // D27 - PC5
  22, // D28 - PC6
  23, // D29 - PC7
  28, // D30 - PD4
  31, // D31 - PD7
#if defined(__AVR_ATmega324PB__)
  32, // D32 - PE0
  33, // D33 - PE1
  34, // D34 - PE2
  35, // D35 - PE3
  36, // D36 - PE4
  37, // D37 - PE5
  38, // D38 - PE6
#endif
};
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
  PD, // D0 - PD0
  PD, // D1 - PD1
  PD, // D2 - PD2
  PD, // D3 - PD3
  PB, // D4 - PB0
  PB, // D5 - PB1
  PB, // D6 - PB2
  PB, // D7 - PB3
  PD, // D8 - PD5
  PD, // D9 - PD6
  PB, // D10 - PB4
  PB, // D11 - PB5
  PB, // D12 - PB6
  PB, // D13 - PB7
  PA, // D14 - PA7
  PA, // D15 - PA6
  PA, // D16 - PA5
  PA, // D17 - PA4
  PA, // D18 - PA3
  PA, // D19 - PA2
  PA, // D20 - PA1
  PA, // D21 - PA0
  PC, // D22 - PC0
  PC, // D23 - PC1
  PC, // D24 - PC2
  PC, // D25 - PC3
  PC, // D26 - PC4
  PC, // D27 - PC5
  PC, // D28 - PC6
  PC, // D29 - PC7
  PD, // D30 - PD4
  PD, // D31 - PD7
#if defined(__AVR_ATmega324PB__)
  PE, // D32 - PE0
  PE, // D33 - PE1
  PE, // D34 - PE2
  PE, // D35 - PE3
  PE, // D36 - PE4
  PE, // D37 - PE5
  PE, // D38 - PE6
#endif
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] =
{
  _BV(0), // D0 - PD0
  _BV(1), // D1 - PD1
  _BV(2), // D2 - PD2
  _BV(3), // D3 - PD3
  _BV(0), // D4 - PB0
  _BV(1), // D5 - PB1
  _BV(2), // D6 - PB2
  _BV(3), // D7 - PB3
  _BV(5), // D8 - PD5
  _BV(6), // D9 - PD6
  _BV(4), // D10 - PB4
  _BV(5), // D11 - PB5
  _BV(6), // D12 - PB6
  _BV(7), // D13 - PB7
  _BV(7), // D14 - PA7
  _BV(6), // D15 - PA6
  _BV(5), // D16 - PA5
  _BV(4), // D17 - PA4
  _BV(3), // D18 - PA3
  _BV(2), // D19 - PA2
  _BV(1), // D20 - PA1
  _BV(0), // D21 - PA0
  _BV(0), // D22 - PC0
  _BV(1), // D23 - PC1
  _BV(2), // D24 - PC2
  _BV(3), // D25 - PC3
  _BV(4), // D26 - PC4
  _BV(5), // D27 - PC5
  _BV(6), // D28 - PC6
  _BV(7), // D29 - PC7
  _BV(4), // D30 - PD4
  _BV(7), // D31 - PD7
#if defined(__AVR_ATmega324PB__)
  _BV(0), // D32 - PE0
  _BV(1), // D33 - PE1
  _BV(2), // D34 - PE2
  _BV(3), // D35 - PE3
  _BV(4), // D36 - PE4
  _BV(5), // D37 - PE5
  _BV(6), // D38 - PE6
#endif
};

#if defined(__AVR_ATmega8535__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
  NOT_ON_TIMER, // D0 - PD0
  NOT_ON_TIMER, // D1 - PD1
  NOT_ON_TIMER, // D2 - PD2
  NOT_ON_TIMER, // D3 - PD3
  NOT_ON_TIMER, // D4 - PB0
  NOT_ON_TIMER, // D5 - PB1
  NOT_ON_TIMER, // D6 - PB2
  TIMER0A,      // D7 - PB3
  TIMER1A,      // D8 - PD5
  NOT_ON_TIMER, // D9 - PD6
  NOT_ON_TIMER, // D10 - PB4
  NOT_ON_TIMER, // D11 - PB5
  NOT_ON_TIMER, // D12 - PB6
  NOT_ON_TIMER, // D13 - PB7
  NOT_ON_TIMER, // D14 - PA7
  NOT_ON_TIMER, // D15 - PA6
  NOT_ON_TIMER, // D16 - PA5
  NOT_ON_TIMER, // D17 - PA4
  NOT_ON_TIMER, // D18 - PA3
  NOT_ON_TIMER, // D19 - PA2
  NOT_ON_TIMER, // D20 - PA1
  NOT_ON_TIMER, // D21 - PA0
  NOT_ON_TIMER, // D22 - PC0
  NOT_ON_TIMER, // D23 - PC1
  NOT_ON_TIMER, // D24 - PC2
  NOT_ON_TIMER, // D25 - PC3
  NOT_ON_TIMER, // D26 - PC4
  NOT_ON_TIMER, // D27 - PC5
  NOT_ON_TIMER, // D28 - PC6
  NOT_ON_TIMER, // D29 - PC7
  TIMER1B,      // D30 - PD4
  TIMER2,       // D31 - PD7
};

#elif defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega644A__) || \
defined(__AVR_ATmega644P__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
  NOT_ON_TIMER, // D0 - PD0
  NOT_ON_TIMER, // D1 - PD1
  NOT_ON_TIMER, // D2 - PD2
  NOT_ON_TIMER, // D3 - PD3
  NOT_ON_TIMER, // D4 - PB0
  NOT_ON_TIMER, // D5 - PB1
  NOT_ON_TIMER, // D6 - PB2
  TIMER0A,      // D7 - PB3
  TIMER1A,      // D8 - PD5
  TIMER2B,      // D9 - PD6
  TIMER0B,      // D10 - PB4
  NOT_ON_TIMER, // D11 - PB5
  NOT_ON_TIMER, // D12 - PB6
  NOT_ON_TIMER, // D13 - PB7
  NOT_ON_TIMER, // D14 - PA7
  NOT_ON_TIMER, // D15 - PA6
  NOT_ON_TIMER, // D16 - PA5
  NOT_ON_TIMER, // D17 - PA4
  NOT_ON_TIMER, // D18 - PA3
  NOT_ON_TIMER, // D19 - PA2
  NOT_ON_TIMER, // D20 - PA1
  NOT_ON_TIMER, // D21 - PA0
  NOT_ON_TIMER, // D22 - PC0
  NOT_ON_TIMER, // D23 - PC1
  NOT_ON_TIMER, // D24 - PC2
  NOT_ON_TIMER, // D25 - PC3
  NOT_ON_TIMER, // D26 - PC4
  NOT_ON_TIMER, // D27 - PC5
  NOT_ON_TIMER, // D28 - PC6
  NOT_ON_TIMER, // D29 - PC7
  TIMER1B,      // D30 - PD4
  TIMER2A,      // D31 - PD7
};

#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
  NOT_ON_TIMER, // D0 - PD0
  NOT_ON_TIMER, // D1 - PD1
  NOT_ON_TIMER, // D2 - PD2
  NOT_ON_TIMER, // D3 - PD3
  NOT_ON_TIMER, // D4 - PB0
  NOT_ON_TIMER, // D5 - PB1
  NOT_ON_TIMER, // D6 - PB2
  TIMER0A,      // D7 - PB3
  TIMER1A,      // D8 - PD5
  TIMER2B,      // D9 - PD6
  TIMER0B,      // D10 - PB4
  NOT_ON_TIMER, // D11 - PB5
  TIMER3A,      // D12 - PB6
  TIMER3B,      // D13 - PB7
  NOT_ON_TIMER, // D14 - PA7
  NOT_ON_TIMER, // D15 - PA6
  NOT_ON_TIMER, // D16 - PA5
  NOT_ON_TIMER, // D17 - PA4
  NOT_ON_TIMER, // D18 - PA3
  NOT_ON_TIMER, // D19 - PA2
  NOT_ON_TIMER, // D20 - PA1
  NOT_ON_TIMER, // D21 - PA0
  NOT_ON_TIMER, // D22 - PC0
  NOT_ON_TIMER, // D23 - PC1
  NOT_ON_TIMER, // D24 - PC2
  NOT_ON_TIMER, // D25 - PC3
  NOT_ON_TIMER, // D26 - PC4
  NOT_ON_TIMER, // D27 - PC5
  NOT_ON_TIMER, // D28 - PC6
  NOT_ON_TIMER, // D29 - PC7
  TIMER1B,      // D30 - PD4
  TIMER2A,      // D31 - PD7
};

#elif defined(__AVR_ATmega324PB__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
  NOT_ON_TIMER, // D0 - PD0
  NOT_ON_TIMER, // D1 - PD1
  NOT_ON_TIMER, // D2 - PD2
  NOT_ON_TIMER, // D3 - PD3
  NOT_ON_TIMER, // D4 - PB0
  NOT_ON_TIMER, // D5 - PB1
  NOT_ON_TIMER, // D6 - PB2
  TIMER0A,      // D7 - PB3
  TIMER1A,      // D8 - PD5
  TIMER2B,      // D9 - PD6
  TIMER0B,      // D10 - PB4
  NOT_ON_TIMER, // D11 - PB5
  TIMER3A,      // D12 - PB6
  TIMER3B,      // D13 - PB7
  NOT_ON_TIMER, // D14 - PA7
  NOT_ON_TIMER, // D15 - PA6
  NOT_ON_TIMER, // D16 - PA5
  NOT_ON_TIMER, // D17 - PA4
  NOT_ON_TIMER, // D18 - PA3
  NOT_ON_TIMER, // D19 - PA2
  NOT_ON_TIMER, // D20 - PA1
  NOT_ON_TIMER, // D21 - PA0
  NOT_ON_TIMER, // D22 - PC0
  NOT_ON_TIMER, // D23 - PC1
  NOT_ON_TIMER, // D24 - PC2
  NOT_ON_TIMER, // D25 - PC3
  TIMER4A,      // D26 - PC4
  NOT_ON_TIMER, // D27 - PC5
  NOT_ON_TIMER, // D28 - PC6
  NOT_ON_TIMER, // D29 - PC7
  TIMER1B,      // D30 - PD4
  TIMER2A,      // D31 - PD7
  NOT_ON_TIMER, // D32 - PE0
  NOT_ON_TIMER, // D33 - PE1
  NOT_ON_TIMER, // D34 - PE2
  NOT_ON_TIMER, // D35 - PE3
  NOT_ON_TIMER, // D36 - PE4
  NOT_ON_TIMER, // D37 - PE5
  NOT_ON_TIMER, // D38 - PE6
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

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.

#define SERIAL_PORT_MONITOR         Serial
#define SERIAL_PORT_HARDWARE        Serial
#define SERIAL_PORT_HARDWARE_OPEN   Serial

#if defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega324PB__) ||   \
defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284__) ||     \
defined(__AVR_ATmega1284P__)
#define SERIAL_PORT_HARDWARE1       Serial1
#define SERIAL_PORT_HARDWARE_OPEN1  Serial1
#endif

#if defined(__AVR_ATmega324PB__)
#define SERIAL_PORT_HARDWARE2       Serial2
#define SERIAL_PORT_HARDWARE_OPEN2  Serial2
#endif

#endif // Pins_Arduino_h
