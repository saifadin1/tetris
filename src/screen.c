#include "../include/screen.h"
#include "../include/term.h"
#include "../include/grid.h"
#include "../include/buf.h"
#include "../include/constants.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void draw_board() {
    buf_t buf = {NULL, 0};

	int third_width = screen_width / 3;	
	int fourth_height = screen_height / 4;
	int x = 0 , y = 0;
	while (y<fourth_height) {
		y++;
		append_buf(&buf, "\n", 1);
	}


	while (x<third_width) {
		x++;
		append_buf(&buf, " ", 1);
	}
 

	grid.top_left.x = x + 1;
	grid.top_left.y = y;
	

	append_buf(&buf, TOP_LEFT_CORNER, 4);
	for (int i=0; i+2<grid.width; i++) {
		append_buf(&buf, HORIZONTAL_BAR, 4);
	}
	append_buf(&buf, TOP_RIGHT_CORNER, 4);
	append_buf(&buf, "\n\r", 2);
	y++; 	

	int complete_height = 1;

	while (complete_height + 1 < grid.height) {
		x = 0;
		while (x<third_width) {
			x++;
			append_buf(&buf, " ", 1);
		}
		append_buf(&buf, VERTICAL_BAR, 4);
		for (int i=0; i+2<grid.width; i++) {
			append_buf(&buf, " ", 1);
		}
		append_buf(&buf, VERTICAL_BAR, 4);
		append_buf(&buf, "\n\r", 2);
		complete_height++;
		y++;
	}


	x = 0;
	while (x<third_width) {
		x++;
		append_buf(&buf, " ", 1);
	}
	append_buf(&buf, BOTTOM_LEFT_CORNER, 4);
	for (int i=0; i+2<grid.width; i++) {
		append_buf(&buf, HORIZONTAL_BAR, 4);
		x++;
	}
	append_buf(&buf, BOTTOM_RIGHT_CORNER, 4);
	x++;

	grid.bottom_right.x = x - 1;
	grid.bottom_right.y = y;


	move_cursor(0, screen_height - 1, &buf);
	append_buf(&buf, "Score: 0", strlen("Score: 0"));


    write(STDOUT_FILENO, buf.buf, buf.len);
    free_buf(&buf);
}