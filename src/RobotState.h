#ifndef RobotState_H
#define RobotState_H

struct RobotState;
struct Instruction;

typedef struct Instruction Instruction;
typedef struct RobotState RobotState;
typedef void state_fn(struct RobotState *);

#include "input/Location.h"
#include "Cell.h"


#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

struct Instruction {
	struct Instruction * nextInstruction;
	state_fn * next;
} __attribute__ ((packed));

struct RobotState {
	int LSpeed;
	int RSpeed;
	int LEncoders;
	int REncoders;
	int prevREncoder;
	int prevLEncoder;
	int LDR;
	int orientation;
	int cellsVisited;
	struct Instruction * instruction;
	struct Cell * curCell;
	struct Cell * nest;
	struct Location * location;
	state_fn * next;
} __attribute__ ((packed));

#endif /* RobotState_H*/