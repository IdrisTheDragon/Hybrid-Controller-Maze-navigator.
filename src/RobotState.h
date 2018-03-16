#ifndef RobotState_H
#define RobotState_H

struct RobotState;
typedef struct RobotState RobotState;
typedef void state_fn(struct RobotState *);

#include "input/Location.h"
#include "Cell.h"


#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

struct RobotState {
	int LSpeed;
	int RSpeed;
	int LEncoders[10];
	int REncoders[10];
	int LDR;
	int orientation;
	struct Cell * curCell;
	struct Location * location;
	state_fn * next;
};

#endif /* RobotState_H*/