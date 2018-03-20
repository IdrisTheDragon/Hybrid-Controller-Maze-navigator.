#include "../RobotState.h"
#include "../lib/allcode_api.h"
#include "../output/setMotors.h"
#include <stdio.h>

unsigned long time;
unsigned long prevTime = 0;
void broadcastLocation(struct RobotState * robotState){
    time = FA_ClockMS();
    if(time - prevTime > 1000){
        prevTime = time;
        if(FA_BTConnected () == 1){
        char message[100];
        sprintf(message,"SR_%d_%d_%d_%d_%d_%d_%d_%d\nSL_%d\nSE_%d_%d\n",
            robotState->location->frontLeftDistance,
            robotState->location->frontDistance,
            robotState->location->frontRightDistance,
            robotState->location->rightDistance,
            robotState->location->rearRightDistance,
            robotState->location->rearDistance,
            robotState->location->rearLeftDistance,
            robotState->location->leftDistance,
            robotState->LDR,
            robotState->LEncoders,
            robotState->REncoders
        );
        FA_BTSendString (message, 100);
    }
    }
    robotState->next = setMotors;
}