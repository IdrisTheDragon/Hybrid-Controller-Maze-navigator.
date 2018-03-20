#include "../RobotState.h"
#include "../output/bluetooth.h"
#include "master.h"
#include "movingInstructions.h"

void masterControl(struct RobotState * robotState){
    if(robotState->instruction){
            robotState->next = robotState->instruction->next;
    } else if(robotState->cellsVisited == 16) {
        robotState->next = headToDarkness;

    } else {
        robotState->next = updateCell;
    }
}

void updateCell(struct RobotState * robotState){
    robotState->curCell->visited = 1;
    robotState->curCell->lightLevel = robotState->LDR;
    robotState->cellsVisited++;
    robotState->curCell->wallNorth->wallExists = robotState->location->frontDistance;
    robotState->curCell->wallSouth->wallExists =  robotState->location->rearDistance;
    robotState->curCell->wallEast->wallExists = robotState->location->rightDistance;
    robotState->curCell->wallWest->wallExists =  robotState->location->leftDistance;
    robotState->next = headToNextCell;
}

void headToNextCell(struct RobotState * robotState){
    robotState->instruction = searchCells(robotState,robotState->curCell,robotState->orientation);

    robotState->next = masterControl;
}

void headToDarkness(struct RobotState * robotState){
    robotState->instruction = gotoDarkest(robotState,robotState->curCell,robotState->orientation);
    robotState->next = masterControl;
}

struct Instruction * gotoDarkest(struct RobotState * robotState, struct Cell * curCell, int orientation){
    //plot route to darkest cell
    return ;
}

struct Instruction * searchCells(struct RobotState * robotState, struct Cell * curCell, int orientation){
    if(curCell->visited == 1){
        if(orientation == NORTH){
            return westCheck(robotState, curCell, orientation);
        } else if(orientation == EAST){
            return northCheck(robotState, curCell, orientation);
        } else if(orientation == SOUTH){
            return eastCheck(robotState, curCell, orientation);
        } else if(orientation == WEST){
            return southCheck(robotState, curCell, orientation);
        }
    } else {
        return ;
    }
}

struct Instruction * westCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        struct Instruction instruction;
        if(curCell->wallWest->wallExists < 90){
            instruction.nextInstruction = searchCells(robotState, curCell->wallWest->westCell,WEST);
            instruction.next = gotoCellWest; 
            return &instruction;
        } else {
            return northCheck(robotState, curCell, orientation);
        }
}

struct Instruction * northCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        struct Instruction instruction;
        if(curCell->wallNorth->wallExists < 90){
            instruction.nextInstruction = searchCells(robotState, curCell->wallNorth->northCell,NORTH);
            instruction.next = gotoCellNorth; 
            return &instruction;
        } else {
            return eastCheck(robotState, curCell, orientation);
        }
}

struct Instruction * eastCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        struct Instruction instruction;
        if(curCell->wallEast->wallExists < 90){
            instruction.nextInstruction = searchCells(robotState, curCell->wallEast->eastCell,EAST);
            instruction.next = gotoCellEast; 
            return &instruction;
        } else {
            return southCheck(robotState, curCell, orientation);
        }
}

struct Instruction * southCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        struct Instruction instruction;
        if(curCell->wallSouth->wallExists < 90){
            instruction.nextInstruction = searchCells(robotState, curCell->wallSouth->southCell,SOUTH);
            instruction.next = gotoCellSouth; 
            return &instruction;
        } else {
            return westCheck(robotState, curCell, orientation);
        }
}

