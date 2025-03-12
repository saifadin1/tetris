#pragma once 

#include "../include/grid.h"

typedef struct {
    point_t points[4];  // first point is the pivot point and always the center of the tetrominoe (0,0)
    char *color;
} tetrominoe_t;


tetrominoe_t create_tetrominoe(int type);
void rotate_tetrominoe(tetrominoe_t *tetrominoe);