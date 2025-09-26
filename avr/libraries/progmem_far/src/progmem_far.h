/* Arduino library: progmem_far.h
 *
 * Version: 1.0.2
 *
 * Copyright: Bernhard Nebel 2025
 *
 * This library is free software (MIT license). It provides 
 * the missing PROGMEM_FAR macro for Arduino. This macro
 * can be used to place constant data into flash at a memory 
 * location, where it is not interfering with data that needs to be 
 * located in the first 64k bytes of flash memory. You then 
 * have to use the macros pgm_read_byte_far, pgm_read_word_far, 
 * pgm_read_dward_far, pgm_read_float_near, pgm_read_ptr_far. 
 * The parameter to these macros is always a 32-bit address,
 * which can be determined by pgm_get_far_address. 
 *
 * v1.0.0
 * - first working version
 *
 * v1.0.1
 * - renamed the termination function to something hopefully not clashing wit the user sketch
 * - added weak attribute so that it can be imported into more than one translation unit
 * - put an include guard around it
 *
 * v1.0.2
 * - added an example sketch demonstrating the silent failures 
 * - added another example that demonstrates the simple fix by using PROGMEM_FAR
 * - renamed the termination function once more
 *
 * v1.0.3
 * - fixed includes for example sketches
 */

#ifndef PROGMEM_FAR_H
#define PROGMEM_FAR_H

// We (ab-)use the linker section .fini0, the last section in the .text segment, as the progmem_far segment
#define PROGMEM_FAR __attribute__((section (".fini0")))

// In order to make sure that after program termination, we end up in an
// infinite loop, we make use of the user-definable section .fini1, which
// is placed immediately before .fini0
void __terminate_program_before_entering_progmem_section__(void) __attribute__((naked, section(".fini1"), used, weak));
void __terminate_program_before_entering_progmem_section__(void)
{
  while(1);
}


#endif
