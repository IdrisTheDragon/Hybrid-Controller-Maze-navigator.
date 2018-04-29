#ifndef Master_H
#define Master_H


#include "../RobotState.h"
void masterControl(struct RobotState * robotState);

void updateCell(struct RobotState * robotState);

void headToNextCell(struct RobotState * robotState);

void headToDarkness(struct RobotState * robotState);



struct Instruction * gotoDarkest(struct RobotState * robotState, struct Cell * curCell, int orientation, struct Cell **path);


//



#endif /* !Master_H*/