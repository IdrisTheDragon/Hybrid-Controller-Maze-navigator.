#include "../lib/allcode_api.h"
#include "../output/bluetooth.h"
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
	
	location.leftDistance = 		log10(log10(IRDataAverage[IR_LEFT])) 	* Mw + C;
	location.frontLeftDistance = 	log10(log10(IRDataAverage[IR_FRONT_LEFT])) 	* Mw + C;
	location.frontDistance = 		log10(log10(IRDataAverage[IR_FRONT])) 	* Mw + C;
	location.frontRightDistance = 	log10(log10(IRDataAverage[IR_FRONT_RIGHT]))	* Mw + C;
	location.rightDistance = 		log10(log10(IRDataAverage[IR_RIGHT])) 	* Mw + C;
	location.rearRightDistance = 	log10(log10(IRDataAverage[IR_REAR_RIGHT])) 	* Mw + C;
	location.rearDistance = 		log10(log10(IRDataAverage[IR_REAR])) 	* Mw + C;
	location.rearLeftDistance = 	log10(log10(IRDataAverage[IR_REAR_LEFT])) 	* Mw + C;
	robotState->location = &location;
	robotState->next = outputState;
}