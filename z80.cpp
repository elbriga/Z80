#include "esp32-hal.h"
#include <Arduino.h> // para Serial
#include "z80.h"

Z80::Z80() : ativa(false) {}

void Z80::begin() {
  pinMode(Z80_CLOCK_PIN, OUTPUT);
  pinMode(Z80_INT_PIN,   OUTPUT);
  pinMode(Z80_NMI_PIN,   OUTPUT);
  pinMode(Z80_WAIT_PIN,  OUTPUT);
  pinMode(Z80_RESET_PIN, OUTPUT);

  digitalWrite(Z80_CLOCK_PIN, LOW);
  digitalWrite(Z80_INT_PIN,   HIGH);
  digitalWrite(Z80_NMI_PIN,   HIGH);
  digitalWrite(Z80_WAIT_PIN,  HIGH);
  digitalWrite(Z80_RESET_PIN, HIGH);
}

void Z80::reset() {
  digitalWrite(Z80_RESET_PIN, LOW);
  delayMicroseconds(500);
  digitalWrite(Z80_RESET_PIN, HIGH);
}
