#include "LED_Functions.h"
#include "stm32f10x.h"                  /* STM32F10x.h definitions            */

#define LED_AMOUNT 8

void RunTimer(unsigned long tenths);

extern void delay10th(unsigned long tenthMsecs);
extern void delay(int secs);
