#!/bin/bash
progmem_end=`$1 -t d $2 | grep __ctors_start | cut -d ' ' -f 1`
if [ "x$progmem_end" != "x" ] && [ $progmem_end -gt 65535 ]; then
    warning="| Severe Warning: PROGMEM section too large by $(expr $progmem_end - 65535) bytes.            "
    echo "_______________________________________________________________"
    echo "${warning:0:62}|"
    echo "| Your program will most probably be unstable!                |"
    echo "| Use the macro PROGMEM_FAR from <progmem_far.h> and          |"
    echo "| pgm_get_far_address/pgm_read_xxxx_far from <avr/pgmspace.h>.|"
    echo "|_____________________________________________________________|"
fi
