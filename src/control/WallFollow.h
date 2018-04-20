#ifndef WallFollow_H
#define WallFollow_H


struct Instruction * searchCells(struct RobotState * robotState, struct Cell * curCell, int orientation);

struct Instruction * westCheck(struct RobotState * robotState, struct Cell * curCell, int orientation);
struct Instruction * northCheck(struct RobotState * robotState, struct Cell * curCell, int orientation);
struct Instruction * eastCheck(struct RobotState * robotState, struct Cell * curCell, int orientation);
struct Instruction * southCheck(struct RobotState * robotState, struct Cell * curCell, int orientation);

#endif /* WallFollow_H*/