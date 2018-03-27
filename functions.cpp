#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "constants.h"
#include "dungeon_generator.h"
#include "functions.h"
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