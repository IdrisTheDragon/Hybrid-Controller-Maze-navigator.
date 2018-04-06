#include "../RobotState.h"
#include "movingInstructions.h"
#include "../output/setMotors.h"
#include "../lib/allcode_api.h"
#include "stdlib.h"

int goneForward = false;
void gotoCellWest(struct RobotState * robotState){
    //turn the robot to west and drive forward
    FA_BTSendString ("WestAction\n", 12);
    turnThenStraight(WEST,robotState);
    robotState->next = setMotors;
}

void gotoCellNorth(struct RobotState * robotState){
    //turn the robot to North and drive foreward
    FA_BTSendString ("NorthAction\n", 13);
    turnThenStraight(NORTH,robotState);
    robotState->next = setMotors;
}

void gotoCellEast(struct RobotState * robotState){
    //turn the robot to East and drive foreward
    FA_BTSendString ("EASTAction\n", 12);
    turnThenStraight(EAST,robotState);
    robotState->next = setMotors;
}

void gotoCellSouth(struct RobotState * robotState){
    //turn the robot south and drive foreward
    FA_BTSendString ("SouthAction\n", 13);
    turnThenStraight(SOUTH,robotState);
    robotState->next = setMotors;
}

void turnThenStraight(int direction, struct RobotState * robotState){
    if(robotState->orientation != direction) 
        turn(direction,robotState); 
    else {
        if(goneForward != true){
            foreward(140*3,robotState);
        } else {
            //must be done go to next instruction
            struct Instruction * i = robotState->instruction;
            robotState->instruction = robotState->instruction->nextInstruction;
            free(i);
            goneForward = false;
        }
    }
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
    } else {
        robotState->LSpeed = -30;
        robotState->RSpeed = 30;
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
        goneForward = true;
    } else {
        robotState->LSpeed = 30;
        robotState->RSpeed = 30;
    }
}

