#ifndef Location_H
#define Location_H

struct Location {
	int leftDistance;
	int frontLeftDistance;
	int frontDistance;
	int frontRightDistance;
	int rightDistance;
	int rearRightDistance;
	int rearDistance;
	int rearLeftDistance;
};

typedef struct Location Location;

void printLocation(struct Location);

#include "RobotState.h"
void getLocation(struct RobotState * robotState);

#endif /* !Location_H*/