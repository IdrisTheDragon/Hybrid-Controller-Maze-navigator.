
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

void printLocation(struct Location);
struct Location getLocation();

#endif /* !Location_H*/