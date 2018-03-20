#include "../RobotState.h"
#include "../lib/allcode_api.h"

void setMotors(struct RobotState * robotState){
    FA_SetMotors(robotState->LSpeed,robotState->RSpeed);
}