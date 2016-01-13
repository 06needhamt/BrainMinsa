// Game Welcome Screen

#include <stdio.h>
#include "GLCD.h"
#include "LCD_Functions.h"
#include "Button_Functions.h"
#include "String_Functions.h"
#include "GameConstants.h"

void WelcomeScreen(void) {
	
	//This configuration allows 20 characters per line and 10 lines (16x24 pixel characters).
	GLCD_Clear(Blue);                    /* Clear graphical LCD display        */
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(0, 0, __FI, "Welcome 2 BrainMINSA");
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(4, 0, __FI, "By");
	GLCD_DisplayString(5, 2, __FI, "Alex Keidel");
	GLCD_DisplayString(6, 2, __FI, "Tom Needham");
	GLCD_DisplayString(7, 2, __FI, "Chris Nicholas");
	GLCD_DisplayString(9, 0, __FI, " Press User Button ");
}



