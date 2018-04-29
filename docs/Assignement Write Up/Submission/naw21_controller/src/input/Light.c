#include "../lib/allcode_api.h"
#include "Light.h"
#include "Encoders.h"

void getLight(struct RobotState * robotState){
	robotState->LDR = FA_ReadLight();
	robotState->next = getEncoders;
}