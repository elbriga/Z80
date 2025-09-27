/*
const unsigned int Z80_ROM_len = 12;

const unsigned char Z80_ROM[] = {
  0x3E, 0x55,             // LD A,55h
  0x32, 0x00, 0x80,       // LD (8000h),A
  0x3A, 0x00, 0x80,       // LD A,(8000h)
  0x32, 0x01, 0x80,       // LD (8001h),A
  0xC3, 0x00, 0x00        // JP 0000h
};
*/
/*
const unsigned int Z80_ROM_len = 12;

const unsigned char Z80_ROM[] = {
  0x3E, 0x42,             // LD A,42h
  0xCD, 0x08, 0x00,       // CALL 0008h
  0xC3, 0x00, 0x00,       // JP 0000h
  0x32, 0x00, 0x80,       // LD (8000h),A   [subrotina]
  0xC9                    // RET
};
*/
const unsigned int Z80_ROM_len = 19;

const unsigned char Z80_ROM[] = {
  0x31, 0xFF, 0x00,       // LD SP,00FFh
  0x3E, 0x55,             // LD A,55h
  0xCD, 0x0B, 0x00,       // CALL 000Bh
  0xC3, 0x03, 0x00,       // JP 0003h
  0xF5,                   // PUSH AF
  0xC1,                   // POP BC
  0x0E, 0x00,             // LD C,00h (substituído na simulação pelo POP AF → BC)
  0x32, 0x01, 0x80,       // LD (8001h),A
  0xC9                    // RET
};
