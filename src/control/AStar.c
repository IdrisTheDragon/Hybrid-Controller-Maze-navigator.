#include <stdlib.h>
#include <stdbool.h>
#include "AStar.h"
#include "../RobotState.h"
#include "../lib/allcode_api.h"
#include "movingInstructions.h"
#include "../output/sounds.h"

struct Instruction * searchDarkness(struct RobotState * robotState, struct Cell * curCell, int orientation){
    if(curCell->x != robotState->nest->x || curCell->y != robotState->nest->y){
        if(orientation == NORTH){
            return eastCheckD(robotState, curCell, orientation);
        } else if(orientation == EAST){
            return southCheckD(robotState, curCell, orientation);
        } else if(orientation == SOUTH){
            return westCheckD(robotState, curCell, orientation);
        } else if(orientation == WEST){
            return northCheckD(robotState, curCell, orientation);
        } else {
            FA_BTSendString ("notValid\n", 11);
            FA_DelayMillis(5); 
            return NULL;
        }
    } else {
        //FA_BTSendString ("atNest\n", 17);
        //FA_DelayMillis(5);
        robotState->curCell = curCell;
        struct Instruction * instruction = malloc(sizeof(struct Instruction));
        if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(5);
        }
        instruction->nextInstruction = NULL;
        instruction->next = stop;
        return instruction;
    }
}
struct Instruction * westCheckD(struct RobotState * robotState, struct Cell * curCell, int orientation){
        if(curCell->wallWest != NULL && curCell->wallWest->wallExists > 100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(5);
            }
            //FA_BTSendString ("TurnWest\n", 10);
            //FA_DelayMillis(5);
            instruction->nextInstruction = searchDarkness(robotState, curCell->wallWest->westCell,WEST);
            if(instruction->nextInstruction->next == gotoCellEast){ //checks if doubling back on self
                free(instruction);
                return southCheckD(robotState, curCell, orientation);
            }
            instruction->next = gotoCellWest; 
            return instruction;
        } else {
            return southCheckD(robotState, curCell, orientation);
        }
}

struct Instruction * northCheckD(struct RobotState * robotState, struct Cell * curCell, int orientation){
        if(curCell->wallNorth != NULL && curCell->wallNorth->wallExists > 100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(5);
            }
            //FA_BTSendString ("TurnNorth\n", 11);
            //FA_DelayMillis(5);
            instruction->nextInstruction = searchDarkness(robotState, curCell->wallNorth->northCell,NORTH);
            if(instruction->nextInstruction->next == gotoCellSouth){ //checks if doubling back on self
                free(instruction);
                return westCheckD(robotState, curCell, orientation);
            }
            instruction->next = gotoCellNorth; 
            return instruction;
        } else {
            return westCheckD(robotState, curCell, orientation);
        }
}

struct Instruction * eastCheckD(struct RobotState * robotState, struct Cell * curCell, int orientation){ 
        if(curCell->wallEast != NULL && curCell->wallEast->wallExists >100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(5);
            }
            //FA_BTSendString ("TurnEast\n", 10);
            //FA_DelayMillis(5);
            instruction->nextInstruction = searchDarkness(robotState, curCell->wallEast->eastCell,EAST);
            if(instruction->nextInstruction->next == gotoCellWest){ //checks if doubling back on self
                free(instruction);
                return northCheckD(robotState, curCell, orientation);
            }
            instruction->next = gotoCellEast; 
            return instruction;
        } else {
            return northCheckD(robotState, curCell, orientation);
        }
}

struct Instruction * southCheckD(struct RobotState * robotState, struct Cell * curCell, int orientation){
        if(curCell->wallSouth != NULL && curCell->wallSouth->wallExists > 100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(5);
            }
            //FA_BTSendString ("TurnSouth\n", 10);
            //FA_DelayMillis(5);
            instruction->nextInstruction = searchDarkness(robotState, curCell->wallSouth->southCell,SOUTH);
            if(instruction->nextInstruction->next == gotoCellNorth){ //checks if doubling back on self
                free(instruction);
                return eastCheckD(robotState, curCell, orientation);
            }
            instruction->next = gotoCellSouth; 
            return instruction;
        } else {
            return eastCheckD(robotState, curCell, orientation);
        }
}


void stop(struct RobotState * robotState){
    musicPlayer();
    FA_BTSendString("Good Night, sleep well.\n",12);
    robotState->next = NULL;
};