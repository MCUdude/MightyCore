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

#define BOBUINO_PINOUT
#if defined(__AVR_ATmega324PB__)
#define NUM_DIGITAL_PINS            39
#else
#define NUM_DIGITAL_PINS            32
#endif
#define NUM_ANALOG_INPUTS           8
#define EXTERNAL_NUM_INTERRUPTS     3
#define analogInputToDigitalPin(p)  ((p < NUM_ANALOG_INPUTS) ? (p) + 14 : -1)
#define analogPinToChannel(p)       ((p) < NUM_ANALOG_INPUTS) ? (7 - (p)) : ((p)  >=  14 && (p) <= 21) ? (21 - (p)) : -1
#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 3 ? 1 : ((p) == 6 ? 2 : NOT_AN_INTERRUPT)))
#define ifpin(p,what,ifnot)         (((p) >= 0 && (p) < NUM_DIGITAL_PINS) ? (what) : (ifnot))

#if defined(__AVR_ATmega8535__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
#define digitalPinHasPWM(p)         ((p) == 7 || (p) == 8 || (p) == 30 || (p) == 31)

#elif defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega644__) || \
defined(__AVR_ATmega644P__)
#define digitalPinHasPWM(p)         ((p) == 7 || (p) == 8 || (p) == 9 || (p) == 10 || (p) == 30 || (p) == 31)

#elif defined(__AVR_ATmega324PB__)
#define digitalPinHasPWM(p)         ((p) == 7 || (p) == 8 || (p) == 9 || (p) == 10 || (p) == 12 || (p) == 13 || (p) == 26 || (p) == 30 || (p) == 31)

#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
#define digitalPinHasPWM(p)         ((p) == 7 || (p) == 8 || (p) == 9 || (p) == 10 || (p) == 12 || (p) == 13 || (p) == 30 || (p) == 31)
#endif


static const uint8_t SS   = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK  = 13;

static const uint8_t LED = 13;
#define LED_BUILTIN 13

static const uint8_t SDA = 23;
static const uint8_t SCL = 22;

#if defined(__AVR_ATmega324PB__)
static const uint8_t SS0   = 10;
static const uint8_t MOSI0 = 11;
static const uint8_t MISO0 = 12;
static const uint8_t SCK0  = 13;
static const uint8_t SDA0  = 23;
static const uint8_t SCL0  = 22;
static const uint8_t SS1   = 9;
static const uint8_t SCK1  = 31;
static const uint8_t MISO1 = 34;
static const uint8_t MOSI1 = 35;
static const uint8_t SDA1  = 37;
static const uint8_t SCL1  = 38;
#endif

static const uint8_t A0 = 14;
static const uint8_t A1 = 15;
static const uint8_t A2 = 16;
static const uint8_t A3 = 17;
static const uint8_t A4 = 18;
static const uint8_t A5 = 19;
static const uint8_t A6 = 20;
static const uint8_t A7 = 21;


#if defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega324PB__) || \
defined(__AVR_ATmega644__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284__) || \
defined(__AVR_ATmega1284P__)

#if defined(__AVR_ATmega324PB__)
#define PORT_NDX_TO_PCMSK(x) ((x) == 0 ? &PCMSK0 : ((x) == 1 ? &PCMSK1 : ((x) == 2 ? &PCMSK2 : ((x) == 3 ? &PCMSK3 : ((x) == 4 ? &PCMSK4 : (uint8_t )0)))))
#else
#define PORT_NDX_TO_PCMSK(x) ((x) == 0 ? &PCMSK0 : ((x) == 1 ? &PCMSK1 : ((x) == 2 ? &PCMSK2 : ((x) == 3 ? &PCMSK3 : (uint8_t )0))))
#endif
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

#if defined(__AVR_ATmega164PA__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__)\
|| defined(__AVR_ATmega324PA__)
/**** Needed to get the SD library to work. 
Missing definitions in the iom164.h/iom324.h file ****/
#define SPR0 SPR00
#define SPR1 SPR10
#define CPHA CPHA0
#define CPOL CPOL0
#define MSTR MSTR0
#define DORD DORD0
#define SPE SPE0
#define SPIE SPIE0
#define SPSR SPSR0
#define SPI2X SPI2X0
#define WCOL WCOL0
#define SPIF SPIF0
#define SPCR SPCR0
#define SPDR SPDR0
#endif

// Missing definitions in iom324pb.h file
#if defined(__AVR_ATmega324PB__)
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
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega644__) || \
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

#endif // Pins_Arduino_h

// vim:ai:cin:sts=2 sw=2 ft=cpp
