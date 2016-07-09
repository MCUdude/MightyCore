# Makefile for ATmegaBOOT
# E.Lins, 18.7.2005
# $Id$
#
# Instructions
#
# To make bootloader .hex file:
# make diecimila
# make lilypad
# make ng
# etc...
#
# To burn bootloader .hex file:
# make diecimila_isp
# make lilypad_isp
# make ng_isp
# etc...
#
# Edit History
# 201406xx: WestfW: More Makefile restructuring.
#                   Split off Makefile.1284, Makefile.extras, Makefile.custom
#                   So that in theory, the main Makefile contains only the
#                   official platforms, and does not need to be modified to
#                   add "less supported" chips and boards.
# 201303xx: WestfW: Major Makefile restructuring.
#                   Allows options on Make command line "make xx LED=B3"
#                   (see also pin_defs.h)
#                   Divide into "chip" targets and "board" targets.
#                   Most boards are (recursive) board targets with options.
#                   Move isp target to separate makefile (fixes m8 EFUSE)
#                   Some (many) targets will now be rebuilt when not
#                     strictly necessary, so that options will be included.
#                     (any "make" with options will always compile.)
#                   Set many variables with ?= so they can be overridden
#                   Use arduinoISP settings as default for ISP targets
#
#
# * Copyright 2013-2015 by Bill Westfield.  Part of Optiboot.
# * This software is licensed under version 2 of the Gnu Public Licence.
# * See optiboot.c for details.

#----------------------------------------------------------------------
#
# program name should not be changed...
PROGRAM    = optiboot_flash

# The default behavior is to build using tools that are in the users
# current path variables, but we can also build using an installed
# Arduino user IDE setup, or the Arduino source tree.
# Uncomment this next lines to build within the arduino environment,
# using the arduino-included avrgcc toolset (mac and pc)
# ENV ?= arduino
# ENV ?= arduinodev
# OS ?= macosx
# OS ?= windows

# export symbols to recursive makes (for ISP)
export

# defaults
MCU_TARGET = atmega168
LDSECTIONS  = -Wl,--section-start=.text=0x3e00 -Wl,--section-start=.version=0x3ffe

# Build environments
# Start of some ugly makefile-isms to allow optiboot to be built
# in several different environments.  See the README.TXT file for
# details.

# default
fixpath = $(1)
SH := bash

ifeq ($(ENV), arduino)
# For Arduino, we assume that we're connected to the optiboot directory
# included with the arduino distribution, which means that the full set
# of avr-tools are "right up there" in standard places.
# (except that in 1.5.x, there's an additional level of "up")
TESTDIR := $(firstword $(wildcard ../../../tools/*))
ifeq (,$(TESTDIR))
# Arduino 1.5.x tool location compared to optiboot dir
  TOOLROOT = ../../../../tools
else
# Arduino 1.0 (and earlier) tool location
  TOOLROOT = ../../../tools
endif
GCCROOT = $(TOOLROOT)/avr/bin/

ifeq ($(OS), windows)
# On windows, SOME of the tool paths will need to have backslashes instead
# of forward slashes (because they use windows cmd.exe for execution instead
# of a unix/mingw shell?)  We also have to ensure that a consistent shell
# is used even if a unix shell is installed (ie as part of WINAVR)
fixpath = $(subst /,\,$1)
SHELL = cmd.exe
SH = sh
endif

else ifeq ($(ENV), arduinodev)
# Arduino IDE source code environment.  Use the unpacked compilers created
# by the build (you'll need to do "ant build" first.)
ifeq ($(OS), macosx)
TOOLROOT = ../../../../build/macosx/work/Arduino.app/Contents/Resources/Java/hardware/tools
endif
ifeq ($(OS), windows)
TOOLROOT = ../../../../build/windows/work/hardware/tools
endif

GCCROOT = $(TOOLROOT)/avr/bin/
AVRDUDE_CONF = -C$(TOOLROOT)/avr/etc/avrdude.conf

else
GCCROOT =
AVRDUDE_CONF =
endif

STK500 = "C:\Program Files\Atmel\AVR Tools\STK500\Stk500.exe"
STK500-1 = $(STK500) -e -d$(MCU_TARGET) -pf -vf -if$(PROGRAM)_$(TARGET).hex \
           -lFF -LFF -f$(HFUSE)$(LFUSE) -EF8 -ms -q -cUSB -I200kHz -s -wt
STK500-2 = $(STK500) -d$(MCU_TARGET) -ms -q -lCF -LCF -cUSB -I200kHz -s -wt
#
# End of build environment code.


OBJ        = $(PROGRAM).o
OPTIMIZE = -Os -fno-split-wide-types -mrelax

DEFS       = 

#
# platforms support EEPROM and large bootloaders need the eeprom functions that
# are defined in libc, even though we explicity remove it with -nostdlib because
# of the space-savings.
LIBS       =  -lc

CC         = $(GCCROOT)avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) -DF_CPU=$(AVR_FREQ) $(DEFS)
override LDFLAGS       = $(LDSECTIONS) -Wl,--relax -nostartfiles -nostdlib
#-Wl,--gc-sections

OBJCOPY        = $(GCCROOT)avr-objcopy
OBJDUMP        = $(call fixpath,$(GCCROOT)avr-objdump)

SIZE           = $(GCCROOT)avr-size

#
# Make command-line Options.
# Permit commands like "make atmega328 LED_START_FLASHES=10" to pass the
# appropriate parameters ("-DLED_START_FLASHES=10") to gcc
#

ifdef BAUD_RATE
BAUD_RATE_CMD = -DBAUD_RATE=$(BAUD_RATE)
dummy = FORCE
else
BAUD_RATE_CMD = -DBAUD_RATE=115200
endif

ifdef LED_START_FLASHES
LED_START_FLASHES_CMD = -DLED_START_FLASHES=$(LED_START_FLASHES)
dummy = FORCE
else
LED_START_FLASHES_CMD = -DLED_START_FLASHES=3
endif

# BIG_BOOT: Include extra features, up to 1K.
ifdef BIGBOOT
BIGBOOT_CMD = -DBIGBOOT=1
dummy = FORCE
endif

ifdef SOFT_UART
SOFT_UART_CMD = -DSOFT_UART=1
dummy = FORCE
endif

ifdef LED_DATA_FLASH
LED_DATA_FLASH_CMD = -DLED_DATA_FLASH=1
dummy = FORCE
endif

ifdef LED
LED_CMD = -DLED=$(LED)
dummy = FORCE
endif

ifdef SINGLESPEED
SSCMD = -DSINGLESPEED=1
endif

COMMON_OPTIONS = $(BAUD_RATE_CMD) $(LED_START_FLASHES_CMD) $(BIGBOOT_CMD)
COMMON_OPTIONS += $(SOFT_UART_CMD) $(LED_DATA_FLASH_CMD) $(LED_CMD) $(SSCMD)

#UART is handled separately and only passed for devices with more than one.
ifdef UART
UARTCMD = -DUART=$(UART)
endif

# Not supported yet
# ifdef SUPPORT_EEPROM
# SUPPORT_EEPROM_CMD = -DSUPPORT_EEPROM
# dummy = FORCE
# endif

# Not supported yet
# ifdef TIMEOUT_MS
# TIMEOUT_MS_CMD = -DTIMEOUT_MS=$(TIMEOUT_MS)
# dummy = FORCE
# endif
#

#.PRECIOUS: %.elf

#---------------------------------------------------------------------------
# "Chip-level Platform" targets.
# A "Chip-level Platform" compiles for a particular chip, but probably does
# not have "standard" values for things like clock speed, LED pin, etc.
# Makes for chip-level platforms should usually explicitly define their
# options like: "make atmega1285 AVR_FREQ=16000000L LED=D0"
#---------------------------------------------------------------------------
#
# Note about fuses:
# the efuse should really be 0xf8; since, however, only the lower
# three bits of that byte are used on the atmega168, avrdude gets
# confused if you specify 1's for the higher bits, see:
# http://tinker.it/now/2007/02/24/the-tale-of-avrdude-atmega168-and-extended-bits-fuses/
#
# similarly, the lock bits should be 0xff instead of 0x3f (to
# unlock the bootloader section) and 0xcf instead of 0x2f (to
# lock it), but since the high two bits of the lock byte are
# unused, avrdude would get confused.
#---------------------------------------------------------------------------
#


# ATmega8535/A
atmega8535: TARGET = atmega8535
atmega8535: MCU_TARGET = atmega8535
atmega8535: CFLAGS += $(COMMON_OPTIONS)
atmega8535: AVR_FREQ ?= 16000000L
atmega8535: LDSECTIONS = -Wl,--section-start=.text=0x1e00 -Wl,--section-start=.version=0x1ffe
atmega8535: atmega8535/$(PROGRAM)_atmega8535_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega8535: atmega8535/$(PROGRAM)_atmega8535_$(BAUD_RATE)_$(AVR_FREQ).lst
atmega8535a: atmega8535


# ATmega16/A
atmega16: TARGET = atmega16
atmega16: MCU_TARGET = atmega16
atmega16: CFLAGS += $(COMMON_OPTIONS)
atmega16: AVR_FREQ ?= 16000000L
atmega16: LDSECTIONS  = -Wl,--section-start=.text=0x3e00 -Wl,--section-start=.version=0x3ffe
atmega16: atmega16/$(PROGRAM)_atmega16_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega16: atmega16/$(PROGRAM)_atmega16_$(BAUD_RATE)_$(AVR_FREQ).lst
atmega16a: atmega16


# ATmega32/A
atmega32: TARGET = atmega32
atmega32: MCU_TARGET = atmega32
atmega32: CFLAGS += $(COMMON_OPTIONS)
atmega32: AVR_FREQ ?= 16000000L
atmega32: LDSECTIONS  = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe
atmega32: atmega32/$(PROGRAM)_atmega32_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega32: atmega32/$(PROGRAM)_atmega32_$(BAUD_RATE)_$(AVR_FREQ).lst
atmega32a: atmega32


# ATmega164/A
atmega164a: TARGET = atmega164a
atmega164a: MCU_TARGET = atmega164a
atmega164a: CFLAGS += $(COMMON_OPTIONS)
atmega164a: AVR_FREQ ?= 16000000L
atmega164a: LDSECTIONS  = -Wl,--section-start=.text=0x3e00
atmega164a: CFLAGS += $(UARTCMD)
atmega164a: atmega164a/$(PROGRAM)_atmega164a_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega164a: atmega164a/$(PROGRAM)_atmega164a_$(BAUD_RATE)_$(AVR_FREQ).lst
atmega164: atmega164a


# ATmega164P/PA
atmega164p: TARGET = atmega164p
atmega164p: MCU_TARGET = atmega164p
atmega164p: CFLAGS += $(COMMON_OPTIONS)
atmega164p: AVR_FREQ ?= 16000000L
atmega164p: LDSECTIONS  = -Wl,--section-start=.text=0x3e00
atmega164p: CFLAGS += $(UARTCMD)
atmega164p: atmega164p/$(PROGRAM)_atmega164p_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega164p: atmega164p/$(PROGRAM)_atmega164p_$(BAUD_RATE)_$(AVR_FREQ).lst
atmega164pa: atmega164p


# ATmega324A
atmega324a: TARGET = atmega324a
atmega324a: MCU_TARGET = atmega324a
atmega324a: CFLAGS += $(COMMON_OPTIONS)
atmega324a: AVR_FREQ ?= 16000000L
atmega324a: LDSECTIONS  = -Wl,--section-start=.text=0x7e00
atmega324a: CFLAGS += $(UARTCMD)
atmega324a: atmega324a/$(PROGRAM)_atmega324a_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega324a: atmega324a/$(PROGRAM)_atmega324a_$(BAUD_RATE)_$(AVR_FREQ).lst
atmega324: atmega324a


# ATmega324P
atmega324p: TARGET = atmega324p
atmega324p: MCU_TARGET = atmega324p
atmega324p: CFLAGS += $(COMMON_OPTIONS)
atmega324p: AVR_FREQ ?= 16000000L
atmega324p: LDSECTIONS  = -Wl,--section-start=.text=0x7e00
atmega324p: CFLAGS += $(UARTCMD)
atmega324p: atmega324p/$(PROGRAM)_atmega324p_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega324p: atmega324p/$(PROGRAM)_atmega324p_$(BAUD_RATE)_$(AVR_FREQ).lst


# ATmega324PA
atmega324pa: TARGET = atmega324pa
atmega324pa: MCU_TARGET = atmega324pa
atmega324pa: CFLAGS += $(COMMON_OPTIONS)
atmega324pa: AVR_FREQ ?= 16000000L
atmega324pa: LDSECTIONS  = -Wl,--section-start=.text=0x7e00
atmega324pa: CFLAGS += $(UARTCMD)
atmega324pa: atmega324pa/$(PROGRAM)_atmega324pa_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega324pa: atmega324pa/$(PROGRAM)_atmega324pa_$(BAUD_RATE)_$(AVR_FREQ).lst


# ATmega644/A
atmega644: TARGET = atmega644
atmega644: MCU_TARGET = atmega644
atmega644: CFLAGS += $(COMMON_OPTIONS) -DBIGBOOT
atmega644: AVR_FREQ ?= 16000000L
atmega644: LDSECTIONS  = -Wl,--section-start=.text=0xfc00 -Wl,--section-start=.version=0xfffe
atmega644: CFLAGS += $(UARTCMD)
atmega644: atmega644/$(PROGRAM)_atmega644_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega644: atmega644/$(PROGRAM)_atmega644_$(BAUD_RATE)_$(AVR_FREQ).lst
atmega644a: atmega644

# ATmega644P/PA
atmega644p: TARGET = atmega644p
atmega644p: MCU_TARGET = atmega644p
atmega644p: CFLAGS += $(COMMON_OPTIONS) -DBIGBOOT
atmega644p: AVR_FREQ ?= 16000000L
atmega644p: LDSECTIONS  = -Wl,--section-start=.text=0xfc00 -Wl,--section-start=.version=0xfffe
atmega644p: CFLAGS += $(UARTCMD)
atmega644p: atmega644p/$(PROGRAM)_atmega644p_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega644p: atmega644p/$(PROGRAM)_atmega644p_$(BAUD_RATE)_$(AVR_FREQ).lst
atmega644pa: atmega644p


# ATmega1284
atmega1284: TARGET = atmega1284
atmega1284: MCU_TARGET = atmega1284
atmega1284: CFLAGS += $(COMMON_OPTIONS) -DBIGBOOT
atmega1284: AVR_FREQ ?= 16000000L
atmega1284: LDSECTIONS  = -Wl,--section-start=.text=0x1fc00 -Wl,--section-start=.version=0x1fffe
atmega1284: CFLAGS += $(UARTCMD)
atmega1284: atmega1284/$(PROGRAM)_atmega1284_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega1284: atmega1284/$(PROGRAM)_atmega1284_$(BAUD_RATE)_$(AVR_FREQ).lst


# ATmega1284P
atmega1284p: TARGET = atmega1284p
atmega1284p: MCU_TARGET = atmega1284p
atmega1284p: CFLAGS += $(COMMON_OPTIONS) -DBIGBOOT
atmega1284p: AVR_FREQ ?= 16000000L
atmega1284p: LDSECTIONS  = -Wl,--section-start=.text=0x1fc00 -Wl,--section-start=.version=0x1fffe
atmega1284p: CFLAGS += $(UARTCMD)
atmega1284p: atmega1284p/$(PROGRAM)_atmega1284p_$(BAUD_RATE)_$(AVR_FREQ).hex
atmega1284p: atmega1284p/$(PROGRAM)_atmega1284p_$(BAUD_RATE)_$(AVR_FREQ).lst


#---------------------------------------------------------------------------
#
# Generic build instructions
#

FORCE:

baudcheck: FORCE
	- @$(CC) --version
	- @$(CC) $(CFLAGS) -E baudcheck.c -o baudcheck.tmp.sh
	- @$(SH) baudcheck.tmp.sh

isp: $(TARGET)
	$(MAKE) -f Makefile.isp isp TARGET=$(TARGET)

isp-stk500: $(PROGRAM)_$(TARGET).hex
	$(STK500-1)
	$(STK500-2)

%.elf: $(OBJ) baudcheck $(dummy)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)
	$(SIZE) $@

clean:
	rm -rf *.o *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex *.tmp.sh
	rm -rf atmega8535/*.hex atmega8535/*.lst
	rm -rf atmega16/*.hex atmega16/*.lst
	rm -rf atmega32/*.hex atmega32/*.lst
	rm -rf atmega164a/*.hex atmega164a/*.lst
	rm -rf atmega164p/*.hex atmega164p/*.lst
	rm -rf atmega324a/*.hex atmega324a/*.lst
	rm -rf atmega324p/*.hex atmega324p/*.lst
	rm -rf atmega324pa/*.hex atmega324pa/*.lst
	rm -rf atmega644/*.hex atmega644/*.lst
	rm -rf atmega644p/*.hex atmega644p/*.lst
	rm -rf atmega1284/*.hex atmega1284/*.lst
	rm -rf atmega1284p/*.hex atmega1284p/*.lst

clean_asm:
	rm -rf atmega8535/*.lst
	rm -rf atmega16/*.lst
	rm -rf atmega32/*.lst
	rm -rf atmega164a/*.lst
	rm -rf atmega164p/*.lst
	rm -rf atmega324a/*.lst
	rm -rf atmega324p/*.lst
	rm -rf atmega324pa/*.lst
	rm -rf atmega644/*.lst
	rm -rf atmega644p/*.lst
	rm -rf atmega1284/*.lst
	rm -rf atmega1284p/*.lst



%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O binary $< $@
