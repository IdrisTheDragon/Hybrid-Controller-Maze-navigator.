#ifndef RobotState_H
#define RobotState_H

struct RobotState;
typedef struct RobotState RobotState;
typedef void state_fn(struct RobotState *);

#include "input/Location.h"

struct RobotState {
	int LSpeed;
	int RSpeed;
	struct Location * location;
	state_fn * next;
};

#endif /* RobotState_H*/