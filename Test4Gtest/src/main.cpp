#include <iostream>
#include "spdlog/spdlog.h"
#include "gtest/gtest.h"
#include "include/pow.h"

using namespace std;

int main(int argc, char ** argv) {
    if (argc != 3) {
        auto console = spdlog::stdout_color_mt("console");
        console->info("{}: [number] [exponent]", argv[0]);
        exit(1);
    }
    cout << pow(atoi(argv[1]), atoi(argv[2])) << endl;
    return 0;
}
