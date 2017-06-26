#include <iostream>
#include <csignal>

using namespace std;


void signal_handler(int signal) {
    switch (signal) {
        case SIGINT:
            cout << "SIGINT" << endl;
            exit(0);
        case SIGTERM:
            cout << "SIGTERM" << endl;
            exit(1);
        default:
            break;
    }
}

int main(int argc, char **argv) {
    // Ctrl + C
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    while (true) {
    }
    return 0;
}
