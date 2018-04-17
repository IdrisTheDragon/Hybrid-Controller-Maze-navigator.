#ifndef AStar_H
#define AStar_H

#include "../RobotState.h"

struct Data {
    struct Cell * cell;
    struct Data * parent;
    int scoreF;
    int costG;
    int costH;
} __attribute__ ((packed));

int distance(int curX, int curY, int desX, int desY);
struct Data * get(struct Data * data, struct Cell * t, int dataStart, int dataEnd);
int contains(struct Data ** data, struct Cell * t,int dataStart, int dataEnd);
struct Data * getLowest(struct Data * data, int *dataStart, int *dataEnd);
void AStar(struct Cell * t,struct Data * open,struct Data ** closed,struct RobotState * robotState,int * openStart,int * openEnd,int * closedStart,int * closedEnd);


#endif /* AStar_H*/