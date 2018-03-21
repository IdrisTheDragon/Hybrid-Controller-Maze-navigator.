#include "../RobotState.h"
#include "movingInstructions.h"
#include "../output/bluetooth.h"
#include "../lib/allcode_api.h"

int flag = false;
void gotoCellWest(struct RobotState * robotState){
    //turn the robot to west and drive forward
    FA_BTSendString ("WestAction\n", 12);
    FA_DelayMillis(30);
    if(robotState->orientation != WEST){
        turn(WEST,robotState);
        robotState->next = broadcastLocation;
    } else if (flag == true){
        //
        foreward(15,robotState);
        robotState->next = broadcastLocation;
    } else {
        //must be done go to next instruction
        robotState->instruction = robotState->instruction->nextInstruction;
    }
}

void gotoCellNorth(struct RobotState * robotState){
    //turn the robot to North and drive foreward
}

void gotoCellEast(struct RobotState * robotState){
    //turn the robot to East and drive foreward
}

void gotoCellSouth(struct RobotState * robotState){
    //turn the robot south and drive foreward
}

void turn(int orientation, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;

    if(L - robotState->prevLEncoder > 500 && R - robotState->prevREncoder > 500 ){
        robotState->orientation = (robotState->orientation + 1) % 4;
        robotState->prevLEncoder = L;
        robotState->prevREncoder = R;
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
        flag = true;
        FA_ResetEncoders();
    } else {
        robotState->LSpeed = 20;
        robotState->RSpeed = -20;
    }
}

void foreward(int distance, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;

    if(L - robotState->prevLEncoder > ((double)(distance*10))/0.32 && R - robotState->prevREncoder >((double)(distance*10))/0.32 ){
        robotState->orientation = (robotState->orientation + 1) % 4;
        robotState->prevLEncoder = L;
        robotState->prevREncoder = R;
        flag=false;
    } else {
        robotState->LSpeed = 20;
        robotState->RSpeed = 20;
    }
}

