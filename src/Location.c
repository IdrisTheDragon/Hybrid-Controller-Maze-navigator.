#include "lib/allcode_api.h"
#include <math.h>
#include "Location.h"

void printLocation(struct Location location){
	FA_LCDClear();
    FA_LCDNumber(location.rightDistance, 		0 , 12, FONT_NORMAL, LCD_OPAQUE);
    FA_LCDNumber(location.rearRightDistance, 	0 , 1 , FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location.rearDistance, 		40, 1 , FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location.rearLeftDistance, 	80, 1 , FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location.leftDistance, 		80, 12, FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location.frontLeftDistance, 	80, 20, FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location.frontDistance, 		40, 20, FONT_NORMAL, LCD_OPAQUE);
	FA_LCDNumber(location.frontRightDistance, 	0 , 20, FONT_NORMAL, LCD_OPAQUE);
	FA_DelayMillis(100);
}

void getLocation(struct RobotState * robotState) {
	struct Location location;
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
	/**
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
	/**/
	//BLACK
	//double M = -198.057;
	//double C = 110.046;
	//WHITE
	double M = -279.159;
	double C = 163.882;
	location.leftDistance = 		log10(log10(IRDataAverage[IR_LEFT])) 	* M + C;
	location.frontLeftDistance = 	log10(log10(IRDataAverage[IR_FRONT_LEFT])) 	* M + C;
	location.frontDistance = 		log10(log10(IRDataAverage[IR_FRONT])) 	* M + C;
	location.frontRightDistance = 	log10(log10(IRDataAverage[IR_FRONT_RIGHT]))	* M + C;
	location.rightDistance = 		log10(log10(IRDataAverage[IR_RIGHT])) 	* M + C;
	location.rearRightDistance = 	log10(log10(IRDataAverage[IR_REAR_RIGHT])) 	* M + C;
	location.rearDistance = 		log10(log10(IRDataAverage[IR_REAR])) 	* M + C;
	location.rearLeftDistance = 	log10(log10(IRDataAverage[IR_REAR_LEFT])) 	* M + C;
	robotState->location = &location;
	robotState->next = detectObstacle;
}