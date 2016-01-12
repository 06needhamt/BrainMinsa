#include "String_Functions.h"

char* GenerateRandomString(int difficulty)
{
	int i = 0;
	unsigned int bits;
    if(difficulty == 5){
        difficulty++;
    }
		for(i = 0; i < difficulty + 4; i++)
		{
			srand(Seed);
			AnswerString[i] = CharSet[rand() % (CHARSET_LENGTH - 1)];
			//delay(1);
			Seed++;
		}
    AnswerString[i + 1] = '\0';
    return AnswerString;
}