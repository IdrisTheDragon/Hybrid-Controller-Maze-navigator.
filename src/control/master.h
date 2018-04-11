#ifndef Master_H
#define Master_H


#include "../RobotState.h"
void masterControl(struct RobotState * robotState);

void updateCell(struct RobotState * robotState);

void headToNextCell(struct RobotState * robotState);

void headToDarkness(struct RobotState * robotState);



struct Instruction * gotoDarkest(struct RobotState * robotState, struct Cell * curCell, int orientation, struct Cell **path);
struct Instruction * searchCells(struct RobotState * robotState, struct Cell * curCell, int orientation);


//
struct Instruction * westCheck(struct RobotState * robotState, struct Cell * curCell, int orientation);
struct Instruction * northCheck(struct RobotState * robotState, struct Cell * curCell, int orientation);
struct Instruction * eastCheck(struct RobotState * robotState, struct Cell * curCell, int orientation);
struct Instruction * southCheck(struct RobotState * robotState, struct Cell * curCell, int orientation);


#endif /* !Master_H*/