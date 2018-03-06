#include "../lib/allcode_api.h"
int calibrateSpeed(int LSpeed) {
	int LEncoder = FA_ReadEncoder(CHANNEL_LEFT);
	int REncoder = FA_ReadEncoder(CHANNEL_RIGHT);
	if( LEncoder > REncoder){
		LSpeed--;
		if(LSpeed < 0){
			LSpeed = 30;
		}
		FA_ResetEncoders ();
		return LSpeed;
	} else if(LEncoder < REncoder){
		LSpeed++;
		if(LSpeed > 100){
			LSpeed = 30;
		}
		FA_ResetEncoders ();
		return LSpeed;
	} else {
		return LSpeed;
	}	
}