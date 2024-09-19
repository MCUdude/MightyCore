Note that autobaud bootloaders normally can only detect host baud rates = f/8, f/16, ... f/2048 +/- 1.5%, where f=F<sub>CPU</sub>. Internal oscillators have a high unknown deviation: baud rates under f/260 are recommended for these.

|Size|Usage|Version|Features|Hex file|
|:-:|:-:|:-:|:-:|:--|
|256|256|u8.0|`w---jPra-`|[urboot_atmega324a.hex](https://raw.githubusercontent.com/stefanrueger/urboot.hex/main/cores/mightycore/atmega324a/watchdog_1_s/autobaud/uart1_rxd2_txd3/led%2Bb7/urboot_atmega324a.hex)|
|256|256|u8.0|`w---jPra-`|[urboot_atmega324a_pr.hex](https://raw.githubusercontent.com/stefanrueger/urboot.hex/main/cores/mightycore/atmega324a/watchdog_1_s/autobaud/uart1_rxd2_txd3/led%2Bb7/urboot_atmega324a_pr.hex)|
|368|384|u8.0|`w-U-jPrac`|[urboot_atmega324a_pr_ce.hex](https://raw.githubusercontent.com/stefanrueger/urboot.hex/main/cores/mightycore/atmega324a/watchdog_1_s/autobaud/uart1_rxd2_txd3/led%2Bb7/urboot_atmega324a_pr_ce.hex)|
|378|384|u8.0|`weU-jPra-`|[urboot_atmega324a_pr_ee.hex](https://raw.githubusercontent.com/stefanrueger/urboot.hex/main/cores/mightycore/atmega324a/watchdog_1_s/autobaud/uart1_rxd2_txd3/led%2Bb7/urboot_atmega324a_pr_ee.hex)|
|384|384|u8.0|`weU-jPrac`|[urboot_atmega324a_pr_ee_ce.hex](https://raw.githubusercontent.com/stefanrueger/urboot.hex/main/cores/mightycore/atmega324a/watchdog_1_s/autobaud/uart1_rxd2_txd3/led%2Bb7/urboot_atmega324a_pr_ee_ce.hex)|
|406|512|u8.0|`weU-hprac`|[urboot_atmega324a_ee_ce_hw.hex](https://raw.githubusercontent.com/stefanrueger/urboot.hex/main/cores/mightycore/atmega324a/watchdog_1_s/autobaud/uart1_rxd2_txd3/led%2Bb7/urboot_atmega324a_ee_ce_hw.hex)|

- **Size:** Bootloader code size including small table at top end
- **Usage:** How many bytes of flash are needed, ie, HW boot section or a multiple of the page size
- **Version:** For example, u7.6 is an urboot version, o5.2 is an optiboot version
- **Features:**
  + `w` bootloader provides `pgm_write_page(sram, flash)` for the application at `FLASHEND-4+1`
  + `e` EEPROM read/write support
  + `U` checks whether flash pages need writing before doing so
  + `h` hardware boot section: make sure fuses are set for reset to jump to boot section
  + `j` vector bootloader: applications *need to be patched externally*, eg, using `avrdude -c urclock`
  + `p` bootloader protects itself from being overwritten
  + `P` vector bootloader only: protects itself and reset vector from being overwritten
  + `r` preserves reset flags for the application in the register R2
  + `a` autobaud detection (f_cpu/8n using discrete divisors, n = 1, 2, ..., 256)
  + `c` bootloader provides chip erase functionality (recommended for large MCUs)
  + `-` corresponding feature not present
- **Hex file:** often qualified by the MCU name and/or configuration
  + `pr` vector bootloader protecting the reset vector
  + `ee` bootloader supports EEPROM read/write
  + `ce` bootloader provides a chip erase command
  + `hw` hardware supported bootloader: set fuses to jump to the HW boot section, not to addr 0


Note below that baud rate and F<sub>CPU</sub> may be different from the path name's as long as the quotient F<sub>CPU</sub>/baud rate is the same.

### Make commands
```
make MCU=atmega324a WDTO=1S F_CPU=16000000L AUTOBAUD=1 UARTNUM=1 RX=AtmelPD2 TX=AtmelPD3 VBL=1 EEPROM=0 CHIP_ERASE=0 LED=AtmelPB7 BLINK=1 AUTOFRILLS=0,6,8..10,5,4,3,2 NAME=urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7
make MCU=atmega324a WDTO=1S F_CPU=16000000L AUTOBAUD=1 UARTNUM=1 RX=AtmelPD2 TX=AtmelPD3 VBL=1 PROTECTRESET=1 EEPROM=0 CHIP_ERASE=0 LED=AtmelPB7 BLINK=1 AUTOFRILLS=0,6,8..10,5,4,3,2 NAME=urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7_pr
make MCU=atmega324a WDTO=1S F_CPU=16000000L AUTOBAUD=1 UARTNUM=1 RX=AtmelPD2 TX=AtmelPD3 VBL=1 PROTECTRESET=1 EEPROM=0 CHIP_ERASE=1 LED=AtmelPB7 BLINK=1 AUTOFRILLS=0,6,8..10,5,4,3,2 NAME=urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7_pr_ce
make MCU=atmega324a WDTO=1S F_CPU=16000000L AUTOBAUD=1 UARTNUM=1 RX=AtmelPD2 TX=AtmelPD3 VBL=1 PROTECTRESET=1 EEPROM=1 CHIP_ERASE=0 LED=AtmelPB7 BLINK=1 AUTOFRILLS=0,6,8..10,5,4,3,2 NAME=urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7_pr_ee
make MCU=atmega324a WDTO=1S F_CPU=16000000L AUTOBAUD=1 UARTNUM=1 RX=AtmelPD2 TX=AtmelPD3 VBL=1 PROTECTRESET=1 EEPROM=1 CHIP_ERASE=1 LED=AtmelPB7 BLINK=1 AUTOFRILLS=0,6,8..10,5,4,3,2 NAME=urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7_pr_ee_ce
make MCU=atmega324a WDTO=1S F_CPU=16000000L AUTOBAUD=1 UARTNUM=1 RX=AtmelPD2 TX=AtmelPD3 VBL=0 EEPROM=1 CHIP_ERASE=1 LED=AtmelPB7 BLINK=1 AUTOFRILLS=0,6,8..10,5,4,3,2 NAME=urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7_ee_ce_hw
```

### Avr-gcc commands
```
./avr-toolchain/7.3.0/bin/avr-gcc -DSTART=0x7f00UL -DRJMPWP=0xcfdc -Wl,--section-start=.text=0x7f00 -Wl,--section-start=.version=0x7ffa -DFRILLS=3 -D_urboot_AVAILABLE=14 -g -Wundef -Wall -Os -fno-split-wide-types -mrelax -mmcu=atmega324a -DF_CPU=16000000L -Wno-clobbered -DWDTO=1S -DAUTOBAUD=1 -DLED=AtmelPB7 -DBLINK=1 -DDUAL=0 -DEEPROM=0 -DVBL=1 -DCHIP_ERASE=0 -DUARTNUM=1 -DTX=AtmelPD3 -DRX=AtmelPD2 -DPGMWRITEPAGE=1 -Wl,--relax -nostartfiles -nostdlib -o urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7.elf urboot.c
./avr-toolchain/7.3.0/bin/avr-gcc -DSTART=0x7f00UL -DRJMPWP=0xcfdc -Wl,--section-start=.text=0x7f00 -Wl,--section-start=.version=0x7ffa -DFRILLS=3 -D_urboot_AVAILABLE=0 -g -Wundef -Wall -Os -fno-split-wide-types -mrelax -mmcu=atmega324a -DF_CPU=16000000L -Wno-clobbered -DWDTO=1S -DAUTOBAUD=1 -DLED=AtmelPB7 -DBLINK=1 -DDUAL=0 -DEEPROM=0 -DVBL=1 -DCHIP_ERASE=0 -DUARTNUM=1 -DTX=AtmelPD3 -DRX=AtmelPD2 -DPGMWRITEPAGE=1 -DPROTECTRESET=1 -Wl,--relax -nostartfiles -nostdlib -o urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7_pr.elf urboot.c
./avr-toolchain/7.3.0/bin/avr-gcc -DSTART=0x7e80UL -DRJMPWP=0xcfbb -Wl,--section-start=.text=0x7e80 -Wl,--section-start=.version=0x7ffa -DFRILLS=10 -D_urboot_AVAILABLE=16 -g -Wundef -Wall -Os -fno-split-wide-types -mrelax -mmcu=atmega324a -DF_CPU=16000000L -Wno-clobbered -DWDTO=1S -DAUTOBAUD=1 -DLED=AtmelPB7 -DBLINK=1 -DDUAL=0 -DEEPROM=0 -DVBL=1 -DCHIP_ERASE=1 -DUARTNUM=1 -DTX=AtmelPD3 -DRX=AtmelPD2 -DPGMWRITEPAGE=1 -DPROTECTRESET=1 -Wl,--relax -nostartfiles -nostdlib -o urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7_pr_ce.elf urboot.c
./avr-toolchain/7.3.0/bin/avr-gcc -DSTART=0x7e80UL -DRJMPWP=0xcfc0 -Wl,--section-start=.text=0x7e80 -Wl,--section-start=.version=0x7ffa -DFRILLS=10 -D_urboot_AVAILABLE=6 -g -Wundef -Wall -Os -fno-split-wide-types -mrelax -mmcu=atmega324a -DF_CPU=16000000L -Wno-clobbered -DWDTO=1S -DAUTOBAUD=1 -DLED=AtmelPB7 -DBLINK=1 -DDUAL=0 -DEEPROM=1 -DVBL=1 -DCHIP_ERASE=0 -DUARTNUM=1 -DTX=AtmelPD3 -DRX=AtmelPD2 -DPGMWRITEPAGE=1 -DPROTECTRESET=1 -Wl,--relax -nostartfiles -nostdlib -o urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7_pr_ee.elf urboot.c
./avr-toolchain/7.3.0/bin/avr-gcc -DSTART=0x7e80UL -DRJMPWP=0xcfcd -Wl,--section-start=.text=0x7e80 -Wl,--section-start=.version=0x7ffa -DFRILLS=6 -D_urboot_AVAILABLE=0 -g -Wundef -Wall -Os -fno-split-wide-types -mrelax -mmcu=atmega324a -DF_CPU=16000000L -Wno-clobbered -DWDTO=1S -DAUTOBAUD=1 -DLED=AtmelPB7 -DBLINK=1 -DDUAL=0 -DEEPROM=1 -DVBL=1 -DCHIP_ERASE=1 -DUARTNUM=1 -DTX=AtmelPD3 -DRX=AtmelPD2 -DPGMWRITEPAGE=1 -DPROTECTRESET=1 -Wl,--relax -nostartfiles -nostdlib -o urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7_pr_ee_ce.elf urboot.c
./avr-toolchain/7.3.0/bin/avr-gcc -DSTART=0x7e00UL -DRJMPWP=0xcf97 -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffa -DFRILLS=10 -D_urboot_AVAILABLE=106 -g -Wundef -Wall -Os -fno-split-wide-types -mrelax -mmcu=atmega324a -DF_CPU=16000000L -Wno-clobbered -DWDTO=1S -DAUTOBAUD=1 -DLED=AtmelPB7 -DBLINK=1 -DDUAL=0 -DEEPROM=1 -DVBL=0 -DCHIP_ERASE=1 -DUARTNUM=1 -DTX=AtmelPD3 -DRX=AtmelPD2 -DPGMWRITEPAGE=1 -Wl,--relax -nostartfiles -nostdlib -o urboot_m324a_1s_autobaud_uart1_rxd2_txd3_led+b7_ee_ce_hw.elf urboot.c
```

