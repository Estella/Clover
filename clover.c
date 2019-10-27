/*******************************************************************************************************/
// Clover Cipher - 128bit block, 128bit key
/*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/*******************************************************************************************************/
#define ROL32(X, R) (((X) << ((R) & 31)) | ((X) >> (32 - ((R) & 31))))
#define ROR32(X, R) (((X) >> ((R) & 31)) | ((X) << (32 - ((R) & 31))))
#define XOR32(x,y) (x^y)
#define NOP32(x) (x)
#define INV32(x) (~x)
#define END32(x) ( ( x >> 24 ) | (( x << 8) & 0x00ff0000 ) | ((x >> 8) & 0x0000ff00) | ( x << 24) )
/*******************************************************************************************************/
uint32_t MetaCLU32(uint32_t AA, uint32_t BB, int MODE) {
  int meta = (BB % 6);
  switch(meta) {
    case 0:
      if (MODE) { AA = ROL32(AA,BB); } else { AA = ROR32(AA,BB); }
      break;
    case 1:
       if (MODE) { AA = ROR32(AA,BB); } else { AA = ROL32(AA,BB); }
      break;
    case 2:
       if (MODE) { AA = XOR32(AA,BB); } else { AA = XOR32(BB,AA); }
      break;
    case 3:
      AA = INV32(AA);
      break;
    case 4:
      AA = END32(AA);
    case 5:
      AA = NOP32(AA);
      break;
  }
  return AA;
}
/*******************************************************************************************************/
void CLOVER_ENC(uint32_t * x, const uint32_t * k, int rounds, uint32_t Q, int mode) {
  unsigned int i;

  uint32_t rk0 = k[0];
  uint32_t rk1 = k[1];
  uint32_t rk2 = k[2];
  uint32_t rk3 = k[3];

  for (i = 0; i < rounds; i++) {
    rk0 += Q; rk1 -= Q;
    rk2 -= Q; rk3 += Q;

    x[0] ^= rk0; x[2] ^= rk2;
    x[0] += x[1]; x[2] -= x[3];
    x[0] = ROR32(x[0], x[1]); x[2] = ROL32(x[2], x[3]);
    x[0] = MetaCLU32(x[0], x[1], mode); x[2] = MetaCLU32(x[2], x[3], mode);

    x[0] ^= x[2]; x[3] ^= x[1];
    x[1] ^= x[3]; x[2] ^= x[0];

    x[3] = MetaCLU32(x[3], x[2], mode); x[1] = MetaCLU32(x[1], x[0], mode);
    x[3] = ROR32(x[3], x[2]); x[1] = ROL32(x[1], x[0]);
    x[3] += x[2]; x[1] -= x[0];
    x[3] ^= rk3; x[1] ^= rk1;

  }
  rk0 = x[0]; x[0] = x[1]; x[1] = rk0;
  rk2 = x[2]; x[2] = x[3]; x[3] = rk2;
}
/*******************************************************************************************************/
void CLOVER_DEC(uint32_t * x, const uint32_t * k, int rounds, uint32_t Q) {
  uint32_t dk[4] = {
    k[1] - Q * (rounds + 1),
    k[0] + Q * (rounds + 1),
    k[3] + Q * (rounds + 1),
    k[2] - Q * (rounds + 1)
  };
  CLOVER_ENC(x, dk,rounds,Q,1);
}
/*******************************************************************************************************/
int main() {
  uint32_t X[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; // INPUT plaintext
  uint32_t K[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; // KEY
  uint32_t P[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; // COPY plaintext
  uint32_t C[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; // OUTPUT ciphertext
  uint32_t Q = 0xB7E15162; // math constant
  int R = 17; // rounds
  P[0] = X[0]; // COPY X to P
  P[1] = X[1];
  P[2] = X[2];
  P[3] = X[3];
  CLOVER_ENC(X,K,R,Q,0); // ENCRYPT X with K
  C[0] = X[0]; // COPY X to C
  C[1] = X[1];
  C[2] = X[2];
  C[3] = X[3];
  CLOVER_DEC(X,K,R,Q); // DECRYPT X with K 
  printf("CLOVER Cipher, R: %d (rounds)\nK : %08X %08X %08X %08X\nP1: %08X %08X %08X %08X\nC : %08X %08X %08X %08X\nP2: %08X %08X %08X %08X\n",
  R,
  K[0],K[1],K[2],K[3],
  P[0],P[1],P[2],P[3],
  C[0],C[1],C[2],C[3],
  X[0],X[1],X[2],X[3]);
  return(0);
}
/*******************************************************************************************************/
// EOF
