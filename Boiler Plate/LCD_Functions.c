#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"                  /* STM32F10x.h definitions            */
#include "GLCD.h"						/* Required for the LCD screen		  */

#include "LCD_Functions.h"



//The following function is used to display a test banner
//and show the number of cycles the test is repeated (see the main body).
void displayTestMessage(int lineNo, int colNo, unsigned char* msgText, int loopCount) {
	static int oldLineNo = 0;
	char loopNoStr [4] = {0,0,0,0};			/* Assigns a 3-digit counter display string */

	if (oldLineNo > 0) {
		GLCD_DisplayString(oldLineNo, colNo, __FI, "  ");
	}
	
	GLCD_SetTextColor(Red);
	//Show the currently executing test
	GLCD_DisplayString(lineNo, colNo, __FI, ">>");
	GLCD_SetTextColor(Blue);

	GLCD_DisplayString(lineNo, colNo + 2, __FI, msgText);
	sprintf(loopNoStr, "%d", loopCount);	/* Converts integer value to its string format */
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(White);
	
  GLCD_DisplayString(lineNo, strlen((const char*)msgText) + colNo + 3, __FI, (unsigned char*)loopNoStr);
	
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);

	oldLineNo = lineNo;
}

void updateScoreAndDifficulty(int score, int currentDifficulty, int nextDifficulty){
	char message[20]; //maximum size of a message displayed in a single row
	
	/*work out buffer size used within sprintf for the score
	we have a total of 20 spaces; "Score:" is 6 characters long
	" Lvl " is 5, "(" and ")" are 2, 
	nextDifficulty as well as currentDifficulty both one character long, so together 2
	*/
	
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	
	sprintf(message, "Score:%05d%s%d%c%d%c", score, " Lvl ", currentDifficulty, '(', nextDifficulty, ')');
	GLCD_DisplayString(1,0, __FI, message);
}

void updateNextDifficulty(int nextDifficulty){
	char msg[4];
	sprintf(msg, "%1d", nextDifficulty);
	GLCD_DisplayChar(1,18, __FI, *msg);
}
