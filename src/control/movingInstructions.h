#ifndef MovingI_H
#define MovingI_H


#include "../RobotState.h"


void gotoCellWest(struct RobotState * robotState);
void gotoCellNorth(struct RobotState * robotState);
void gotoCellEast(struct RobotState * robotState);
void gotoCellSouth(struct RobotState * robotState);


//Helper states
void turn(int orientation, struct RobotState * robotState);
void turnA(int orientation, struct RobotState * robotState);
void foreward(struct RobotState * robotState);
void turnThenStraight(int direction, struct RobotState * robotState);

#endif /* !MovingI_H*/