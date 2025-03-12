#pragma once 
#include <stdio.h>
#include "../include/buf.h"
#include <string.h>

void move_cursor(int x, int y, buf_t *buf); 
void get_index_in_grid(int x, int y, int *new_x, int *new_y);
int is_valid_point(int x, int y);