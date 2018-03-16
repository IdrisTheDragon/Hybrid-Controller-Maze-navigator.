#include "../lib/allcode_api.h"
#include "Light.h"
#include "../control/ObstacleDetection.h"

void getEncoders(struct RobotState * robotState){
	int i;
	
	for(i = 9; i > 0; i--){
		robotState->LEncoders[i] = robotState->LEncoders[i-1];
		robotState->REncoders[i] = robotState->REncoders[i-1];
	}
	robotState->REncoders[0] = FA_ReadEncoder(CHANNEL_RIGHT);
	robotState->LEncoders[0] = FA_ReadEncoder(CHANNEL_LEFT);
	robotState->next = detectObstactle;
}