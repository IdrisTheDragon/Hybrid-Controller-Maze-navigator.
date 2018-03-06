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