#include <stdlib.h>
#include <stdbool.h>
#include "AStar.h"
#include "../RobotState.h"
#include "../lib/allcode_api.h"

int distance(int curX, int curY, int desX, int desY){
 int deltaX = curX-desX;
 if(deltaX < 0) deltaX =  deltaX *-1;
 int deltaY = curY-desX;
 if(deltaY < 0) deltaY = deltaY * -1;
 return deltaX+deltaY;
}

struct Data * get(struct Data * data, struct Cell * t, int dataStart, int dataEnd){
    int i;
    for(i = dataStart; i < dataEnd; i++){
        if(data[i].cell == t){
            return &data[i];
        }
    }
    return NULL;
}

int contains(struct Data ** data, struct Cell * t,int dataStart, int dataEnd){
    int i;
    for(i = dataStart; i<dataEnd; i++){
        if(data[i]->cell == t){
            return true;
        }
    }
    return false;
}

struct Data * getLowest(struct Data * data, int * dataStart, int * dataEnd){
    struct Data * d = &data[*dataStart];
    int i;
    for(i = *dataStart; i < *dataEnd; i++){
        if(data[i].scoreF <  d->scoreF){
            d = &data[i];
        }
    }
    i = dataStart;
    while(d != &data[i]){
        i++;
    }
    while(i<dataEnd-1){
        data[i] = data[i+1];
        i++;
    }
    *dataEnd = *dataEnd-1;
    return d;
}

void AStar(struct Cell * t,struct Data * open,struct Data ** closed,struct RobotState * robotState,int * openStart,int * openEnd,int * closedStart,int * closedEnd){
    if(contains(closed,t,*closedStart,*closedEnd)){ //if already closed
        //ignore it
    } else {
        struct Data * d = get(open,t,*openStart,*openEnd);
        char message[30];
        sprintf(message, "cur_%d_%d\n",
            d->cell->x,
            d->cell->y
        );
        FA_BTSendString(message,30);
        if(d == NULL){ //if not in open
            open[*openEnd].cell = t; //add it and compute score
            open[*openEnd].parent = closed[*closedEnd];
            open[*openEnd].costG = closed[*closedEnd]->costG + 1;
            open[*openEnd].costH = distance(t->x,t->y,robotState->nest->x,robotState->nest->y); 
            open[*openEnd].scoreF = open[*openEnd].costG + open[*openEnd].costH;
            *openEnd = *openEnd + 1;
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