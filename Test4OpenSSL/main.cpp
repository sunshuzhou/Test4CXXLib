#include "main.h"

#include <iostream>

#include <openssl/rand.h>

#include "rfc/rfc.h"

using namespace std;

int main(int argc, char**argv) {
  (void)argc;
  (void)argv;

  // Test random number generation
  GenerateRandom(8);
  Rfc3686TestVectors();

  return 0;
}

void PrintHexString(const void *data, int length) {
  const unsigned char *p = (const unsigned char *)data;
  for (int i = 0; i < length; i++) {
    printf("%02X  ", p[i]);
  }
  printf("\n");
}

void GenerateRandom(int count) {
  printf("Testing: Generate Random\n");
  unsigned char iv[count];
  if (RAND_bytes(iv, count)) {
    PrintHexString(iv, count);
  } else {
    cerr << "ERROR: RAND_bytes" << endl;
  }
}


