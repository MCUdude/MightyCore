# MightyCore
[![MegaCore forum thread](https://img.shields.io/badge/support-forum-blue.svg)](http://forum.arduino.cc/index.php?topic=379427.0)

An Arduino core for ATmega8535, ATmega16, ATmega32, ATmega164, ATmega324, ATmega644 and ATmega1284, all running the [Urboot](#write-to-own-flash) bootloader. Most Arduino UNO-compatible libraries will work with this core. If not, it's fairly straightforward to [port a library](#library-porting).
MightyCore works with flawless with Arduino IDE 1.8.x, but if you want to debug using a hardware debugger, you'll need Arduino IDE 2.x.

*From version 3.1.0 onwards, debugging in the Arduino IDE 2 is supported. You can use any of Microchip's EDBG-based hardware debuggers. For documentation, see [https://pyavrocd.io](https://pyavrocd.io).*

*From MightyCore version 3 and onwards, the Optiboot bootloader has been replaced by the superior [Urboot bootloader](https://github.com/stefanrueger/urboot/). It's smaller, faster, and has automatic baud rate detection. Other cool features the bootloader provides but are not utilized by MightyCore are user program metadata stored in flash that (can easily be viewed by Avrdude -xshowall) and chip erase functionality.
If you already have Optiboot installed and don't want to replace it with Urboot, you can still upload programs without any compatibility issues. However, if you're burning a bootloader to a new chip, Urboot is the way to go.*

If you're looking for a great development board for these DIP-40 microcontrollers, I got you covered! I've used the Arduino UNO for years,
but felt like vital functionality was missing on the board. When designing this board I made sure all missing functionality was added. [The board can be bought on my Tindie store](https://www.tindie.com/products/MCUdude/dip-40-arduino-compatible-development-board).
<br/>
**Read more in the hardware section below.**
<br/> 

<br/>
<img src="https://i.imgur.com/MYKePw6.jpg" width="400"><img src="https://i.imgur.com/LUwmwrR.jpg" width="400">

# Table of contents
* [Supported microcontrollers](#supported-microcontrollers)
* [Supported clock frequencies](#supported-clock-frequencies)
* [Bootloader option](#bootloader-option)
* [Baud rate option](#baud-rate-option)
* [BOD option](#bod-option)
* [EEPROM retain option](#eeprom-option)
* [Link time optimization / LTO](#link-time-optimization--lto)
* [Printf support](#printf-support)
* [Pin macros](#pin-macros)
* [Write to own flash](#write-to-own-flash)
* [PROGMEM with flash sizes greater than 64kiB](#progmem-with-flash-sizes-greater-than-64kib)
* **[Pinout](#pinout)**
* [Programmers](#programmers)
* **[How to install](#how-to-install)**
  - [Boards Manager Installation](#boards-manager-installation)
  - [Manual Installation](#manual-installation)
  - [Arduino CLI Installation](#arduino-cli-installation)
  - [PlatformIO](#platformio)
* **[Getting started with MightyCore](#getting-started-with-mightycore)**
* [Wiring reference](#wiring-reference)
* [Library porting](#library-porting)
* [Hardware](#hardware)
* **[Minimal setup](#minimal-setup)**


## Supported microcontrollers
* ATmega1284
* ATmega644
* ATmega324
* ATmega164
* ATmega32
* ATmega16
* ATmega8535

All variants - P, PA, A, PB. Select the correct version in the 'Variant' menu
<br/> <br/>
Can't decide what microcontroller to choose? Have a look at the specification table below:

|                  | mega1284 | mega644 | mega324 | mega164 | mega32 | mega16 | mega8535 |
|------------------|----------|---------|---------|---------|--------|--------|----------|
| **Flash**        | 128kiB   | 64kiB   | 32kiB   | 16kiB   | 32kiB  | 16kiB  | 8kiB     |
| **RAM**          | 16kiB    | 4kiB    | 2kiB    | 1kiB    | 2kiB   | 1kiB   | 0.5kiB   |
| **EEPROM**       | 4kiB     | 2kiB    | 1kiB    | 0.5kiB  | 0.5kiB | 0.5kiB | 0.5kiB   |
| **Serial ports** | 2        | 2       | 2/3*    | 2       | 1      | 1      | 1        |
| **PWM pins**     | 8        | 6       | 6/9*    | 6       | 4      | 4      | 4        |
| **IO pins**      | 32       | 32      | 32/39*  | 32      | 32     | 32     | 32       |

<b>*</b> ATmega324PB has 3 serial ports, 9 PWM pins, and 39 IO pins if the internal oscillator is used.


## Supported clock frequencies
MightyCore supports a variety of different clock frequencies. Select the microcontroller in the boards menu, then select the clock frequency. *You will have to hit "Burn bootloader" in order to set the correct fuses and upload the correct bootloader. This also has to be done if you want to change any of the fuse settings (BOD and EEPROM settings) regardless if a bootloader is installed or not*.
Make sure you connect an ISP programmer, and select the correct one in the "Programmers" menu. For time-critical operations, an external crystal/oscillator is recommended. The Urboot bootloader has automatic baud rate detection, so UART uploads should work fine even though the oscillator is a little too fast or too slow.

| Frequency   | Oscillator type             | Default upload speed <br/>(bootloader has auto-baud)  | Comment                                           |
|-------------|-----------------------------|-------------------------------------------------------|---------------------------------------------------|
| 16 MHz      | External crystal/oscillator | 115200                                                | Default clock on most AVR based Arduino boards    |
| 20 MHz      | External crystal/oscillator | 115200                                                |                                                   |
| 18.4320 MHz | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 14.7456 MHz | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 12 MHz      | External crystal/oscillator | 57600                                                 |                                                   |
| 11.0592 MHz | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 9.216 MHz   | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 8 MHz       | External crystal/oscillator | 57600                                                 | Common clock when working with 3.3V               |
| 7.3728 MHz  | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 6 MHz       | External crystal/oscillator | 57600                                                 |                                                   |
| 4 MHz       | External crystal/oscillator | 9600                                                  |                                                   |
| 3.6864 MHz  | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 2 MHz       | External crystal/oscillator | 9600                                                  |                                                   |
| 1.8432 MHz  | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 1 MHz       | External crystal/oscillator | 9600                                                  |                                                   |
| 8 MHz       | Internal oscillator         | 38400                                                 | Might cause UART upload issues. See comment above |
| 4 MHz       | Internal oscillator         | 9600                                                  | Derived from the 8 MHz internal oscillator        |
| 2 MHz       | Internal oscillator         | 9600                                                  | Derived from the 8 MHz internal oscillator        |
| 1 MHz       | Internal oscillator         | 9600                                                  | Derived from the 8 MHz internal oscillator        |


## Bootloader option
MightyCore lets you select which serial port you want to use for uploading. UART0 is the default port for all targets, but ATmega324/644/1284 can also use UART1 for upload.
If your application doesn't need or require a bootloader for uploading you can also choose to disable it by selecting *No bootloader*.
This frees 384 bytes of flash memory on ATmega8535/16/32/164/324 and 512 bytes on ATmega644/1284.

Note that you need to connect a programmer and hit **Burn bootloader** if you want to change any of the *Bootloader settings*.


# Baud rate option
Since Urboot has automatic baud rate detection, the upload baud rate can be changed without having to re-flash the bootloader. The default baud rate setting will pick a suited baud rate that also works with the legacy Optiboot bootloader used in earlier MightyCore versions.
The other baud rate options may or may not work, depending on the clock frequency and accuracy of the clock source. A rule of thumb is that "non-round" baud rates like 230400 works best with "non-round" clock speeds like 18.4320 MHz,
while "round" ones like 16 MHz work best with "round" baud rates like 250000.


## BOD option
Brown-out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown-out setting. To change the BOD settings you'll have to connect an ISP programmer and hit "Burn bootloader". Below is a table that shows the available BOD options:
<br/>

| ATmega1284 | Atmega644 | ATmega324 | ATmega164 | ATmega32 | ATmega16 | ATmega8535 |
|------------|-----------|-----------|-----------|----------|----------|------------|
| 4.3V       | 4.3V      | 4.3V      | 4.3V      | 4.0V     | 4.0V     | 4.0V       |
| 2.7V       | 2.7V      | 2.7V      | 2.7V      | 2.7V     | 2.7V     | 2.7V       |
| 1.8V       | 1.8V      | 1.8V      | 1.8V      | -        | -        | -          |
| Disabled   | Disabled  | Disabled  | Disabled  | Disabled | Disabled | Disabled   |


## EEPROM option
If you want the EEPROM to be erased every time you burn the bootloader or upload using a programmer, you can turn off this option. You'll have to connect an ISP programmer and hit "Burn bootloader" to enable or disable EEPROM retain. Note that when uploading using a bootloader, the EEPROM will always be retained.

Note that if you're using an ISP programmer or have the Urboot bootloader installed, data specified in the user program using the `EEMEM` attribute will be uploaded to EEPROM when you upload your program in Arduino IDE. This feature is not available when using the older Optiboot bootloader.

```cpp
#include <avr/eeprom.h>

volatile const char ee_data EEMEM = {"Data that's loaded straight into EEPROM\n"};

void setup() {
}

void loop() {
}
```


## Link time optimization / LTO
Link time optimization (LTO for short) optimizes the code at link time, usually making the code significantly smaller without affecting performance. You don't need to hit "Burn Bootloader" in order to enable or disable LTO. Simply choose your preferred option in the "Tools" menu, and your code is ready for compilation. If you want to read more about LTO and GCC flags in general, head over to the [GNU GCC website](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)!


## Printf support
Unlike the official Arduino cores, MightyCore has printf support out of the box. If you're not familiar with printf you should probably [read this first](https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm). It's added to the Print class and will work with all libraries that inherit Print. Printf is a standard C function that lets you format text much easier than using Arduino's built-in print and println. Note that this implementation of printf will NOT print floats or doubles. This is disabled by default to save space but can be enabled using a build flag if using PlatformIO.

If you're using a serial port, simply use `Serial.printf(F("Milliseconds since start: %ld\n"), millis());`. As you can see, printf supports the `F()` macro, but you don't _have_ to use it. Other libraries that inherit the Print class (and thus support printf) are the LiquidCrystal LCD library and the U8G2 graphical LCD library.


## Pin macros
Note that you don't have to use the digital pin numbers to refer to the pins. You can also use some predefined macros that map "Arduino pins" to the port and port number:

```c++
// Use PIN_PB0 macro to refer to pin PB0 (Arduino pin 0 with the standard and Sanguino pinout)
digitalWrite(PIN_PB0, HIGH);

// Results in the exact same compiled code
digitalWrite(0, HIGH);

```


## Write to own flash
MightyCore uses the excellent Urboot bootloader, written by [Stefan Rueger](https://github.com/stefanrueger). Urboot supports flash writing within the running application, meaning that content from e.g. a sensor can be stored in the flash memory directly without needing external memory. Flash memory is much faster than EEPROM, and can handle at least 10,000 write cycles before wear becomes an issue.
For more information on how it works and how you can use this in your own application, check out the [Serial_read_write](https://github.com/MCUdude/MightyCore/blob/master/avr/libraries/Flash/examples/Serial_read_write/Serial_read_write.ino) for a simple proof-of-concept demo, and
[Flash_get_put](https://github.com/MCUdude/MightyCore/blob/master/avr/libraries/Flash/examples/Flash_get_put/Flash_get_put.ino) + [Flash_iterate](https://github.com/MCUdude/MightyCore/blob/master/avr/libraries/Flash/examples/Flash_iterate/Flash_iterate.ino) for useful examples on how you can store strings, structs, and variables to flash and retrieve then afterward.


## PROGMEM with flash sizes greater than 64kB
The  `PROGMEM` attribute stores constant data, such as string arrays, in flash and is great if you want to preserve the precious RAM. However, the usual PROGMEM library macros can access data only in the lower part of flash memory up to 64kiB.  If you store more data in the PROGMEM section (on an ATmega1284/P), you will get a warning during the compilation process because some of the PROGMEM data will not be accessible in the usual way.

If you want to store and access data independently from the 64kiB limit, use `PROGMEM_FAR` from the "progmem_far" library (which is bundled with MightyCore). Data with that attribute is stored at the far end of flash memory. Accessing this data is not as straightforward as with `PROGMEM`, but it's still doable:

```cpp
#include <progmem_far.h>

const char far_away[] PROGMEM_FAR = "Hello from far away!\n"; 

void print_progmem()
{
  char c;

  // Print out far_away
  for(uint8_t i = 0; i < sizeof(far_away); i++)
  {
    c = pgm_read_byte_far(pgm_get_far_address(far_away) + i);
    Serial.write(c);
  }
}

```

## Pinout
This core has three different pinout options:
- **Standard**: The default pinout, and is based on the original AVR pinout.
- **Bobuino**: Basically an Arduino UNO pinout setting. This pinout version is great for use with shields or code that's written for the Arduino UNO, as the pin functions stay the same (MOSI on D11, MISO on D12, SCK on D13).
- **Sanguino**: This pinout is common on older 3D printer controllers such as the Sanguino, RepRap Sanguinololu, and RepRap Gen7. This pinout is also known as "avr_developers".

Please have a look at the (`pins_arduino.h`) files for detailed info. Pick your favorite!</br> </br>
<b>Click to enlarge:</b>



| **MightyCore Standard pinout**                                                                                                                                           | **MightyCore Bobuino pinout**                                                                                                                                            | **MightyCore Sanguino pinout**                                                                                                                                           |
|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|<img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/MightyCore_DIP40_standard_pinout.png" width="260"><img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/MightyCore_TQFP44_standard_pinout.jpg" width="260"><br/><img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/MightyCore_ATmega324PB_standard_pinout.jpg" width="260">|<img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/MightyCore_DIP40_bobuino_pinout.png" width="260"><img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/MightyCore_TQFP44_bobuino_pinout.jpg" width="260"><br/><img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/MightyCore_ATmega324PB_bobuino_pinout.jpg" width="260">|<img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/MightyCore_DIP40_sanguino_pinout.png" width="260"><img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/MightyCore_TQFP44_sanguino_pinout.jpg" width="260"><br/><img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/MightyCore_ATmega324PB_sanguino_pinout.jpg" width="260">|


## Programmers
Select your microcontroller in the boards menu, then select the clock frequency. You'll have to hit "Burn bootloader" in order to set the correct fuses and upload the correct bootloader. <br/>
Make sure you connect an ISP programmer, and select the correct one in the "Programmers" menu. For time-critical operations, an external oscillator is recommended.


## How to install
#### Boards Manager Installation
* Open the Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**:
    ```
    https://mcudude.github.io/MightyCore/package_MCUdude_MightyCore_index.json
    ```
* Open the **Tools > Board > Boards Manager...** menu item.
* Wait for the platform indexes to finish downloading.
* Scroll down until you see the **MightyCore** entry and click on it.
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

#### Manual Installation
Click on the "Download ZIP" button. Extract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE and a new category in the boards menu called "MightyCore" will show up.

#### Arduino CLI Installation
Run the following command in a terminal:

```
arduino-cli core install MightyCore:avr --additional-urls https://mcudude.github.io/MightyCore/package_MCUdude_MightyCore_index.json
```

#### PlatformIO
[PlatformIO](http://platformio.org) is an open-source ecosystem for IoT and embedded systems, and supports MightyCore.

**See [PlatformIO.md](https://github.com/MCUdude/MightyCore/blob/master/PlatformIO.md) for more information.**


## Getting started with MightyCore
* Hook up your microcontroller as shown in the [pinout diagram](#pinout).
  - If you're not planning to use the bootloader (uploading code using a USB to serial adapter), the FTDI header and the 100 nF capacitor on the reset pin can be omitted.
* Open the **Tools > Board** menu item, select **MightyCore** and select your preferred target.
* If the *BOD option* is presented, you can select at what voltage the microcontroller will shut down at. Read more about BOD [here](#bod-option).
* Select your preferred pinout. Personally, Standard is the most logical one; Bobuino is better for Arduino UNO pin compatibility. Read more about the different pinouts [here](#pinouts).
* Select your preferred clock frequency. **16 MHz** is standard on most Arduino boards.
* Select what kind of programmer you're using under the **Programmers** menu.
* If the *Variants* option is presented, you'll have to specify what version of the microcontroller you're using. E.g the ATmega1284 and the ATmega1284P have different device signatures, so selecting the wrong one will result in an error.
* Hit **Burn Bootloader**. The LED pin will not toggle after the bootloader has been loaded.
* Disconnect the ISP programmer, and connect a USB to serial adapter to the target microcontroller shown in the [pinout diagram](#pinout). Select the correct serial port under the **Tools** menu, and click the **Upload** button. If you're getting a timeout error, it may be because the RX and TX pins are swapped, or the auto-reset circuit isn't working properly (the 100 nF capacitor and a 10k resistor on the reset line).

Your code should now be running on the microcontroller!


## Wiring reference
To extend this core's functionality a bit further, I've added a few missing Wiring functions. As many of you know Arduino is based on Wiring, but that doesn't mean the Wiring development isn't active. These functions are used as "regular" Arduino functions, and there's no need to include an external library.<br/>
I hope you find this useful because they really are!

### Function list
* portMode()
* portRead()
* portWrite()
* sleepMode()
* sleep()
* noSleep()
* enablePower()
* disablePower()

### For more information please view the [Wiring reference page](https://github.com/MCUdude/MightyCore/blob/master/Wiring_reference.md)


## Library porting
Some users have reported issues when trying to use some 3rd party libraries with the ATmega8535, ATmega16, or ATmega32.
A simple guide on how to port a library can be found <b>[here](https://github.com/MCUdude/MightyCore/blob/master/Library_porting.md)</b>.

## Hardware
I've designed a development board for this particular core. I've added all the functionality I missed with the original Arduino boards and added the original AVR pinout.
Not all supported microcontrollers have the same pin functions, and differences are highlighted. The boards measures 8.0 * 10.0 cm (3.15 * 3.94 in)<br/>
The development board has some additional unique features:
* A voltage select jumper to run the microcontroller at 5V or 3.3V
* A breadboard-friendly AVR with 32 IO pins, including 8 analog inputs
* All pins located on the same side of the board, making it easy to hook it up to a breadboard
* Male and female IO pin headers
* Plenty of 5V, 3.3V, and GND points broken out, both male and female
* A large ground pad on the underside of the board for connecting alligator clips, such as the ground clip of your oscilloscope
* A potentiometer for use as a voltage reference (e.g. adjusting the LCD contrast)
* Onboard LED connected to digital pin 0 (PB0)
* A socketed crystal, perfect for experimenting with different clock frequencies
* An auto reset enable header if you don't want the microcontroller to be reset every time you open the serial monitor on your PC
* PWM pins clearly marked and a lookup table that can be found on the underside of the board (three `~` - all microcontrollers, two `~` - 164; 324; 644; 1284, one `~` - 1284)
* IO peripherals are written on the underside of the board. No need to search in the datasheet anymore!
* A Mini USB connector instead of a large USB Type-B plug
* All serial handshake pins broken out for applications such as bit-banging (CTS, DTR, RI, DCD, DRT, RST)
* JTAG header for programming and debugging (the JTAG enable fuse must be sat first)

#### [The development board can be bought on my Tindie store.](https://www.tindie.com/products/MCUdude/dip-40-arduino-compatible-development-board/) This includes a pre-programmed ATmega32 chip. <br/>
<br/>
Click the images for full resolution <br/>

![Development board front](https://i.imgur.com/CaHA4Qj.jpg)
<br/>

![Development board back](https://i.imgur.com/TJVdZ4n.jpg)
<br/>

![Bottom row](https://i.imgur.com/alK0gAA.jpg)

## Minimal setup
Here is a simple schematic showing a minimal setup using an external crystal. Skip the crystal and the two capacitors if you're using the internal oscillator. <br/>
<b>Click to enlarge:</b>

| DIP-40 package                                        | TQFP-44 SMD package                                   | ATmega324PB SMD package                               |
|-------------------------------------------------------|-------------------------------------------------------|-------------------------------------------------------|
|<img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/Minimal_setup_MightyCore_DIP40.png" width="280">|<img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/Minimal_setup_MightyCore_TQFP44.png" width="280">|<img src="https://raw.githubusercontent.com/MCUdude/MightyCore/refs/heads/master/avr/images/Minimal_setup_MightyCore_ATMEGA324PB_TQFP44.png" width="280">|
