#include "../include/utils.h"
#include "../include/buf.h"
#include "../include/grid.h"
#include <string.h>
#include <stdio.h>


void move_cursor(int x, int y, buf_t *buf) {
    char buffer[32];
    int n = snprintf(buffer, sizeof(buffer), "\x1b[%d;%dH", y + 1, x + 1);
    append_buf(buf, buffer, strlen(buffer));
}


void get_index_in_grid(int x, int y, int *new_x, int *new_y) {
    *new_x = (x - grid.top_left.x); 
    *new_y = (y - grid.top_left.y);
}

int is_valid_point(int x, int y) {
    int new_x, new_y;
    get_index_in_grid(x, y, &new_x, &new_y);
    if (new_x < 0 || new_x >= grid.width || new_y < 0 || new_y >= grid.height || grid.cells[new_y][new_x] == 1) {
        return 0;
    }
    return 1;
}