#include "rfc.h"

#include <openssl/aes.h>

#include "../main.h"


void SetCounter(u8 *ctrblk, const u32 counter) {
  ctrblk[0] = (counter >> 24) & 0xFF;
  ctrblk[1] = (counter >> 16) & 0xFF;
  ctrblk[2] = (counter >> 8) & 0xFF;
  ctrblk[3] = (counter >> 0) & 0xFF;
}

void Rfc3686TestVector1();
void Rfc3686TestVector2();
void Rfc3686TestVector8();
void Rfc3686TestVector9();

void Rfc3686TestVectors() {
  printf("\n\nTesting: Rfc3686TestVectors\n");
  Rfc3686TestVector1();
  Rfc3686TestVector2();
  Rfc3686TestVector8();
  Rfc3686TestVector9();
}

void Rfc3686TestVector1() {
  printf("Test Vector #1:\n");
  u8 key[] = {0xAE, 0x68, 0x52, 0xF8, 0x12, 0x10, 0x67, 0xCC, 0x4B, 0xF7, 0xA5, 0x76, 0x55, 0x77, 0xF3, 0x9E};
  u8 ctrblk[AES_BLOCK_SIZE] = {
    0x00, 0x00, 0x00, 0x30, // Nonce: 4 bytes
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // IV: 8 bytes
    0x00, 0x00, 0x00, 0x00 // Counter: 4 bytes
  };
  u32 counter = 1;
  unsigned char plaintext[] = "Single block msg";

  SetCounter(ctrblk + 12, counter);

  AES_KEY aes_key;
  if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
    printf("ERROR: Can't set AES encrypt key");
    return;
  }

  u8 ciphertext[AES_BLOCK_SIZE];
  u8 ecount[AES_BLOCK_SIZE];
  // must be all 0
  memset(ecount, 0, AES_BLOCK_SIZE);
  u32 num = 0;
  AES_ctr128_encrypt(plaintext, ciphertext, AES_BLOCK_SIZE, &aes_key, ctrblk, ecount, &num);
  printf("Plaintext    : ");
  PrintHexString(plaintext, AES_BLOCK_SIZE);
  printf("Counter Block: ");
  PrintHexString(ctrblk, AES_BLOCK_SIZE);
  printf("Key Stream   : ");
  PrintHexString(ecount, AES_BLOCK_SIZE);
  printf("Ciphertext   : ");
  PrintHexString(ciphertext, AES_BLOCK_SIZE);
  printf("Left Bytes   : %d\n", num);
}

void Rfc3686TestVector2() {
  printf("Test Vector #2:\n");
  u8 key[] = {0x7E, 0x24, 0x06, 0x78, 0x17, 0xFA, 0xE0, 0xD7, 0x43, 0xD6, 0xCE, 0x1F, 0x32, 0x53, 0x91, 0x63};
  u8 ctrblk[AES_BLOCK_SIZE] = {
    0x00, 0x6C, 0xB6, 0xDB, // Nonce: 4 bytes
    0xC0, 0x54, 0x3B, 0x59, 0xDA, 0x48, 0xD9, 0x0B, // IV: 8 bytes
    0x00, 0x00, 0x00, 0x00 // Counter: 4 bytes
  };
  u32 counter = 1;

  unsigned char plaintext[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
  u32 len = 32;

  SetCounter(ctrblk + 12, counter);

  AES_KEY aes_key;
  if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
    printf("ERROR: Can't set AES encrypt key");
    return;
  }

  u8 ciphertext[len];
  u8 ecount[AES_BLOCK_SIZE];
  // must be all 0
  memset(ecount, 0, AES_BLOCK_SIZE);
  u32 num = 0;
  printf("Plaintext    : ");
  PrintHexString(plaintext, len);

  printf("Counter Block(1): ");
  PrintHexString(ctrblk, AES_BLOCK_SIZE);
  AES_ctr128_encrypt(plaintext, ciphertext, AES_BLOCK_SIZE, &aes_key, ctrblk, ecount, &num);

  printf("Key Stream(1)   : ");
  PrintHexString(ecount, AES_BLOCK_SIZE);
  printf("Left Bytes   : %d\n", num);

  printf("Counter Block(2): ");
  PrintHexString(ctrblk, AES_BLOCK_SIZE);
  AES_ctr128_encrypt(plaintext + AES_BLOCK_SIZE, ciphertext + AES_BLOCK_SIZE, AES_BLOCK_SIZE, &aes_key, ctrblk, ecount, &num);
  printf("Key Stream(2)   : ");
  PrintHexString(ecount, AES_BLOCK_SIZE);

  printf("Ciphertext   : ");
  PrintHexString(ciphertext, len);
  printf("Left Bytes   : %d\n", num);
}

void Rfc3686TestVector8() {
  printf("Test Vector #8:\n");
  u8 key[] = {0xF6, 0xD6, 0x6D, 0x6B, 0xD5, 0x2D, 0x59, 0xBB, 0x07, 0x96, 0x36, 0x58, 0x79, 0xEF, 0xF8, 0x86, 0xC6, 0x6D, 0xD5, 0x1A, 0x5B, 0x6A, 0x99, 0x74, 0x4B, 0x50, 0x59, 0x0C, 0x87, 0xA2, 0x38, 0x84};
  u8 ctrblk[AES_BLOCK_SIZE] = {
    0x00, 0xFA, 0xAC, 0x24, // Nonce: 4 bytes
    0xC1, 0x58, 0x5E, 0xF1, 0x5A, 0x43, 0xD8, 0x75, // IV: 8 bytes
    0x00, 0x00, 0x00, 0x00 // Counter: 4 bytes
  };
  u32 counter = 1;

  unsigned char plaintext[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
  u32 len = 32;

  SetCounter(ctrblk + 12, counter);

  AES_KEY aes_key;
  if (AES_set_encrypt_key(key, 256, &aes_key) < 0) {
    printf("ERROR: Can't set AES encrypt key");
    return;
  }

  u8 ciphertext[len];
  u8 ecount[AES_BLOCK_SIZE];
  // must be all 0
  memset(ecount, 0, AES_BLOCK_SIZE);
  u32 num = 0;
  printf("Plaintext    : ");
  PrintHexString(plaintext, len);

  printf("Counter Block(1): ");
  PrintHexString(ctrblk, AES_BLOCK_SIZE);
  AES_ctr128_encrypt(plaintext, ciphertext, AES_BLOCK_SIZE, &aes_key, ctrblk, ecount, &num);

  printf("Key Stream(1)   : ");
  PrintHexString(ecount, AES_BLOCK_SIZE);
  printf("Left Bytes   : %d\n", num);

  printf("Counter Block(2): ");
  PrintHexString(ctrblk, AES_BLOCK_SIZE);
  AES_ctr128_encrypt(plaintext + AES_BLOCK_SIZE, ciphertext + AES_BLOCK_SIZE, AES_BLOCK_SIZE, &aes_key, ctrblk, ecount, &num);
  printf("Key Stream(2)   : ");
  PrintHexString(ecount, AES_BLOCK_SIZE);

  printf("Ciphertext   : ");
  PrintHexString(ciphertext, len);
  printf("Left Bytes   : %d\n", num);
}

void Rfc3686TestVector9() {
  printf("Test Vector #9:\n");
  u8 key[] = {0xFF, 0x7A, 0x61, 0x7C, 0xE6, 0x91, 0x48, 0xE4, 0xF1, 0x72, 0x6E, 0x2F, 0x43, 0x58, 0x1D, 0xE2, 0xAA, 0x62, 0xD9, 0xF8, 0x05, 0x53, 0x2E, 0xDF, 0xF1, 0xEE, 0xD6, 0x87, 0xFB, 0x54, 0x15, 0x3D,};
  u8 ctrblk[AES_BLOCK_SIZE] = {
    0x00, 0x1C, 0xC5, 0xB7, // Nonce: 4 bytes
    0x51, 0xA5, 0x1D, 0x70, 0xA1, 0xC1, 0x11, 0x48, // IV: 8 bytes
    0x00, 0x00, 0x00, 0x00 // Counter: 4 bytes
  };
  u32 counter = 1;

  unsigned char plaintext[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23};
  u32 len = 36;

  SetCounter(ctrblk + 12, counter);

  AES_KEY aes_key;
  if (AES_set_encrypt_key(key, 256, &aes_key) < 0) {
    printf("ERROR: Can't set AES encrypt key");
    return;
  }

  u8 ciphertext[len];
  u8 ecount[AES_BLOCK_SIZE];
  // must be all 0
  memset(ecount, 0, AES_BLOCK_SIZE);
  u32 num = 0;
  printf("Plaintext    : ");
  PrintHexString(plaintext, len);

  int i;
  for (i = 0; i < len / AES_BLOCK_SIZE; i++) {
    printf("Counter Block(%d): ", i);
    PrintHexString(ctrblk, AES_BLOCK_SIZE);
    AES_ctr128_encrypt(plaintext + i * AES_BLOCK_SIZE, ciphertext + i * AES_BLOCK_SIZE, AES_BLOCK_SIZE, &aes_key, ctrblk, ecount, &num);
    printf("Key Stream(%d)   : ", i);
    PrintHexString(ecount, AES_BLOCK_SIZE);
    printf("Left Bytes(%d)   : %d\n", i, num);
  }


  printf("Counter Block(%d): ", i);
  PrintHexString(ctrblk, AES_BLOCK_SIZE);
  AES_ctr128_encrypt(plaintext + i * AES_BLOCK_SIZE, ciphertext + i * AES_BLOCK_SIZE, len - i * AES_BLOCK_SIZE, &aes_key, ctrblk, ecount, &num);
  printf("Key Stream(%d)   : ", i);
  PrintHexString(ecount, len - i * AES_BLOCK_SIZE);
  printf("Left Bytes(%d)   : %d\n", i, num);

  printf("Ciphertext   : ");
  PrintHexString(ciphertext, len);
}

