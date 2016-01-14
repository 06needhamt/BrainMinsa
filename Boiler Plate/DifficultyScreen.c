#include "DifficultyScreen.h"
#include "GameConstants.h"



void DrawBarGraph(uint32_t x, uint32_t y, uint32_t w, uint32_t h, int32_t val){
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(6,0,__FI,"Difficulty         ");
			switch(w)
			{
					case 20:
						GLCD_SetBackColor(Green);
						GLCD_Bargraph(x,y,w,h,val);
						GLCD_SetBackColor(White);
					break;
					
					case 40:
						GLCD_SetBackColor(Blue);
						GLCD_Bargraph(x,y,w,h,val);
						GLCD_SetBackColor(White);
					break;

					case 60:
						GLCD_SetBackColor(Magenta);
						GLCD_Bargraph(x,y,w,h,val);
						GLCD_SetBackColor(White);
					break;
						
					case 80:
						GLCD_SetBackColor(Cyan);
						GLCD_Bargraph(x,y,w,h,val);
						GLCD_SetBackColor(White);
					break;

					case 100:
						GLCD_SetBackColor(Red);
						GLCD_Bargraph(x,y,w,h,val);
						GLCD_SetBackColor(White);
					break;
					
					default:

					break;
			}
		  
}

void DisplayInstructions(void){
		GLCD_SetBackColor(Blue);
		GLCD_SetTextColor(Red);
		GLCD_DisplayString(0, 5, __FI, "     BrainMINSA     ");
		GLCD_SetTextColor(White);
		updateScoreAndDifficulty(currentScore, currentDifficulty, nextDifficulty);
		GLCD_DisplayString(2,0,__FI,"Use the POT to change diff");
		GLCD_DisplayString(3,0,__FI,"User button to continue");
}
