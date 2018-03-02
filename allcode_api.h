#ifndef ALLCODE_API_H
#define	ALLCODE_API_H
/* 
 * File:   allcode_api.h
 * Authors: Pete Todd & Laurence Tyler
 * 
 * Aberystwyth University 2018
 *
 * 2017-11-16   CPDT Created
 * 2018-02-05   LGT Extended, with FA_* naming convention
 * 2018-02-20   LGT Added millisecond clock
 */

#ifdef	__cplusplus
extern "C" {
#endif

#define API_VERSION "1.1"
#define API_VER_MAJOR   1
#define AIP_VER_MINOR   1

// IR Sensors
#define IR_LEFT 0
#define IR_FRONT_LEFT 1
#define IR_FRONT 2
#define IR_FRONT_RIGHT 3
#define IR_RIGHT 4
#define IR_REAR_RIGHT 5
#define IR_REAR 6
#define IR_REAR_LEFT 7

// Fonts for LCD display
#define FONT_NORMAL 0
#define FONT_DOUBLE_WIDTH 1
#define FONT_DOUBLE_WIDTH_HEIGHT 2
#define FONT_DOUBLE_HEIGHT 3

// LCD Printing transparency
#define LCD_OPAQUE 0
#define LCD_TRANSPARENT 1
    
// lCD COLOURS
#define LCD_WHITE 0
#define LCD_BLACK 1

// Channels (left and right, used for line sensors and encoders)
#define CHANNEL_LEFT 0
#define CHANNEL_RIGHT 1    

// Typedefs inserted from PIC16BIT_CAL_TypeDefs.c
// (c) Matrix TSL
#include <stdbool.h>
typedef bool           MX_BOOL;   // Or unsigned char, depending on platform
typedef signed char    MX_SINT8;
typedef signed short   MX_SINT16;
typedef signed long    MX_SINT32;
typedef unsigned char  MX_UINT8;
typedef unsigned short MX_UINT16;
typedef unsigned long  MX_UINT32;
typedef char           MX_CHAR;
typedef unsigned char* MX_STRING; // String pointer
typedef double         MX_FLOAT;  // In BoostC, needs '#define MX_FLOAT float'
typedef MX_UINT16      MX_UINT;   // Best integer value for the platform, at least 8 bit
typedef MX_SINT16      MX_SINT;

#define MX_GLOBAL volatile

// Defined API functions
// For now, these are macros for auto-generated firmware functions
//

/*
 * Master initialisation
 */

void FCD_0dcd1_FormulaAllCode1__Initialise();
#define FA_RobotInit    FCD_0dcd1_FormulaAllCode1__Initialise

/* 
 * Motor control
 */

// Set motor power (0 - 100?)
// Must set both at once. Does not use encoders (raw PWM value)
void FCD_0dcd1_FormulaAllCode1__SetMotors(MX_SINT16 FCL_LEFT, MX_SINT16 FCL_RIGHT);
#define FA_SetMotors    FCD_0dcd1_FormulaAllCode1__SetMotors

// Drive forwards specified distance (mm) using encoders
void FCD_0dcd1_FormulaAllCode1__LogoForwards(MX_UINT16 FCL_DISTANCE);
#define FA_Forwards FCD_0dcd1_FormulaAllCode1__LogoForwards

// Drive backwards specified distance (mm) using encoders
void FCD_0dcd1_FormulaAllCode1__LogoBackwards(MX_UINT16 FCL_DISTANCE);
#define FA_Backwards    FCD_0dcd1_FormulaAllCode1__LogoBackwards

// Turn right through specified angle (degrees) using encoders
void FCD_0dcd1_FormulaAllCode1__LogoTurnRight(MX_UINT16 FCL_ANGLE);
#define FA_Right    FCD_0dcd1_FormulaAllCode1__LogoTurnRight

// Turn left through specified angle (degrees) using encoders
void FCD_0dcd1_FormulaAllCode1__LogoTurnLeft(MX_UINT16 FCL_ANGLE);
#define FA_Left FCD_0dcd1_FormulaAllCode1__LogoTurnLeft

// Set motor speed for 'drive' functions (using encoders)
void FCD_0dcd1_FormulaAllCode1__LogoSetSpeed(MX_UINT8 FCL_SPEED);
#define FA_SetDriveSpeed    FCD_0dcd1_FormulaAllCode1__LogoSetSpeed

/*
 * Wheel encoders
 */

// Read wheel encoder current value
// 1 unit = 0.32 mm of travel
MX_UINT16 FCD_0dcd1_FormulaAllCode1__EncoderReadCount(MX_UINT8 FCL_CHANNEL);
#define FA_ReadEncoder  FCD_0dcd1_FormulaAllCode1__EncoderReadCount

// Reset both wheel encoders to 0
void FCD_0dcd1_FormulaAllCode1__EncoderReset();
#define FA_ResetEncoders FCD_0dcd1_FormulaAllCode1__EncoderReset

/*
 * LCD panel display functions
 */

/*=----------------------------------------------------------------------=*\
   Use :This macro prints a decimal number to the Graphical LCD.
       :
       :Parameters for macro PrintNumber:
       :  Number : Byte or Integer number to send to the display.
       :  X : X pixel coordinate to set the output string position.
       :  Line : Line 0-3
       :  Font : Size of the font - 0 = Normal, 1 = Double Width, 2 = Double Width and Height, 3 = Double Height
       :  Transparent : Specifies if the background of the text is drawn - 0 = Background colour is drawn, 1 = Background colour not drawn.
\*=----------------------------------------------------------------------=*/
void FCD_0ab21_gLCD_ST7567_SPI1__PrintNumber(MX_SINT16 FCL_NUMBER, MX_UINT16 FCL_X, MX_UINT16 FCL_LINE, MX_UINT8 FCL_FONT, MX_UINT8 FCL_TRANSPARENT);
#define FA_LCDNumber    FCD_0ab21_gLCD_ST7567_SPI1__PrintNumber

// Set one pixel to current foreground colour
void FCD_0ab21_gLCD_ST7567_SPI1__Plot(MX_UINT8 FCL_X, MX_UINT8 FCL_Y);
#define FA_LCDPlot FCD_0ab21_gLCD_ST7567_SPI1__Plot

// Set one pixel to current background colour
void FCD_0ab21_gLCD_ST7567_SPI1__BPlot(MX_UINT8 FCL_X, MX_UINT8 FCL_Y);
#define FA_LCDBPlot FCD_0ab21_gLCD_ST7567_SPI1__BPlot

/*=----------------------------------------------------------------------=*\
   Use :This macro prints a string of characters to the Graphical LCD.
       :
       :Parameters for macro Print:
       :  Str[50] : String of characters to send to the display.
       :  X1 : X pixel coordinate to set the output string position.
       :  Y1 : Y coordinate 0-31
       :  Font : Size of the font - 0 = Normal, 1 = Double Width, 2 = Double Width and Height, 3 = Double Height
       :  Transparent : Specifies if the background of the text is drawn - 0 = Background colour is drawn, 1 = Background colour not drawn.
\*=----------------------------------------------------------------------=*/
void FCD_0ab21_gLCD_ST7567_SPI1__Print(MX_CHAR *FCL_STR, MX_UINT16 FCLsz_STR, MX_UINT16 FCL_X1, MX_UINT16 FCL_Y1, MX_UINT8 FCL_FONT, MX_UINT8 FCL_TRANSPARENT);
#define FA_LCDPrint FCD_0ab21_gLCD_ST7567_SPI1__Print

// Clear LCD display
void FCD_0ab21_gLCD_ST7567_SPI1__ClearDisplay();
#define FA_LCDClear FCD_0ab21_gLCD_ST7567_SPI1__ClearDisplay

// Set LCD backlight brightness (0 - 100%)
void FCD_0dcd1_FormulaAllCode1__LCDBacklight(MX_UINT8 FCL_BRIGHTNESS);
#define FA_LCDBacklight FCD_0dcd1_FormulaAllCode1__LCDBacklight

// Set current background colour for drawing & printing
void FCD_0ab21_gLCD_ST7567_SPI1__SetBackgroundColour(MX_UINT8 FCL_PIXELCOLOUR);
#define FA_LCDSetBackground FCD_0ab21_gLCD_ST7567_SPI1__SetBackgroundColour

// Set current foreground colour for drawing & printing
void FCD_0ab21_gLCD_ST7567_SPI1__SetForegroundColour(MX_UINT8 FCL_PIXELCOLOUR);
#define FA_LCDSetForeground FCD_0ab21_gLCD_ST7567_SPI1__SetForegroundColour

/*=----------------------------------------------------------------------=*\
   Use :Draws a line with the current foreground colour from pixel location X1, Y1 to pixel location X2, Y2.
       :
       :Parameters for macro DrawLine:
       :  X1 : MX_UINT8
       :  Y1 : MX_UINT8
       :  X2 : MX_UINT8
       :  Y2 : MX_UINT8
\*=----------------------------------------------------------------------=*/
void FCD_0ab21_gLCD_ST7567_SPI1__DrawLine(MX_UINT8 FCL_X1, MX_UINT8 FCL_Y1, MX_UINT8 FCL_X2, MX_UINT8 FCL_Y2);
#define FA_LCDLine  FCD_0ab21_gLCD_ST7567_SPI1__DrawLine

/*=----------------------------------------------------------------------=*\
   Use :Draws a rectangle with the current foreground colour from pixel loaction X1, Y1 to pixel location X2, Y2
       :
       :Parameters for macro DrawRectangle:
       :  X1 : MX_UINT8
       :  Y1 : MX_UINT8
       :  X2 : MX_UINT8
       :  Y2 : MX_UINT8
       :  Transparent : MX_UINT8
       :  Solid : MX_UINT8
\*=----------------------------------------------------------------------=*/
void FCD_0ab21_gLCD_ST7567_SPI1__DrawRectangle(MX_UINT8 FCL_X1, MX_UINT8 FCL_Y1, MX_UINT8 FCL_X2, MX_UINT8 FCL_Y2, MX_UINT8 FCL_TRANSPARENT, MX_UINT8 FCL_SOLID);
#define FA_LCDRectangle FCD_0ab21_gLCD_ST7567_SPI1__DrawRectangle

/*
 * Infra-red obstacle detectors
 */

// Read an IR obstacle detector
MX_UINT16 FCD_0dcd1_FormulaAllCode1__ReadIRSensor(MX_UINT8 FCL_CHANNEL);
#define FA_ReadIR FCD_0dcd1_FormulaAllCode1__ReadIRSensor

/*
 * Visible light sensor
 */

// Read the visible light sensor
MX_UINT16 FCD_0dcd1_FormulaAllCode1__ReadLDR();
#define FA_ReadLight    FCD_0dcd1_FormulaAllCode1__ReadLDR

/*
 * Pushbutton switches
 */

// Read pushbutton state (0: left, 1: right)
MX_UINT8 FCD_0dcd1_FormulaAllCode1__ReadSwitch(MX_UINT8 FCL_SWITCH);
#define FA_ReadSwitch   FCD_0dcd1_FormulaAllCode1__ReadSwitch

// Read switch 0 (left), with debounce code
MX_UINT8 FCD_05262_switch_base__ReadState();
#define FA_ReadSwitch0Debounced FCD_05262_switch_base__ReadState

// Wait until switch 0 (left) pressed, with debounce code
void FCD_05261_switch_base__WaitUntilHigh();
#define FA_Switch0WaitHigh  FCD_05262_switch_base__WaitUntilHigh

// Wait until switch 0 (left) NOT pressed, with debounce code
void FCD_05261_switch_base__WaitUntilLow();
#define FA_Switch0WaitLow   FCD_05262_switch_base__WaitUntilHigh

// Read switch 1 (right), with debounce code
MX_UINT8 FCD_05261_switch_base__ReadState();
#define FA_ReadSwitch1Debounced FCD_05261_switch_base__ReadState

// Wait until switch 1 (right) pressed, with debounce code
void FCD_05261_switch_base__WaitUntilHigh();
#define FA_Switch1WaitHigh  FCD_05261_switch_base__WaitUntilHigh

// Wait until switch 1 (right) NOT pressed, with debounce code
void FCD_05261_switch_base__WaitUntilLow();
#define FA_Switch1WaitLow   FCD_05261_switch_base__WaitUntilHigh

/*
 * Microphone input
 */

// Read one sample from microphone
MX_UINT16 FCD_0dcd1_FormulaAllCode1__ReadMic();
#define FA_ReadMic  FCD_0dcd1_FormulaAllCode1__ReadMic

/*
 * Loudspeaker
 */

// Make tone of specified frequency (Hz) and duration (milliseconds)
void FCD_0dcd1_FormulaAllCode1__PlayNote(MX_UINT16 FCL_NOTE, MX_UINT16 FCL_TIME);
#define FA_PlayNote FCD_0dcd1_FormulaAllCode1__PlayNote

/*
 * Front LED strip (8 green LEDs)
 */

// Switch on specified LED (0 - 7; 0 is leftmost)
void FCD_0dcd1_FormulaAllCode1__LEDOn(MX_UINT8 FCL_LED);
#define FA_LEDOn    FCD_0dcd1_FormulaAllCode1__LEDOn

// Switch off specified LED (0 - 7; 0 is leftmost)
void FCD_0dcd1_FormulaAllCode1__LEDOff(MX_UINT8 FCL_LED);
#define FA_LEDOff   FCD_0dcd1_FormulaAllCode1__LEDOff

// Set all LEDs at once (8-bit value: 0 = off, 1 = on; bit 0 is leftmost)
void FCD_0dcd1_FormulaAllCode1__LEDWrite(MX_UINT8 FCL_LED_BYTE);
#define FA_LEDWrite FCD_0dcd1_FormulaAllCode1__LEDWrite
// alternative name for same function
#define FA_SetLEDs  FCD_0dcd1_FormulaAllCode1__LEDWrite

/*
 * Line sensors
 */

// Read specified line sensor (0 = left, 1 = right)
MX_UINT16 FCD_0dcd1_FormulaAllCode1__ReadLineSensor(MX_UINT8 FCL_CHANNEL);
#define FA_ReadLine FCD_0dcd1_FormulaAllCode1__ReadLineSensor

/*
 * Battery sensor
 */

// Read battery voltage
// 1 unit = 0.001611 volts
MX_UINT16 FCD_08f4d_adc_base__GetInt();
#define FA_ReadBattery  FCD_08f4d_adc_base__GetInt

/*
 * Delay functions
 * (busy delays - CPU looping)
 */

// Delay specified number of microseconds
void FCI_DELAYINT_US(MX_UINT16 Delay);
#define FA_DelayMicros  FCI_DELAYINT_US

// Delay specified number of milliseconds
void FCI_DELAYINT_MS(MX_UINT16 Delay);
#define FA_DelayMillis  FCI_DELAYINT_MS

// Delay specified number of seconds
void FCI_DELAYINT_S(MX_UINT16 Delay);
#define FA_DelaySecs    FCI_DELAYINT_S

/*
 * TO BE IMPLEMENTED:
 * 
 * SD card I/O
 * Bluetooth serial
 * USB serial
 * Accelerometer
 * Magnetometer
 * EEPROM
 * 
 */

/* Millisecond system clock */

/* Initialise clock */
MX_UINT8 XFA_ClockMS_Initialise(void);

/* Return system time in milliseconds */
MX_UINT32 FA_ClockMS(void);

/* Convenience routine - print UINT32 on display */
void XFA_LCDPrintU32(MX_UINT32 FCL_NUMBER, MX_UINT16 FCL_X, MX_UINT16 FCL_LINE, MX_UINT8 FCL_FONT, MX_UINT8 FCL_TRANSPARENT);

/*****************************/

#ifdef	__cplusplus
}
#endif

#endif	/* ALLCODE_API_H */
