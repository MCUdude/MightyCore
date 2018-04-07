#Ethernet Library for Teensy#

Wiznet chips W5100, W5200 and W5500 are automatically detected.

Efficient block mode of W5200 & W5500 are used for data and multi-byte register access.

Wiznet socket registers are cached, which greatly reduces SPI communication overhead, at the cost of a small increase in RAM usage.  TCP connections and UDP packets accessed in small chunks typically see a substantial performance boost.

Adafruit's Ethernet.init(CSPIN) extension is supported, to allow use of different pins for the chip select signal.  Optimized direct register I/O is used for most Arduino compatible boards.

http://www.pjrc.com/teensy/td_libs_Ethernet.html

![](http://www.pjrc.com/store/wiz820_assem5.jpg)

### Tested Hardware


| Board			| Chip	| Shield / Module	| Internet	| Local		|
| ---------------------	| :---: | :-------------------: | ------------: | ------------: |
| Teensy 3.6		| W5500	| WIZ850io		| 97.37		| 1190.90	|
| Teensy 3.6		| W5200	| WIZ820io		| 96.65		| 1157.56	|
| Teensy 3.6		| W5100	| WIZ811MJ		| 9.61		| 10.16		|
| Teensy 3.2		| W5200	| WIZ820io		| 96.56		| 1030.55	|
| Teensy LC		| W5500	| WIZ850io		| 97.51		| 390.46	|
| Teensy 2.0		| W5100	| WIZ811MJ		| 9.75		| 10.16		|
| Arduino Uno R3	| W5500 | Seeed Ethernet	| 96.47		| 284.42	|
| Arduino Uno R3	| W5100 | Arduino Ethernet R3	| 9.66		| 10.17		|
| Arduino Uno R3	| W5100 | Ethernet R2 (clone)	| 9.65		| 10.17		|
| Arduino Due		| W5100 | Arduino Ethernet R3	| 9.72		| 10.16		|
| Arduino Due		| W5500 | Seeed Ethernet	| 96.42		| 378.85	|
| Arduino Zero		| W5500 | Seeed Ethernet	| 96.33		| 234.03	|
| Arduino 101		| W5500 | Seeed Ethernet	| fail		| fail		|
| ChipKit Uno32		| W5500 | Seeed Ethernet	| fail		| fail		|
| Wemos D1 (ESP8266)	| W5500 | Seeed Ethernet	| fail		| fail		|
| Mega 2560 (clone)	| W5500 | Seeed Ethernet	| fail		| fail		|
| Mega 2560 (clone)	| W5100 | Ethernet R2 (clone)	| fail		| fail		|



