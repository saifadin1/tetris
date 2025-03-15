#include "../include/term.h"
#include "../include/screen.h"
#include "../include/grid.h"
#include "../include/game.h"
#include "../include/constants.h"
#include "../include/utils.h"
#include "../include/buf.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
# include <stdlib.h>

int main(void) {
    raw_mode_on();
    atexit(raw_mode_off);

    usage();


    while (1) {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) 
          die("read");
        if (c == 'q') {
            write(STDOUT_FILENO, "\x1b[2J", 4);  // clear the screen
            write(STDERR_FILENO, "\x1b[1;1H", 7); // move the cursor to the top left corner
            exit(0);  
        } else if (c == 's') {
            write(STDOUT_FILENO, "\x1b[2J", 4);  // clear the screen
            write(STDERR_FILENO, "\x1b[1;1H", 7); // move the cursor to the top left corner
            set_up_screen();
            init_grid(10 + 2, 20 + 1);
            draw_board();
            int is_high_score = fall();
            char * msg;
            if (is_high_score) {
                asprintf(&msg, "New high score: %d\n\r", is_high_score); 
            } else {
                asprintf(&msg, "Game over! Your score: %d\n\r", score);
            }
            buf_t buf = {NULL, 0};
            move_cursor(0, 140, &buf);
            append_buf(&buf, msg, strlen(msg));
            write(STDOUT_FILENO, buf.buf, buf.len);
            free(msg);
            usage();
        }
    }

    return 0;
}