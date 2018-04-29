#include "../lib/allcode_api.h"
#include "../RobotState.h"
#include "../input/Location.h"

void calibrateSpeed(struct RobotState * robotState) {
	int LSpeed = robotState->LSpeed;
	int LEncoder = FA_ReadEncoder(CHANNEL_LEFT);
	int REncoder = FA_ReadEncoder(CHANNEL_RIGHT);
	if( LEncoder > REncoder){
		LSpeed--;
		if(LSpeed < 0){
			LSpeed = 30;
		}
	} else if(LEncoder < REncoder){
		LSpeed++;
		if(LSpeed > 100){
			LSpeed = 30;
		}
	}
	robotState->LSpeed = LSpeed;
	robotState->next = getLocation;	
}