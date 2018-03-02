#include "allcode_api.h"
#include "Location.h"

struct RobotState {
	int LSpeed;
	int RSpeed;
	struct Location location;
};


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

void basicObstacleAvoidence(int LSpeed, int RSpeed){
	// Go forward
    FA_SetMotors(LSpeed,RSpeed);
	LSpeed = calibrateSpeed(LSpeed);
		
	if(FA_ReadIR(1) > 600 || FA_ReadIR(2) > 600){  // check front left ir & check front ir
		FA_Backwards(50);
        FA_Right(30);      
    }
	if(FA_ReadIR(3) > 600){  // check front right ir
		FA_Backwards(50);
        FA_Left(30);      
    }
}

int encoderPower(int Speed){
	if(FA_ReadSwitch1Debounced()){
		FA_DelayMillis(1000);
		FA_LCDClear();
		FA_SetMotors(Speed,Speed);
		FA_LCDNumber(Speed, 0 , 1, FONT_NORMAL, LCD_OPAQUE);
		FA_DelayMillis(Speed*50+200);
		int i;
		for(i = 0; i < 5; i++){
			FA_ResetEncoders();
			FA_DelayMillis(1000);
			FA_LCDNumber(FA_ReadEncoder(CHANNEL_RIGHT), i*25 , 12, FONT_NORMAL, LCD_OPAQUE);
			FA_LCDNumber(FA_ReadEncoder(CHANNEL_LEFT), i*25 , 20, FONT_NORMAL, LCD_OPAQUE);
		}
		FA_DelayMillis(10);
		FA_SetMotors(0,0);
	}
		
	if(FA_ReadSwitch0Debounced()){
		Speed = Speed + 10;
		FA_LCDNumber(Speed, 40 , 1, FONT_NORMAL, LCD_OPAQUE);
		FA_DelayMillis(500);
	}
	return Speed;
}

// 0 = front 1 left 2 back 3 right
//-1 infinity/out of range
bool detectObstactle(struct Location location,int side, int distance){
	bool sum;
	switch(side){
		case 0:
			if(location.frontDistance!= -1){
				sum = location.frontDistance < distance;
			} 
			if(location.frontRightDistance!= -1){
				sum = sum || location.frontRightDistance < distance;
			} 
			if(location.frontLeftDistance!= -1){
				sum = sum || location.frontLeftDistance < distance;
			} 
			return sum;
			break;
		case 1:
			if(location.leftDistance!= -1){
				sum = location.leftDistance < distance;
			} 
			if(location.frontLeftDistance!= -1){
				sum = sum || location.frontLeftDistance < distance;
			} 
			if(location.rearLeftDistance!= -1){
				sum = sum || location.rearLeftDistance < distance;
			} 
			return sum;
			break;
		case 2:
			if(location.rearDistance!= -1){
				sum = location.rearDistance < distance;
			} 
			if(location.rearLeftDistance!= -1){
				sum = sum || location.rearLeftDistance < distance;
			} 
			if(location.rearRightDistance!= -1){
				sum = sum || location.rearRightDistance < distance;
			} 
			return sum;
			break;
		case 3:
			if(location.rightDistance!= -1){
				sum = location.rightDistance < distance;
			} 
			if(location.frontRightDistance!= -1){
				sum = sum || location.frontRightDistance < distance;
			} 
			if(location.rearLeftDistance!= -1){
				sum = sum || location.rearRightDistance < distance;
			} 
			return sum;
			break;
		default:
			return false;
			break;
	}
}

int curState = 0;
int prevState = 0;

void updateState(int newState){
	prevState = curState;
	curState = newState;
}

int main(){
	FA_RobotInit();
    
    FA_LCDBacklight(50);
	
	int Speed = 0;
	struct RobotState robot;
	robot.RSpeed = 30;
	robot.LSpeed = 30;
	
    while(1){  
	FA_LCDClear();
	//Speed = encoderPower(Speed);
	int i;
	switch(curState){
		case 0:
			robot.location = getLocation();
			printLocation(robot.location);
			updateState(1);
		case 1:
			//check for obstacle
			if(detectObstactle(robot.location,0,30)){
				updateState(3);
			} else {
				updateState(4);
			};
			break;
		case 2:
			FA_SetMotors(robot.LSpeed,robot.RSpeed);
			if(prevState == 3 ){
				updateState(5);
			} else {
				updateState(0);
			}
			break;
		case 3:
			robot.LSpeed = 0;
			robot.RSpeed = 0;
			updateState(2);
			break;
		case 4:
			i = robot.LSpeed;
			i = calibrateSpeed(i);
			robot.LSpeed = i;
			updateState(2);
			break;
		case 5:
			return 0;
			break;
		default:
			break;
	}
    }            
 	
}



