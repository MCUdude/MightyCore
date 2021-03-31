#ifndef FLASH_H
#define FLASH_H

#include <Arduino.h>

class Flash
{
  public:
    Flash(const uint8_t* flash_array, const uint16_t flash_array_size, uint8_t *ram_array, const uint16_t ram_array_size = SPM_PAGESIZE);
    #ifdef RAMPZ
    void set_far_address(uint32_t address);
    bool check_writable();
    #endif
    void clear_buffer(uint8_t fill = 0x00);
    uint8_t read_buffer(uint8_t index);
    void write_buffer(uint8_t index, uint8_t value);
    uint16_t buffer_size();
    void write_page(uint16_t flash_page_number);
    void fetch_page(uint16_t flash_page_number);
    void fetch_data(uint16_t start_address, uint16_t stop_address);

    // Operator overload to be able to read and write directly to the RAM array from a byte level
    uint8_t& operator[] (int16_t index);

    //Functionality to 'put' and 'get' objects to and from the RAM array.
    template< typename T > const T &put(int idx, const T &t )
    {
      const uint8_t *ptr = (const uint8_t*) &t;
      for(uint16_t count = 0; count < sizeof(T); count++)
        _ram_array[idx + count] = *ptr++;
      return t;
    }

    template< typename T > T &get( int idx, T &t )
    {
      uint8_t *ptr = (uint8_t*) &t;
      for(uint16_t count = 0; count < sizeof(T); count++)
        *ptr++ = _ram_array[idx + count];
      return t;
    }

  private:
    const uint8_t *_flash_array;
    uint32_t _far_flash_array_addr;
    const uint16_t _flash_array_size;
    uint8_t *_ram_array;
    const uint16_t _ram_array_size;
};

#endif
