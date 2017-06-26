#include <iostream>
#include "spdlog/spdlog.h"

using namespace std;

int main(void) {
    auto console = spdlog::stdout_color_mt("console");
    console->info("Welcome to spdlog!");
    console->info("An info message example {}..", 1);
    console->warn("an important message: 0x{:08X}", 12);
    console->error("This is an error message!");
    return 0;
}
