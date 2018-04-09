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

/* Global structures */


/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

void debug_print (struct cell_info map[ROWS][COLUMNS]);
void draw_static (WINDOW *local_win);
void new_generate_dungeon (struct cell_info map[ROWS][COLUMNS], int rooms, int corridors);
void new_draw_map (struct cell_info map[ROWS][COLUMNS], WINDOW *local_win);

/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

int main(int argc, char *argv[]) {

	
	int i;
	char map [ROWS][COLUMNS][MAP_LAYER_COUNT];
	struct cell_info new_map[ROWS][COLUMNS];
	srand( time(NULL) ); //Randomize seed initialization for map_fill
	new_map_filler (new_map);

	new_generate_dungeon (new_map, 7, 4);
	
	#ifdef DEBUG
		debug_print (new_map);
	#endif
	
	//ncurses init
	initscr();
	curs_set(0);
	
	//size, location
	WINDOW* map_window = newwin(ROWS + 2, COLUMNS + 2, 0, 0);
	WINDOW* text_window = newwin(10, COLUMNS + 2, ROWS+2, 0);

	box(text_window,0,0);
	start_color();
	draw_static (map_window);
	new_draw_map (new_map, map_window);
	
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
void debug_print (struct cell_info map[ROWS][COLUMNS]){
	
	int i, j;
	
	for (i = 0; i < ROWS; i++){
		for (j = 0; j < COLUMNS; j++){
			if (map[i][j].cell_wall == 1){
				std::cout << "#";
				
			}			
			
			if (map[i][j].cell_empty == 1){
				std::cout << ".";
				
			}			
			
			if (map[i][j].cell_door == 1){
				std::cout << "/";
				
			}
			
		}
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
void new_draw_map (struct cell_info map[ROWS][COLUMNS], WINDOW *local_win){
	int i, j;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
		
	
	
	for(i = 0; i < ROWS; i++){
		
		//change to else if later
		for(j = 0; j < COLUMNS; j++){
			if (map[i][j].cell_wall == 1){
				wattron(local_win, COLOR_PAIR(2));
				mvwprintw(local_win, i+1, j+1, "#");
				wattroff(local_win, COLOR_PAIR(2));	
			}
			if ((map[i][j].cell_empty == 1)){
				wattron(local_win, COLOR_PAIR(3));
				mvwprintw(local_win, i+1, j+1, ".");
				wattroff(local_win, COLOR_PAIR(3));
			}			
			if ((map[i][j].cell_door == 1)){
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
void new_generate_dungeon (struct cell_info map[ROWS][COLUMNS], int rooms, int corridors){
	int i;
	
	new_create_first_room (map);
		for (i = 0; i < corridors; i++){
		new_create_corridor (map);
	}	
	
	new_create_first_room (map);
		for (i = 0; i < rooms; i++){
		new_create_room (map);	
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