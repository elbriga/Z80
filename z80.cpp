#include <Arduino.h> // para Serial
#include <SPI.h>

#include "z80.h"

#define SPI_CLOCK 1000000 // 10 MHz
SPISettings settings595(SPI_CLOCK, MSBFIRST, SPI_MODE0); // para o 74HC595
SPISettings settings165(SPI_CLOCK, MSBFIRST, SPI_MODE2); // para o 74LS165

Z80::Z80() : controlPins(0), address(0), dataIN(0) {}

void Z80::printPins(String tag) {
  Serial.print("RD:");
  Serial.print(controlPins & Z80_RD_BIT ? 1 : 0);
  Serial.print(" WR:");
  Serial.print(controlPins & Z80_WR_BIT ? 1 : 0);
  Serial.print(" MREQ:");
  Serial.print(controlPins & Z80_MREQ_BIT ? 1 : 0);
  Serial.print(" IORQ:");
  Serial.print(controlPins & Z80_IORQ_BIT ? 1 : 0);
  Serial.print(" M1:");
  Serial.print(controlPins & Z80_M1_BIT ? 1 : 0);
  Serial.print(" RFSH:");
  Serial.print(controlPins & Z80_RFSH_BIT ? 1 : 0);
  Serial.print(" HALT:");
  Serial.print(controlPins & Z80_HALT_BIT ? 1 : 0);

  Serial.print(" ADDR:");
  Serial.print(address, HEX);

  Serial.print(" DATAIN:");
  Serial.print(dataIN, HEX);

  Serial.println(tag);
}

void Z80::cycle(String tag) {
  clock(1);
  //readPins(); // le controlPins + address + dataIN
  printPins(tag);
}

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

  pinMode(DATA_OUTPUT_ENABLE_PIN, OUTPUT);
  pinMode(SPI_OUT_LATCH_PIN,      OUTPUT);
  pinMode(SPI_IN_LATCH_PIN,       OUTPUT);

  digitalWrite(DATA_OUTPUT_ENABLE_PIN, HIGH);
  digitalWrite(SPI_OUT_LATCH_PIN,      HIGH);
  digitalWrite(SPI_IN_LATCH_PIN,       HIGH);

  SPI.begin();
  // SPI.setFrequency(1000000);  // 1 MHz
  // SPI.setDataMode(SPI_MODE2); // 74LS165 trabalha em modo 2
}

void Z80::readPins() {
  uint8_t addrL, addrH;
  
  // --- LER DOS 165 (MODE2) ---
  SPI.beginTransaction(settings165);
  digitalWrite(SPI_IN_LATCH_PIN, LOW);
  digitalWrite(SPI_IN_LATCH_PIN, HIGH);
  // delayMicroseconds(1);
  dataIN      = SPI.transfer(0x00);
  addrL       = SPI.transfer(0x00);
  addrH       = SPI.transfer(0x00);
  controlPins = SPI.transfer(0x00);
  SPI.endTransaction();

  address = (addrH << 8) + addrL;
}

void Z80::writeDataOut(uint8_t dataOut) {
  // --- ESCREVER NO 595 (MODE0) ---
  // delayMicroseconds(1);
  SPI.beginTransaction(settings595);
  SPI.transfer(dataOut);
  SPI.endTransaction();

  digitalWrite(SPI_OUT_LATCH_PIN, LOW);
  digitalWrite(SPI_OUT_LATCH_PIN, HIGH);
}

void Z80::writeRAM() {
  RAM[address] = dataIN;
}

uint8_t Z80::readRAM() {
  return RAM[address];
}

void Z80::reset() {
  digitalWrite(Z80_RESET_PIN, LOW);
  // pulsar o clock durante o reset, no minimo 3 vezes
  clock(4);
  digitalWrite(Z80_RESET_PIN, HIGH);
}

#define Z80_DELAY_uS_CLOCK 5000
void Z80::clock(int num) {
  for (int i=0; i<num; i++) {
    digitalWrite(Z80_CLOCK_PIN, HIGH);
    delayMicroseconds(Z80_DELAY_uS_CLOCK);

    readPins(); // le controlPins + address + dataIN

    digitalWrite(Z80_CLOCK_PIN, LOW);
    delayMicroseconds(Z80_DELAY_uS_CLOCK);
  }
}
