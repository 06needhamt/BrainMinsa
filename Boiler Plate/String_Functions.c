#include "String_Functions.h"

char AnswerString[ANSWER_LENGTH];
char CharSet[] = { 'A', 'B' ,'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char OriginalCharSet[] = { 'A', 'B' ,'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

char* GenerateRandomString(int difficulty, char *codeString)
{
	
	int let1, let2, t;
	int i = 0;
	char temp;
	
	
		srand(Seed);
	
		// Randomise the charset
		for(t = 0; t < 1000; t++) {
			
			
			let1 = rand() % (CHARSET_LENGTH - 1);
			
		
			let2 = rand() % (CHARSET_LENGTH - 1);
			
			temp = CharSet[let1];
			
			CharSet[let1] = CharSet[let2];
			CharSet[let2] = temp;
		}
	
		if(difficulty == 5){
        difficulty++;
    }
		
		for(i = 0; i < difficulty + 4; i++)
		{
			
			codeString[i] = CharSet[i];
			//AnswerString[i] = CharSet[i];
			
			// AnswerString[i] = CharSet[rand() % (CHARSET_LENGTH - 1)];
			//delay(1);
			Seed++;
		}
    //AnswerString[i] = '\0';
		codeString[i] = '\0';
		
    return codeString;
}