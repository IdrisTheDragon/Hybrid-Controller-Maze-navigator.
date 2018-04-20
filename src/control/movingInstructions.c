#include "../RobotState.h"
#include "movingInstructions.h"
#include "../output/setMotors.h"
#include "../lib/allcode_api.h"
#include "stdlib.h"

#define CM15 432
#define TURNDURATION 155
#define INITIALL 30
#define INITIALR 35

int goneForward = false;

void gotoCellWest(struct RobotState * robotState){
    //turn the robot to west and drive forward
    //FA_BTSendString ("WestAction\n", 12);
    turnThenStraight(WEST,robotState);
    robotState->next = setMotors;
}

void gotoCellNorth(struct RobotState * robotState){
    //turn the robot to North and drive foreward
    //FA_BTSendString ("NorthAction\n", 13);
    turnThenStraight(NORTH,robotState);
    robotState->next = setMotors;
}

void gotoCellEast(struct RobotState * robotState){
    //turn the robot to East and drive foreward
   //FA_BTSendString ("EASTAction\n", 12);
    turnThenStraight(EAST,robotState);
    robotState->next = setMotors;
}

void gotoCellSouth(struct RobotState * robotState){
    //turn the robot south and drive foreward
    //FA_BTSendString ("SouthAction\n", 13);
    turnThenStraight(SOUTH,robotState);
    robotState->next = setMotors;
}

void turnThenStraight(int direction, struct RobotState * robotState){
    if(robotState->orientation != direction) 
        if((robotState->orientation+1)%4 == direction) turnA(direction,robotState);
        else turn(direction,robotState); 
    else {
        if(goneForward != true){
            foreward(robotState);
        } else {
            FA_DelaySecs(1); //big delay after each movement so chance to correct robot.
            //must be done go to next instruction
            struct Instruction * i = robotState->instruction;
            robotState->instruction = robotState->instruction->nextInstruction;
            free(i);
            goneForward = false;
        }
    }
}



void turnA(int orientation, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;
    //FA_BTSendString ("TurnA\n", 7);
    if(L> TURNDURATION && R > TURNDURATION ){
        int i = (robotState->orientation + 1)%4;
        robotState->orientation = i;
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
    } else {
        robotState->LSpeed = INITIALL;
        robotState->RSpeed = -INITIALR - (robotState->REncoders - robotState->LEncoders) ;
    }
}

void turn(int orientation, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;
    //FA_BTSendString ("Turn\n", 6);
    if(L > TURNDURATION && R > TURNDURATION ){
        int i = robotState->orientation - 1;
        if(i <0){
            i=3;
        }
        robotState->orientation = i;
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
    } else {
        robotState->LSpeed = -INITIALL;
        robotState->RSpeed = INITIALR + robotState->REncoders - robotState->LEncoders;
    }
}

void foreward(struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;
    //FA_BTSendString ("foreward\n", 10);
    if( robotState->location->frontDistance < 30 || (L > CM15 && R > CM15) ){
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
        goneForward = true;
    } else {
        if(robotState->LSpeed == 0){
            robotState->LSpeed =  INITIALL;
            robotState->RSpeed =  INITIALR;
        } else {
            //Go in a straight line.
            //if (robotState->location->leftDistance < 30 ) robotState->LSpeed = INITIALL + 2; else robotState->LSpeed = INITIALL;
            //if (robotState->location->rightDistance < 30 ) robotState->RSpeed = INITIALR + 2; else robotState->RSpeed = INITIALR;
            robotState->RSpeed = INITIALR +  robotState->REncoders - robotState->LEncoders;
            /**/
        }  
    }
}

