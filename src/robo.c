#include "lib/allcode_api.h"
#include "input/Location.h"
#include "RobotState.h"

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



