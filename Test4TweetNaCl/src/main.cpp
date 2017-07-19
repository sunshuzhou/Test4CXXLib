#include <iostream>
#include <fstream>
#include <memory>

#include <cstdint>
#include <cstdio>

#include "tweetnacl.h"

using namespace std;

int main(int argc, char ** argv) {

    uint8_t data[64], hash[64];
    uint8_t pk[crypto_box_PUBLICKEYBYTES], sk[crypto_box_SECRETKEYBYTES];

    ifstream input("./test/1K");

    input.read((char*)data, sizeof(data));
    crypto_box_keypair(pk, sk);
    //crypto_hash_sha256(hash, data, 64);

    for (int i = 0; i < crypto_box_PUBLICKEYBYTES; i ++) {
        printf("%02X", pk[i]);
    }
    cout << endl;
    
    return 0;
}
