#include "Flash.h"
#include "optiboot.h"

Flash::Flash(const uint8_t* flash_array, const uint16_t flash_array_size, uint8_t *ram_array, const uint16_t ram_array_size)
  : _flash_array(flash_array),
    _flash_array_size(flash_array_size),
    _ram_array(ram_array),
    _ram_array_size(ram_array_size)
{
}

uint8_t& Flash::operator[](int16_t index)
{
  return _ram_array[index];
}

#ifdef RAMPZ
void Flash::set_far_address(uint32_t address)
{
  _far_flash_array_addr = address;
}
#endif

bool Flash::check_writable()
{
  uint8_t content = 0;
  // 256kiB flash
  #if FLASHEND == 0x3FFFF
    content = pgm_read_byte_far(0x3FFFF);
  // 128kiB flash
  #elif FLASHEND == 0x1FFFF
    content = pgm_read_byte_far(0x1FFFF);
  //64kiB flash
  #elif FLASHEND == 0xFFFF
    content = pgm_read_byte(0xFFFF);
  // 32kiB flash
  #elif FLASHEND == 0x7FFF
    content = pgm_read_byte(0x7FFF);
  // 16kiB flash
  #elif FLASHEND == 0x3FFF
    content = pgm_read_byte(0x3FFF);
  // 8kiB flash
  #elif FLASHEND == 0x1FFF
    content = pgm_read_byte(0x1FFF);
  #endif

  if(content >= 8)
    return true;
  else
    return false;
}

void Flash::clear_buffer(uint8_t fill)
{
  memset(_ram_array, fill, sizeof(_ram_array_size));
}

uint8_t Flash::read_buffer(uint8_t index)
{
  return _ram_array[index];
}

void Flash::write_buffer(uint8_t index, uint8_t value)
{
  _ram_array[index] = value;
}

uint16_t Flash::buffer_size()
{
  return _ram_array_size;
}

void Flash::write_page(uint16_t flash_page_number)
{
  // For devices with 128kiB or more, and data is stored in far progmem
  #ifdef RAMPZ
  if(_far_flash_array_addr != 0x0000)
  {
    optiboot_writePage(_far_flash_array_addr, _ram_array, flash_page_number);
  }
  // For devices with where flash space is allocated in near progmem
  else
  #endif
  {
    optiboot_writePage(_flash_array, _ram_array, flash_page_number);
  }
}

void Flash::fetch_page(uint16_t flash_page_number)
{
  // For devices with 128kiB or more, and data is stored in far progmem
  #ifdef RAMPZ
  if(_far_flash_array_addr != 0x0000)
  {
    optiboot_read(_far_flash_array_addr, _ram_array, flash_page_number, 0, _ram_array_size);
  }
  // For devices with where flash space is allocated in near progmem
  else
  #endif
  {
    optiboot_read(_flash_array, _ram_array, flash_page_number, 0, _ram_array_size);
  }
}

void Flash::fetch_data(uint16_t start_address, uint16_t stop_address)
{
  uint16_t end_address;
  if(stop_address - start_address > _ram_array_size)
    end_address = _ram_array_size;
  else
    end_address = stop_address;

  #ifdef RAMPZ
  if(_far_flash_array_addr != 0x0000)
  {
    optiboot_read(_far_flash_array_addr, _ram_array, 0, start_address, end_address);
  }
  // For devices with where flash space is allocated in near progmem
  else
  #endif
  {
    optiboot_read(_flash_array, _ram_array, 0, start_address, end_address);
  }
}
