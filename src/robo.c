#include "lib/allcode_api.h"
#include "input/Location.h"
#include "output/bluetooth.h"
#include "RobotState.h"
#include "Cell.h"

void init(struct RobotState * robotState){
	FA_RobotInit();
	XFA_ClockMS_Initialise();
	FA_LCDBacklight(50);
	robotState->next = getLocation;
}



int main(){
	int x,y; //loop variables for x and y directions
	struct Cell map[4][4]; //create 16 Cells.
	
	//put in the vertical walls
	for(y=0;y<4;y++){
		//west walls
		struct VWall wall;
		wall.eastCell = &map[0][y];
		wall.wallExists = true;
		map[0][y].wallWest = &wall;
		//east walls
		struct VWall wall1;
		wall1.westCell = &map[3][y];
		wall1.wallExists = true;
		map[3][y].wallEast = &wall1;
	}
	//middle walls
	for(x=0;x<3; x++){
		for(y=0;y<4;y++){
			struct VWall wall;
			wall.westCell = &map[x-1][y];
			wall.eastCell = &map[x][y];
			map[x][y].wallWest = &wall;
			map[x-1][y].wallEast = &wall;
		}
	}
	//put in the horizotal walls
	for(x=0;x<4;x++){
		//southern wall
		struct HWall wall;
		wall.northCell = &map[x][0];
		wall.wallExists = true;
		map[x][3].wallSouth = &wall;
		
		//northern wall
		struct HWall wall1;
		wall1.southCell = &map[x][3];
		wall1.wallExists = true;
		map[x][3].wallNorth = &wall1;
	}
	//middle walls
	for(x=0;x<4; x++){
		for(y=0;y<3;y++){
			struct HWall wall;
			wall.southCell = &map[x][y-1];
			wall.northCell = &map[x][y];
			map[x][y].wallSouth = &wall;
			map[x][y-1].wallNorth = &wall;
		}
	}
	
	struct RobotState robotState;          //create a robot State to store the sensor speed data etc.
	robotState.next = init;                //add the first function to the state machine: initialise the robot.
	robotState.orientation = NORTH;        //set it's genral orientation to North
	robotState.REncoders = 0;
	robotState.LEncoders = 0;
	robotState.cellsVisited = 0;
	robotState.curCell = &map[1][0];       //set it's current cell location
    while(robotState.next) {               //begin the state machine while loop.
		robotState.next(&robotState);      //excute the code for the next state.
	}	
	return 0;
}



