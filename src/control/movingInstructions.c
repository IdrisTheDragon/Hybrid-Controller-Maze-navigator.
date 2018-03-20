#include "../RobotState.h"
#include "movingInstructions.h"
#include "../output/bluetooth.h"

void gotoCellWest(struct RobotState * robotState){
    //turn the robot to west and drive forward
    if(robotState->orientation != WEST){
        turn(WEST,robotState);
        robotState->next = broadcastLocation;
    } else if (robotState->prevLEncoder !=0){
        //
        foreward(15,robotState);
        robotState->next = broadcastLocation;
        return;
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

    if(L - robotState->prevLEncoder > 50 && R - robotState->prevREncoder > 50 ){
        robotState->orientation = (robotState->orientation + 1) % 4;
        robotState->prevLEncoder = L;
        robotState->prevREncoder = R;
    } else {
        robotState->LSpeed = 50;
        robotState->RSpeed = -50;
    }
}

void foreward(int distance, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;

    if(L - robotState->prevLEncoder > distance && R - robotState->prevREncoder > distance ){
        robotState->orientation = (robotState->orientation + 1) % 4;
        robotState->prevLEncoder = L;
        robotState->prevREncoder = R;
    } else {
        robotState->LSpeed = 50;
        robotState->RSpeed = 50;
    }
}

