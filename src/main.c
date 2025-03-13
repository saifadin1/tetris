#include "../include/term.h"
#include "../include/screen.h"
#include "../include/grid.h"
#include "../include/game.h"
#include "../include/constants.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
# include <stdlib.h>

int main(void) {
    raw_mode_on();
    atexit(raw_mode_off);

    set_up_screen();
	init_grid(10 + 2, 20 + 1);
    while (1) {
        draw_board();
		fall();
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) 
          die("read");
        if (c == _CTRL('q')) {
            write(STDOUT_FILENO, "\x1b[2J", 4); 
            write(STDERR_FILENO, "\x1b[1;1H", 7);
            exit(0);  
        }
    }

    return 0;
}