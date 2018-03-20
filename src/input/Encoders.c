#include "../lib/allcode_api.h"
#include "Encoders.h"
#include "../control/master.h"

void getEncoders(struct RobotState * robotState){
	robotState->LEncoders = robotState->LEncoders + FA_ReadEncoder(CHANNEL_RIGHT);;
	robotState->REncoders = robotState->REncoders + FA_ReadEncoder(CHANNEL_LEFT);
	FA_ResetEncoders();
	robotState->next = masterControl;
}