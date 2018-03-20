#include "../RobotState.h"
#include "../lib/allcode_api.h"
#include "../input/Location.h"
#include <stdio.h>

void blue(struct RobotState * robotState){
    if(FA_BTConnected () == 1){
        int bytes = FA_BTAvailable ();
        if(bytes > 0){
            char * string[50];
            char input;
            int i;
            for(i =0; i <bytes; i++){
                input = FA_BTGetByte ();
                string[i] = input;
            }
            FA_BTSendString (string, bytes);
        }    
    }
}

void broadcastLocation(struct RobotState * robotState){
    if(FA_BTConnected () == 1){
        char string[50];
        sprintf(string,"SR_%d_%d_%d_%d_%d_%d_%d_%d\n",
            robotState->location->frontLeftDistance,
            robotState->location->frontDistance,
            robotState->location->frontRightDistance,
            robotState->location->rightDistance,
            robotState->location->rearRightDistance,
            robotState->location->rearDistance,
            robotState->location->rearLeftDistance,
            robotState->location->leftDistance
        );
        FA_BTSendString (string, 50);
    }
    FA_DelaySecs(2);
    robotState->next = getLocation;
}