#define DEBUG
//determines the size of the map
#define ROWS 30
#define COLUMNS 80
#define FILL_PERCENTAGE 30
#define ROOM_GEN_REP 20
#define MAP_LAYER_COUNT 2
#define MAP_MAINLAYER 0
//define directions, not in use atm
#define NORTH map [i-1][j][MAP_MAINLAYER]
#define SOUTH map [i+1][j][MAP_MAINLAYER]
#define EAST map [i][j+1][MAP_MAINLAYER]
#define WEST map [i][j-1][MAP_MAINLAYER]
#define NORTHEAST map [i-1][j+1][MAP_MAINLAYER]
#define SOUTHEAST map [i+1][j+1][MAP_MAINLAYER]
#define NORTHWEST map [i-1][j-1][MAP_MAINLAYER]
#define SOUTHWEST map [i+1][j-1][MAP_MAINLAYER]


struct cell_info {
   int cell_wall;
   int cell_door;
   int cell_empty;
};