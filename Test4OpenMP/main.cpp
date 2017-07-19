#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
#pragma omp parallel for
    for (int i = 0; i < 10; ++i) {
        std::cout << i << std::endl;
    }
    return 0;
}
