#include "../RobotState.h"
#include "../lib/allcode_api.h"
#include "../output/bluetooth.h"
#include "master.h"
#include "AStar.h"
#include "WallFollow.h"
#include <stdlib.h>
#include "../output/sounds.c"

int flag = false;

void masterControl(struct RobotState * robotState){
    if(!robotState->instruction == NULL){
        //FA_BTSendString ("followInstruction\n", 19);
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
       // musicPlayer();
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
         FA_BTSendString("new_Nest\n",10);
    }
    robotState->next = broadcastCell;
}

void headToNextCell(struct RobotState * robotState){
    //FA_BTSendString ("nextCell\n", 9);
    //FA_DelayMillis(10);
    robotState->instruction = searchCells(robotState,robotState->curCell,robotState->orientation);
    robotState->next = getLocation;
}



void headToDarkness(struct RobotState * robotState){
    struct Data * closed[16];
    struct Data open[16];
    int openStart = 0, openEnd = 0, closedStart = 0, closedEnd =0;
    FA_BTSendString("array\n",7);
    open[openEnd].cell = robotState->curCell;
    open[openEnd].parent = NULL;
    open[openEnd].costG = 0;
    open[openEnd].costH = distance(open[openEnd].cell->x,open[openEnd].cell->y,robotState->nest->x,robotState->nest->y); 
    open[openEnd].scoreF= open[openEnd].costG + open[openEnd].costH;
    openEnd++;
    FA_BTSendString("init\n",6);
    do{
        struct Data * curLowest = getLowest(open,&openStart,&openEnd);
        char message[30];
        sprintf(message, "curLow_%d_%d\n",
            curLowest->cell->x,
            curLowest->cell->y
        );
        FA_BTSendString(message,30);
        closed[closedEnd] = curLowest;
        //check each neighbour
        if(curLowest->cell->wallEast!=NULL && curLowest->cell->wallEast->wallExists > 100 && curLowest->cell->wallEast->eastCell != NULL){
           AStar(curLowest->cell->wallEast->eastCell,open,closed,robotState,&openStart,&openEnd,&closedStart,&closedEnd); 
        }
        if(curLowest->cell->wallWest!=NULL && curLowest->cell->wallWest->wallExists > 100 && curLowest->cell->wallWest->westCell != NULL){
           AStar(curLowest->cell->wallWest->westCell,open,closed,robotState,&openStart,&openEnd,&closedStart,&closedEnd); 
        } 
        if(curLowest->cell->wallNorth!=NULL && curLowest->cell->wallNorth->wallExists > 100 && curLowest->cell->wallNorth->northCell != NULL){
           AStar(curLowest->cell->wallNorth->northCell,open,closed,robotState,&openStart,&openEnd,&closedStart,&closedEnd); 
        } 
        if(curLowest->cell->wallSouth!=NULL && curLowest->cell->wallSouth->wallExists > 100 && curLowest->cell->wallSouth->southCell != NULL){
           AStar(curLowest->cell->wallSouth->southCell,open,closed,robotState,&openStart,&openEnd,&closedStart,&closedEnd); 
        }
        FA_BTSendString("Done\n",7);
    }while(openEnd-openStart > 0 || closed[closedEnd]->cell != robotState->nest);
    //build up path of cells in reverse order into correct order using parent of the data point
    struct Data * d = closed[closedEnd];
    do {
        char message[30];
        sprintf(message, "Cell_%d_%d\n",
            d->cell->x,
            d->cell->y
        );
        FA_BTSendString(message,30);
        d = d->parent;
    } while(d != NULL);
    
    //robotState->instruction = gotoDarkest(robotState,robotState->curCell,robotState->orientation);
    robotState->next = NULL;
}

struct Instruction * gotoDarkest(struct RobotState * robotState, struct Cell * curCell, int orientation, struct Cell ** path){
    
    //build instruction set to navigate through the cells.
    return NULL;
}