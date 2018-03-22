#include "../RobotState.h"
#include "movingInstructions.h"
#include "../output/bluetooth.h"
#include "../lib/allcode_api.h"

int flag = false;
void gotoCellWest(struct RobotState * robotState){
    //turn the robot to west and drive forward
    FA_BTSendString ("WestAction\n", 12);
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
    FA_BTSendString ("NorthAction\n", 13);
    if(robotState->orientation != NORTH){
        turn(NORTH,robotState);
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

void gotoCellEast(struct RobotState * robotState){
    //turn the robot to East and drive foreward
    FA_BTSendString ("EASTAction\n", 12);
    if(robotState->orientation != EAST){
        turn(EAST,robotState);
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

void gotoCellSouth(struct RobotState * robotState){
    //turn the robot south and drive foreward
    FA_BTSendString ("SouthAction\n", 13);
    if(robotState->orientation != SOUTH){
        turn(SOUTH,robotState);
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

void turn(int orientation, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;

    if(L - robotState->prevLEncoder > 20 && R - robotState->prevREncoder > 20 ){
        robotState->orientation = (robotState->orientation + 1) % 4;
        robotState->prevLEncoder = L;
        robotState->prevREncoder = R;
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
        flag = true;
        FA_ResetEncoders();
    } else {
        robotState->LSpeed = -15;
        robotState->RSpeed = 15;
    }
}

void foreward(int distance, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;

    if(L - robotState->prevLEncoder > distance*10*3 && R - robotState->prevREncoder >distance*10*3 ){
        robotState->orientation = (robotState->orientation + 1) % 4;
        robotState->prevLEncoder = L;
        robotState->prevREncoder = R;
        flag=false;
    } else {
        robotState->LSpeed = 20;
        robotState->RSpeed = 20;
    }
}

