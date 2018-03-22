#ifndef Bluetooth_H
#define Bluetooth_H


#include "../RobotState.h"
void broadcastLocation(struct RobotState * robotState);
void broadcastCell(struct RobotState * robotState);

#endif /* !Bluetooth_H*/