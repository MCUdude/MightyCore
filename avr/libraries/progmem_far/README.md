# PROGMEM_FAR: The missing macro

Have you ever dealt with PROGMEM data that exceeded the 64kB limit? And then wondered, why did your program started to behave completely strangely? This (tiny) library provides a cure to that problem. 

Certain PROGMEM data needs to be necessarily located in the first 64kB of flash memory. This includes lookup tables for core functions such as digitalWrite and strings stored in flash memory. If you put too much data into flash memory, then lookup tables or strings might end up somewhere above the limit and cannot be accessed any longer by the ordinary library macros. This could mean that the LED no longer blinks, the outputs appear garbled, or that you cannot access the data you placed in a PROGMEM array. The example sketch `progmem_fail` demonstrates all that. 

If you have such a large amount of constant data, probably some of it does not need to be accessed efficiently using 16-bit addressing by the ordinary library functions. Instead it is enough to use the slower and more cumbersome access with 32-bit addresses. For this purpose, the following macros exist in the `pgmspace.h` library:

- `pgm_get_far_address`(\<var\>) returns a 32-bit address of the variable \<var\> stored in flash, 
- `pgm_get_byte_far`(\<32-bit address\>) returns a byte value from the 32-bit address given as the argument,
- `pgm_get_word_far`(\<32-bit address\>) returns a word value from the 32-bit address given as the argument, etc.

In addition, there are also special string functions with the `_PF` suffix that can deal with strings that are addressable using 32-bit addresses.

However, is there a way to make sure that data is stored at the 'far' end of the flash memory so that it does not interfere with strings and lookup tables? Avr-libc, version 2.2.0, contains the macro `PROGMEM_FAR`  for this purpose. However, the Arduino code base still uses version 2.0.0. This library helps out by providing the missing macro. The macro PROGMEM_FAR defined here pushes PROGMEM data to locations that do not interfere with PROGMEM data that needs to reside in the first 64 kB. The example sketch `progmem_repaired` shows that this solves indeed all the problems demonstrated in `progmem_fail`.
