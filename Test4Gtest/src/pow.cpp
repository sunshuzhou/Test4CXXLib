#include "include/pow.h"

/*
* return a^n
*/
int pow(int a, int n) {
    int result = 1;
    while (n-- > 0) {
        result *= a;
    }
    return result;
}
