#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "../include/term.h"

struct termios orig_termios;

void raw_mode_off(void) {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) 
      die("tcsetattr");
}

void raw_mode_on(void) {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) 
      die("tcgetattr");

    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST); 
    raw.c_cflag |= (CS8); 
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)  
      die("tcsetattr");
}


void die(const char *s) {
    perror(s);
    exit(1);
}