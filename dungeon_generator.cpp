#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "constants.h"
#include "dungeon_generator.h"
#include "functions.h"

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: map_filler
; DESCRIPTION: Fills map array with wall characters
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void map_filler (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]){
	int i, j;
	
	for(i = 0; i < ROWS; i++){

		for(j = 0; j < COLUMNS; j++){
			map[i][j][MAP_MAINLAYER] = CELL_WALL;
		}
	}
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: create_first_room
; DESCRIPTION: Creates a rectangular room roughly at the center of the map
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void create_first_room (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]){
	int room_width, room_height, center_width, center_height, i, j;
	
	//room_width = random_value_filler (4, 10);
	room_width = 5;
	//room_height = random_value_filler (4, 10);
	room_height = 5;
	center_width = COLUMNS / 2;
	center_height = ROWS / 2;
	
	for (i = 0; i < room_width; i++){
		for (j = 0; j < room_height; j++){
			map [center_height+i][center_width+j][MAP_MAINLAYER] = CELL_EMPTY;
			
		}	
	}
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: create_corridor
; DESCRIPTION: Finds wall and checks if it can make door and carve corridor
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void create_corridor (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]){
	
	int random_row, random_column, random_corridor_size, legal_direction, i;
	
	//find horizontal or vertical wall
	while(1){
		random_row = random_value_filler (0, ROWS-1);
		random_column = random_value_filler (0, COLUMNS-1);
		random_corridor_size = random_value_filler (3, 15);
		
		//check for north walls

		if (map [random_row][random_column][MAP_MAINLAYER] == CELL_WALL && map [random_row+1][random_column][MAP_MAINLAYER] == CELL_EMPTY){
			
			
			#ifdef DEBUG
			std::cout << "random_corridor_size " << random_corridor_size << "\n";
			#endif
			legal_direction = 1;
			//check if there's room for 3 cells for corridor

			for (i = 0; i < random_corridor_size+1; i++){
				
				if (map [random_row-1-i][random_column][MAP_MAINLAYER] == CELL_EMPTY && map [random_row-1-i][random_column-1][MAP_MAINLAYER] == CELL_EMPTY && map [random_row-1-i][random_column+1][MAP_MAINLAYER] == CELL_EMPTY){
					legal_direction = 0;
				}
			}
			if (legal_direction == 1 && ROWS-random_row-random_corridor_size > 0){
				map [random_row][random_column][MAP_MAINLAYER] = CELL_DOOR;
				for(i = 0; i < random_corridor_size; i++){
					map [random_row-1-i][random_column][MAP_MAINLAYER] = CELL_EMPTY;
				}
			}
			break;
		}		
		//check for south walls
		if (map [random_row][random_column][MAP_MAINLAYER] == CELL_WALL && map [random_row-1][random_column][MAP_MAINLAYER] == CELL_EMPTY){

			#ifdef DEBUG
			std::cout << "random_corridor_size " << random_corridor_size << "\n";
			#endif
			legal_direction = 1;
			for (i = 0; i < random_corridor_size+1; i++){
				if (map [random_row+1+i][random_column][MAP_MAINLAYER] == CELL_EMPTY && map [random_row+1+i][random_column-1][MAP_MAINLAYER] == CELL_EMPTY && map [random_row+1+i][random_column+1][MAP_MAINLAYER] == CELL_EMPTY){
					legal_direction = 0;
				}
			}
			
			if (legal_direction == 1 && ROWS-random_row+random_corridor_size < ROWS - 1){
				map [random_row][random_column][MAP_MAINLAYER] = CELL_DOOR;
				for(i = 0; i < random_corridor_size; i++){
					map [random_row+1+i][random_column][MAP_MAINLAYER] = CELL_EMPTY;
				}
			}
			break;
		}		
		//check for east walls
		if (map [random_row][random_column][MAP_MAINLAYER] == CELL_WALL && map [random_row][random_column-1][MAP_MAINLAYER] == CELL_EMPTY){

			#ifdef DEBUG
			std::cout << "random_corridor_size " << random_corridor_size << "\n";
			#endif
			legal_direction = 1;
			for (i = 0; i < random_corridor_size+1; i++){
				if (map [random_row][random_column+1+i][MAP_MAINLAYER] == CELL_EMPTY && map [random_row-1][random_column+1+i][MAP_MAINLAYER] == CELL_EMPTY && map [random_row+1][random_column+1+i][MAP_MAINLAYER] == CELL_EMPTY){
					legal_direction = 0;
				}
			}
			
			if (legal_direction == 1 && COLUMNS-random_column+random_corridor_size < COLUMNS - 1){
				map [random_row][random_column][MAP_MAINLAYER] = CELL_DOOR;
				for(i = 0; i < random_corridor_size; i++){
					map [random_row][random_column+1+i][MAP_MAINLAYER] = CELL_EMPTY;
				}
			}
			break;
		}		
		//check for west walls
		if (map [random_row][random_column][MAP_MAINLAYER] == CELL_WALL && map [random_row][random_column+1][MAP_MAINLAYER] == CELL_EMPTY){

			#ifdef DEBUG
			std::cout << "random_corridor_size " << random_corridor_size << "\n";
			#endif
			legal_direction = 1;
			for (i = 0; i < random_corridor_size+1; i++){
				if (map [random_row][random_column-1-i][MAP_MAINLAYER] == CELL_EMPTY && map [random_row-1][random_column-1-i][MAP_MAINLAYER] == CELL_EMPTY && map [random_row+1][random_column-1-i][MAP_MAINLAYER] == CELL_EMPTY){
					legal_direction = 0;
				}
			}
			
			if (legal_direction == 1 && COLUMNS-random_column-random_corridor_size > 0){
				map [random_row][random_column][MAP_MAINLAYER] = CELL_DOOR;
				for(i = 0; i < random_corridor_size; i++){
					map [random_row][random_column-1-i][MAP_MAINLAYER] = CELL_EMPTY;
				}
			}
			break;
		}
	}
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: create_room
; DESCRIPTION: Finds a suitable place for a new room and creates it
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
//TODO
//define room sizes delete magic numbers
//check that there's no doors next to each other
//add some protection against segmentation fault && infinite loop
void create_room (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]){
	int random_row, random_column, room_width, room_height, i , j, legal_direction;
	
	while(1){
		random_row = random_value_filler (0, ROWS-1);
		random_column = random_value_filler (0, COLUMNS-1);
		room_width = random_value_filler (4, 15);
		room_height = random_value_filler (4, 15);
		
		//check for north walls and check if you can build a room on north side
		if (map [random_row][random_column][MAP_MAINLAYER] == CELL_WALL && map [random_row+1][random_column][MAP_MAINLAYER] == CELL_EMPTY){
			
			legal_direction = 1;
			
			for (i = 0; i < room_width; i++){
				for (j = 0; j < room_height; j++){
					//check if there's enough room for the new room
					if (map [random_row-1-i][random_column][MAP_MAINLAYER] == CELL_EMPTY && map [random_row-1-i][random_column+j][MAP_MAINLAYER] == CELL_EMPTY){
						#ifdef DEBUG
						std::cout << "Found north wall, room_height: " << room_height << " room_width: " << room_width << " random_row: " << random_row << " random_column: " << random_column << "\n";
						#endif
						legal_direction = 0;
					}
				}
				
			}
			
			//create room if enough space
			if (legal_direction == 1 && ROWS - 1 -random_row-room_height > 0 && COLUMNS-random_column-room_width > 0 && COLUMNS-random_column+room_width < COLUMNS - 1){
				#ifdef DEBUG
				std::cout << "Found north room, room_height: " << room_height << " room_width: " << room_width << " random_row: " << random_row << " random_column: " << random_column << "\n";
				#endif
				map [random_row][random_column][MAP_MAINLAYER] = CELL_DOOR;
				for(i = 0; i < room_width; i++){
					for (j = 0; j < room_height; j++){
						map [random_row-1-i][random_column+j][MAP_MAINLAYER] = CELL_EMPTY;
					}
				}
			}
			
			
			break;
		}		
		//south
		if (map [random_row][random_column][MAP_MAINLAYER] == CELL_WALL && map [random_row-1][random_column][MAP_MAINLAYER] == CELL_EMPTY){
			

			legal_direction = 1;
			
			for (i = 0; i < room_width; i++){
				for (j = 0; j < room_height; j++){
					
					if (map [random_row+1+i][random_column][MAP_MAINLAYER] == CELL_EMPTY && map [random_row+1+i][random_column+j][MAP_MAINLAYER] == CELL_EMPTY){
						#ifdef DEBUG
						std::cout << "Found south wall, room_height: " << room_height << " room_width: " << room_width << " random_row: " << random_row << " random_column: " << random_column << "\n";
						#endif
						legal_direction = 0;
					}
				}
				
			}
			
			//create room if enough space
			if (legal_direction == 1  && ROWS - 1 - random_row + room_height < ROWS - 1 && COLUMNS-random_column-room_width > 0 && COLUMNS-random_column+room_width < COLUMNS - 1){
				#ifdef DEBUG
				std::cout << "Found south room, room_height: " << room_height << " room_width: " << room_width << " random_row: " << random_row << " random_column: " << random_column << "\n";
				#endif
				map [random_row][random_column][MAP_MAINLAYER] = CELL_DOOR;
				for(i = 0; i < room_width; i++){
					for (j = 0; j < room_height; j++){
						map [random_row+1+i][random_column+j][MAP_MAINLAYER] = CELL_EMPTY;
					}
				}
			}
			
			
			break;
		}		
		//east
		//check for east walls and check if you can build a room on west side
		if (map [random_row][random_column][MAP_MAINLAYER] == CELL_WALL && map [random_row][random_column-1][MAP_MAINLAYER] == CELL_EMPTY){

			legal_direction = 1;
			
			for (i = 0; i < room_width; i++){
				for (j = 0; j < room_height; j++){
					//check if there's enough room for the new room
					if (map [random_row][random_column+1+j][MAP_MAINLAYER] == CELL_EMPTY && map [random_row+i][random_column+1+j][MAP_MAINLAYER] == CELL_EMPTY){
						#ifdef DEBUG
						std::cout << "Found east wall, room_height: " << room_height << " room_width: " << room_width << " random_row: " << random_row << " random_column: " << random_column << "\n";
						#endif
						legal_direction = 0;
					}
				}
				
			}
			
			//create room if enough space
			if (legal_direction == 1 && COLUMNS - 1 -random_column+room_width < COLUMNS - 1 && ROWS-random_row-room_height > 0 && ROWS-random_row+room_height < ROWS - 1){
				#ifdef DEBUG
				std::cout << "Found east room, room_height: " << room_height << " room_width: " << room_width << " random_row: " << random_row << " random_column: " << random_column << "\n";
				#endif
				map [random_row][random_column][MAP_MAINLAYER] = CELL_DOOR;
				for(i = 0; i < room_width; i++){
					for (j = 0; j < room_height; j++){
						map [random_row+i][random_column+1+j][MAP_MAINLAYER] = CELL_EMPTY;
					}
				}
			}
			
			
			break;
		}		
		//west

		if (map [random_row][random_column][MAP_MAINLAYER] == CELL_WALL && map [random_row][random_column+1][MAP_MAINLAYER] == CELL_EMPTY){

			legal_direction = 1;
			
			for (i = 0; i < room_width; i++){
				for (j = 0; j < room_height; j++){
					//check if there's enough room for the new room
					if (map [random_row][random_column-1-j][MAP_MAINLAYER] == CELL_EMPTY && map [random_row+i][random_column-1-j][MAP_MAINLAYER] == CELL_EMPTY){
						#ifdef DEBUG
						std::cout << "Found west wall, room_height: " << room_height << " room_width: " << room_width << " random_row: " << random_row << " random_column: " << random_column << "\n";
						#endif
						legal_direction = 0;
					}
				}
				
				
			}
			
			//create room if enough space
			if (legal_direction == 1 && COLUMNS - 1 -random_column-room_width > 0 && ROWS-random_row-room_height > 0 && ROWS-random_row+room_height < ROWS - 1){
				#ifdef DEBUG
				std::cout << "Found west room, room_height: " << room_height << " room_width: " << room_width << " random_row: " << random_row << " random_column: " << random_column << "\n";
				#endif
				map [random_row][random_column][MAP_MAINLAYER] = CELL_DOOR;
				for(i = 0; i < room_width; i++){
					for (j = 0; j < room_height; j++){
						map [random_row+i][random_column-1-j][MAP_MAINLAYER] = CELL_EMPTY;
					}
				}
			}
						
			break;
		}
	}
}