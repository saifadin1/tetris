#include "../include/logger.h"
#include "../include/grid.h"
#include "../include/tetrominoe.h"


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

void log_tet(tetrominoe_t curr_tetrominoe) {
    FILE *f = fopen("log/tet.log", "w");
    if (f == NULL) {
        perror("fopen");
        return;
    }
    for (int i = 0; i < 4; i++) {
        fprintf(f, "%d %d\n", curr_tetrominoe.points[i].x, curr_tetrominoe.points[i].y);
    }
    fclose(f);
}


void log_message(const char *msg) {
    FILE *f = fopen("log/gen.log", "a");
    if (f == NULL) {
        perror("fopen");
        return;
    }
    fprintf(f, "%s\n", msg);
    fclose(f);
}

int save_high_score(int score) {
    FILE *f = fopen("log/hs.txt", "w");
    int curr_score = load_high_score();
    if (curr_score < score) {
        fprintf(f, "%d", score);
        fclose(f);
        return score; // new high score
    } else {
        fprintf(f, "%d", curr_score);
        fclose(f);
        return 0;
    }
}

int load_high_score() {
    FILE *f = fopen("log/hs.txt", "r");
    if (f == NULL) {
        perror("fopen");
        return 0;
    }
    int score;
    fscanf(f, "%d", &score);
    fclose(f);
    return score;
}

