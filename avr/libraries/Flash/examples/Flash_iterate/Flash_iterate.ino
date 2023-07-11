/***********************************************************************|
| Urboot read/write interface library                                   |
|                                                                       |
| Flash_iterate.ino                                                     |
|                                                                       |
| A library for interfacing with Urboot's flash write functionality     |
| Developed in 2023 by Stefan Rueger and MCUdude                        |
| https://github.com/stefanrueger/                                      |
| https://github.com/MCUdude/                                           |
|                                                                       |
| In this example we fill the flash[] buffer with numbers and write it  |
| to flash page 0. After a reset or power cycle, we read the values     |
| back and prints them to the serial monitor.                           |
|                                                                       |
| A RAM buffer (ram_buffer) is required for this library to work. It    |
| acts as a memory pool you can read from and write to, and recommended |
| size for this buffer is one flash page, 256/128/64 bytes depending on |
| what chip you're using. ram_buffer[] and flash[] is the exact same    |
| array, flash[] is just pointing to ram_buffer[].                      |
|***********************************************************************/

#include <Flash.h>

// RAM buffer needed by the Flash library. Use flash[] to access the buffer. This
uint8_t ram_buffer[SPM_PAGESIZE];

// Allocate two flash pages for storing data. Use PROGMEM1 to allocate space above 64kiB
#define NUMBER_OF_PAGES 2
const uint8_t flash_space[SPM_PAGESIZE * NUMBER_OF_PAGES] __attribute__((aligned(SPM_PAGESIZE))) PROGMEM = {};

// Flash constructor
Flash flash(flash_space, sizeof(flash_space), ram_buffer, sizeof(ram_buffer));

void write_data()
{
  // First, make sure there are no content in out buffer
  flash.clear_buffer();

  // Fill buffer with numbers, starting from 0
  for(uint8_t i = 0; i < 64; i++)
    flash[i] = i + 65;

  // Write buffer to the first allocated flash page (page 0)
  flash.write_page(0);

  // Now let's set a flag on another flash page to indicate that the flash memory contains content
  // Here we're treating the object as an array
  flash.clear_buffer();
  flash[5] = 'X';
  flash.write_page(1);

  Serial.println(F("Page 0 written to!\nReset your board to view the contents!\n"));
}

void read_data()
{
  Serial.println(F("Read float from flash page 0: "));

  // Fetch first flash page
  flash.fetch_page(0);

  for(uint16_t i = 0; i < flash.buffer_size(); i++)
  {
    Serial.print(F("Addr: "));
    Serial.print(i);
    Serial.print(F(" \tValue: "));
    Serial.print(flash[i]);
    Serial.print(F(" \tCharacter: "));
    Serial.println((char)flash[i]);
  }
}

void setup()
{
  delay(2000);
  Serial.begin(9600);

  if(!flash.check_writable())
  {
    Serial.println(F("Incompatible or no Urboot compatible bootloader present! Please burn correct bootloader"));
    while(1);
  }

  // If the allocated flash space is above 64kiB, a 16-bit pointer won't be enough anymore.
  // As a workaround, you can set the address to the allocated space like this, and the
  // library will handle the rest. You'll also have to allocate your flash space in
  // PROGMEM1 rather than PROGMEM.
  //flash.set_far_address(pgm_get_far_address(flash_space));

  // Fetch flash page 1, where we may have a flag
  flash.fetch_page(1);

  // Check if our flag is present
  if(flash[5] == 'X')
  {
    Serial.println(F("Content found!"));
    read_data();
  }
  else
  {
    Serial.print(F("Flash page size for this chip: "));
    Serial.print(SPM_PAGESIZE);
    Serial.print(F(" bytes\nTotal assigned flash space: "));
    Serial.print(NUMBER_OF_PAGES * SPM_PAGESIZE);
    Serial.println(F(" bytes"));

    Serial.println(F("No content found! Writing new content..."));
    write_data();
  }
}

void loop()
{

}
