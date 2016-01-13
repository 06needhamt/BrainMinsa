#include "CoundownTimer.h"

void RunTimer(unsigned long tenths)
{
		int t = 0;
		All_LEDs_On();
	
		for(t = 0; t < LED_AMOUNT; t++)
		{
			delay10th(tenths);
			LED_Off(t);
		}
}