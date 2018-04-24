#include "../RobotState.h"
#include "../lib/allcode_api.h"
#include "../output/bluetooth.h"
#include "master.h"
#include "AStar.h"
#include "WallFollow.h"
#include <stdlib.h>
#include "../output/sounds.h"

int flag = false;

void masterControl(struct RobotState * robotState){
    if(!robotState->instruction == NULL){
        //FA_BTSendString ("followInstruction\n", 19);
        robotState->next = robotState->instruction->next;
    } else if (flag && robotState->cellsVisited !=16) {
        //FA_BTSendString ("plotRoutetoNextCell\n", 21);
        //FA_DelayMillis(10);
        robotState->next = headToNextCell;
        flag = false;
    } else if(robotState->cellsVisited != 16) {
        //FA_BTSendString ("updateCell\n", 12);
        //FA_DelayMillis(10);
        robotState->next = updateCell;
        flag = true;
    } else {
        //FA_BTSendString ("HeadToDarkness\n", 16);
        //FA_DelayMillis(10);
        FA_LCDBacklight(50);
        FA_PlayNote(523,200);
        FA_LCDBacklight(0);
        FA_PlayNote(784,200);
        FA_DelayMillis(200);
        FA_PlayNote(523,200);
        FA_LCDBacklight(50);
        char message[30];
        sprintf(message,"nest_X_%d_Y_%d\n",
            robotState->nest->x,
            robotState->nest->y
        );
        FA_BTSendString(message,30);
        FA_DelayMillis(10);
        robotState->next = headToDarkness;
    }
}


//update the the current cell walls based on the robots orientation
void updateCell(struct RobotState * robotState){
    robotState->curCell->visited = true;
    robotState->curCell->lightLevel = robotState->LDR;
    robotState->cellsVisited++;
    switch(robotState->orientation){
        case NORTH:
            if(robotState->curCell->wallNorth != NULL){
                robotState->curCell->wallNorth->wallExists = robotState->location->frontDistance;
            }
            if(robotState->curCell->wallSouth != NULL){
                robotState->curCell->wallSouth->wallExists =  robotState->location->rearDistance;
            }
            if(robotState->curCell->wallEast != NULL){
                robotState->curCell->wallEast->wallExists = robotState->location->rightDistance;
            }
            if(robotState->curCell->wallWest != NULL){
                robotState->curCell->wallWest->wallExists =  robotState->location->leftDistance;
            }
            break;
        case EAST:
            if(robotState->curCell->wallEast != NULL){
                robotState->curCell->wallEast->wallExists = robotState->location->frontDistance;
            }
            if(robotState->curCell->wallWest != NULL){
                robotState->curCell->wallWest->wallExists =  robotState->location->rearDistance;
            }
            if(robotState->curCell->wallSouth != NULL){
                robotState->curCell->wallSouth->wallExists = robotState->location->rightDistance;
            }
            if(robotState->curCell->wallNorth != NULL){
                robotState->curCell->wallNorth->wallExists =  robotState->location->leftDistance;
            }
            break;
        case SOUTH:
            if(robotState->curCell->wallSouth != NULL){
                robotState->curCell->wallSouth->wallExists = robotState->location->frontDistance;
            }
            if(robotState->curCell->wallNorth != NULL){
                robotState->curCell->wallNorth->wallExists =  robotState->location->rearDistance;
            }
            if(robotState->curCell->wallWest != NULL){
            robotState->curCell->wallWest->wallExists = robotState->location->rightDistance;
            }
            if(robotState->curCell->wallEast != NULL){
                robotState->curCell->wallEast->wallExists =  robotState->location->leftDistance;
            }
            break;
        case WEST:
            if(robotState->curCell->wallWest != NULL){
                robotState->curCell->wallWest->wallExists = robotState->location->frontDistance;
            }
            if(robotState->curCell->wallEast != NULL){
                robotState->curCell->wallEast->wallExists =  robotState->location->rearDistance;
            }
            if(robotState->curCell->wallNorth != NULL){
                robotState->curCell->wallNorth->wallExists = robotState->location->rightDistance;
            }
            if(robotState->curCell->wallSouth != NULL){
                robotState->curCell->wallSouth->wallExists =  robotState->location->leftDistance;
            }
            break;
    }
    //check if this is the nest
    if(robotState->nest == NULL || robotState->curCell->lightLevel < robotState->nest->lightLevel){
        robotState->nest = robotState->curCell;
        //FA_BTSendString ("new_nest\n", 10);
    }
    robotState->next = broadcastCell;
}

//Plot a route the the next non visited cell
void headToNextCell(struct RobotState * robotState){
    //FA_BTSendString ("nextCell\n", 9);
    //FA_DelayMillis(10);
    robotState->instruction = searchCells(robotState,robotState->curCell,robotState->orientation);
    robotState->next = getLocation;
}

//plot a optimal route to the darkest cell
void headToDarkness(struct RobotState * robotState){
    robotState->instruction = searchDarkness(robotState,robotState->curCell,robotState->orientation);
    robotState->next = getLocation;
}