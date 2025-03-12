#pragma once
#include "../include/tetrominoe.h"


extern tetrominoe_t curr_tetrominoe;
extern int score;

void fall();
int can_move_down();
void update_grid();
void move_left();
void move_right();
void drop_fast();
void increase_score();
void shadow();
void erase_previous_position();
void process();

