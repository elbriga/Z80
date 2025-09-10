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

class Z80 {
private:
  bool ativa;

public:
  Z80();

  void begin();
  void reset();
};
