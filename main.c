#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h> 
#include <fcntl.h>
#include <unistd.h>

size_t filesize(int fd) {
  off_t fsize;
  fsize = lseek(fd, 0L, SEEK_END);
  lseek(fd, 0L, SEEK_SET);
  return fsize;
}

uint8_t *ld_program(char *filename, size_t *progsize) {
  int fd = open(filename, O_RDONLY);
  size_t size = filesize(fd);
  if (progsize != NULL) *progsize = size;
  return mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0L);
}

off_t fconvert_8080(uint8_t *program, off_t offset, FILE *fp) {
  uint8_t *code = &program[offset];
  size_t cs = 1;

  switch (*code) {
    case 0x00: fprintf(fp, "NOP"); break;
		case 0x01: fprintf(fp, "LXI    B,#$%02x%02x", code[2], code[1]); cs=3; break;
		case 0x02: fprintf(fp, "STAX   B"); break;
		case 0x03: fprintf(fp, "INX    B"); break;
		case 0x04: fprintf(fp, "INR    B"); break;
		case 0x05: fprintf(fp, "DCR    B"); break;
		case 0x06: fprintf(fp, "MVI    B,#$%02x", code[1]); cs=2; break;
		case 0x07: fprintf(fp, "RLC"); break;
		case 0x08: fprintf(fp, "NOP"); break;
		case 0x09: fprintf(fp, "DAD    B"); break;
		case 0x0a: fprintf(fp, "LDAX   B"); break;
		case 0x0b: fprintf(fp, "DCX    B"); break;
		case 0x0c: fprintf(fp, "INR    C"); break;
		case 0x0d: fprintf(fp, "DCR    C"); break;
		case 0x0e: fprintf(fp, "MVI    C,#$%02x", code[1]); cs = 2;	break;
		case 0x0f: fprintf(fp, "RRC"); break;
		case 0x10: fprintf(fp, "NOP"); break;
		case 0x11: fprintf(fp, "LXI    D,#$%02x%02x", code[2], code[1]); cs=3; break;
		case 0x12: fprintf(fp, "STAX   D"); break;
		case 0x13: fprintf(fp, "INX    D"); break;
		case 0x14: fprintf(fp, "INR    D"); break;
		case 0x15: fprintf(fp, "DCR    D"); break;
		case 0x16: fprintf(fp, "MVI    D,#$%02x", code[1]); cs=2; break;
		case 0x17: fprintf(fp, "RAL"); break;
		case 0x18: fprintf(fp, "NOP"); break;
		case 0x19: fprintf(fp, "DAD    D"); break;
		case 0x1a: fprintf(fp, "LDAX   D"); break;
		case 0x1b: fprintf(fp, "DCX    D"); break;
		case 0x1c: fprintf(fp, "INR    E"); break;
		case 0x1d: fprintf(fp, "DCR    E"); break;
		case 0x1e: fprintf(fp, "MVI    E,#$%02x", code[1]); cs = 2; break;
		case 0x1f: fprintf(fp, "RAR"); break;
		case 0x20: fprintf(fp, "NOP"); break;
		case 0x21: fprintf(fp, "LXI    H,#$%02x%02x", code[2], code[1]); cs=3; break;
		case 0x22: fprintf(fp, "SHLD   $%02x%02x", code[2], code[1]); cs=3; break;
		case 0x23: fprintf(fp, "INX    H"); break;
		case 0x24: fprintf(fp, "INR    H"); break;
		case 0x25: fprintf(fp, "DCR    H"); break;
		case 0x26: fprintf(fp, "MVI    H,#$%02x", code[1]); cs=2; break;
		case 0x27: fprintf(fp, "DAA"); break;
		case 0x28: fprintf(fp, "NOP"); break;
		case 0x29: fprintf(fp, "DAD    H"); break;
		case 0x2a: fprintf(fp, "LHLD   $%02x%02x", code[2], code[1]); cs=3; break;
		case 0x2b: fprintf(fp, "DCX    H"); break;
		case 0x2c: fprintf(fp, "INR    L"); break;
		case 0x2d: fprintf(fp, "DCR    L"); break;
		case 0x2e: fprintf(fp, "MVI    L,#$%02x", code[1]); cs = 2; break;
		case 0x2f: fprintf(fp, "CMA"); break;
		case 0x30: fprintf(fp, "NOP"); break;
		case 0x31: fprintf(fp, "LXI    SP,#$%02x%02x", code[2], code[1]); cs=3; break;
		case 0x32: fprintf(fp, "STA    $%02x%02x", code[2], code[1]); cs=3; break;
		case 0x33: fprintf(fp, "INX    SP"); break;
		case 0x34: fprintf(fp, "INR    M"); break;
		case 0x35: fprintf(fp, "DCR    M"); break;
		case 0x36: fprintf(fp, "MVI    M,#$%02x", code[1]); cs=2; break;
		case 0x37: fprintf(fp, "STC"); break;
		case 0x38: fprintf(fp, "NOP"); break;
		case 0x39: fprintf(fp, "DAD    SP"); break;
		case 0x3a: fprintf(fp, "LDA    $%02x%02x", code[2], code[1]); cs=3; break;
		case 0x3b: fprintf(fp, "DCX    SP"); break;
		case 0x3c: fprintf(fp, "INR    A"); break;
		case 0x3d: fprintf(fp, "DCR    A"); break;
		case 0x3e: fprintf(fp, "MVI    A,#$%02x", code[1]); cs = 2; break;
		case 0x3f: fprintf(fp, "CMC"); break;
		case 0x40: fprintf(fp, "MOV    B,B"); break;
		case 0x41: fprintf(fp, "MOV    B,C"); break;
		case 0x42: fprintf(fp, "MOV    B,D"); break;
		case 0x43: fprintf(fp, "MOV    B,E"); break;
		case 0x44: fprintf(fp, "MOV    B,H"); break;
		case 0x45: fprintf(fp, "MOV    B,L"); break;
		case 0x46: fprintf(fp, "MOV    B,M"); break;
		case 0x47: fprintf(fp, "MOV    B,A"); break;
		case 0x48: fprintf(fp, "MOV    C,B"); break;
		case 0x49: fprintf(fp, "MOV    C,C"); break;
		case 0x4a: fprintf(fp, "MOV    C,D"); break;
		case 0x4b: fprintf(fp, "MOV    C,E"); break;
		case 0x4c: fprintf(fp, "MOV    C,H"); break;
		case 0x4d: fprintf(fp, "MOV    C,L"); break;
		case 0x4e: fprintf(fp, "MOV    C,M"); break;
		case 0x4f: fprintf(fp, "MOV    C,A"); break;
		case 0x50: fprintf(fp, "MOV    D,B"); break;
		case 0x51: fprintf(fp, "MOV    D,C"); break;
		case 0x52: fprintf(fp, "MOV    D,D"); break;
		case 0x53: fprintf(fp, "MOV    D.E"); break;
		case 0x54: fprintf(fp, "MOV    D,H"); break;
		case 0x55: fprintf(fp, "MOV    D,L"); break;
		case 0x56: fprintf(fp, "MOV    D,M"); break;
		case 0x57: fprintf(fp, "MOV    D,A"); break;
		case 0x58: fprintf(fp, "MOV    E,B"); break;
		case 0x59: fprintf(fp, "MOV    E,C"); break;
		case 0x5a: fprintf(fp, "MOV    E,D"); break;
		case 0x5b: fprintf(fp, "MOV    E,E"); break;
		case 0x5c: fprintf(fp, "MOV    E,H"); break;
		case 0x5d: fprintf(fp, "MOV    E,L"); break;
		case 0x5e: fprintf(fp, "MOV    E,M"); break;
		case 0x5f: fprintf(fp, "MOV    E,A"); break;
		case 0x60: fprintf(fp, "MOV    H,B"); break;
		case 0x61: fprintf(fp, "MOV    H,C"); break;
		case 0x62: fprintf(fp, "MOV    H,D"); break;
		case 0x63: fprintf(fp, "MOV    H.E"); break;
		case 0x64: fprintf(fp, "MOV    H,H"); break;
		case 0x65: fprintf(fp, "MOV    H,L"); break;
		case 0x66: fprintf(fp, "MOV    H,M"); break;
		case 0x67: fprintf(fp, "MOV    H,A"); break;
		case 0x68: fprintf(fp, "MOV    L,B"); break;
		case 0x69: fprintf(fp, "MOV    L,C"); break;
		case 0x6a: fprintf(fp, "MOV    L,D"); break;
		case 0x6b: fprintf(fp, "MOV    L,E"); break;
		case 0x6c: fprintf(fp, "MOV    L,H"); break;
		case 0x6d: fprintf(fp, "MOV    L,L"); break;
		case 0x6e: fprintf(fp, "MOV    L,M"); break;
		case 0x6f: fprintf(fp, "MOV    L,A"); break;
		case 0x70: fprintf(fp, "MOV    M,B"); break;
		case 0x71: fprintf(fp, "MOV    M,C"); break;
		case 0x72: fprintf(fp, "MOV    M,D"); break;
		case 0x73: fprintf(fp, "MOV    M.E"); break;
		case 0x74: fprintf(fp, "MOV    M,H"); break;
		case 0x75: fprintf(fp, "MOV    M,L"); break;
		case 0x76: fprintf(fp, "HLT");        break;
		case 0x77: fprintf(fp, "MOV    M,A"); break;
		case 0x78: fprintf(fp, "MOV    A,B"); break;
		case 0x79: fprintf(fp, "MOV    A,C"); break;
		case 0x7a: fprintf(fp, "MOV    A,D"); break;
		case 0x7b: fprintf(fp, "MOV    A,E"); break;
		case 0x7c: fprintf(fp, "MOV    A,H"); break;
		case 0x7d: fprintf(fp, "MOV    A,L"); break;
		case 0x7e: fprintf(fp, "MOV    A,M"); break;
		case 0x7f: fprintf(fp, "MOV    A,A"); break;
		case 0x80: fprintf(fp, "ADD    B"); break;
		case 0x81: fprintf(fp, "ADD    C"); break;
		case 0x82: fprintf(fp, "ADD    D"); break;
		case 0x83: fprintf(fp, "ADD    E"); break;
		case 0x84: fprintf(fp, "ADD    H"); break;
		case 0x85: fprintf(fp, "ADD    L"); break;
		case 0x86: fprintf(fp, "ADD    M"); break;
		case 0x87: fprintf(fp, "ADD    A"); break;
		case 0x88: fprintf(fp, "ADC    B"); break;
		case 0x89: fprintf(fp, "ADC    C"); break;
		case 0x8a: fprintf(fp, "ADC    D"); break;
		case 0x8b: fprintf(fp, "ADC    E"); break;
		case 0x8c: fprintf(fp, "ADC    H"); break;
		case 0x8d: fprintf(fp, "ADC    L"); break;
		case 0x8e: fprintf(fp, "ADC    M"); break;
		case 0x8f: fprintf(fp, "ADC    A"); break;
		case 0x90: fprintf(fp, "SUB    B"); break;
		case 0x91: fprintf(fp, "SUB    C"); break;
		case 0x92: fprintf(fp, "SUB    D"); break;
		case 0x93: fprintf(fp, "SUB    E"); break;
		case 0x94: fprintf(fp, "SUB    H"); break;
		case 0x95: fprintf(fp, "SUB    L"); break;
		case 0x96: fprintf(fp, "SUB    M"); break;
		case 0x97: fprintf(fp, "SUB    A"); break;
		case 0x98: fprintf(fp, "SBB    B"); break;
		case 0x99: fprintf(fp, "SBB    C"); break;
		case 0x9a: fprintf(fp, "SBB    D"); break;
		case 0x9b: fprintf(fp, "SBB    E"); break;
		case 0x9c: fprintf(fp, "SBB    H"); break;
		case 0x9d: fprintf(fp, "SBB    L"); break;
		case 0x9e: fprintf(fp, "SBB    M"); break;
		case 0x9f: fprintf(fp, "SBB    A"); break;
		case 0xa0: fprintf(fp, "ANA    B"); break;
		case 0xa1: fprintf(fp, "ANA    C"); break;
		case 0xa2: fprintf(fp, "ANA    D"); break;
		case 0xa3: fprintf(fp, "ANA    E"); break;
		case 0xa4: fprintf(fp, "ANA    H"); break;
		case 0xa5: fprintf(fp, "ANA    L"); break;
		case 0xa6: fprintf(fp, "ANA    M"); break;
		case 0xa7: fprintf(fp, "ANA    A"); break;
		case 0xa8: fprintf(fp, "XRA    B"); break;
		case 0xa9: fprintf(fp, "XRA    C"); break;
		case 0xaa: fprintf(fp, "XRA    D"); break;
		case 0xab: fprintf(fp, "XRA    E"); break;
		case 0xac: fprintf(fp, "XRA    H"); break;
		case 0xad: fprintf(fp, "XRA    L"); break;
		case 0xae: fprintf(fp, "XRA    M"); break;
		case 0xaf: fprintf(fp, "XRA    A"); break;
		case 0xb0: fprintf(fp, "ORA    B"); break;
		case 0xb1: fprintf(fp, "ORA    C"); break;
		case 0xb2: fprintf(fp, "ORA    D"); break;
		case 0xb3: fprintf(fp, "ORA    E"); break;
		case 0xb4: fprintf(fp, "ORA    H"); break;
		case 0xb5: fprintf(fp, "ORA    L"); break;
		case 0xb6: fprintf(fp, "ORA    M"); break;
		case 0xb7: fprintf(fp, "ORA    A"); break;
		case 0xb8: fprintf(fp, "CMP    B"); break;
		case 0xb9: fprintf(fp, "CMP    C"); break;
		case 0xba: fprintf(fp, "CMP    D"); break;
		case 0xbb: fprintf(fp, "CMP    E"); break;
		case 0xbc: fprintf(fp, "CMP    H"); break;
		case 0xbd: fprintf(fp, "CMP    L"); break;
		case 0xbe: fprintf(fp, "CMP    M"); break;
		case 0xbf: fprintf(fp, "CMP    A"); break;
		case 0xc0: fprintf(fp, "RNZ"); break;
		case 0xc1: fprintf(fp, "POP    B"); break;
		case 0xc2: fprintf(fp, "JNZ    $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xc3: fprintf(fp, "JMP    $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xc4: fprintf(fp, "CNZ    $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xc5: fprintf(fp, "PUSH   B"); break;
		case 0xc6: fprintf(fp, "ADI    #$%02x",code[1]); cs = 2; break;
		case 0xc7: fprintf(fp, "RST    0"); break;
		case 0xc8: fprintf(fp, "RZ"); break;
		case 0xc9: fprintf(fp, "RET"); break;
		case 0xca: fprintf(fp, "JZ     $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xcb: fprintf(fp, "JMP    $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xcc: fprintf(fp, "CZ     $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xcd: fprintf(fp, "CALL   $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xce: fprintf(fp, "ACI    #$%02x",code[1]); cs = 2; break;
		case 0xcf: fprintf(fp, "RST    1"); break;
		case 0xd0: fprintf(fp, "RNC"); break;
		case 0xd1: fprintf(fp, "POP    D"); break;
		case 0xd2: fprintf(fp, "JNC    $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xd3: fprintf(fp, "OUT    #$%02x",code[1]); cs = 2; break;
		case 0xd4: fprintf(fp, "CNC    $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xd5: fprintf(fp, "PUSH   D"); break;
		case 0xd6: fprintf(fp, "SUI    #$%02x",code[1]); cs = 2; break;
		case 0xd7: fprintf(fp, "RST    2"); break;
		case 0xd8: fprintf(fp, "RC");  break;
		case 0xd9: fprintf(fp, "RET"); break;
		case 0xda: fprintf(fp, "JC     $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xdb: fprintf(fp, "IN     #$%02x",code[1]); cs = 2; break;
		case 0xdc: fprintf(fp, "CC     $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xdd: fprintf(fp, "CALL   $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xde: fprintf(fp, "SBI    #$%02x",code[1]); cs = 2; break;
		case 0xdf: fprintf(fp, "RST    3"); break;
		case 0xe0: fprintf(fp, "RPO"); break;
		case 0xe1: fprintf(fp, "POP    H"); break;
		case 0xe2: fprintf(fp, "JPO    $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xe3: fprintf(fp, "XTHL");break;
		case 0xe4: fprintf(fp, "CPO    $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xe5: fprintf(fp, "PUSH   H"); break;
		case 0xe6: fprintf(fp, "ANI    #$%02x",code[1]); cs = 2; break;
		case 0xe7: fprintf(fp, "RST    4"); break;
		case 0xe8: fprintf(fp, "RPE"); break;
		case 0xe9: fprintf(fp, "PCHL");break;
		case 0xea: fprintf(fp, "JPE    $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xeb: fprintf(fp, "XCHG"); break;
		case 0xec: fprintf(fp, "CPE     $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xed: fprintf(fp, "CALL   $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xee: fprintf(fp, "XRI    #$%02x",code[1]); cs = 2; break;
		case 0xef: fprintf(fp, "RST    5"); break;
		case 0xf0: fprintf(fp, "RP");  break;
		case 0xf1: fprintf(fp, "POP    PSW"); break;
		case 0xf2: fprintf(fp, "JP     $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xf3: fprintf(fp, "DI");  break;
		case 0xf4: fprintf(fp, "CP     $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xf5: fprintf(fp, "PUSH   PSW"); break;
		case 0xf6: fprintf(fp, "ORI    #$%02x",code[1]); cs = 2; break;
		case 0xf7: fprintf(fp, "RST    6"); break;
		case 0xf8: fprintf(fp, "RM");  break;
		case 0xf9: fprintf(fp, "SPHL");break;
		case 0xfa: fprintf(fp, "JM     $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xfb: fprintf(fp, "EI");  break;
		case 0xfc: fprintf(fp, "CM     $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xfd: fprintf(fp, "CALL   $%02x%02x",code[2],code[1]); cs = 3; break;
		case 0xfe: fprintf(fp, "CPI    #$%02x",code[1]); cs = 2; break;
		case 0xff: fprintf(fp, "RST    7"); break;
  }

  printf("\n");

  return offset + cs;
}

off_t convert_8080(uint8_t *program, off_t offset) {
  return fconvert_8080(program, offset, stdout);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
  }

  char *filename = argv[1];
  size_t progsize;
  uint8_t *program = ld_program(filename, &progsize);

  off_t pc = 0;

  while (pc < progsize) pc = convert_8080(program, pc);

  return 0;
}
