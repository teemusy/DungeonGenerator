/*compile with -lncurses option*/

/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */

/* Global constants */
//determines the size of the map
#define ROWS 50
#define COLUMNS 100
#define FILL_PERCENTAGE 30
#define ROOM_GEN_REP 20
//define directions
#define NORTH map [i-1][j][MAP_MAINLAYER]
#define SOUTH map [i+1][j][MAP_MAINLAYER]
#define EAST map [i][j+1][MAP_MAINLAYER]
#define WEST map [i][j-1][MAP_MAINLAYER]
#define NORTHEAST map [i-1][j+1][MAP_MAINLAYER]
#define SOUTHEAST map [i+1][j+1][MAP_MAINLAYER]
#define NORTHWEST map [i-1][j-1][MAP_MAINLAYER]
#define SOUTHWEST map [i+1][j-1][MAP_MAINLAYER]

#define MAP_MAINLAYER 0

//number of map layers
#define MAP_LAYER_COUNT 2

#define DEBUG

/* Global structures */

//map cell types, maybe create a struct to store them?
char CELL_WALL = '#';
char CELL_EMPTY = '.';
char CELL_DOOR = '/';



/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

void map_filler (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);
void debug_print (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);
void create_first_room (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);
void create_corridor (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);
void create_room (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);
int random_value_filler (int min, int max);
void draw_map (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]);
void draw_static ();

//function that handles dungeon creation
void generate_dungeon (char map [ROWS][COLUMNS][MAP_LAYER_COUNT], int rooms, int corridors);

/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

int main(int argc, char *argv[]) {
	int i;
	char map [ROWS][COLUMNS][MAP_LAYER_COUNT];
	srand( time(NULL) ); //Randomize seed initialization for map_fill
	map_filler (map);
	
	generate_dungeon (map, 7, 4);
	
	#ifdef DEBUG
	debug_print (map);
	#endif
	
	//ncurses init
	initscr();
	curs_set(0);
	start_color();
	draw_static ();
	draw_map (map);
	refresh();
		
	getch();
	endwin();	
	return 0;
	
}/* end of main */

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
		j = 0;
	}
}
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
		j = 0;		
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
*    FUNCTIONS                                                     *
**********************************************************************/
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: random_value_filler
; DESCRIPTION: Returns random integer within given range
;	Input: Range min and max
;	Output: Random value
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
int random_value_filler (int min, int max){
	int random_value;

	random_value = min + rand() % static_cast<int>(max-min+1);
	

	return random_value;
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: draw_map
; DESCRIPTION: Draws map with ncurses
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void draw_map (char map [ROWS][COLUMNS][MAP_LAYER_COUNT]){
	int i, j;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
		
	
	
	for(i = 0; i < ROWS; i++){
		
		for(j = 0; j < COLUMNS; j++){
			if (map[i][j][0] == CELL_WALL){
				attron(COLOR_PAIR(2));
				mvprintw(i+1, j+1, "#");
				attroff(COLOR_PAIR(2));	
			}
			else if ((map[i][j][0] == CELL_EMPTY)){
				attron(COLOR_PAIR(3));
				mvprintw(i+1, j+1, ".");
				attroff(COLOR_PAIR(3));
			}			
			else if ((map[i][j][0] == CELL_DOOR)){
				attron(COLOR_PAIR(1));
				mvprintw(i+1, j+1, "/");
				attroff(COLOR_PAIR(1));
			}
		}
		j = 0;
	}
	attroff(COLOR_PAIR(2));	
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
						std::cout << "Found empty\n";
						std::cout << "room_width " << room_width << "room_height " << room_height << "\n";
						#endif
						legal_direction = 0;
					}
				}
				j = 0;
				
				
			}
			
			//create room if enough space
			if (legal_direction == 1 && ROWS-random_row-room_height > 0){
				#ifdef DEBUG
				std::cout << "Found north\n";
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
						std::cout << "Found empty\n";
						std::cout << "room_width " << room_width << "room_height " << room_height << "\n";
						#endif
						legal_direction = 0;
					}
				}
				j = 0;
				
				
			}
			
			//create room if enough space
			if (legal_direction == 1  && ROWS-random_row+room_height < ROWS - 1){
				#ifdef DEBUG
				std::cout << "Found south\n";
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
						std::cout << "Found empty\n";
						std::cout << "room_width " << room_width << "room_height " << room_height << "\n";
						#endif
						legal_direction = 0;
					}
				}
				j = 0;
				
				
			}
			
			//create room if enough space
			if (legal_direction == 1 && COLUMNS-random_column+room_width < COLUMNS - 1){
				#ifdef DEBUG
				std::cout << "Found east\n";
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
						std::cout << "Found empty\n";
						std::cout << "room_width " << room_width << "room_height " << room_height << "\n";
						#endif
						legal_direction = 0;
					}
				}
				j = 0;
				
				
			}
			
			//create room if enough space
			if (legal_direction == 1 && COLUMNS-random_column-room_width > 0){
				#ifdef DEBUG
				std::cout << "Found west\n";
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
;	Input: None
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void draw_static (){
	int i;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
	
	//draw horizontal borders
	attron(COLOR_PAIR(1));
	for(i = 0; i < COLUMNS + 2; i++){
		mvprintw(0, i, "@");
		mvprintw(ROWS + 1, i, "@");
	}
	//draw vertical bordersgit status

	for(i = 0; i < ROWS + 2; i++){
		mvprintw(i, 0, "@");
		mvprintw(i, COLUMNS + 1, "@");
	}
	attroff(COLOR_PAIR(1));
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