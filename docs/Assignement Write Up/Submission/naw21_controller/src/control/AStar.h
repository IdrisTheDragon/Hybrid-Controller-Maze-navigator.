#ifndef AStar_H
#define AStar_H

#include "../RobotState.h"

struct Instruction * searchDarkness(struct RobotState * robotState, struct Cell * curCell, int orientation);

struct Instruction * westCheckD(struct RobotState * robotState, struct Cell * curCell, int orientation);
struct Instruction * northCheckD(struct RobotState * robotState, struct Cell * curCell, int orientation);
struct Instruction * eastCheckD(struct RobotState * robotState, struct Cell * curCell, int orientation);
struct Instruction * southCheckD(struct RobotState * robotState, struct Cell * curCell, int orientation);

void stop(struct RobotState * robotState);

#endif /* AStar_H*/