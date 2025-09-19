#include "z80.h"
#include "ROM.h"

#define LED_PIN 8

Z80 Z80;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Z80.begin();
  Z80.reset();

  Serial.println("\nInit!");
  delay(1000);
}

uint8_t led = 0, cnt = 0;
void loop() {
  if (cnt++ >= 40) {
    cnt = 0;
    Z80.reset();
    Serial.println("\n\n\n>>> RESET!");
    delay(1000);
  }

  Z80.cycle(); // clock > readPins > printPins

  if (!(Z80.controlPins & Z80_MREQ_BIT)) { // Memory Request
    if (!(Z80.controlPins & Z80_RD_BIT)) { // READ
      uint8_t data = 0xFF; // valor default
      if (Z80.address < Z80_ROM_len) {
        data = Z80_ROM[Z80.address];
      } else {
        data = Z80.readRAM();
      }

      Serial.print("> READ ");
      Serial.print(Z80.address, HEX);
      Serial.print(" = ");
      Serial.println(data, HEX);

      Z80.writeDataOut(data);                     // coloca no barramento

      digitalWrite(DATA_OUTPUT_ENABLE_PIN, LOW);  // habilita saídas
      Z80.cycle(" **");                           // deixa CPU capturar
      Z80.cycle(" **2");
      digitalWrite(DATA_OUTPUT_ENABLE_PIN, HIGH); // solta o barramento
      delayMicroseconds(1);
    }
    
    else if (!(Z80.controlPins & Z80_WR_BIT)) { // WRITE
      Serial.print("> WRITE ");
      Serial.print(Z80.address, HEX);
      Serial.print(" = ");
      Serial.println(Z80.dataIN, HEX);

      Z80.writeRAM();
    }
    
    else {
      // INVALIDO!
      Serial.println("> SOh MREQ??");
    }
  }

  led = 1 - led;
  digitalWrite(LED_PIN, led);

  // delay(1000);
}
