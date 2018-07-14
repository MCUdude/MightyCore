/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "w5100.h"

#if defined(__arm__) && defined(TEENSYDUINO)
#include "SPIFIFO.h"
#ifdef  HAS_SPIFIFO
#define USE_SPIFIFO
#endif
#endif

//#define W5500_4K_BUFFERS
//#define W5200_4K_BUFFERS

// If the core library defines a SS pin, use it as the
// default.  Otherwise, default the default to pin 10.
#if defined(__AVR__)
#define SS_PIN_DEFAULT  SS
#elif defined(PIN_SPI_SS)
#define SS_PIN_DEFAULT  PIN_SPI_SS
#elif defined(CORE_SS0_PIN)
#define SS_PIN_DEFAULT  CORE_SS0_PIN
#else
#define SS_PIN_DEFAULT  10
#endif

// W5100 controller instance
uint16_t W5100Class::SBASE[MAX_SOCK_NUM];
uint16_t W5100Class::RBASE[MAX_SOCK_NUM];
uint16_t W5100Class::CH_BASE;
uint16_t W5100Class::SSIZE;
uint16_t W5100Class::SMASK;
uint8_t  W5100Class::chip;
uint8_t  W5100Class::ss_pin = SS_PIN_DEFAULT;
W5100Class W5100;

// pointers and bitmasks for optimized SS pin
#if defined(__AVR__)
  volatile uint8_t * W5100Class::ss_pin_reg;
  uint8_t W5100Class::ss_pin_mask;
#elif defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK66FX1M0__) || defined(__MK64FX512__)
  volatile uint8_t * W5100Class::ss_pin_reg;
#elif defined(__MKL26Z64__)
  volatile uint8_t * W5100Class::ss_pin_reg;
  uint8_t W5100Class::ss_pin_mask;
#elif defined(__SAM3X8E__) || defined(__SAM3A8C__) || defined(__SAM3A4C__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(__PIC32MX__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(ARDUINO_ARCH_ESP8266)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(__SAMD21G18A__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#endif


uint8_t W5100Class::init(void)
{
  uint16_t TXBUF_BASE, RXBUF_BASE;
  uint8_t i;

  // Many Ethernet shields have a CAT811 or similar reset chip
  // connected to W5100 or W5200 chips.  The W5200 will not work at
  // all, and may even drive its MISO pin, until given an active low
  // reset pulse!  The CAT811 has a 240 ms typical pulse length, and
  // a 400 ms worst case maximum pulse length.  MAX811 has a worst
  // case maximum 560 ms pulse length.  This delay is meant to wait
  // until the reset pulse is ended.  If your hardware has a shorter
  // reset time, this can be edited or removed.
  delay(560);
  //Serial.println("w5100 init");

#ifdef USE_SPIFIFO
  SPI.begin();
  SPIFIFO.begin(ss_pin, SPI_CLOCK_12MHz);  // W5100 is 14 MHz max
#else
  SPI.begin();
  initSS();
  resetSS();
#endif
  SPI.beginTransaction(SPI_ETHERNET_SETTINGS);

  // Attempt W5200 detection first, because W5200 does not properly
  // reset its SPI state when CS goes high (inactive).  Communication
  // from detecting the other chips can leave the W5200 in a state
  // where it won't recover, unless given a reset pulse.
  if (isW5200()) {
    CH_BASE = 0x4000;
    #ifdef W5200_4K_BUFFERS
    SSIZE = 4096;
    SMASK = 0x0FFF;
    #else
    SSIZE = 2048;    // 2K buffers
    SMASK = 0x07FF;
    #endif
    TXBUF_BASE = 0x8000;
    RXBUF_BASE = 0xC000;
    for (i=0; i<MAX_SOCK_NUM; i++) {
      writeSnRX_SIZE(i, SSIZE >> 10);
      writeSnTX_SIZE(i, SSIZE >> 10);
    }
    for (; i<8; i++) {
      writeSnRX_SIZE(i, 0);
      writeSnTX_SIZE(i, 0);
    }
  // Try W5500 next.  Wiznet finally seems to have implemented
  // SPI well with this chip.  It appears to be very resilient,
  // so try it after the fragile W5200
  } else if (isW5500()) {
    CH_BASE = 0x1000;
    #ifdef W5500_4K_BUFFERS
    SSIZE = 4096;    // 4K buffers
    SMASK = 0x0FFF;
    #else
    SSIZE = 2048;    // 2K buffers
    SMASK = 0x07FF;
    #endif
    TXBUF_BASE = 0x8000;
    RXBUF_BASE = 0xC000;
    #ifdef W5500_4K_BUFFERS
    for (i=0; i<MAX_SOCK_NUM; i++) {
      writeSnRX_SIZE(i, SSIZE >> 10);
      writeSnTX_SIZE(i, SSIZE >> 10);
    }
    for (; i<8; i++) {
      writeSnRX_SIZE(i, 0);
      writeSnTX_SIZE(i, 0);
    }
    #endif
  // Try W5100 last.  This simple chip uses fixed 4 byte frames
  // for every 8 bit access.  Terribly inefficient, but so simple
  // it recovers from "hearing" unsuccessful W5100 or W5200
  // communication.  W5100 is also the only chip without a VERSIONR
  // register for identification, so we check this last.
  } else if (isW5100()) {
    CH_BASE = 0x0400;
    SSIZE = 2048;
    SMASK = 0x07FF;
    TXBUF_BASE = 0x4000;
    RXBUF_BASE = 0x6000;
    writeTMSR(0x55);
    writeRMSR(0x55);
  // No hardware seems to be present.  Or it could be a W5200
  // that's heard other SPI communication if its chip select
  // pin wasn't high when a SD card or other SPI chip was used.
  } else {
    //Serial.println("no chip :-(");
    chip = 0;
    SPI.endTransaction();
    return 0; // no known chip is responding :-(
  }
  SPI.endTransaction();
  // Initialize the socket base addresses
  for (int i=0; i<MAX_SOCK_NUM; i++) {
    SBASE[i] = TXBUF_BASE + SSIZE * i;
    RBASE[i] = RXBUF_BASE + SSIZE * i;
  }
  return 1; // successful init
}

// Soft reset the Wiznet chip, by writing to its MR register reset bit
uint8_t W5100Class::softReset(void)
{
  uint16_t count=0;

  //Serial.println("Wiznet soft reset");
  // write to reset bit
  writeMR(0x80);
  // then wait for soft reset to complete
  do {
    uint8_t mr = readMR();
    //Serial.print("mr=");
    //Serial.println(mr, HEX);
    if (mr == 0) return 1;
    delay(1);
  } while (++count < 20);
  return 0;
}

uint8_t W5100Class::isW5100(void)
{
  chip = 51;
  //Serial.println("w5100.cpp: detect W5100 chip");
  if (!softReset()) return 0;
  writeMR(0x10);
  if (readMR() != 0x10) return 0;
  writeMR(0x12);
  if (readMR() != 0x12) return 0;
  writeMR(0x00);
  if (readMR() != 0x00) return 0;
  //Serial.println("chip is W5100");
  return 1;
}

uint8_t W5100Class::isW5200(void)
{
  chip = 52;
  //Serial.println("w5100.cpp: detect W5200 chip");
  if (!softReset()) return 0;
  writeMR(0x08);
  if (readMR() != 0x08) return 0;
  writeMR(0x10);
  if (readMR() != 0x10) return 0;
  writeMR(0x00);
  if (readMR() != 0x00) return 0;
  int ver = readVERSIONR_W5200();
  //Serial.print("version=");
  //Serial.println(ver);
  if (ver != 3) return 0;
  //Serial.println("chip is W5200");
  return 1;
}

uint8_t W5100Class::isW5500(void)
{
  chip = 55;
  //Serial.println("w5100.cpp: detect W5500 chip");
  if (!softReset()) return 0;
  writeMR(0x08);
  if (readMR() != 0x08) return 0;
  writeMR(0x10);
  if (readMR() != 0x10) return 0;
  writeMR(0x00);
  if (readMR() != 0x00) return 0;
  int ver = readVERSIONR_W5500();
  //Serial.print("version=");
  //Serial.println(ver);
  if (ver != 4) return 0;
  //Serial.println("chip is W5500");
  return 1;
}


#ifdef USE_SPIFIFO
uint16_t W5100Class::write(uint16_t addr, const uint8_t *buf, uint16_t len)
{
  uint32_t i;

  if (chip == 51) {
    for (i=0; i<len; i++) {
  SPIFIFO.write16(0xF000 | (addr >> 8), SPI_CONTINUE);
  SPIFIFO.write16((addr << 8) | buf[i]);
  addr++;
  SPIFIFO.read();
  SPIFIFO.read();
    }
  } else if (chip == 52) {
  SPIFIFO.clear();
  SPIFIFO.write16(addr, SPI_CONTINUE);
  SPIFIFO.write16(len | 0x8000, SPI_CONTINUE);
  for (i=0; i<len; i++) {
    SPIFIFO.write(buf[i], ((i+1<len) ? SPI_CONTINUE : 0));
    SPIFIFO.read();
  }
  SPIFIFO.read();
  SPIFIFO.read();
  } else {
  //SPIFIFO.clear();
  SPIFIFO.write16(addr, SPI_CONTINUE);
  if (addr < 0x100) {
    // common registers 00nn
    SPIFIFO.write16(0x0400 | *buf++,
      ((len > 1) ? SPI_CONTINUE : 0));
  } else if (addr < 0x8000) {
    // socket registers  10nn, 11nn, 12nn, 13nn, etc
    SPIFIFO.write16(((addr << 5) & 0xE000) | 0x0C00 | *buf++,
      ((len > 1) ? SPI_CONTINUE : 0));
  } else if (addr < 0xC000) {
    // transmit buffers  8000-87FF, 8800-8FFF, 9000-97FF, etc
    #ifdef W5500_4K_BUFFERS
    SPIFIFO.write16(((addr << 1) & 0x6000) | 0x1400 | *buf++, // 4K buffers
      ((len > 1) ? SPI_CONTINUE : 0));
    #else
    SPIFIFO.write16(((addr << 2) & 0xE000) | 0x1400 | *buf++, // 2K buffers
      ((len > 1) ? SPI_CONTINUE : 0));
    #endif
  } else {
    // receive buffers
    #ifdef W5500_4K_BUFFERS
    SPIFIFO.write16(((addr << 1) & 0x6000) | 0x1C00 | *buf++, // 4K buffers
      ((len > 1) ? SPI_CONTINUE : 0));
    #else
    SPIFIFO.write16(((addr << 2) & 0xE000) | 0x1C00 | *buf++, // 2K buffers
      ((len > 1) ? SPI_CONTINUE : 0));
    #endif
  }
  len--;
  while (len >= 2) {
    len -= 2;
    SPIFIFO.write16((*buf << 8) | *(buf+1), (len == 0) ? 0 : SPI_CONTINUE);
    buf += 2;
    SPIFIFO.read();
  }
  if (len) {
    SPIFIFO.write(*buf);
    SPIFIFO.read();
  }
  SPIFIFO.read();
  SPIFIFO.read();
  }
  return len;
}
#else
uint16_t W5100Class::write(uint16_t addr, const uint8_t *buf, uint16_t len)
{
  if (chip == 51) {
    for (uint16_t i=0; i<len; i++) {
      setSS();
      SPI.transfer(0xF0);
      SPI.transfer(addr >> 8);
      SPI.transfer(addr & 0xFF);
      addr++;
      SPI.transfer(buf[i]);
      resetSS();
    }
  } else if (chip == 52) {
    setSS();
    SPI.transfer(addr >> 8);
    SPI.transfer(addr & 0xFF);
    SPI.transfer(((len >> 8) & 0x7F) | 0x80);
    SPI.transfer(len & 0xFF);
    for (uint16_t i=0; i<len; i++) {
      SPI.transfer(buf[i]);
    }
    resetSS();
  } else {
    setSS();
    if (addr < 0x100) {
      // common registers 00nn
      SPI.transfer(0);
      SPI.transfer(addr & 0xFF);
      SPI.transfer(0x04);
    } else if (addr < 0x8000) {
      // socket registers  10nn, 11nn, 12nn, 13nn, etc
      SPI.transfer(0);
      SPI.transfer(addr & 0xFF);
      SPI.transfer(((addr >> 3) & 0xE0) | 0x0C);
    } else if (addr < 0xC000) {
      // transmit buffers  8000-87FF, 8800-8FFF, 9000-97FF, etc
      //  10## #nnn nnnn nnnn
      SPI.transfer(addr >> 8);
      SPI.transfer(addr & 0xFF);
      #ifdef W5500_4K_BUFFERS
      SPI.transfer(((addr >> 7) & 0x60) | 0x14); // 4K buffers
      #else
      SPI.transfer(((addr >> 6) & 0xE0) | 0x14); // 2K buffers
      #endif
    } else {
      // receive buffers
      SPI.transfer(addr >> 8);
      SPI.transfer(addr & 0xFF);
      #ifdef W5500_4K_BUFFERS
      SPI.transfer(((addr >> 7) & 0x60) | 0x1C); // 4K buffers
      #else
      SPI.transfer(((addr >> 6) & 0xE0) | 0x1C); // 2K buffers
      #endif
    }
    for (uint16_t i=0; i<len; i++) {
      SPI.transfer(buf[i]);
    }
    resetSS();
  }
  return len;
}
#endif







#ifdef USE_SPIFIFO
uint16_t W5100Class::read(uint16_t addr, uint8_t *buf, uint16_t len)
{
  uint32_t i;

  if (chip == 51) {
    for (i=0; i<len; i++) {
  #if 1
  SPIFIFO.write(0x0F, SPI_CONTINUE);
  SPIFIFO.write16(addr, SPI_CONTINUE);
  addr++;
  SPIFIFO.read();
  SPIFIFO.write(0);
  SPIFIFO.read();
  buf[i] = SPIFIFO.read();
  #endif
  #if 0
  // this does not work, but why?
  SPIFIFO.write16(0x0F00 | (addr >> 8), SPI_CONTINUE);
  SPIFIFO.write16(addr << 8);
  addr++;
  SPIFIFO.read();
  buf[i] = SPIFIFO.read();
  #endif
    }
  } else if (chip == 52) {
  // len = 1:  write header, write 1 byte, read
  // len = 2:  write header, write 2 byte, read
  // len = 3,5,7
  SPIFIFO.clear();
  SPIFIFO.write16(addr, SPI_CONTINUE);
  SPIFIFO.write16(len & 0x7FFF, SPI_CONTINUE);
  SPIFIFO.read();
  if (len == 1) {
    // read only 1 byte
    SPIFIFO.write(0);
    SPIFIFO.read();
    *buf = SPIFIFO.read();
  } else if (len == 2) {
    // read only 2 bytes
    SPIFIFO.write16(0);
    SPIFIFO.read();
    uint32_t val = SPIFIFO.read();
    *buf++ = val >> 8;
    *buf = val;
  } else if ((len & 1)) {
    // read 3 or more, odd length
      //Serial.print("W5200 read, len=");
    //Serial.println(len);
    uint32_t count = len / 2;
    SPIFIFO.write16(0, SPI_CONTINUE);
    SPIFIFO.read();
    do {
      if (count > 1) SPIFIFO.write16(0, SPI_CONTINUE);
      else SPIFIFO.write(0);
      uint32_t val = SPIFIFO.read();
      //TODO: WebClient_speedtest with READSIZE 7 is
      //dramatically faster with this Serial.print(),
      //and the 2 above, but not without both.  Why?!
      //Serial.println(val, HEX);
      *buf++ = val >> 8;
      *buf++ = val;
    } while (--count > 0);
    *buf = SPIFIFO.read();
    //Serial.println(*buf, HEX);
  } else {
    // read 4 or more, even length
      //Serial.print("W5200 read, len=");
    //Serial.println(len);
    uint32_t count = len / 2 - 1;
    SPIFIFO.write16(0, SPI_CONTINUE);
    SPIFIFO.read();
    do {
      SPIFIFO.write16(0, (count > 1) ? SPI_CONTINUE : 0);
      uint32_t val = SPIFIFO.read();
      *buf++ = val >> 8;
      *buf++ = val;
    } while (--count > 0);
    uint32_t val = SPIFIFO.read();
    *buf++ = val >> 8;
    *buf++ = val;
  }
  } else {
  //SPIFIFO.clear();
  SPIFIFO.write16(addr, SPI_CONTINUE);
  if (addr < 0x100) {
    // common registers 00nn
    SPIFIFO.write16(0,
      ((len > 1) ? SPI_CONTINUE : 0));
  } else if (addr < 0x8000) {
    // socket registers  10nn, 11nn, 12nn, 13nn, etc
    SPIFIFO.write16(((addr << 5) & 0xE000) | 0x0800,
      ((len > 1) ? SPI_CONTINUE : 0));
  } else if (addr < 0xC000) {
    // transmit buffers  8000-87FF, 8800-8FFF, 9000-97FF, etc
    #ifdef W5500_4K_BUFFERS
    SPIFIFO.write16(((addr << 1) & 0x6000) | 0x1000, // 4K buffers
      ((len > 1) ? SPI_CONTINUE : 0));
    #else
    SPIFIFO.write16(((addr << 2) & 0xE000) | 0x1000, // 2K buffers
      ((len > 1) ? SPI_CONTINUE : 0));
    #endif
  } else {
    // receive buffers
    #ifdef W5500_4K_BUFFERS
    SPIFIFO.write16(((addr << 1) & 0x6000) | 0x1800, // 4K buffers
      ((len > 1) ? SPI_CONTINUE : 0));
    #else
    SPIFIFO.write16(((addr << 2) & 0xE000) | 0x1800, // 2K buffers
      ((len > 1) ? SPI_CONTINUE : 0));
    #endif
  }
  SPIFIFO.read();
  if (len <= 1) {
    *buf++ = SPIFIFO.read();
  } else if (len == 2) {
    SPIFIFO.write(0);
    *buf++ = SPIFIFO.read();
    *buf++ = SPIFIFO.read();
  } else if (len & 1) {
    uint32_t count = len >> 1;
    SPIFIFO.write16(0, (count > 1) ? SPI_CONTINUE : 0);
    *buf++ = SPIFIFO.read();
    while (count > 1) {
      count--;
      SPIFIFO.write16(0, (count > 1) ? SPI_CONTINUE : 0);
      uint32_t val = SPIFIFO.read();
      *buf++ = val >> 8;
      *buf++ = val;
    }
    uint32_t val = SPIFIFO.read();
    *buf++ = val >> 8;
    *buf++ = val;
  } else {
    SPIFIFO.write16(0, SPI_CONTINUE);
    *buf++ = SPIFIFO.read();
    uint32_t count = len >> 1;
    while (count > 1) {
      count--;
      if (count > 1) {
        SPIFIFO.write16(0, SPI_CONTINUE);
      } else {
        SPIFIFO.write(0, 0);
      }
      uint32_t val = SPIFIFO.read();
      *buf++ = val >> 8;
      *buf++ = val;
    }
    *buf = SPIFIFO.read();
  }
  }
  return len;
}
#else
uint16_t W5100Class::read(uint16_t addr, uint8_t *buf, uint16_t len)
{
  if (chip == 51) {
    for (uint16_t i=0; i<len; i++) {
      setSS();
      SPI.transfer(0x0F);
      SPI.transfer(addr >> 8);
      SPI.transfer(addr & 0xFF);
      addr++;
      buf[i] = SPI.transfer(0);
      resetSS();
    }
  } else if (chip == 52) {
    setSS();
    SPI.transfer(addr >> 8);
    SPI.transfer(addr & 0xFF);
    SPI.transfer((len >> 8) & 0x7F);
    SPI.transfer(len & 0xFF);
    for (uint16_t i=0; i<len; i++) {
      buf[i] = SPI.transfer(0);
    }
    resetSS();
  } else {
    setSS();
    if (addr < 0x100) {
      // common registers 00nn
      SPI.transfer(0);
      SPI.transfer(addr & 0xFF);
      SPI.transfer(0x00);
    } else if (addr < 0x8000) {
      // socket registers  10nn, 11nn, 12nn, 13nn, etc
      SPI.transfer(0);
      SPI.transfer(addr & 0xFF);
      SPI.transfer(((addr >> 3) & 0xE0) | 0x08);
    } else if (addr < 0xC000) {
      // transmit buffers  8000-87FF, 8800-8FFF, 9000-97FF, etc
      //  10## #nnn nnnn nnnn
      SPI.transfer(addr >> 8);
      SPI.transfer(addr & 0xFF);
      #ifdef W5500_4K_BUFFERS
      SPI.transfer(((addr >> 7) & 0x60) | 0x10); // 4K buffers
      #else
      SPI.transfer(((addr >> 6) & 0xE0) | 0x10); // 2K buffers
      #endif
    } else {
      // receive buffers
      SPI.transfer(addr >> 8);
      SPI.transfer(addr & 0xFF);
      #ifdef W5500_4K_BUFFERS
      SPI.transfer(((addr >> 7) & 0x60) | 0x18); // 4K buffers
      #else
      SPI.transfer(((addr >> 6) & 0xE0) | 0x18); // 2K buffers
      #endif
    }
    for (uint16_t i=0; i<len; i++) {
      buf[i] = SPI.transfer(0);
    }
    resetSS();
  }
  return len;
}
#endif

void W5100Class::execCmdSn(SOCKET s, SockCMD _cmd) {
  // Send command to socket
  writeSnCR(s, _cmd);
  // Wait for command to complete
  while (readSnCR(s))
    ;
}
