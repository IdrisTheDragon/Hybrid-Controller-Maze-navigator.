#include "../lib/allcode_api.h"
#include "../RobotState.h"
#include "RobotCalibrate.h"

void basicObstacleAvoidence(int LSpeed, int RSpeed){
	// Go forward
    FA_SetMotors(LSpeed,RSpeed);
	//LSpeed = calibrateSpeed(LSpeed);
		
	if(FA_ReadIR(1) > 600 || FA_ReadIR(2) > 600){  // check front left ir & check front ir
		FA_Backwards(50);
        FA_Right(30);      
    }
	if(FA_ReadIR(3) > 600){  // check front right ir
		FA_Backwards(50);
        FA_Left(30);      
    }
}


void detectObstactle(struct RobotState * robotState){
	if(robotState->location->frontDistance < 40){
		robotState->next = getLocation;
	} else if (robotState->location->leftDistance < 40){
		robotState->next = getLocation;
	} else {
		robotState->next = getLocation;
	}
}