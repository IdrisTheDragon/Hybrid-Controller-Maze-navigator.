#include "../RobotState.h"
#include "../lib/allcode_api.h"
#include "../output/setMotors.h"
#include "../control/master.h"
#include <stdio.h>

unsigned long time;
unsigned long prevTime = 0;
void broadcastLocation(struct RobotState * robotState){
    time = FA_ClockMS();
    if(time - prevTime > 50){
        prevTime = time;
        if(FA_BTConnected()== 1){
        char message[50];
        sprintf(message,"SR_%d_%d_%d_%d_%d_%d_%d_%d\n",
            robotState->location->frontLeftDistance,
            robotState->location->frontDistance,
            robotState->location->frontRightDistance,
            robotState->location->rightDistance,
            robotState->location->rearRightDistance,
            robotState->location->rearDistance,
            robotState->location->rearLeftDistance,
            robotState->location->leftDistance 
        );
        FA_BTSendString (message, 50);
        FA_DelayMillis(10);
        sprintf(message,"SL_%d\nSE_%d_%d\n",
            robotState->LDR,
            robotState->LEncoders,
            robotState->REncoders
        );
        FA_BTSendString (message, 50);
        FA_DelayMillis(10);
    }
    }
    robotState->next = setMotors;
}

void broadcastCell(struct RobotState * robotState){
    if(FA_BTConnected()== 1){
        char message[50];
        sprintf(message,"C_%d_%d_%d_%d_%d\n",
            robotState->curCell->lightLevel,
            robotState->curCell->wallNorth,
            robotState->curCell->wallSouth,
            robotState->curCell->wallEast,
            robotState->curCell->wallWest
        );
        FA_BTSendString (message, 50);
        FA_DelayMillis(10);
    }
    robotState->next = headToNextCell;
}