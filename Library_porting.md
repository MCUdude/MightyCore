# MightyCore library porting
If you have used this core for a while, you might have discovered that some 3rd party libraries don't work with these microcontrollers. 
The ATmega8535, ATmega16 and ATmega32 are particularly vulnerable, while the newer generation (ATmega164, ATmega324, ATmega644 and ATmega1284) mostly work without modifications. Here's why: </br>

According to the [AVR505 Application note](http://www.atmel.com/Images/doc8001.pdf) which was released in 2006, the ATmega164/324 (as well as 644/1284) are new and enhanced versions of the ATmega16/32.
They feature lower power consumption, lower operating voltages and an extra USART port, but also different register names. These names are the ones that break compatibility.
While the new generation (ATmega164/324/644/1284) share the same register names as the ATmega168/328, the "old" generation (ATmega8535/16/32) share the same register names as the ATmega8. </br>
Just remember that the ATmega8535/16/32 doesn't have more than 4 PWM outputs and no pin change interrupt (PCINT), so some libraries (like SoftwareSerial) will never work.

<b>Here's how to port a library</b>
* Download your library and open the header file (the one that ends with *.h)
* Copy the code below and paste it in the first line of the header file.
* Save and close. <b>The library should now be working!</b>

<b>Why am I still getting an error message?</b>
* The library is using a PWM pin that's not supported. Only digital pins 3, 12, 13 and 15 support PWM on ATmega8535/16/32 (using the standard pinout)
* The library relies on pin change interrupt (which the ATmega8535/16/32 doesn't support)
* You haven't pasted the code in the correct header file


``` c++
#if defined(__AVR_ATmega8535__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
//Register names
#define OCR0A   OCR0
#define EIMSK   GICR
#define EIFR    GIFR
#define TIMSK0  TIMSK
#define TIMSK1  TIMSK
#define TIMSK2  TIMSK
#define TIFR0   TIFR
#define TIFR1   TIFR
#define TIFR2   TIFR
#define SPMCSR  SPMCR
#define SMCR    MCUCR
#define EICRA   MCUCR
#define MCUSR   MCUCSR
#define TCCR0A  TCCR0
#define ADCSRB  SFIOR
#define TCCR2A  TCCR2
#define OCR2A   OCR2
#define WDTCSR  WDTCR
#define UBRR0H  UBRRH
#define UCSR0C  UCSRC
#define UDR0    UDR
#define UCSR0A  UCSRA
#define UCSR0B  UCSRB
#define UBRR0L  UBRRL

//Bit names
#define OCIE2A  OCIE2
#define ICIE1   TICIE1
#define OCIE0A  OCIE0
#define OCF2A   OCF2
#define OCF0A   OCF0
#define ISC20   ISC2
#define FOC0A   FOC0
#define COM0A1  COM01
#define COM0A0  COM00
#define PSRASY  PSR2
#define PSRSYNC PSR10
#define FOC2A   FOC2
#define COM2A1  COM21
#define COM2A0  COM20
#define OCR2AUB OCR2UB
#define TCR2AUB TCR2UB
#define UMSEL00 UMSEL
#define UPM10   UPM1
#define UPM00   UPM0
#define USBS0   USBS
#define UCSZ00  UCSZ1
#define UCSZ10  UCSZ2
#define UCPOL0  UCPOL
#define RXC0    RXC
#define TXC0    TXC
#define UDRE0   UDRE
#define FE0     FE
#define DOR0    DOR
#define UPE0    PE
#define U2X0    U2X
#define MPCM0   MPCM
#define RXCIE0  RXCIE
#define TXCIE0  TXCIE
#define UDRIE0  UDRIE
#define RXEN0   RXEN
#define TXEN0   TXEN
#define UCSZ02  UCSZ2
#define RXB80   RXB8
#define TXB80   TXB8

//Interrupt vectors
#define TIMER2_COMPA_vect     TIMER2_COMP_vect
#define TIMER2_COMPA_vect_num TIMER2_COMP_vect_num
#define TIMER0_COMPA_vect     TIMER0_COMP_vect
#define TIMER0_COMPA_vect_num TIMER0_COMP_vect_num 
#define USART0_RX_vect        USART_RXC_vect
#define USART0_RX_vect_num    USART_RXC_vect_num
#define USART0_UDRE_vect      USART_UDRE_vect
#define USART0_UDRE_vect_num  USART_UDRE_vect_num
#define USART0_TX_vect        USART_TXC_vect
#define USART0_TX_vect_num    USART_TXC_vect_num
#define ANALOG_COMP_vect      ANA_COMP_vect
#define ANALOG_COMP_vect_num  ANA_COMP_vect_num
#endif
```


