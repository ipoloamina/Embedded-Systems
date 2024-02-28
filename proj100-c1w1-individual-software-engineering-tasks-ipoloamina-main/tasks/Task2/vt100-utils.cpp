#include "vt100-utils.hpp"


void clearTerminal() {
    printf("\033c");
}

void homeCursor() {
    printf("\033[H");
}

void hideCursor() {
    printf("\033[?25l");
}

