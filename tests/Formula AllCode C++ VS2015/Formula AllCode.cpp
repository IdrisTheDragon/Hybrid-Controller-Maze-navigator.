#include "stdafx.h"
#include "FA_API.h"

int main()
{
	//Create variable to hold COM port number
	//Remember to change this to match your Formula AllCode port number
	char PortNumber = 12;
	
	//Open Port
	FA_ComOpen(PortNumber);

	//Send play Note Command
	FA_PlayNote(PortNumber, 500, 100);
	FA_PlayNote(PortNumber, 100, 100);
	FA_PlayNote(PortNumber, 600, 100);

	//Print a string to the LCD
	FA_LCDClear(PortNumber);
	FA_LCDPrintString(PortNumber, 19, 8, (unsigned char *) "Formula AllCode");
	FA_LCDPrintString(PortNumber, 31, 16, (unsigned char *) "C++ Example");

	//Close Port
	FA_ComClose(PortNumber);

    return 0;
}


