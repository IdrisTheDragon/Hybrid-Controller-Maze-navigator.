#include "lib/allcode_api.h"
#include "input/Location.h"
#include "output/bluetooth.h"
#include "RobotState.h"
#include "Cell.h"
#include "stdlib.h"

#define MAPSIZE 4

struct Cell map[MAPSIZE][MAPSIZE]; //create 16 Cells.

void init(struct RobotState * robotState){
	FA_RobotInit();
	XFA_ClockMS_Initialise();
	FA_LCDBacklight(50);

	int x,y; //loop variables for x and y directions

	for(x=0;x<MAPSIZE;x++){
		for(y=0;y<MAPSIZE;y++){
			map[x][y].visited = false;
			map[x][y].x = x;
			map[x][y].y = y;
		}
	}
	
	//put in the outside vertical walls
	for(y=0;y<MAPSIZE;y++){
		//west walls
		map[0][y].wallWest = NULL;
		//east walls
		map[3][y].wallEast = NULL;
	}
	//middle walls
	for(x=0;x<MAPSIZE-1; x++){
		for(y=0;y<MAPSIZE;y++){
			struct VWall * wall = malloc(sizeof(struct VWall));
			if(wall==NULL){
            FA_BTSendString ("error allocation wall memory\n", 30);
            FA_DelayMillis(30);
            }
			wall->westCell = &map[x][y];
			wall->eastCell = &map[x+1][y];
			map[x][y].wallEast = wall;
			map[x+1][y].wallWest = wall;
		}
	}
	//put in the horizotal walls
	for(x=0;x<MAPSIZE;x++){
		//southern wall
		map[x][0].wallSouth = NULL;
		//northern wall
		map[x][3].wallNorth = NULL;
	}
	//middle walls
	for(x=0;x<MAPSIZE; x++){
		for(y=0;y<MAPSIZE-1;y++){
			struct HWall * wall = malloc(sizeof(struct HWall));
			if(wall==NULL){
            FA_BTSendString ("error allocation wall memory\n", 30);
            FA_DelayMillis(30);
            }
			wall->southCell = &map[x][y];
			wall->northCell = &map[x][y+1];
			map[x][y].wallNorth = wall;
			map[x][y+1].wallSouth = wall;
		}
	}



	
	robotState->orientation = NORTH;        //set it's genral orientation to North
	robotState->REncoders = 0;
	robotState->LEncoders = 0;
	robotState->prevLEncoder = 0;
	robotState->prevLEncoder = 0;
	robotState->cellsVisited = 0;
	robotState->instruction = NULL;
	robotState->curCell = &map[1][0];       //set it's current cell location
	struct Location * location = malloc(sizeof(struct Location));
	if(location==NULL){
        FA_BTSendString ("error allocation location memory\n", 34);
        FA_DelayMillis(30);
    }
	robotState->location = location;
	robotState->next = getLocation;
}



int main(){
	struct RobotState robotState;          //create a robot State to store the sensor speed data etc.
	robotState.next = init;                //add the first function to the state machine: initialise the robot.
    while(robotState.next) {               //begin the state machine while loop.
		robotState.next(&robotState);      //excute the code for the next state.
	}


	return 0;
}



