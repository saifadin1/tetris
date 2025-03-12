#include "../include/screen.h"
#include "../include/term.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int screen_width;
int screen_height;


int set_up_screen() {
    write(STDOUT_FILENO, "\x1b[?25l", 6);
    write(STDOUT_FILENO, "\x1b[2J", 4);
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        die("ioctl");
    }
    screen_width = ws.ws_col;
    screen_height = ws.ws_row;

    return 0;
}