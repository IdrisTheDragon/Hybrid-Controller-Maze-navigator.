#include "../lib/allcode_api.h"
#include "Encoders.h"
#include "../output/bluetooth.h"

void getEncoders(struct RobotState * robotState){
	robotState->LEncoders = FA_ReadEncoder(CHANNEL_RIGHT);
	robotState->REncoders = FA_ReadEncoder(CHANNEL_LEFT);
	robotState->next = broadcastLocation;
}