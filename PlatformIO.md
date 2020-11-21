# PlatformIO

[PlatformIO](https://platformio.org) is an open source ecosystem for embedded development. 
It has a built-in library manager and is Arduino compatible. It supports most operating systems; Windows, MacOS, Linux 32 and 64-bit, ARM and X86.  
And best of all, MightyCore is supported!

* [What is PlatformIO?](http://docs.platformio.org/en/latest/what-is-platformio.html)
* [PlatformIO IDE](http://platformio.org/#!/platformio-ide)
* Getting started with [PlatformIO IDE](http://docs.platformio.org/en/latest/ide/atom.html#quick-start) or [PlatformIO command line interface](http://docs.platformio.org/en/latest/quickstart.html)
* [Advanced functionality](http://docs.platformio.org/en/latest/platforms/atmelavr.html) 
* [Project Examples](http://docs.platformio.org/en/latest/platforms/atmelavr.html#examples)


## MightyCore + PlatformIO 
MightyCore and PlatformIO goes great together. You can do serial uploads and upload using a dedicated programmer, but you can also let PlatformIO calulate the fuses and load the correct bootloader file, just like Arduino IDE does!

PlatformIO uses the information provided in platformio.ini to calculate what fuse bits and what bootloader file to load.  
Simply provide enough information and run the following commands:  

```ini
; Only set fuses
pio run -t fuses -e fuses_bootloader
; Set fuses and burn bootloader
pio run -t bootloader -e fuses_bootloader
; (where "fuses_bootloader" can be replace with a different environment to match your build configuration)
```

You can find a platformio.ini template you can use when creating a project for a MightyCore compatible device below.  
The most common functionality is available in this template. As you can see, the templated is divided into multiple environments.  

* The default build environment are defined under *[platformio]*.
* All parameters that are common for all environments are defined under *[env]*.
* Use the *[env:Upload_UART]* or *[env:Upload_ISP]* to upload to your target.
* Use *[env:fuses_bootloader]* to set the fuses or burn the bootloader.

More information on what each line means can be found futher down on this page.


## platformio.ini template

``` ini
; PlatformIO Project Configuration File for MightyCore
; https://github.com/MCUdude/MightyCore/
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed, and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options
; https://github.com/MCUdude/MightyCore/blob/master/PlatformIO.md
; https://docs.platformio.org/page/projectconf.html


[platformio]
default_envs = Upload_UART ; Default build target


; Common settings for all environments
[env]
platform = atmelavr
framework = arduino

; TARGET SETTINGS
; Chip in use
board = ATmega1284P
; Clock frequency in [Hz]
board_build.f_cpu = 16000000L
; Current pinout
board_build.variant = standard

; BUILD OPTIONS
; Comment out to enable LTO (this line unflags it)
build_unflags = -flto
; Extra build flags
build_flags = 

; SERIAL MONITOR OPTIONS
; Serial monitor port defined in the Upload_UART environment
monitor_port = ${env:Upload_UART.upload_port}
; Serial monitor baud rate
monitor_speed = 9600


; Run the following command to upload with this environment
; pio run -e Upload_UART -t upload
[env:Upload_UART]
;  Serial bootloader protocol
upload_protocol = arduino
; Serial upload port
upload_port = /dev/cu.usbserial*
; Get upload baud rate defined in the fuses_bootloader environment
board_upload.speed = ${env:fuses_bootloader.board_bootloader.speed}


; Run the following command to upload with this environment
; pio run -e Upload_ISP -t upload
[env:Upload_ISP]
; Custom upload procedure
upload_protocol = custom
; Avrdude upload flags
upload_flags =
  -C$PROJECT_PACKAGES_DIR/tool-avrdude/avrdude.conf
  -p$BOARD_MCU
  -PUSB
  -cusbasp
; Avrdude upload command
upload_command = avrdude $UPLOAD_FLAGS -U flash:w:$SOURCE:i


; Run the following command to set fuses
; pio run -e fuses_bootloader -t fuses
; Run the following command to set fuses + burn bootloader
; pio run -e fuses_bootloader -t bootloader
[env:fuses_bootloader]
board_hardware.oscillator = external ; Oscillator type
board_hardware.uart = uart0          ; Set UART to use for serial upload
board_bootloader.speed = 115200      ; Set bootloader baud rate
board_hardware.bod = 2.7v            ; Set brown-out detection
board_hardware.eesave = yes          ; Preserve EEPROM when uploading using programmer
upload_protocol = usbasp             ; Use the USBasp as programmer
upload_flags =                       ; Select USB as upload port and divide the SPI clock by 8
  -PUSB
  -B8

```


### `board`
PlatformIO requires the `board` parameter to be present.
The table below shows what board name should be used for each target

| Target                                         | Board name    |
|------------------------------------------------|---------------|
| ATmega1284P                                    | `ATmega1284P` |
| ATmega1284                                     | `ATmega1284`  |
| ATmega644P/PA                                  | `ATmega644P`  |
| ATmega644/A                                    | `ATmega644A`  |
| ATmega324PB                                    | `ATmega324PB` |
| ATmega324PA                                    | `ATmega324PA` |
| ATmega324P                                     | `ATmega324P`  |
| ATmega324A                                     | `ATmega324A`  |
| ATmega164P/PA                                  | `ATmega164P`  |
| ATmega164A                                     | `ATmega164A`  |
| ATmega32                                       | `ATmega32`    |
| ATmega16                                       | `ATmega16`    |
| ATmega8535                                     | `ATmega8535`  |


### `board_build.f_cpu`
Specifies the clock frequency in [Hz]. 
Used to determine what oscillator option to choose. A capital L has to be added to the end of the frequency number.
Below is a table with supported clocks for MiniCore. Defaults to 16 MHz if not specified.

| Clock speed | Oscillator | board_build.f_cpu         |
|-------------|------------|---------------------------|
| 20 MHz      | External   | `20000000L`               |
| 18.432 MHz  | External   | `18432000L`               |
| 16 MHz      | External   | `16000000L` (default)     |
| 14.7456 MHz | External   | `14745600L`               |
| 12 MHz      | External   | `12000000L`               |
| 11.0592 MHz | External   | `11059200L`               |
| 8 MHz       | External   | `8000000L`                |
| 7.3728  MHz | External   | `7372800L`                |
| 4 MHz       | External   | `4000000L`                |
| 3.6864  MHz | External   | `3686400L`                |
| 2 MHz       | External   | `2000000L`                |
| 1.8432  MHz | External   | `1843200L`                |
| 1 MHz       | External   | `1000000L`                |
| 8 MHz       | Internal   | `8000000L`                |
| 1 MHz       | Internal   | `1000000L`                |


### `board_hardware.oscillator`
Spefices to use the internal or an external oscillator.  
Internal oscillator only works with `board_build.f_cpu` values `8000000L` and `1000000L`.

| Oscillator option    |
|----------------------|
| `external` (default) |
| `internal`           |


### `board_hardware.uart`
Specifies the hardware UART port used for serial upload. Use `no_bootloader` if you’re using a dedicated programmer, i.e not using a bootloader for serial upload.

| Upload serial port option |
|---------------------------|
| `no_bootloader`           |
| `uart0` (default)         |
| `uart1`                   |
| `uart2` (324PB only)      |


### `board_hardware.bod`
Specifies the hardware brown-out detection. Use `disabled` to disable.

| ATmega164/324/644/1284 | ATmega8535/16/32 |
|------------------------|------------------|
| `4.3v`                 | `4.0v`           |
| `2.7v` (default)       | `2.7v` (default) |
| `1.8v`                 |                  |
| `disabled`             | `disabled`       |


### `board_hardware.eesave`
Specifies if the EEPROM memory should be retained when uploading using a programmer. Use `no` to disable.

| EEPROM retain   |
|-----------------|
| `yes` (default) |
| `no`            |

### `board_hardware.ckout`
Enable clock output on pin PB1 on targets that supports it (ATmega164/324/644/1284).

| Clock output enable |
|---------------------|
| `yes`               |
| `no` (default)      |


### `board_hardware.jtagen`
Enable the JTAG port on targets that supports it (ATmega16/32/164/324/644/1284).

| JTAG enable     |
|-----------------|
| `yes`           |
| `no` (default)  |


### `board_hardware.cfd`
Enable clock failure detection. The internal 1 MHz oscillator will kick in if the external oscillator fails (only available on ATmega324PB).

| Clock failure detection |
|-------------------------|
| `yes`                   |
| `no` (default)          |


### `board_upload.speed` / `board_bootloader.speed`
Specifies the upload baud rate. Available baud rates is shown in the table below, had has to corrolate with `build_board.f_cpu`.  
  
**Note that if you're using a programmer that communicates with Avrdude with a serial port (Arduino as ISP, STK500, etc.) the `board_upload.speed` field will interfere with the programmer's baud rate.  
In this case, use `board_bootloader.speed` to set the bootloader baud rate, and `board_upload.speed` to set the baud rate for the programmer.**  
  
Recommended baud rate for the particular clock speed is in **bold text**.

|             | 1000000 | 500000 | 460800 | 250000 | 230400 | 115200 | 57600  | 38400  | 19200 | 9600   |
|-------------|---------|--------|--------|--------|--------|--------|--------|--------|-------|--------|
| `20000000L` |         |  X     |        |  X     |        |  **X** |        |        |  X    |        |
| `18432000L` |         |        |  X     |        |  X     |  **X** |  X     |  X     |  X    |  X     |
| `16000000L` |  X      |  X     |        |  X     |        |  **X** |        |  X     |  X    |  X     |
| `14745600L` |         |        |  X     |        |  X     |  **X** |  X     |  X     |  X    |  X     |
| `12000000L` |         |  X     |        |  X     |        |        |  **X** |        |  X    |  X     |
| `11059200L` |         |        |  X     |        |  X     |  X     |  **X** |  X     |  X    |  X     |
| `8000000L`  |  X      |  X     |        |  X     |        |  X     |  X     |  **X** |  X    |  X     |
| `7372800L`  |         |        |  X     |        |  X     |  **X** |  X     |  X     |  X    |  X     |
| `4000000L`  |         |  X     |        |        |        |        |        |        |  X    |  **X** |
| `3686400L`  |         |        |  X     |        |  X     |  **X** |  X     |  X     |  X    |  X     |
| `2000000L`  |         |        |        |  X     |        |        |        |        |  X    |  **X** |
| `1843200L`  |         |        |        |        |  X     |  **X** |  X     |  X     |  X    |  X     |
| `1000000L`  |         |        |        |        |        |        |        |        |       |  **X** |


### `board_build.variant`
Holds the current pinout in use.  
See [pinout pics](https://github.com/MCUdude/MightyCore#pinout) for more info.

| Pinouts              |
|----------------------|
| `standard` (default) |
| `bobuino`            |
| `sanguino`           |


### `build_unflags`
This parameter is used to unflag. Since LTO is enabled by default in PlatformIO we may disable it by unflagging `-flto`.


### `build_flags`
This parameter is used to set compiler flags. This is useful if you want to for instance want to chage the serial RX or TX buffer. Here's a list of the current available core files flags:

| Flag                        | Default size | Description                                               |
|-----------------------------|--------------|-----------------------------------------------------------|
| -lprintf_flt                |              | Lets you print floats with printf (occupies ~1.5 kB)      |
| -Wall -Wextra               |              | Show all compiler warnings                                |
| -DSERIAL_RX_BUFFER_SIZE=128 | 64 bytes     | Sets the serial RX buffer to 128 bytes                    |
| -DSERIAL_TX_BUFFER_SIZE=128 | 64 bytes     | Sets the serial TX buffer to 128 bytes                    |
| -DTWI_BUFFER_SIZE=64        | 32 bytes     | Sets the TWI (i2c) buffer to 64 bytes                     |
| -DTWI1_BUFFER_SIZE=64       | 32 bytes     | Sets the TWI1 (i2c) buffer to 64 bytes (ATmega324PB only) |

**Example:**
`build_flags = -DSERIAL_RX_BUFFER_SIZE=128 -DSERIAL_TX_BUFFER_SIZE=128`


### `upload_port`
Holds the serial port used for uploading. PlatformIO automatically detects the serial port. However, uf you want to ovverride this you can uncomment `upload_port`. Use `/dev/[port]` on Unix compatible systems, and use `COMx` on Windows.


### `upload_protocol`
Used when using a programmer rather than using a USB to serial adapter.  
Supports all Avrdude compatible programmers such as `usbasp`, `usbtiny` and `stk500v1`.


### `upload_flags`
Used to pass extra flags to Avrdude when uploading using a programmer.  
Typical parameters are `-PUSB`, `-B[clock divider]` and `-b[baudrate]`.  
**Note that every flag has to be on its own line, and they have to be indented with two spaces:**
```ini
upload_flags =
  -PUSB
  -B32
  -v
```


### `monitor_port`
PlatformIO detects serial ports automatically. However, In the template above it uses the upload port defined in the `env:Upload_UART` environment.
if you want to override this you can insert your uplooad port here. Use `/dev/[port]` on Unix compatible systems, and use `COMx` on Windows.


### `monitor_speed`
Sets the serial monitor baud rate. Defaults to 9600 if not defined.
