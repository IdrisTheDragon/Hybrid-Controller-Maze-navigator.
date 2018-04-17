#include "../lib/allcode_api.h"

#include <math.h>
#include "Location.h"
#include "Light.h"

//#define debug

//BLACK
#define Mb -198.057
#define Cb 110.046
//WHITE
#define Mw -279.159
#define Cw 163.882
//Averge
#define M ((Mw+Mb)/2)
#define C ((Cw+Cb)/2)

void printLocation(struct Location * location){
	FA_LCDClear();
    FA_LCDNumber(location->rightDistance, 		0 , 12, FONT_NORMAL, LCD_OPAQUE);
    FA_LCDNumber(location->rearRightDistance, 	0 , 1 , FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location->rearDistance, 		40, 1 , FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location->rearLeftDistance, 	80, 1 , FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location->leftDistance, 		80, 12, FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location->frontLeftDistance, 	80, 20, FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location->frontDistance, 		40, 20, FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location->frontRightDistance, 	0 , 20, FONT_NORMAL, LCD_OPAQUE);
	FA_DelayMillis(5);
}

void getLocation(struct RobotState * robotState) {
	struct Location * location = robotState->location;
	double IRDataSum[8] = {0,0,0,0,0,0,0,0};
	int j;
	for ( j =0; j < 10; j++) {
		int i;
		for (i = 0; i < 8; i++) {
			IRDataSum[i] = IRDataSum[i] + FA_ReadIR(i);	
		}
	}
	double IRDataAverage[8];
	int i;
	for (i = 0; i < 8; i++) {
		IRDataAverage[i] = IRDataSum[i]/10.0;
		if (IRDataAverage[i] > 600) {
			FA_LEDOn(i);
		} else {
			FA_LEDOff(i);
		}
	}
	#ifdef debug
	FA_LCDClear();
    FA_LCDNumber(IRDataAverage[IR_RIGHT], 		0 , 12, FONT_NORMAL, LCD_OPAQUE);
    FA_LCDNumber(IRDataAverage[IR_REAR_RIGHT], 	0 , 1 , FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(IRDataAverage[IR_REAR], 		40, 1 , FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(IRDataAverage[IR_REAR_LEFT], 	80, 1 , FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(IRDataAverage[IR_LEFT], 		80, 12, FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(IRDataAverage[IR_FRONT_LEFT], 	80, 20, FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(IRDataAverage[IR_FRONT], 		40, 20, FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(IRDataAverage[IR_FRONT_RIGHT], 0 , 20, FONT_NORMAL, LCD_OPAQUE);
	FA_DelayMillis(100);
	#endif
	//calculate an approximate distance form the robot.
	//if formula breaks and returns -1 assume there isn't anything.
	location->leftDistance = 		log10(log10(IRDataAverage[IR_LEFT])) 	* M + C;
	if(location->leftDistance == -1) location->leftDistance = 200;
	location->frontLeftDistance = 	log10(log10(IRDataAverage[IR_FRONT_LEFT])) 	* M + C;
	if(location->frontLeftDistance == -1) location->frontLeftDistance = 200;
	location->frontDistance = 		log10(log10(IRDataAverage[IR_FRONT])) 	* M + C;
	if(location->frontDistance == -1) location->frontDistance = 200;
	location->frontRightDistance = 	log10(log10(IRDataAverage[IR_FRONT_RIGHT]))	* M + C;
	if(location->frontRightDistance == -1) location->frontRightDistance = 200;
	location->rightDistance = 		log10(log10(IRDataAverage[IR_RIGHT])) 	* M + C;
	if(location->rightDistance == -1) location->rightDistance = 200;
	location->rearRightDistance = 	log10(log10(IRDataAverage[IR_REAR_RIGHT])) 	* M + C;
	if(location->rearRightDistance == -1) location->rearRightDistance = 200;
	location->rearDistance = 		log10(log10(IRDataAverage[IR_REAR])) 	* M + C;
	if(location->rearDistance == -1) location->rearDistance = 200;
	location->rearLeftDistance = 	log10(log10(IRDataAverage[IR_REAR_LEFT])) 	* M + C;
	if(location->rearLeftDistance == -1) location->rearLeftDistance = 200;
	printLocation(location);
	robotState->next = getLight;
}