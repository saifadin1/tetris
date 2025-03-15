#include "../include/utils.h"
#include "../include/buf.h"
#include "../include/grid.h"
#include "../include/logger.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>


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
    

    if (new_x < 0 || new_x >= grid.width - 2 || new_y < 0 || new_y >= grid.height || grid.cells[new_y][new_x] == 1) {
        return 0;
    }

    return 1;
}

int is_valid_point_regardless_of_other_tetrominoes(int x, int y) {
    int new_x, new_y;
    get_index_in_grid(x, y, &new_x, &new_y);
    if (new_x < 0 || new_x >= grid.width - 2 || new_y < 0 || new_y >= grid.height) {
        return 0;
    }
    return 1;
}

void rotate_point(int *x, int *y, int pivot_x, int pivot_y) {
    int new_x = *x - pivot_x;
    int new_y = *y - pivot_y;
    *x = pivot_x - new_y;
    *y = pivot_y + new_x;
}

void usage() {
    buf_t buf = {NULL, 0};
    
    // move cursor to the buttom left corner
    move_cursor(0, 140, &buf);



    append_buf(&buf, "Type 's' to start a new game\n\r", strlen("Type 's' to start a new game\n\r"));
    append_buf(&buf, "Type 'q' to quit the game\n", strlen("Type 'q' to quit the game\n"));
    write(STDOUT_FILENO, buf.buf, buf.len);
    free_buf(&buf);
}