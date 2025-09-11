const unsigned int Z80_ROM_len = 8;

const unsigned char Z80_ROM[] = {
  0x3E, 0x55,       // LD A,55h
  0x32, 0x00, 0x80, // LD (8000h),A
  0xC3, 0x00, 0x00  // JP 0000h
};
