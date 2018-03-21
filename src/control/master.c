#include "../RobotState.h"
#include "../lib/allcode_api.h"
#include "../output/bluetooth.h"
#include "master.h"
#include "movingInstructions.h"
#include <stdlib.h>

void masterControl(struct RobotState * robotState){
    FA_BTSendString ("here\n", 5);
    FA_DelayMillis(30);
    if(!robotState->instruction == NULL){
        FA_BTSendString ("here1\n", 7);
        FA_DelayMillis(30);
        robotState->next = robotState->instruction->next;
    } else if(robotState->cellsVisited == 16) {
        FA_BTSendString ("here2\n", 7);
        FA_DelayMillis(30);
        robotState->next = headToDarkness;
    } else {
        FA_BTSendString ("here3\n", 7);
        FA_DelayMillis(30);
        robotState->next = updateCell;
    }
}

void updateCell(struct RobotState * robotState){
    robotState->curCell->visited = true;
    robotState->curCell->lightLevel = robotState->LDR;
    robotState->cellsVisited++;
    switch(robotState->orientation == NORTH){
        case NORTH:
            robotState->curCell->wallNorth->wallExists = robotState->location->frontDistance;
            robotState->curCell->wallSouth->wallExists =  robotState->location->rearDistance;
            robotState->curCell->wallEast->wallExists = robotState->location->rightDistance;
            robotState->curCell->wallWest->wallExists =  robotState->location->leftDistance;
            break;
        case EAST:
            robotState->curCell->wallEast->wallExists = robotState->location->frontDistance;
            robotState->curCell->wallWest->wallExists =  robotState->location->rearDistance;
            robotState->curCell->wallSouth->wallExists = robotState->location->rightDistance;
            robotState->curCell->wallNorth->wallExists =  robotState->location->leftDistance;
            break;
        case SOUTH:
            robotState->curCell->wallSouth->wallExists = robotState->location->frontDistance;
            robotState->curCell->wallNorth->wallExists =  robotState->location->rearDistance;
            robotState->curCell->wallWest->wallExists = robotState->location->rightDistance;
            robotState->curCell->wallEast->wallExists =  robotState->location->leftDistance;
            break;
        case WEST:
            robotState->curCell->wallWest->wallExists = robotState->location->frontDistance;
            robotState->curCell->wallEast->wallExists =  robotState->location->rearDistance;
            robotState->curCell->wallNorth->wallExists = robotState->location->rightDistance;
            robotState->curCell->wallSouth->wallExists =  robotState->location->leftDistance;
            break;
    }
    robotState->next = headToNextCell;
}

void headToNextCell(struct RobotState * robotState){
    FA_BTSendString ("nextCell\n", 9);
    FA_DelayMillis(30);
    
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
    FA_DelayMillis(30);
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
            FA_DelayMillis(30); 
            return NULL;
        }
    } else {
        FA_BTSendString ("atNonVistedCell\n", 17);
        FA_DelayMillis(30);
        return NULL;
    }
}

struct Instruction * westCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        if(curCell->wallWest->wallExists > 100){
            struct Instruction * instruction = (Instruction *)malloc(sizeof(Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(30);
            }
            FA_BTSendString ("TurnWest\n", 10);
            FA_DelayMillis(30);
            instruction->nextInstruction = searchCells(robotState, curCell->wallWest->westCell,WEST);
            instruction->next = gotoCellWest; 
            return instruction;
        } else {
            return northCheck(robotState, curCell, orientation);
        }
}

struct Instruction * northCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        if(curCell->wallNorth->wallExists > 100){
            struct Instruction * instruction = (Instruction *)calloc(1,sizeof(Instruction));
            FA_BTSendString ("TurnNorth\n", 11);
            FA_DelayMillis(30);
            instruction->nextInstruction = searchCells(robotState, curCell->wallNorth->northCell,NORTH);
            instruction->next = gotoCellNorth; 
            return instruction;
        } else {
            return eastCheck(robotState, curCell, orientation);
        }
}

struct Instruction * eastCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){ 
        if(curCell->wallEast->wallExists >100){
            struct Instruction * instruction = (Instruction *)calloc(1,sizeof(Instruction));
            FA_BTSendString ("TurnEast\n", 10);
            FA_DelayMillis(30);
            instruction->nextInstruction = searchCells(robotState, curCell->wallEast->eastCell,EAST);
            instruction->next = gotoCellEast; 
            return instruction;
        } else {
            return southCheck(robotState, curCell, orientation);
        }
}

struct Instruction * southCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        if(curCell->wallSouth->wallExists > 100){
            struct Instruction * instruction = (Instruction *)calloc(1,sizeof(Instruction));
            FA_BTSendString ("TurnSouth\n", 10);
            FA_DelayMillis(30);
            instruction->nextInstruction = searchCells(robotState, curCell->wallSouth->southCell,SOUTH);
            instruction->next = gotoCellSouth; 
            return instruction;
        } else {
            return westCheck(robotState, curCell, orientation);
        }
}

