#pragma once
#include "../include/tetrominoe.h"

#include <stdio.h>

void log_message(const char *msg);
void log_grid();
void log_tet(tetrominoe_t curr_tetrominoe);

// high score loading and saving (i'm not sure this is the best place for this but it's fine for now)
int load_high_score();
int save_high_score();