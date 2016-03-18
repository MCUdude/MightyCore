#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>
/*

		   MIGHTYCORE BOBUINO PINOUT
          ATmega8535, ATmega16, ATmega32, ATmega164, 
               ATmega324, ATmega644, ATmega1284
   	 
  	     	          +---\/---+
              (D 4) PB0  1|        |40  PA0 (A 7 / D21)
              (D 5) PB1  2|        |39  PA1 (A 6 / D20)
         INT2 (D 6) PB2  3|        |38  PA2 (A 5 / D19)
          PWM (D 7) PB3  4|        |37  PA3 (A 4 / D18)
    PWM* /SS (D 10) PB4  5|        |36  PA4 (A 3 / D17)
        MOSI (D 11) PB5  6|        |35  PA5 (A 2 / D16)
 PWM** /MISO (D 12) PB6  7|        |34  PA6 (A 1 / D15)
  PWM** /SCK (D 13) PB7  8|        |33  PA7 (A 0 / D14)
                    RST  9|        |32  AREF
                    VCC 10|        |31  GND 
                    GND 11|        |30  AVCC
                  XTAL2 12|        |29  PC7 (D 29)
                  XTAL1 13|        |28  PC6 (D 28)
          RX0 (D 0) PD0 14|        |27  PC5 (D 27) TDI
          TX0 (D 1) PD1 15|        |26  PC4 (D 26) TDO
   (RX1)/INT0 (D 2) PD2 16|        |25  PC3 (D 25) TMS
   (TX1)/INT1 (D 3) PD3 17|        |24  PC2 (D 24) TCK
         PWM (D 30) PD4 18|        |23  PC1 (D 23) SDA
          PWM (D 8) PD5 19|        |22  PC0 (D 22) SCL
         PWM* (D 9) PD6 20|        |21  PD7 (D 31) PWM
                          +--------+
   	    PWM: ATmega8535/16/32/164/324/644/1284
		PWM*: ATmega164/324/644/1284
		      PWM**: ATmega1284

PCINT ONLY ON ATmega164/324/644/1284
   
*/

#define BOBUINO_PINOUT
#define NUM_DIGITAL_PINS            32
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < NUM_ANALOG_INPUTS) ? (p) + 14 : -1)
#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : ((p) == 6 ? 2 : NOT_AN_INTERRUPT)))
#define ifpin(p,what,ifnot)         (((p) >= 0 && (p) < NUM_DIGITAL_PINS) ? (what) : (ifnot))

#if defined(__AVR_ATmega8535__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
#define digitalPinHasPWM(p)         ((p) == 7 || (p) == 8 || (p) == 30 || (p) == 31)

#elif defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega644__) || \
defined(__AVR_ATmega644P__)
#define digitalPinHasPWM(p)         ((p) == 7 || (p) == 8 || (p) == 9 || (p) == 10 || (p) == 30 || (p) == 31)

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

static const uint8_t A0 = 14;
static const uint8_t A1 = 15;
static const uint8_t A2 = 16;
static const uint8_t A3 = 17;
static const uint8_t A4 = 18;
static const uint8_t A5 = 19;
static const uint8_t A6 = 20;
static const uint8_t A7 = 21;


#if defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)
/**** Needed to get the SD library to work. 
Missing definitions in the iom164.h/iom324.h file ****/
#define SPR0 0
#define SPR1 1
#define CPHA 2
#define CPOL 3
#define MSTR 4
#define DORD 5
#define SPE 6
#define SPIE 7
#define SPSR _SFR_IO8(0x2D)
#define SPI2X 0
#define WCOL 6
#define SPIF 7
#define SPCR _SFR_IO8(0x2C)
#define SPDR _SFR_IO8(0x2E)
#endif


#ifdef ARDUINO_MAIN

#define PA 1
#define PB 2
#define PC 3
#define PD 4


#if defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324A__) || \
defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega644__) || \
defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
extern const uint8_t digital_pin_to_pcint[NUM_DIGITAL_PINS];
extern const uint16_t __pcmsk[];
extern const uint8_t digital_pin_to_timer_PGM[NUM_DIGITAL_PINS];
#define PORT_NDX_TO_PCMSK(x) ((x) == 0 ? &PCMSK0 : ((x) == 1 ? &PCMSK1 : ((x) == 2 ? &PCMSK2 : ((x) == 3 ? &PCMSK3 : (uint8_t )0))))
#define digitalPinToPCICR(p)    ifpin(p,&PCICR,(uint8_t *)0)
#define digitalPinToPCICRbit(p) ifpin(p,digital_pin_to_pcint[p] >> 3,0)
#define digitalPinToPCMSK(p)    ifpin(p,(uint8_t *)PORT_NDX_TO_PCMSK(digital_pin_to_pcint[p] >> 3),(uint8_t *)0)
#define digitalPinToPCMSKbit(p) ifpin(p,digital_pin_to_pcint[p] & 0x7,0)

const uint16_t PROGMEM __pcmsk[] = 
{
  	(uint16_t)&PCMSK0, 
  	(uint16_t)&PCMSK1, 
  	(uint16_t)&PCMSK2, 
  	(uint16_t)&PCMSK3
};

const uint8_t PROGMEM digital_pin_to_pcint[NUM_DIGITAL_PINS] =
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
};
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
};

const uint16_t PROGMEM port_to_output_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
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
  	_BV(7)  // D31 - PD7
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
  	TIMER0A, 	  // D7 - PB3
  	TIMER1A, 	  // D8 - PD5
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
  	TIMER1B, 	  // D30 - PD4
  	TIMER2, 	  // D31 - PD7
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
  	TIMER0A, 	  // D7 - PB3
  	TIMER1A, 	  // D8 - PD5
  	TIMER2B, 	  // D9 - PD6
  	TIMER0B, 	  // D10 - PB4
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
  	TIMER1B, 	  // D30 - PD4
  	TIMER2A, 	  // D31 - PD7
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
  	TIMER0A, 	  // D7 - PB3
  	TIMER1A, 	  // D8 - PD5
  	TIMER2B, 	  // D9 - PD6
  	TIMER0B, 	  // D10 - PB4
  	NOT_ON_TIMER, // D11 - PB5
  	TIMER3A, 	  // D12 - PB6
  	TIMER3B, 	  // D13 - PB7
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
  	TIMER1B, 	  // D30 - PD4
  	TIMER2A, 	  // D31 - PD7
};

#endif // Timer defs

#endif // ARDUINO_MAIN

#endif // Pins_Arduino_h

// vim:ai:cin:sts=2 sw=2 ft=cpp
