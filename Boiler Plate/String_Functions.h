#include "stm32f10x.h"                  /* STM32F10x.h definitions            */
#include <stdio.h>
#include <stdlib.h>

#define ANSWER_LENGTH 20
#define CHARSET_LENGTH 36


extern char AnswerString[ANSWER_LENGTH];
extern char CharSet[];
extern char OriginalCharSet[];
	

extern void inputAnswer(int input);
	
// extern char* GenerateAnswerString(int difficulty);

extern char* GenerateRandomString(int difficulty, char *codeString);

	
extern unsigned long GetTicks(void);
extern void delay(int secs);
	
extern unsigned int Seed;
	
// Structure holds the state of entry by the user
struct entryDetails {
	int letterIndex;				// The letter being pointed at within the answer string
	char answerString[20];  // Holds the list of characters input by the user
};

void initialiseGetAnswer(int length); // Initialises get answer 
