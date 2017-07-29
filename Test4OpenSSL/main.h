#ifndef TEST4OPENSSL_MAIN_H
#define TEST4OPENSSL_MAIN_H

/**
 *
 */
void PrintHexString(const void *data, int length);
/**
 * Generate `count` random bytes, and print it
 * \param count 
 */
void GenerateRandom(int count);
#endif
