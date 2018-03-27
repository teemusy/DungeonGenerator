#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "constants.h"

void map_filler (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);
void create_first_room (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);
void create_corridor (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);
void create_room (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);