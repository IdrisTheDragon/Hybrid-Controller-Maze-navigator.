#include "../Cell.h"
#include "../RobotState.h"
#include "movingInstructions.h"
#include <stdlib.h>
#include "WallFollow.h"
#include "../lib/allcode_api.h"

struct Instruction * searchCells(struct RobotState * robotState, struct Cell * curCell, int orientation){
    //FA_BTSendString ("nextCells\n", 10);
    //FA_DelayMillis(10);
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
            //FA_BTSendString ("notValidO\n", 11);
            //FA_DelayMillis(5); 
            return NULL;
        }
    } else {
        //FA_BTSendString ("atNonVistedCell\n", 17);
       //FA_DelayMillis(5);
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
            //FA_BTSendString ("TurnWest\n", 10);
            //FA_DelayMillis(5);
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
            //FA_BTSendString ("TurnNorth\n", 11);
            //FA_DelayMillis(5);
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
            //FA_BTSendString ("TurnEast\n", 10);
            //FA_DelayMillis(5);
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
            //FA_BTSendString ("TurnSouth\n", 10);
            //FA_DelayMillis(5);
            instruction->nextInstruction = searchCells(robotState, curCell->wallSouth->southCell,SOUTH);
            instruction->next = gotoCellSouth; 
            return instruction;
        } else {
            return westCheck(robotState, curCell, orientation);
        }
}