#include "../include/panic.h"

void panic(char *message) {
    print(message);
    print("\tpanic!");
    while (1) {}
}