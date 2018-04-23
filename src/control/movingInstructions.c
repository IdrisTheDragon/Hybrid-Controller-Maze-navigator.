#include "../RobotState.h"
#include "movingInstructions.h"
#include "../output/setMotors.h"
#include "../lib/allcode_api.h"
#include <stdlib.h>

#define CM15 425
#define TURNDURATION 156
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
        if((robotState->orientation+1)%4 == direction) turnRight(direction,robotState);
        else turnLeft(direction,robotState); 
    else {
        if(goneForward != true){
            foreward(robotState);
        } else {
            //FA_DelaySecs(1); //big delay after each movement so chance to correct robot.
            //must be done go to next instruction
            struct Instruction * i = robotState->instruction;
            robotState->instruction = robotState->instruction->nextInstruction;
            free(i);
            goneForward = false;
        }
    }
}



void turnRight(int orientation, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;
    //FA_BTSendString ("TurnA\n", 7);
    if(L> TURNDURATION && R > TURNDURATION ){
        FA_SetMotors(0,0);
        FA_DelayMillis(100);
        while(L > TURNDURATION + 10 && R > TURNDURATION + 10){
            FA_SetDriveSpeed(20);
            FA_Left(3);
            L = FA_ReadEncoder(CHANNEL_LEFT);
            R = FA_ReadEncoder(CHANNEL_RIGHT);
            char message[30];
            sprintf(message,"L_%d_R_%d\n",
                L,
                R
            );
            FA_BTSendString(message,30);
        }
        while(L < TURNDURATION + 10 && R < TURNDURATION + 10 && L > TURNDURATION && R > TURNDURATION){
            FA_SetDriveSpeed(20);
            FA_Right(3);
            L = FA_ReadEncoder(CHANNEL_LEFT);
            R = FA_ReadEncoder(CHANNEL_RIGHT);
        }
        int i = (robotState->orientation + 1)%4;
        robotState->orientation = i;
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
    } else {
        robotState->LSpeed = INITIALL + (robotState->REncoders - robotState->LEncoders);
        robotState->RSpeed = -INITIALR - (robotState->LEncoders - robotState->REncoders);
    }
}

void turnLeft(int orientation, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;
    //FA_BTSendString ("Turn\n", 6);
    if(L > TURNDURATION && R > TURNDURATION ){
        FA_SetMotors(0,0);
        FA_DelayMillis(100);
        while(L > TURNDURATION + 10 && R > TURNDURATION + 10){
            FA_SetDriveSpeed(20);
            FA_Right(3);
            L = FA_ReadEncoder(CHANNEL_LEFT);
            R = FA_ReadEncoder(CHANNEL_RIGHT);
        }
        while(L < TURNDURATION + 10 && R < TURNDURATION + 10 && L > TURNDURATION && R > TURNDURATION){
            FA_SetDriveSpeed(20);
            FA_Left(3);
            L = FA_ReadEncoder(CHANNEL_LEFT);
            R = FA_ReadEncoder(CHANNEL_RIGHT);
        }
        int i = robotState->orientation - 1;
        if(i <0){
            i=3;
        }
        robotState->orientation = i;
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
    } else {
        robotState->LSpeed = -INITIALL - (robotState->REncoders - robotState->LEncoders);
        robotState->RSpeed = INITIALR + (robotState->LEncoders - robotState->REncoders);
    }
}

void foreward(struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;
    //FA_BTSendString ("foreward\n", 10);
    if( robotState->location->frontDistance < 40 || (L > CM15 && R > CM15) ){ //go for a set distance
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
        goneForward = true;
    } else {
        if(robotState->LSpeed == 0){
            robotState->LSpeed =  INITIALL;
            robotState->RSpeed =  INITIALR;
        } else {
            //Go in a straight line.
            if (robotState->location->frontDistance > 40) { 
                if (robotState->location->leftDistance < 30)             robotState->RSpeed = INITIALR - 6; 
                else if(robotState->location->frontLeftDistance < 35)    robotState->RSpeed = INITIALR - 10; 
                else                                                     robotState->RSpeed = INITIALR;

                if (robotState->location->rightDistance < 30)            robotState->LSpeed = INITIALL - 6; 
                else if (robotState->location->frontRightDistance < 35)  robotState->LSpeed = INITIALL - 10;
                else                                                     robotState->LSpeed = INITIALL;
            }
            robotState->RSpeed = robotState->RSpeed + robotState->LEncoders - robotState->REncoders;
        }  
    }
}

