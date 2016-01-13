/******************************************************************************/
/* Blinky.c: LED Flasher                                                      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2010 Keil - An ARM Company. All rights reserved.             */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

//The following include files are pre-defined for you.
//Standard C library definitions
#include <stdio.h>
#include <string.h>
//STM32 MCU specific definitions
#include "stm32f10x.h"                  /* STM32F10x.h definitions            */
#include "GLCD.h"						/* Required for the LCD screen		  */

#include "LED_Functions.h"
#include "LCD_Functions.h"
#include "Button_Functions.h"
#include "Potentiometer_Functions.h"
#include "Speaker_Functions.h"
#include "CoundownTimer.h"
#include "DifficultyScreen.h"
#include "String_Functions.h"
#include "GameConstants.h"
#include "GameScreens.h"


int currentState = WELCOME_SCREEN; //default current state of the program

extern unsigned char clock_1s;

//Following are used for ADC
extern unsigned short AD_last;	 		//Last ADC conversion value
extern unsigned char  AD_done;			//ADC conversion complete flag
extern unsigned long ticks;
//extern char* GenerateRandomString(int difficulty);

int doTone = 0;
char outputString[20];
unsigned int Seed = 0;
int c = 0;
int currDifficulty = 0;
int nextDifficulty = 0;
int currentScore = 1337;
uint32_t barWidth = 100;
//This function delays program by secs seconds. This function relies on
//a timer which is used to produce an interrupt at regular intervals. See
//further down for the way this timer is activated. The timer interrupt
//handler is in IRQ.c source file. You need to supply the code for this
//interrupt (this is a vectored interrupt) in order for this function
//to work. 
void delay10th(unsigned long tenthMsecs) {
	//Set the tick counter in number of 10th of msecs
	ticks = tenthMsecs;
	//Wait until the tick counter is 0 (zero)
	while (ticks) {}
}

void delay (int secs) {
	int n;
	//Repeat the following secs times
	for (n = 0; n < secs; n++) {
		//First reset clock_1s
		clock_1s = 0;
		//Wait for it to be set after 1 sec	(refer to IRQ.c)
		while (!clock_1s);
	}
}

void Vectored_Interrupt(int button){
	char cString[4], currDiffString[4];
	//GLCD_Clear(White);                    /* Clear graphical LCD display        */
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	
	switch(button){
		case USER_BUTTON:
				//GLCD_DisplayString(0, 0, __FI, "< --User Button -- >");
				switch(currentState) {
					case WELCOME_SCREEN: // If on the welcome screen, set up difficulty screen
						GLCD_Clear(White);
						if(currDifficulty == 0){
							currDifficulty = 1;
						}
						updateNextDifficulty(nextDifficulty);
						DisplayInstructions(NULL,currentScore,currDifficulty,1);
						DrawBarGraph(BAR_X,BAR_Y,currDifficulty * 20,BAR_HEIGHT,BAR_VALUE);
						
						currentState = DIFFICULTY_SCREEN;
						
					break;
						
					case DIFFICULTY_SCREEN: // Transition to Question Screen
						
						updateScoreAndDifficulty(currentScore, currDifficulty, nextDifficulty);
						
						currentState = QUESTION_SCREEN;
					
						questionScreen(); // Display the question screen
													
					break;
					
					case QUESTION_SCREEN: // Question Screen uses countdown timer - no inputs
						
					break;
					
					
				};
						
		
		
				//GLCD_DisplayString(6, 0, __FI, GenerateRandomString(5));
				
				//doTone = ~doTone;
			break;
		
		case JOYSTICK_SELECT:
				//GLCD_DisplayString(0, 0, __FI, "< --JSTK Select -->");
				updateScoreAndDifficulty(100, 2, 3);
				inputAnswer(JOYSTICK_SELECT);
			break;
		
		case JOYSTICK_UP:
				//GLCD_DisplayString(0, 0, __FI, "< --JSTK UP   -- >");
				updateScoreAndDifficulty(99999, 9, 9);
				inputAnswer(JOYSTICK_UP);
			break;
		
		case JOYSTICK_DOWN:
				//GLCD_DisplayString(0, 0, __FI, "< --JSTK DOWN -- >");
				updateScoreAndDifficulty(0, 1, 2);
				inputAnswer(JOYSTICK_DOWN);
			break;
		
		case JOYSTICK_RIGHT:
				//GLCD_DisplayString(0, 0, __FI, "< --JSTK RIGHT-- >");
				updateScoreAndDifficulty(12345, 6, 7);
				inputAnswer(JOYSTICK_RIGHT);
			break;
		
		case JOYSTICK_LEFT:
				//GLCD_DisplayString(0, 0, __FI, "< --JSTK LEFT -- >");
				updateScoreAndDifficulty(1337, 1, 1);
				inputAnswer(JOYSTICK_LEFT);
			break;
		
		case POTENTIOMETER_TURNED:
			  //sprintf(cString, "%02d", c);
		
			switch(currentState) {
				case DIFFICULTY_SCREEN:
					nextDifficulty = (c / 3) + 1;
					sprintf(currDiffString, "%1d", nextDifficulty);
					//updateScoreAndDifficulty(currentScore, currDifficulty, nextDifficulty);
					updateNextDifficulty(nextDifficulty);
					DrawBarGraph(BAR_X,BAR_Y,nextDifficulty * 20,BAR_HEIGHT,BAR_VALUE);
					//GLCD_SetBackColor(Red);
				break;
				
			}		
					
			break;
		
		default:
			break;
	}
}

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	int i;
	char potOutput[20];
	char answer[10];

	//Following statement sets the timer interrupt frequency
	//The clock rate on this boards MCU is 72 Mhz - this means
	//every second there will be 72 million clocks. So, if use this
	//as the parameter to the function the interrupt rate is going
	//to be every second. If it is reduced to 100 times less then
	//it will do that many clocks in 100 times less time, i.e. 10 msecs.
	//NOTE: We could have chosen to generate a timer interrupt every 1 msec
	//if we wished and that would be quite acceptable in which case we would
	//need to modify the interrupt handler routine in IRQ.c file.
  	SysTick_Config(SystemCoreClock/10000);  /* Generate interrupt each 10 ms      */

   	
	LED_init(); /* LED Initialization                 */

	pin_PA4_For_Speaker(); //Function that initializes the Speaker
		
	ADC_init();  //Function that initializes ADC

	GLCD_Init(); /* Initialize graphical LCD display   */
  		
	joyStick_Init(); // Initialise the joystick

	userButton_Init(); // Initialise User Button

	userButton_IntrEnable(); //initialise the User button as an interrupt source

  //Here we initialise the Joystick switches as interrupt sources
  joyStick_IntrEnable_PG15_13();
	joyStick_IntrEnable_PG7();
	joyStick_IntrEnable_PD3();
	
	AD_done = 0;
	ADC1->CR2 |= (1UL << 22);       		//Start the ADC conversion
	doTone = 0;
	
	WelcomeScreen();

	


	initialiseGetAnswer(answer, 10);
//	if(currentState == ON_DIFFICULTY_SCREEN)
//	{
//			GLCD_Clear(White);
//			if(currDifficulty == 0){
//				currDifficulty = 1;
//			}
//			updateNextDifficulty(nextDifficulty);
//			DisplayInstructions(NULL,currentScore,currDifficulty,1);
//			DrawBarGraph(BAR_X,BAR_Y,currDifficulty * 20,BAR_HEIGHT,BAR_VALUE);
//	}	
	while (TRUE) {
	
		
		
//								
//				//RunTimer(TIMER_LENGTH);
//			GLCD_SetBackColor(Red);
//			DrawBarGraph(100,6*24,barWidth,15,1);
//			delay10th(10000);
//			GLCD_SetBackColor(White);
//			barWidth -= 20;
//			if(barWidth <= 0){
//				barWidth = 100;
//			}
//			GLCD_DisplayString(6,0,__FI,"                   ");
				//Check to see if ADC sampling is completed
//				if (AD_done) {
//					//Yes, so get part of the sample value
//					c = (AD_last >> 8) + 4;
//					if (doTone) {
//						//If enabled, switch the tone on
//							sprintf(potOutput,"Pot = %d",c);
//							displayTestMessage(1,0,potOutput,0);
//				   		generate_Tone_On_Speaker(c * 50, 10);
//					}
//					AD_done = 0;  					//Reset the ADC complete flag waiting for next sample
//					ADC1->CR2 |= (1UL << 22);   	//Start the next ADC conversion
	}
}
