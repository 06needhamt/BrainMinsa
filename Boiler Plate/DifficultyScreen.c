#include "DifficultyScreen.h"

void DrawBarGraph(uint32_t x, uint32_t y, uint32_t w, uint32_t h, int32_t val){
		 GLCD_Bargraph(x,y,w,h,val);
}