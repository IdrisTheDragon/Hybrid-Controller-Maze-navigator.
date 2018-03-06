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