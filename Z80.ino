#include <SPI.h>
#include "z80.h"

// SPI = 4 x 74165 > 32 inputs + 1 x 74595 > 8 outputs
#define DATA_OUTPUT_ENABLE_PIN 1
#define SPI_OUT_LATCH_PIN      2
#define SPI_IN_LATCH_PIN       3
#define LED_PIN                8
// SCK  -> GPIO4
// MISO -> GPIO5
// MOSI -> GPIO6

#define SPI_CLOCK 10000000 // 10 MHz
SPISettings settings595(SPI_CLOCK, MSBFIRST, SPI_MODE0); // para o 74HC595
SPISettings settings165(SPI_CLOCK, MSBFIRST, SPI_MODE2); // para o 74LS165

Z80 Z80;

uint32_t transferDataSPI(uint8_t dataOut)
{
  uint8_t control, addrH, addrL, dataIN;
  
  // --- LER DOS 165 (MODE2) ---
  SPI.beginTransaction(settings165);
  digitalWrite(SPI_IN_LATCH_PIN, LOW);
  digitalWrite(SPI_IN_LATCH_PIN, HIGH);
  // delayMicroseconds(1);
  dataIN  = SPI.transfer(0x00);
  addrL   = SPI.transfer(0x00);
  addrH   = SPI.transfer(0x00);
  control = SPI.transfer(0x00);
  SPI.endTransaction();

  // --- ESCREVER NO 595 (MODE0) ---
  // delayMicroseconds(1);
  SPI.beginTransaction(settings595);
  SPI.transfer(dataOut);
  SPI.endTransaction();

  digitalWrite(SPI_OUT_LATCH_PIN, LOW);
  digitalWrite(SPI_OUT_LATCH_PIN, HIGH);

  return (control << 24) + (addrH << 16) + (addrL << 8) + dataIN;
}

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_PIN,                OUTPUT);
  pinMode(DATA_OUTPUT_ENABLE_PIN, OUTPUT);
  pinMode(SPI_OUT_LATCH_PIN,      OUTPUT);
  pinMode(SPI_IN_LATCH_PIN,       OUTPUT);

  digitalWrite(DATA_OUTPUT_ENABLE_PIN, HIGH);
  digitalWrite(SPI_OUT_LATCH_PIN,      HIGH);
  digitalWrite(SPI_IN_LATCH_PIN,       HIGH);

  SPI.begin();
  // SPI.setFrequency(1000000);  // 1 MHz
  // SPI.setDataMode(SPI_MODE2); // 74LS165 trabalha em modo 2

  Z80.begin();
  
  Serial.println("\nInit!");

  Serial.println("Z80 Reset");
  Z80.reset();
}

uint8_t out = 0, led = 0;
void loop() {
  uint32_t in = transferDataSPI(out++);

  Serial.print(in, BIN);
  Serial.print(" : ");
  Serial.println(out);

  led = 1 - led;
  digitalWrite(LED_PIN, led);

  delay(500);
}
