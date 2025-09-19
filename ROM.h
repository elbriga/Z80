const unsigned int Z80_ROM_len = 12;

const unsigned char Z80_ROM[] = {
  0x3E, 0x55,             // LD A,55h
  0x32, 0x00, 0x80,       // LD (8000h),A
  0x3A, 0x00, 0x80,       // LD A,(8000h)
  0x32, 0x01, 0x80,       // LD (8001h),A
  0xC3, 0x00, 0x00        // JP 0000h
};

/*
const unsigned int Z80_ROM_len = 11;

const unsigned char Z80_ROM[] = {
  0x3E, 0x42,             // LD A,42h
  0xCD, 0x07, 0x00,       // CALL 0007h
  0xC3, 0x00, 0x00,       // JP 0000h
  0x32, 0x00, 0x80,       // LD (8000h),A   [subrotina]
  0xC9                    // RET
};
*/