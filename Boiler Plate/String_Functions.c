#include "String_Functions.h"

char* GenerateRandomString(int difficulty)
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
			AnswerString[i] = CharSet[i];
			
			// AnswerString[i] = CharSet[rand() % (CHARSET_LENGTH - 1)];
			//delay(1);
			Seed++;
		}
    AnswerString[i + 1] = '\0';
    return AnswerString;
}