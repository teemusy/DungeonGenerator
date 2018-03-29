/*compile with -lncurses option*/

/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "constants.h"
#include "dungeon_generator.h"
#include "functions.h"

/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */

/* Global constants */

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

void debug_print (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);
void draw_map (char map [ROWS][COLUMNS][MAP_LAYER_COUNT], WINDOW *local_win);
void draw_static (WINDOW *local_win);
void generate_dungeon (char map [ROWS][COLUMNS][MAP_LAYER_COUNT], int rooms, int corridors);

/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

int main(int argc, char *argv[]) {
	int i;
	char map [ROWS][COLUMNS][MAP_LAYER_COUNT];
	srand( time(NULL) ); //Randomize seed initialization for map_fill
	map_filler (map);
	//magic numbers
	generate_dungeon (map, 7, 4);
	
	#ifdef DEBUG
		debug_print (map);
	#endif
	
	//ncurses init
	initscr();
	curs_set(0);
	
	//size, location
	WINDOW* map_window = newwin(ROWS + 2, COLUMNS + 2, 0, 0);
	WINDOW* text_window = newwin(10, COLUMNS + 2, ROWS+2, 0);
	//box(map_window,0,0);
	//box(map_window, '*', '*');
	box(text_window,0,0);
	start_color();
		
	//should remove sraw_static later?
	draw_static (map_window);
	draw_map (map, map_window);
	
	refresh();
	wrefresh(map_window);
	wrefresh(text_window);
	

	getch();
	endwin();	
	
	#ifdef DEBUG
	for(i = 0; i < 5; i++){
		//printf("%d\n", random_value_filler(0,50));
	}
	#endif
	
	return 0;
	
}/* end of main */


/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: debug_print
; DESCRIPTION: Allows easier debugging by disabling ncurses and printing map to console
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void debug_print (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]){
	
	int i, j;
	
	for (i = 0; i < ROWS; i++){
		for (j = 0; j < COLUMNS; j++){
			std::cout << map[i][j][MAP_MAINLAYER];
		}
		j = 0;
		std::cout << "\n";
	}
	std::cout << "\n";
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: draw_map
; DESCRIPTION: Draws map with ncurses
;	Input: Array, Ncurses window
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void draw_map (char map [ROWS][COLUMNS][MAP_LAYER_COUNT], WINDOW *local_win){
	int i, j;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
		
	
	
	for(i = 0; i < ROWS; i++){
		
		for(j = 0; j < COLUMNS; j++){
			if (map[i][j][0] == CELL_WALL){
				wattron(local_win, COLOR_PAIR(2));
				mvwprintw(local_win, i+1, j+1, "#");
				wattroff(local_win, COLOR_PAIR(2));	
			}
			else if ((map[i][j][0] == CELL_EMPTY)){
				wattron(local_win, COLOR_PAIR(3));
				mvwprintw(local_win, i+1, j+1, ".");
				wattroff(local_win, COLOR_PAIR(3));
			}			
			else if ((map[i][j][0] == CELL_DOOR)){
				wattron(local_win, COLOR_PAIR(1));
				mvwprintw(local_win, i+1, j+1, "/");
				wattroff(local_win, COLOR_PAIR(1));
			}
		}
		j = 0;
	}
	attroff(COLOR_PAIR(2));	
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: generate_dungeon
; DESCRIPTION: Creates dungeon using given variables
;	Input: Array, room count and corridor count as integers
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void generate_dungeon (char map [ROWS][COLUMNS][MAP_LAYER_COUNT], int rooms, int corridors){
	int i;
	
	create_first_room (map);
		for (i = 0; i < corridors; i++){
		create_corridor (map);
	}	
	
	create_first_room (map);
		for (i = 0; i < rooms; i++){
		create_room (map);	
	}
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: draw_static
; DESCRIPTION: Draws borders for creatures, uses ncurses
;	Input: Ncurses window
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void draw_static (WINDOW *local_win){
	int i;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
	
	//draw horizontal borders
	wattron(local_win, COLOR_PAIR(1));
	for(i = 0; i < COLUMNS + 2; i++){
		mvwprintw(local_win, 0, i, "@");
		mvwprintw(local_win, ROWS + 1, i, "@");
	}
	//draw vertical bordersgit status

	for(i = 0; i < ROWS + 2; i++){
		mvwprintw(local_win, i, 0, "@");
		mvwprintw(local_win, i, COLUMNS + 1, "@");
	}
	wattroff(local_win, COLOR_PAIR(1));
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:
; DESCRIPTION:
;	Input:
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/