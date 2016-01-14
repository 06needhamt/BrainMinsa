// Game Screens

#include <stdio.h>
#include "GLCD.h"
#include "LCD_Functions.h"
#include "Button_Functions.h"
#include "String_Functions.h"
#include "GameConstants.h"
#include "DifficultyScreen.h"
#include "GameScreens.h"
#include "CoundownTimer.h"


extern int currentState; // default current state of the program

// Display Marking Screen

void markingScreen(void) {
	if(currentState != MARKING_SCREEN)
		return;
	
	GLCD_Clear(Blue);                    /* Clear graphical LCD display        */
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(0, 5, __FI, "BrainMINSA");
	GLCD_SetTextColor(White);
	GLCD_DisplayString(2, 0, __FI, "Below is your marked");
	GLCD_DisplayString(3, 0, __FI, "answer:");
	GLCD_DisplayString(4, 0, __FI, "Green = Correct");
	GLCD_DisplayString(5, 0, __FI, "Red = Incorrect");
	
	GLCD_DisplayString(9, 0, __FI, "User button = finish");	
}



// Display Enter Answer Screen

void answerScreen(void) {
	
	if(currentState != ANSWER_SCREEN)
		return;
	
	GLCD_Clear(Blue);                    /* Clear graphical LCD display        */
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(0, 5, __FI, "BrainMINSA");
	GLCD_SetTextColor(White);
	GLCD_DisplayString(2, 0, __FI, "Answer Screen");
	GLCD_DisplayString(3, 0, __FI, "Please use Joystick");
	GLCD_DisplayString(4, 0, __FI, "To enter the code");
	GLCD_DisplayString(5, 0, __FI, "User button = finish");
	
	initialiseGetAnswer(currentDifficulty);
	
	}


// Display Question Screen

void questionScreen(void) {
	
	if(currentState != QUESTION_SCREEN)
		return;
	
	GLCD_Clear(Blue);                    /* Clear graphical LCD display        */
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(0, 5, __FI, "BrainMINSA");
	GLCD_SetTextColor(White);
	GLCD_DisplayString(2, 0, __FI, "Question Screen");
	GLCD_DisplayString(3, 0, __FI, "Memorise the code");
	GLCD_DisplayString(4, 0, __FI, "Before the LED");
	GLCD_DisplayString(5, 0, __FI, "countdown expires:");
	
	GenerateRandomString(currentDifficulty, questionString);
	GLCD_DisplayString(7, 0, __FI, questionString);
}


// Display Welcome Screen
void WelcomeScreen(void) {
	
	//This configuration allows 20 characters per line and 10 lines (16x24 pixel characters).
	GLCD_Clear(Blue);                    /* Clear graphical LCD display        */
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(0, 0, __FI, "Welcome 2 BrainMINSA");
	GLCD_SetTextColor(White);
	GLCD_DisplayString(4, 0, __FI, "By");
	GLCD_DisplayString(5, 2, __FI, "Alex Keidel");
	GLCD_DisplayString(6, 2, __FI, "Tom Needham");
	GLCD_DisplayString(7, 2, __FI, "Chris Nicholas");
	GLCD_DisplayString(9, 0, __FI, " Press User Button ");
}


