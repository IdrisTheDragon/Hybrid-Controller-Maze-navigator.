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

void outputState(struct RobotState * robotState){
    if(FA_BTConnected () == 1){
        char string[50];
        sprintf(string,"%d_%d_%d\n%d_____%d\n%d_%d_%d\n\n",
            robotState->location->frontLeftDistance,
            robotState->location->frontDistance,
            robotState->location->frontRightDistance,
            robotState->location->leftDistance,
            robotState->location->rightDistance,
            robotState->location->rearLeftDistance,
            robotState->location->rearDistance,
            robotState->location->rearRightDistance
        );
        FA_BTSendString (string, 50);
    }
    FA_DelaySecs(2);
    robotState->next = getLocation;
}