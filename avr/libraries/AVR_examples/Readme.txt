This library contains a few example that shows how to write "pure" AVR C code using the Arduino IDE. It also contains a fairy large keywords.txt file which contains all register and bit names (and most library functions and definitions) for all microcontrollers supported by the MightyCore. The keywords file will make Arduino IDE highlight these bit and register names, making it easier to read and write AVR code using the IDE.

If you're using Arduino IDE 1.6.5 or lower, you'll have to select a MightyCore compatible microcontroller and restart the IDE in order to highlight the keywords.

There are some minor differences between the ATmega8535/16/32 and ATmega164/324/644/1284 when it comes to register name. Read more about these differences in the AVR505 application note: http://www.atmel.com/Images/doc8001.pdf

Make sure to use the preprocessor's  #define, #ifdef, #if, #elif, #else and #elseif in order to make your code hardware independent (see example Blink_using_Timer0).