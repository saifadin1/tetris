#include "../include/logger.h"
#include "../include/grid.h"

void log_grid() {
    FILE *f = fopen("log/grid.log", "w");
    if (f == NULL) {
        perror("fopen");
        return;
    }
    for (int i = 0; i < grid.height; i++) {
        for (int j = 0; j < grid.width; j++) {
            fprintf(f, "%d ", grid.cells[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}