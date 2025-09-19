#pragma once

// z80 > entradas
#define Z80_CLOCK_PIN       0
#define Z80_INT_PIN         21
#define Z80_NMI_PIN         20
#define Z80_WAIT_PIN        10
#define Z80_RESET_PIN       9

// z80 > saidas > 4o 74165 > byte control
#define Z80_HALT_BIT        1
#define Z80_MREQ_BIT        2
#define Z80_IORQ_BIT        4
#define Z80_RD_BIT          8
#define Z80_WR_BIT          16
#define Z80_M1_BIT          32
#define Z80_RFSH_BIT        64

// SPI = 4 x 74165 > 32 inputs + 1 x 74595 > 8 outputs
#define DATA_OUTPUT_ENABLE_PIN 1
#define SPI_OUT_LATCH_PIN      2
#define SPI_IN_LATCH_PIN       3
// SCK  -> GPIO4
// MISO -> GPIO5
// MOSI -> GPIO6

class Z80 {
private:
  uint8_t RAM[65536]; // 64K de RAM

public:
  uint16_t address;
  uint8_t  controlPins, dataIN; // lidos por SPI dos 74165

  Z80();

  void begin();
  void cycle(String tag="");
  void printPins(String tag="");

  void readPins();
  void writeDataOut(uint8_t dataOut);
  
  void writeRAM();
  uint8_t readRAM();

  void reset();
  void clock(int num=1);
};
