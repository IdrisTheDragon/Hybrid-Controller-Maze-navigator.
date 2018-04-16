#include "../RobotState.h"
#include "movingInstructions.h"
#include "../output/setMotors.h"
#include "../lib/allcode_api.h"
#include "stdlib.h"

#define CM15 (140*3) 
#define TURNDURATION 155

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
        if((robotState->orientation+1)%4 == direction) turnA(direction,robotState);
        else turn(direction,robotState); 
    else {
        if(goneForward != true){
            foreward(robotState);
        } else {
            FA_DelaySecs(1);
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
    FA_BTSendString ("Turn\n", 6);
    if(L - robotState->prevLEncoder > TURNDURATION && R - robotState->prevREncoder > TURNDURATION ){
        int i = (robotState->orientation + 1)%4;
        robotState->orientation = i;
        robotState->prevLEncoder = 0;
        robotState->prevREncoder = 0;
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
    } else {
        robotState->LSpeed = 30;
        robotState->RSpeed = -30;
    }
}

void turn(int orientation, struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;
    FA_BTSendString ("Turn\n", 6);
    if(L > TURNDURATION && R > TURNDURATION ){
        int i = robotState->orientation - 1;
        if(i <0){
            i=3;
        }
        robotState->orientation = i;
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
    } else {
        robotState->LSpeed = -30;
        robotState->RSpeed = 35;
    }
}

void foreward(struct RobotState * robotState){
    int L = robotState->LEncoders;
    int R = robotState->REncoders;
    FA_BTSendString ("foreward\n", 10);
    if( robotState->location->frontDistance < 30 || (L > CM15 && R > CM15) ){
        robotState->LSpeed = 0;
        robotState->RSpeed = 0;
        goneForward = true;
    } else {
        if(robotState->LSpeed == 0){
            robotState->LSpeed = 30;
            robotState->RSpeed = 35;
        } else {
            //Go in a straight line.
            if(robotState->LEncoders < robotState->REncoders){
                robotState->RSpeed = robotState->RSpeed +  3;
            } else if(robotState->LEncoders > robotState->REncoders) {
                robotState->RSpeed = robotState->RSpeed - 3;
            }
            /**
            int Lline = FA_ReadLine(CHANNEL_LEFT);
            int Rline = FA_ReadLine(CHANNEL_RIGHT);
            char message[30];
            sprintf(message,"L_%d_%d\n",
                Lline,Rline
            );
            FA_BTSendString(message,30);
            if(Lline < 100 && Lline > Rline ){
                robotState->LSpeed = robotState->LSpeed - 3;
            } else if (Rline < 100 && Lline < Rline) {
                robotState->LSpeed = robotState->LSpeed + 3;
            }
            /**/
        }  
    }
}

