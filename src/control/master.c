#include "../RobotState.h"
#include "../lib/allcode_api.h"
#include "../output/bluetooth.h"
#include "master.h"
#include "movingInstructions.h"
#include <stdlib.h>

int flag = false;

void masterControl(struct RobotState * robotState){
    if(!robotState->instruction == NULL){
        FA_BTSendString ("followInstruction\n", 19);
        robotState->next = robotState->instruction->next;
    } else if (flag && robotState->cellsVisited !=16) {
        FA_BTSendString ("plotRoutetoNextCell\n", 21);
        FA_DelayMillis(10);
        robotState->next = headToNextCell;
        flag = false;
    } else if(robotState->cellsVisited != 16) {
        FA_BTSendString ("updateCell\n", 12);
        FA_DelayMillis(10);
        robotState->next = updateCell;
        flag = true;
    } else {
        //todo do a dance or make noise before heading to darkest cell.
        FA_BTSendString ("HeadToDarkness\n", 16);
        FA_DelayMillis(10);
        robotState->next = headToDarkness;
    }
}

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
    if(robotState->nest == NULL || robotState->curCell->lightLevel < robotState->nest->lightLevel){
         robotState->nest = robotState->curCell;
    }
    robotState->next = broadcastCell;
}

void headToNextCell(struct RobotState * robotState){
    FA_BTSendString ("nextCell\n", 9);
    FA_DelayMillis(10);
    robotState->instruction = searchCells(robotState,robotState->curCell,robotState->orientation);
    robotState->next = getLocation;
}

void headToDarkness(struct RobotState * robotState){
    robotState->instruction = gotoDarkest(robotState,robotState->curCell,robotState->orientation);
    robotState->next = masterControl;
}

struct Instruction * gotoDarkest(struct RobotState * robotState, struct Cell * curCell, int orientation){
    //plot route to darkest cell
    return NULL;
}

struct Instruction * searchCells(struct RobotState * robotState, struct Cell * curCell, int orientation){
    FA_BTSendString ("nextCells\n", 10);
    FA_DelayMillis(10);
    if(curCell->visited == true){
        if(orientation == NORTH){
            return westCheck(robotState, curCell, orientation);
        } else if(orientation == EAST){
            return northCheck(robotState, curCell, orientation);
        } else if(orientation == SOUTH){
            return eastCheck(robotState, curCell, orientation);
        } else if(orientation == WEST){
            return southCheck(robotState, curCell, orientation);
        } else {
            FA_BTSendString ("notValidO\n", 11);
            FA_DelayMillis(5); 
            return NULL;
        }
    } else {
        FA_BTSendString ("atNonVistedCell\n", 17);
        FA_DelayMillis(5);
        robotState->curCell = curCell;
        return NULL;
    }
}

struct Instruction * westCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        if(curCell->wallWest != NULL && curCell->wallWest->wallExists > 100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(5);
            }
            FA_BTSendString ("TurnWest\n", 10);
            FA_DelayMillis(5);
            instruction->nextInstruction = searchCells(robotState, curCell->wallWest->westCell,WEST);
            instruction->next = gotoCellWest; 
            return instruction;
        } else {
            return northCheck(robotState, curCell, orientation);
        }
}

struct Instruction * northCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        if(curCell->wallNorth != NULL && curCell->wallNorth->wallExists > 100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(5);
            }
            FA_BTSendString ("TurnNorth\n", 11);
            FA_DelayMillis(5);
            instruction->nextInstruction = searchCells(robotState, curCell->wallNorth->northCell,NORTH);
            instruction->next = gotoCellNorth; 
            return instruction;
        } else {
            return eastCheck(robotState, curCell, orientation);
        }
}

struct Instruction * eastCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){ 
        if(curCell->wallEast != NULL && curCell->wallEast->wallExists >100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(5);
            }
            FA_BTSendString ("TurnEast\n", 10);
            FA_DelayMillis(5);
            instruction->nextInstruction = searchCells(robotState, curCell->wallEast->eastCell,EAST);
            instruction->next = gotoCellEast; 
            return instruction;
        } else {
            return southCheck(robotState, curCell, orientation);
        }
}

struct Instruction * southCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        if(curCell->wallSouth != NULL && curCell->wallSouth->wallExists > 100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(5);
            }
            FA_BTSendString ("TurnSouth\n", 10);
            FA_DelayMillis(5);
            instruction->nextInstruction = searchCells(robotState, curCell->wallSouth->southCell,SOUTH);
            instruction->next = gotoCellSouth; 
            return instruction;
        } else {
            return westCheck(robotState, curCell, orientation);
        }
}

