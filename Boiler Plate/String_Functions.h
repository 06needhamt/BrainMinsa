#include "stm32f10x.h"                  /* STM32F10x.h definitions            */
#include <stdio.h>
#include <stdlib.h>


#define ANSWER_LENGTH 20
#define CHARSET_LENGTH 36

char AnswerString[20];

char CharSet[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B' ,'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char* GenerateAnswerString(int difficulty);
	
extern unsigned long GetTicks();
extern void delay(int secs);
	
extern unsigned int Seed;