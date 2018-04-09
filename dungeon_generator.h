#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

void new_create_first_room (struct cell_info map[ROWS][COLUMNS]);
void new_create_corridor (struct cell_info map[ROWS][COLUMNS]);
void new_create_room (struct cell_info map[ROWS][COLUMNS]);
void new_map_filler (struct cell_info map[ROWS][COLUMNS]);