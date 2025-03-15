#include "../include/grid.h"
#include "../include/constants.h"
#include <stdlib.h>


grid_t grid;

// [y][x] 

void init_grid(int width, int height) {
    grid.width = width;
    grid.height = height;
    grid.colors = malloc(sizeof(char **) * height);
    for (int i = 0; i < height; i++) {
        grid.colors[i] = malloc(sizeof(char *) * width);
        for (int j = 0; j < width; j++) {
            grid.colors[i][j] = WHITE;
        }
    }
    grid.cells = malloc(sizeof(int *) * height); 
    for (int i = 0; i < height; i++) {
        grid.cells[i] = malloc(sizeof(int) * width);
        for (int j = 0; j < width; j++) {
            grid.cells[i][j] = 0;
        }
    }
}