#pragma once



typedef struct {
    int x;
    int y;
} point_t;


typedef struct {
    char ***colors;
    int **cells;
    point_t top_left;
    point_t bottom_right;
    int width;
    int height;
} grid_t;

void init_grid(int width, int height);

extern grid_t grid; 