#include "main.h"

#include <iostream>

#include <openssl/rand.h>

using namespace std;

int main(int argc, char**argv) {
  (void)argc;
  (void)argv;

  // Test random number generation
  GenerateRandom(8);

  return 0;
}

void PrintHexString(const void *data, int length) {
  const unsigned char *p = (const unsigned char *)data;
  for (int i = 0; i < length; i++) {
    printf("%02x", p[i]);
  }
  printf("\n");
}

void GenerateRandom(int count) {
  unsigned char iv[count];
  if (RAND_bytes(iv, count)) {
    PrintHexString(iv, count);
  } else {
    cerr << "ERROR: RAND_bytes" << endl;
  }
}


