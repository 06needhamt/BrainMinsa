// Instruction screen, displays instructions to the user.

/*
Test and exercise your short term memory: 
How many characters from the sequence can you remember?

The game provides 5 levels of difficulty

You can dynamically change the difficulty using the potentiometer. 
Changes to the level will be reflected on the NEXT question.
When you start a game you will be shown a sequence of characters to remember
You will hava a short period to remember the sequence before it is hidden,
then you must try to recreate the sequence on the answer screen.
The more accurately you remember the sequence, the higher your score.
Bonuses are awarded for perfect answers based on the game difficulty.
*/

// Massive string holding the entire instruction text
char *originalInstructionText = 
"Test and exercise your short term memory:\n\
How many characters from the sequence can you remember?\
The game provides 5 levels of difficulty\n\
You can dynamically change the difficulty using the potentiometer.\
Changes to the level will be reflected on the NEXT question.\
When you start a game you will be shown a sequence of characters to remember\
you will then hava a short period to remember the sequence before it is hidden, \
then you must try to recreate the sequence on the answer screen.\
The more accurately you remember the sequence, the higher your score\
Bonuses are awarded for perfect answers based on the game difficulty.";


// The maximum number of lines acceptable
#define MAX_LINES 100

// Array of string pointers, each one will point to a 20 character line from the originalInstructionText
char *parsedInstructionText[MAX_LINES]; // Array of string pointers upt MAX_LINES in length
int numberOfLines; // The number of lines 20 character lines parsed out of the originalInstructionText;



void instructionScreen(void) {
	
	
	
	
}

// Parses the instruction text
void parseInstructionText(void) {
	int parsedFlag = 0;
	int lineParsedFlag = 0;
	char *ptr = originalInstructionText; // Point at the start of the text
	char *lineStart= originalInstructionText; // Will point at the start of the line of text
	int lineCounter = 0;
	int count; // Character counter
	
	do { // Do while runs through the text deciding where line breaks should go
		parsedInstructionText[lineCounter] = ptr; // Set the start of the text line
		
		//lineStart = ptr; // Point at start of line
		
		
		
		lineParsedFlag = 0; // Ready to parse the next line
		do { // Run through charaters, looking for NULL, new line or max line length reached 
			if(*ptr == '\n' || count == 20) // End of this line found
				lineParsedFlag = 1; // This line is parsed
			
			if(*ptr == 0) // End of entire text
				parsedFlag = 1; // We have reached the end of the entire text
			else 
				ptr++; // Move to next character
			
		} while(!lineParsedFlag);
		
		
		
		
		
		if(lineCounter++ == MAX_LINES) // only accept up to MAX_LINES lines
			parsedFlag = 1; 
		
	} while(!parsedFlag);
}


















