#include "../include/term.h"
# include <stdlib.h>

int main(void) {
    raw_mode_on();
    atexit(raw_mode_off);

    return 0;
}