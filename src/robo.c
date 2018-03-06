#include "lib/allcode_api.h"
#include "Location.h"
#include "ObstacleDetection.h"
#include "LightReaction.h"
#include "WallFollow.h"
#include "dataCollect.h"
#include "RobotState.h"
#include "RobotCalibrate.h"

void init(struct RobotState * robotState){
	FA_RobotInit();
	FA_LCDBacklight(50);
	robotState->RSpeed = 30;
	robotState->LSpeed = 30;
	
	robotState->next = getLocation;
}



int main(){
	struct RobotState robotState;
	robotState.next = init;
    while(robotState.next) {
		FA_LCDClear();
		robotState.next(&robotState);
	}	
	return 0;	
}



