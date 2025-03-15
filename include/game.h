#pragma once
#include "../include/tetrominoe.h"


extern tetrominoe_t curr_tetrominoe;
extern int score;

int fall();
int can_move_down(tetrominoe_t *tetrominoe);
void update_grid();
void move_left();
void move_right();
void drop_fast();
void increase_score();
void shadow();
void erase_previous_position();
void process();
void rotate_tetrominoe(tetrominoe_t *tetrominoe);
void clear_full_rows();
void draw_tetrominoe();

