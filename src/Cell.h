#ifndef Cell_H
#define Cell_H




struct Cell;
struct HWall;
struct VWall;
typedef struct HWall HWall;
typedef struct VWall VWall;
typedef struct Cell Cell;

struct Cell {
	int visited;
	int x;
	int y;
	struct HWall * wallNorth;
	struct HWall * wallSouth;
	struct VWall * wallEast;
	struct VWall * wallWest;
	int lightLevel;
} __attribute__ ((packed));


struct VWall {
	int wallExists;
	int stripeExists;
	struct Cell * eastCell;
	struct Cell * westCell;
} __attribute__ ((packed));

struct HWall {
	int wallExists;
	int stripeExists;
	struct Cell * northCell;
	struct Cell * southCell;
} __attribute__ ((packed));

#endif /* RobotState_H*/