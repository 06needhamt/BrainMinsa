#include "stm32f10x.h"
#include "GLCD.h"
#include "LCD_Functions.h"
#include <stdint.h>


void DrawBarGraph(uint32_t x, uint32_t y, uint32_t w, uint32_t h, int32_t val);

void DisplayInstructions(char* message, int score, int currentDifficulty, int nextDifficulty);
