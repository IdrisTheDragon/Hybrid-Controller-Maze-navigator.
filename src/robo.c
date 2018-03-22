#include "lib/allcode_api.h"
#include "input/Location.h"
#include "output/bluetooth.h"
#include "RobotState.h"
#include "Cell.h"
#include "stdlib.h"

struct Cell map[4][4]; //create 16 Cells.

void init(struct RobotState * robotState){
	FA_RobotInit();
	XFA_ClockMS_Initialise();
	FA_LCDBacklight(50);

	int x,y; //loop variables for x and y directions

	for(x=0;x<4;x++){
		for(y=0;y<4;y++){
			map[x][y].visited = false;
		}
	}
	
	//put in the vertical walls
	for(y=0;y<4;y++){
		//west walls
		struct VWall * wall = malloc(sizeof(VWall));
		wall->eastCell = &map[0][y];
		wall->wallExists = 2000;
		map[0][y].wallWest = wall;
		//east walls
		struct VWall * wall1 = malloc(sizeof(VWall));
		wall1->westCell = &map[3][y];
		wall1->wallExists = 2000;
		map[3][y].wallEast = wall1;
	}
	//middle walls
	for(x=0;x<3; x++){
		for(y=0;y<4;y++){
			struct VWall * wall = malloc(sizeof(VWall));
			wall->westCell = &map[x-1][y];
			wall->eastCell = &map[x][y];
			map[x][y].wallWest = wall;
			map[x-1][y].wallEast = wall;
		}
	}
	//put in the horizotal walls
	for(x=0;x<4;x++){
		//southern wall
		struct HWall * wall  = malloc(sizeof(HWall));
		wall->northCell = &map[x][0];
		wall->wallExists = 2000;
		map[x][3].wallSouth = wall;
		
		//northern wall
		struct HWall * wall1 = malloc(sizeof(HWall));
		wall1->southCell = &map[x][3];
		wall1->wallExists = 2000;
		map[x][3].wallNorth = wall1;
	}
	//middle walls
	for(x=0;x<4; x++){
		for(y=0;y<3;y++){
			struct HWall * wall = malloc(sizeof(HWall));
			wall->southCell = &map[x][y-1];
			wall->northCell = &map[x][y];
			map[x][y].wallSouth = wall;
			map[x][y-1].wallNorth = wall;
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
	struct Location * location = malloc(sizeof(Location));
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



