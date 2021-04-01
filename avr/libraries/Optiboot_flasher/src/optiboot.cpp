#include "optiboot.h"


// The same as do_smp but with disable/restore interrupts state required
// successful SPM execution. On devices with more than 64kB flash,
// 16-bit address is not enough, so there is also RAMPZ used in this case
void do_spm_cli(optiboot_addr_t address, uint8_t command, uint16_t data)
{
  uint8_t sreg_save;

  sreg_save = SREG;    // Save old SREG value
  asm volatile("cli"); // Disable interrupts
  #ifdef RAMPZ
    RAMPZ = (address >> 16) & 0xff;  // Address bits 23-16 goes to RAMPZ
    do_spm((address & 0xffff), command, data); // do_spm accepts only lower 16 bits of address
  #else
    do_spm(address, command, data);  // 16-bit address - no problems to pass directly
  #endif
  SREG = sreg_save; // Restore last interrupts state
}


// Erase page in FLASH
void optiboot_page_erase(optiboot_addr_t address)
{
  do_spm_cli(address, __BOOT_PAGE_ERASE, 0);
}


// Write word into temporary buffer
void optiboot_page_fill(optiboot_addr_t address, uint16_t data)
{
  do_spm_cli(address, __BOOT_PAGE_FILL, data);
}


//Write temporary buffer into FLASH
void optiboot_page_write(optiboot_addr_t address)
{
  do_spm_cli(address, __BOOT_PAGE_WRITE, 0);
}


// Higher level functions for reading and writing from flash

// Function to read bytes from a given page and further out in the memory
void optiboot_read(const uint8_t allocated_flash_space[], uint8_t storage_array[], uint16_t page_number, uint16_t start_address, uint16_t stop_address)
{
  for(uint16_t j = start_address; j < stop_address; j++)
  {
    uint8_t read_character = pgm_read_byte(&allocated_flash_space[j + SPM_PAGESIZE * (page_number)]);
    storage_array[j - start_address] = read_character;
  }
}




// Function to read a flash page and store it in an array (storage_array[])
void optiboot_readPage(const uint8_t allocated_flash_space[], uint8_t storage_array[], uint16_t page_number)
{
  optiboot_read(allocated_flash_space, storage_array, page_number, 0, SPM_PAGESIZE);
}


// Function to write data to a flash page to low memory (<64kiB)
void optiboot_writePage(const uint8_t allocated_flash_space[], uint8_t data_to_store[], uint16_t page_number)
{
  uint16_t word_buffer = 0;

  // Erase the flash page
  optiboot_page_erase((optiboot_addr_t)&allocated_flash_space[SPM_PAGESIZE * page_number]);

  // Copy ram buffer to temporary flash buffer
  for(uint16_t i = 0; i < SPM_PAGESIZE; i++)
  {
    if(!(i & 0x01)) // We must write words
      word_buffer = data_to_store[i];
    else
    {
      word_buffer += (data_to_store[i] << 8);
      optiboot_page_fill((optiboot_addr_t)(void*) &allocated_flash_space[i + SPM_PAGESIZE * (page_number)], word_buffer);
    }
  }

  // Write temporary buffer to flash
  optiboot_page_write((optiboot_addr_t)(void*) &allocated_flash_space[SPM_PAGESIZE * (page_number)]);
}



// Functions to read and write to the "far" part of the flash memory (>64kiB)
#ifdef RAMPZ

// Function to read an arbitrary number of bytes from the far memory (64kiB+) and store it in an array (storage_array[])
void optiboot_read(uint32_t flash_space_address, uint8_t storage_array[], uint16_t page_number, uint16_t start_address, uint16_t stop_address)
{
  for(uint16_t j = start_address; j < stop_address; j++)
  {
    uint8_t read_character = pgm_read_byte_far(flash_space_address + j + SPM_PAGESIZE * (page_number));
    storage_array[j - start_address] = read_character;
  }
}


// Function to read a flash page from the far memory (>64kiB) and store it in an array (storage_array[])
void optiboot_readPage(uint32_t flash_space_address, uint8_t storage_array[], uint16_t page_number)
{
  optiboot_read(flash_space_address, storage_array, page_number, 0, SPM_PAGESIZE);
}


// Function to write data to a flash page to far memory (>64kiB)
void optiboot_writePage(uint32_t flash_space_address, uint8_t data_to_store[], uint16_t page_number)
{
  uint16_t word_buffer = 0;

  // Erase the flash page
  optiboot_page_erase(flash_space_address + SPM_PAGESIZE * page_number);

  // Copy ram buffer to temporary flash buffer
  for(uint16_t i = 0; i < SPM_PAGESIZE; i++)
  {
    if(!(i & 0x01)) // We must write words
      word_buffer = data_to_store[i];
    else
    {
      word_buffer += (data_to_store[i] << 8);
      optiboot_page_fill((flash_space_address + i + SPM_PAGESIZE * page_number), word_buffer);
    }
  }
  // Write temporary buffer to flash
  optiboot_page_write(flash_space_address + SPM_PAGESIZE * page_number);
}

#endif // RAMPZ
