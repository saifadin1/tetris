#include "../include/tetrominoe.h"
#include "../include/grid.h"
#include "../include/constants.h"



#define X grid.top_left.x + grid.width / 2
#define Y grid.top_left.y

tetrominoe_t create_tetrominoe(int type) {
    tetrominoe_t tetrominoe;

    for (int i = 0; i < 4; i++) {
        tetrominoe.points[i].x = X;
        tetrominoe.points[i].y = Y;
    }

    switch (type) {
        case 0: // I
            tetrominoe.points[0].x += 0;
            tetrominoe.points[0].y += 0;
            tetrominoe.points[1].x += 0;
            tetrominoe.points[1].y += 1;
            tetrominoe.points[2].x += 0;
            tetrominoe.points[2].y += 2;
            tetrominoe.points[3].x += 0;
            tetrominoe.points[3].y += 3;
            tetrominoe.color = CYAN;
            break;
        case 1: // J
            tetrominoe.points[0].x += 0;
            tetrominoe.points[0].y += 0;
            tetrominoe.points[1].x += 0;
            tetrominoe.points[1].y += 1;
            tetrominoe.points[2].x += 0;
            tetrominoe.points[2].y += 2;
            tetrominoe.points[3].x += -1;
            tetrominoe.points[3].y += 2;
            tetrominoe.color = BLUE;
            break;
        case 2: // L
            tetrominoe.points[0].x += 0;
            tetrominoe.points[0].y += 0;
            tetrominoe.points[1].x += 0;
            tetrominoe.points[1].y += 1;
            tetrominoe.points[2].x += 0;
            tetrominoe.points[2].y += 2;
            tetrominoe.points[3].x += 1;
            tetrominoe.points[3].y += 2;
            tetrominoe.color = ORANGE;
            break;
        case 3: // O
            tetrominoe.points[0].x += 0;
            tetrominoe.points[0].y += 0;
            tetrominoe.points[1].x += 0;
            tetrominoe.points[1].y += 1;
            tetrominoe.points[2].x += 1;
            tetrominoe.points[2].y += 0;
            tetrominoe.points[3].x += 1;
            tetrominoe.points[3].y += 1;
            tetrominoe.color = YELLOW;
            break;
        case 4: // S
            tetrominoe.points[0].x += 0;
            tetrominoe.points[0].y += 0;
            tetrominoe.points[1].x += 0;
            tetrominoe.points[1].y += 1;
            tetrominoe.points[2].x += -1;
            tetrominoe.points[2].y += 1;
            tetrominoe.points[3].x += 1;
            tetrominoe.points[3].y += 0;
            tetrominoe.color = GREEN;
            break;
        case 5: // T
            tetrominoe.points[0].x += 0;
            tetrominoe.points[0].y += 0;
            tetrominoe.points[1].x += 0;
            tetrominoe.points[1].y += 1;
            tetrominoe.points[2].x += 1;
            tetrominoe.points[2].y += 0;
            tetrominoe.points[3].x += -1;
            tetrominoe.points[3].y += 0;
            tetrominoe.color = PURPLE;
            break;
        case 6: // Z
            tetrominoe.points[0].x += 0;
            tetrominoe.points[0].y += 0;
            tetrominoe.points[1].x += -1;
            tetrominoe.points[1].y += 0;
            tetrominoe.points[2].x += 0;
            tetrominoe.points[2].y += 1;
            tetrominoe.points[3].x += 1;
            tetrominoe.points[3].y += 1;
            tetrominoe.color = RED;
            break;
        default:
            break;
    }

    return tetrominoe;
}