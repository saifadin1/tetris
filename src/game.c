#include "../include/game.h"
#include "../include/tetrominoe.h"
#include "../include/buf.h"
#include "../include/grid.h"
#include "../include/utils.h"
#include "../include/constants.h"
#include "../include/logger.h"
#include "../include/screen.h"
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/select.h>



tetrominoe_t curr_tetrominoe;
tetrominoe_t shadow_tetrominoe;
int score, level;

int fall() {
    for(int i=0; !game_over() ; i++, level = (i + 1) / 5) {
        log_grid();



        // ctrl-Q for quit
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) 
          die("read");
        if (c == _CTRL('q')) {
            write(STDOUT_FILENO, "\x1b[2J", 4); 
            write(STDERR_FILENO, "\x1b[1;1H", 7);
            exit(0);
        }


        int i, stime;
        long ltime;
        ltime = time(NULL);
        stime = (unsigned) ltime/2;
        srand(stime);
        int type = rand() % 7; 
        // printf("type: %d\n", type);
        curr_tetrominoe = create_tetrominoe(type);

        int rot = 0;


        while (can_move_down(&curr_tetrominoe)) {            
            process();



            for (int j = 0; j < 100 + level * 10; j++) {   // 100 * 10000 micro seconds
                struct timeval tv = {0, 10000};
                fd_set read_fds;
                FD_ZERO(&read_fds);
                FD_SET(STDIN_FILENO, &read_fds);


                if (select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &tv) > 0) {
                    char buffer[64];
                    int n = read(STDIN_FILENO, buffer, sizeof(buffer));
            
                    if (n == 1 && buffer[0] == _CTRL('q')) exit(0);
                    if (n == 3 && buffer[0] == '\x1B' && buffer[1] == '[') {
                        switch (buffer[2]) {
                            case 'D': move_left(); break;
                            case 'C': move_right(); break;
                            case 'B': drop_fast(); break;
                            case 'A': rot = 1 , rotate_tetrominoe(&curr_tetrominoe); break;
                        }
                    }

                    shadow();
                    draw_tetrominoe();
                }
            }
        }

        

        process();        

        update_grid();

        clear_full_rows();

    }

    // game over time to update the high score
    return save_high_score(score);
}

void draw_tetrominoe() {
    buf_t draw_buf = {NULL, 0};

    // color the tetromino
    append_buf(&draw_buf, curr_tetrominoe.color, strlen(curr_tetrominoe.color));
    

    // draw the tetromino itself
    for (int i = 0; i < 4; i++) {
        move_cursor(curr_tetrominoe.points[i].x, curr_tetrominoe.points[i].y, &draw_buf);
        append_buf(&draw_buf, BLOCK_CHAR, 4);
    }
    // reset color
    append_buf(&draw_buf, RESET, 4);

    write(STDOUT_FILENO, draw_buf.buf, draw_buf.len);
    free_buf(&draw_buf);
}


void process() {
    if (can_move_down(&curr_tetrominoe)) {
        erase_previous_position();

        for (int i = 0; i < 4; i++) {
            curr_tetrominoe.points[i].y += 1;
        }
    }

    shadow();

    draw_tetrominoe();
}

void erase_previous_position() {
    buf_t buf = {NULL, 0};
    for (int i = 0; i < 4; i++) {
        move_cursor(curr_tetrominoe.points[i].x, curr_tetrominoe.points[i].y, &buf);
        append_buf(&buf, " ", 1);
    }
    write(STDOUT_FILENO, buf.buf, buf.len);
    free_buf(&buf);
}

void move_left() {
    for (int i = 0; i < 4; i++) {
        if (is_valid_point(curr_tetrominoe.points[i].x - 1, curr_tetrominoe.points[i].y) == 0) return;
    }

    erase_previous_position();

    for (int i = 0; i < 4; i++) {
        curr_tetrominoe.points[i].x -= 1;
    }
}

void move_right() {
    for (int i = 0; i < 4; i++) {
        if (is_valid_point(curr_tetrominoe.points[i].x + 1, curr_tetrominoe.points[i].y) == 0) return;
    }

    erase_previous_position();

    for (int i = 0; i < 4; i++) {
        curr_tetrominoe.points[i].x += 1;
    }
}

void rotate_tetrominoe(tetrominoe_t *tetrominoe) {    
    tetrominoe_t temp = *tetrominoe;
    
    for (int i=0; i<4; i++) {
        rotate_point(&temp.points[i].x, &temp.points[i].y, temp.points[0].x, temp.points[0].y);
    }

    for (int i=0; i<4; i++) {
        int x_index, y_index;
        get_index_in_grid(temp.points[i].x, temp.points[i].y, &x_index, &y_index);
        // if out of right boundary , then i should move left
        if (temp.points[i].x >= grid.bottom_right.x) {
            move_left();
            // try rotate again 
            rotate_tetrominoe(tetrominoe);
            return;
        }
        // if out of left boundary , then i should move right
        if (temp.points[i].x < grid.top_left.x) {
            move_right();
            rotate_tetrominoe(tetrominoe);
            return;
        }
    }

    // double check if the new position is valid
    for (int i=0; i<4; i++) {
        if (is_valid_point(temp.points[i].x, temp.points[i].y) == 0) return;
    }

    erase_previous_position();

    *tetrominoe = temp;
}


void drop_fast() {
    for (int i=0; i<2 && can_move_down(&curr_tetrominoe); i++) {   // make the drop faster by increasing the loop count
        
        erase_previous_position();


        for (int i = 0; i < 4; i++) {
            curr_tetrominoe.points[i].y += 1;
        }
    }
}


int can_move_down(tetrominoe_t *tetrominoe) {
    for (int i = 0; i < 4; i++) {
        int new_y = tetrominoe->points[i].y + 1;
        int x_index , y_index;
        get_index_in_grid(tetrominoe->points[i].x, new_y, &x_index, &y_index);
        if (new_y >= grid.bottom_right.y || grid.cells[y_index][x_index] == 1) {
            return 0;
        }
    }
    return 1;
}


void update_grid() {
    for (int i = 0; i < 4; i++) {
        int x , y;
        get_index_in_grid(curr_tetrominoe.points[i].x, curr_tetrominoe.points[i].y, &x, &y);

        grid.cells[y][x] = 1;
        grid.colors[y][x] = strdup(curr_tetrominoe.color);
    }
}

void clear_full_rows() {                                // last two columns are not considered for now
    for (int y = 0; y < grid.height; y++) {
        int full = 1;
        for (int x = 0; x + 2 < grid.width; x++) {
            if (grid.cells[y][x] == 0) {
                full = 0;
                break;
            }
        }
        if (full) {

            // increase the score
            increase_score();

            
            // Shift everything down straight above the full row
            for (int r = y; r > 0; r--) { 
                for (int c = 0; c + 2 < grid.width; c++) { 
                    if (r - 1 >= 0) { 
                        grid.cells[r][c] = grid.cells[r - 1][c]; 
                    }
                }
            }
            
            
            // log_message("full row");
            // Clear the top row
            for (int c = 1; c + 1 < grid.width; c++) {
                grid.cells[1][c] = 0;
            }

            buf_t buf = {NULL, 0};            

            // Draw the grid
            for (int r = 0; r < grid.height - 1; r++) {
                for (int c = 0; c + 2 < grid.width; c++) {
                    move_cursor(grid.top_left.x + c, grid.top_left.y + r, &buf);
                    if (grid.cells[r][c] == 1) {
                        if (grid.colors[r][c] != NULL) 
                            append_buf(&buf, grid.colors[r][c], strlen(grid.colors[r][c]));
                        append_buf(&buf, BLOCK_CHAR, 4);
                        append_buf(&buf, RESET, 4);
                    } else {
                        append_buf(&buf, " ", 1);
                    }
                }
            }

            write(STDOUT_FILENO, buf.buf, buf.len);
            free_buf(&buf);
        }
    }
}

void increase_score() {
    score++;

    buf_t buf = {NULL, 0};
    move_cursor(0, screen_height - 1, &buf);

    append_buf(&buf, "\033[2K", 4); // Clear line



    char score_str[32];
    sprintf(score_str, "Score: %d", score);
    append_buf(&buf, score_str, strlen(score_str));

    write(STDOUT_FILENO, buf.buf, buf.len);
    free_buf(&buf);
}

void shadow() {
    // delete the previous shadow
    // but first ensure the shadow is not null
    buf_t buf = {NULL, 0};
    if (shadow_tetrominoe.points[0].x && shadow_tetrominoe.points[0].y) {

        for (int i = 0; i < 4; i++) {
            // check if the pre shadow becaome a block
            int x_index, y_index;
            get_index_in_grid(shadow_tetrominoe.points[i].x, shadow_tetrominoe.points[i].y, &x_index, &y_index);
            if (grid.cells[y_index][x_index] == 0) {
                move_cursor(shadow_tetrominoe.points[i].x, shadow_tetrominoe.points[i].y, &buf);
                append_buf(&buf, " ", 1);
            }
        }
        write(STDOUT_FILENO, buf.buf, buf.len);
        free_buf(&buf);
    }



    // create a new shadow
    shadow_tetrominoe = curr_tetrominoe;   
    
    while (can_move_down(&shadow_tetrominoe)) {
        for (int i = 0; i < 4; i++) {
            shadow_tetrominoe.points[i].y += 1;
        }
    }

    buf = (buf_t) {NULL, 0};

    // color the tetromino
    append_buf(&buf, curr_tetrominoe.color, strlen(curr_tetrominoe.color));

    // draw the tetromino itself
    for (int i = 0; i < 4; i++) {
        move_cursor(shadow_tetrominoe.points[i].x, shadow_tetrominoe.points[i].y, &buf);
        append_buf(&buf, SHADE_CHAR, 4);
    }
    // reset color
    append_buf(&buf, RESET, 4);

    write(STDOUT_FILENO, buf.buf, buf.len);
    free_buf(&buf);
}

int game_over() {
    // if the first row is not clear, then the game is over
    for (int i = 0; i < grid.width - 2; i++) {
        if (grid.cells[0][i] == 1) {
            score = 0;
            return 1;
        }
    }
    return 0;
}