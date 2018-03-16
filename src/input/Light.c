#include "../lib/allcode_api.h"
#include "Light.h"
#include "Encoders.h"

void getLight(struct RobotState * robotState){
	int i;
	int sum = 0;
	for(i =0;i<5; i++){
		sum = FA_ReadLight();
	}
	
	robotState->LDR = sum/5;
	
	robotState->next = getEncoders;
}