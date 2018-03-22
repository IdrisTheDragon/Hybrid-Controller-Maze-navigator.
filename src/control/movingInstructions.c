#include "../RobotState.h"
#include "movingInstructions.h"
#include "../output/setMotors.h"
#include "../lib/allcode_api.h"

int flag = false;
void gotoCellWest(struct RobotState * robotState){
    //turn the robot to west and drive forward
    FA_BTSendString ("WestAction\n", 12);
    if(robotState->orientation != WEST){
        turn(WEST,robotState);
    } else if (flag == true){
        //
        foreward(150*3,robotState);
    } else {
        //must be done go to next instruction
        robotState->instruction = robotState->instruction->nextInstruction;
    }
    robotState->next = setMotors;
}

void gotoCellNorth(struct RobotState * robotState){
    //turn the robot to North and drive foreward
    FA_BTSendString ("NorthAction\n", 13);
    if(robotState->orientation != NORTH){
        turn(NORTH,robotState);
    } else if (flag == true){
        //
        foreward(150*3,robotState);
    } else {
        //must be done go to next instruction
        robotState->instruction = robotState->instruction->nextInstruction;
    }
    robotState->next = setMotors;
}

void gotoCellEast(struct RobotState * robotState){
    //turn the robot to East and drive foreward
    FA_BTSendString ("EASTAction\n", 12);
    if(robotState->orientation != EAST){
        turn(EAST,robotState);
    } else if (flag == true){
        //
        foreward(150*3,robotState);
    } else {
        //must be done go to next instruction
        robotState->instruction = robotState->instruction->nextInstruction;
    }
    robotState->next = setMotors;
}

void gotoCellSouth(struct RobotState * robotState){
    //turn the robot south and drive foreward
    FA_BTSendString ("SouthAction\n", 13);
    if(robotState->orientation != SOUTH){
        turn(SOUTH,robotState);
    } else if (flag == true){
        //
        foreward(150*3,robotState);
    } else {
        //must be done go to next instruction
        robotState->instruction = robotState->instruction->nextInstruction;
    }
    robotState->next = setMotors;
}

void turn(int orientation, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;
    FA_BTSendString ("Turn\n", 6);
    if(L - robotState->prevLEncoder > 100 && R - robotState->prevREncoder > 100 ){
        int i = robotState->orientation - 1;
        if(i <0){
            i=3;
        }
        robotState->orientation = i;
        robotState->prevLEncoder = 0;
        robotState->prevREncoder = 0;
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
        flag = true;
        FA_ResetEncoders();
    } else {
        robotState->LSpeed = -20;
        robotState->RSpeed = 20;
    }
}

void foreward(int distance, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;
    FA_BTSendString ("foreward\n", 10);
    if(L - robotState->prevLEncoder > distance && R - robotState->prevREncoder >distance ){
        robotState->prevLEncoder = 0;
        robotState->prevREncoder = 0;
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
        flag=false;
        FA_ResetEncoders();
    } else {
        robotState->LSpeed = 20;
        robotState->RSpeed = 20;
    }
}

