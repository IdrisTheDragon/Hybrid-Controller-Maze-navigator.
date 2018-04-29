#include "../RobotState.h"
#include "../lib/allcode_api.h"
#include "../control/master.h"
#include <stdio.h>

unsigned long time;
unsigned long prevTime = 0;
void broadcastLocation(struct RobotState * robotState){
    /**
    time = FA_ClockMS();
    if(time - prevTime > 100){
        prevTime = time;
        
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
        FA_DelayMillis(2);
        sprintf(message,"SL_%d\nSE_%d_%d\n",
            robotState->LDR,
            robotState->LEncoders,
            robotState->REncoders
        );
        FA_BTSendString (message, 50);
        FA_DelayMillis(2);
    }
    /**/
    robotState->next = masterControl;
}

void broadcastCell(struct RobotState * robotState){
    if(FA_BTConnected()== 1){
        char message[50];
        int n = 0;
        int s = 0;
        int w = 0;
        int e = 0;
        if(robotState->curCell->wallNorth != NULL){
            n = robotState->curCell->wallNorth->wallExists;
        }
        if(robotState->curCell->wallSouth != NULL){
            s = robotState->curCell->wallSouth->wallExists;
        }
        if(robotState->curCell->wallWest != NULL){
            w = robotState->curCell->wallWest->wallExists;
        }
        if(robotState->curCell->wallEast != NULL){
            e = robotState->curCell->wallEast->wallExists;
        }


        sprintf(message,"C_%d_%d_%d_%d_%d_%d_%d\n",
            robotState->curCell->x,
            robotState->curCell->y,
            robotState->curCell->lightLevel,
            n,
            s,
            e,
            w
        );
        FA_BTSendString (message, 50);
    }
    robotState->next = getLocation;
}