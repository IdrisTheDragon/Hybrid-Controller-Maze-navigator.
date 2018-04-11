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
        FA_DelayMillis(10);
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
    FA_DelayMillis(30);
    robotState->instruction = searchCells(robotState,robotState->curCell,robotState->orientation);
    robotState->next = getLocation;
}

int distance(int curX, int curY, int desX, int desY){
 int deltaX = curX-desX;
 if(deltaX < 0) deltaX =  deltaX *-1;
 int deltaY = curY-desX;
 if(deltaY < 0) deltaY = deltaY * -1;
 return deltaX+deltaY;
};
 struct Data {
        struct Cell * cell;
        struct Data * parent;
        int scoreF;
        int costG;
        int costH;
    } __attribute__ ((packed));

void AStar(struct Cell * t,struct Data * open,struct Data ** closed,struct RobotState * robotState,int * openStart,int * openEnd,int * closedStart,int * closedEnd){
     if(contains(closed,t,closedStart,closedEnd)){ //if already closed
        //ignore it
    } else {
        struct Data * d = get(open,t,openStart,openEnd);
        if(d == NULL){ //if not in open
            open[*openEnd].cell = t; //add it and compute score
            open[*openEnd].parent = closed[*closedEnd];
            open[*openEnd].costG = closed[*closedEnd]->costG + 1;
            open[*openEnd].costH = distance(t->x,t->y,robotState->nest->x,robotState->nest->y); 
            open[*openEnd].scoreF = open[*openEnd].costG + open[*openEnd].costH;
            openEnd++;
        } else {
            int newF = closed[*closedEnd]->costG + 1 + d->costH;
            if(newF < d->scoreF){
                d->scoreF = newF;
                d->costG = closed[*closedEnd]->costG + 1;
                d->parent = closed[*closedEnd];
            }
        }
            
    }
}

void headToDarkness(struct RobotState * robotState){
    struct Data * closed[16];
    struct Data open[16];
    int openStart = 0, openEnd = 0, closedStart = 0, closedEnd =0;

    open[openEnd].cell = robotState->curCell;
    open[openEnd].parent = NULL;
    open[openEnd].costG = 0;
    open[openEnd].costH = distance(open[openEnd].cell->x,open[openEnd].cell->y,robotState->nest->x,robotState->nest->y); 
    open[openEnd].scoreF= open[openEnd].costG + open[openEnd].costH;
    openEnd++;
    do{
        struct Data * curLowest = getLowest(open,openStart,openEnd);
        closed[closedEnd] = curLowest;
        //check each neighbour
        if(curLowest->cell->wallEast!=NULL && curLowest->cell->wallEast->wallExists > 100 && curLowest->cell->wallEast->eastCell != NULL){
           AStar(curLowest->cell->wallEast->eastCell,&open[0],closed,robotState,&openStart,&openEnd,&closedStart,&closedEnd); 
        }
        if(curLowest->cell->wallWest!=NULL && curLowest->cell->wallWest->wallExists > 100 && curLowest->cell->wallWest->westCell != NULL){
           AStar(curLowest->cell->wallWest->westCell,&open[0],closed,robotState,&openStart,&openEnd,&closedStart,&closedEnd); 
        } 
        if(curLowest->cell->wallNorth!=NULL && curLowest->cell->wallNorth->wallExists > 100 && curLowest->cell->wallNorth->northCell != NULL){
           AStar(curLowest->cell->wallNorth->northCell,&open[0],closed,robotState,&openStart,&openEnd,&closedStart,&closedEnd); 
        } 
        if(curLowest->cell->wallSouth!=NULL && curLowest->cell->wallSouth->wallExists > 100 && curLowest->cell->wallSouth->southCell){
           AStar(curLowest->cell->wallSouth->southCell,&open[0],closed,robotState,&openStart,&openEnd,&closedStart,&closedEnd); 
        }  
    }while(isElementsIn(open) && closed[closedEnd]->cell != robotState->nest);
    //build up path of cells in reverse order into correct order using parent of the data point
    int path = closed[closedEnd];

    robotState->instruction = gotoDarkest(robotState,robotState->curCell,robotState->orientation,path);
    robotState->next = masterControl;
}

struct Instruction * gotoDarkest(struct RobotState * robotState, struct Cell * curCell, int orientation, struct Cell ** path){
    
    //build instruction set to navigate through the cells.
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
        robotState->curCell = curCell;
        return NULL;
    }
}

struct Instruction * westCheck(struct RobotState * robotState, struct Cell * curCell, int orientation){
        if(curCell->wallWest != NULL && curCell->wallWest->wallExists > 100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
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
        if(curCell->wallNorth != NULL && curCell->wallNorth->wallExists > 100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(30);
            }
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
        if(curCell->wallEast != NULL && curCell->wallEast->wallExists >100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(30);
            }
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
        if(curCell->wallSouth != NULL && curCell->wallSouth->wallExists > 100){
            struct Instruction * instruction = malloc(sizeof(struct Instruction));
            if(instruction==NULL){
            FA_BTSendString ("error\n", 7);
            FA_DelayMillis(30);
            }
            FA_BTSendString ("TurnSouth\n", 10);
            FA_DelayMillis(30);
            instruction->nextInstruction = searchCells(robotState, curCell->wallSouth->southCell,SOUTH);
            instruction->next = gotoCellSouth; 
            return instruction;
        } else {
            return westCheck(robotState, curCell, orientation);
        }
}

