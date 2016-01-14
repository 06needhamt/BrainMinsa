// Get an answer of length characters from the user
#include <stdio.h>
#include "GLCD.h"
#include "LCD_Functions.h"
#include "Button_Functions.h"
#include "String_Functions.h"
#include "GameConstants.h"


void joystickLeft(void);
void joystickRight(void);
void joystickUp(void);
void joystickDown(void);
void acceptPressed(void);

// define letter place holder as a . (dot)
#define LETTER_PLACEHOLDER '.'
#define ROW_NUMBER 7


// Structure holds the state of entry by the user
static struct entryDetails answerDetails;
static int getAnswerState = 0;
static int length = 0;
static int margin = 0;


void initialiseGetAnswer(int len) { // Len based on difficulty
	int t;
	int position;
  unsigned char letters[2] = {'\0', '\0'}; // Short string used to display letters

	if(len == 5) // Correct length of answer
		len++;
	
	len+=4;
	
	if(getAnswerState == 1)  // Get answer is is already functioning
		return;
	
	getAnswerState = 1; // Signal getAnswerState is active

//	answerString = answer; // Point answerString as answer
//	questionString = question; // Point at the question - ready for marking 
		
	answerDetails.letterIndex = 0; // index first character of answer string
	
	for(t = 0; t < len; t++)
		answerDetails.answerString[t] = LETTER_PLACEHOLDER; // Fill initial answer string with PLACE_HOLDER
	answerDetails.answerString[t] = '\0';  // Null terminate answerDetails
	
	
	length = len; // Remember the length of the answer
	
	margin= (20 - length) / 2; // The width of the left margin for the answer
	
	// Display the empty answer place holders with cursor highlighted
	position = margin + answerDetails.letterIndex;
	letters[0] = LETTER_PLACEHOLDER;
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(ROW_NUMBER, position, __FI, letters);
	
	// Reset default text colours
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	
	for(t = 1; t < length; t++) 
		GLCD_DisplayString(ROW_NUMBER, position + t, __FI, letters);

	
	return; // Return the address of the answer string
	
}

void inputAnswer(int input) {
		
	if(!getAnswerState) // We are not expecting the user to be entering an answer
		return; 
	
	switch(input) {
		case USER_BUTTON:
				acceptPressed();// Accept button pressed
		break;
		case JOYSTICK_UP:
				joystickUp();    // Up on joystick
		break;
		case JOYSTICK_DOWN:
				joystickDown();  // Down on joystick
		break;
		case JOYSTICK_LEFT: 
				joystickLeft();  // Left on joystick pressed
		break;
		case JOYSTICK_RIGHT:
				joystickRight(); // Right on joystick
		break;
	}
}


// User pressed LEFT on joystick
void joystickLeft() {
	int position = 0;
	unsigned char letters[2] = {'\0', '\0'}; // Short string used to display letters

	// Display last letter using normal colours
	position = margin + answerDetails.letterIndex;
	letters[0] = answerDetails.answerString[answerDetails.letterIndex];
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(ROW_NUMBER, position, __FI, letters);
	
	// Move the cursor left
	if(--answerDetails.letterIndex < 0) {
		answerDetails.letterIndex = length -1;
	}
	
	// Display the current letter using highlight colours
	position = margin + answerDetails.letterIndex;
	letters[0] = answerDetails.answerString[answerDetails.letterIndex];
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(ROW_NUMBER, position, __FI, letters);
	
	// Reset default text colours
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);	
	
	
}


// User pressed RIGHT
void joystickRight() {
	int position = 0;
	unsigned char letters[2] = {'\0', '\0'}; // Short string used to display letters

	// Display last letter using normal colours
	position = margin + answerDetails.letterIndex;
	letters[0] = answerDetails.answerString[answerDetails.letterIndex];
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(ROW_NUMBER, position, __FI, letters);

	if(++answerDetails.letterIndex >= length) {
		answerDetails.letterIndex = 0;
	}

	// Display the current letter using highlight colours
	position = margin + answerDetails.letterIndex;
	letters[0] = answerDetails.answerString[answerDetails.letterIndex];
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(ROW_NUMBER, position, __FI, letters);
	
	// Reset default text colours
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);	
	
}

// User pressed UP
void joystickUp() {
	int index = 0;
	int position = 0;
	//char newLetter;
	unsigned char letters[2] = {'\0', '\0'}; // Short string used to display letters
	
	char character = answerDetails.answerString[answerDetails.letterIndex]; // Get the current letter from the answerString
	
	for(index = 0; index < CHARSET_LENGTH && character != OriginalCharSet[index]; index++) ; // Find the current character in the original set
		
	//newLetter = index; // Get the appropriate letter from the original character set

	// This will also filter out the LETTER_PLACEHOLDER being outside the legal answer string range
	if(++index >= CHARSET_LENGTH) // Gone past the last letter, return to the begining
		index = 0; 
		
	answerDetails.answerString[answerDetails.letterIndex] = OriginalCharSet[index];
	
	// Display the letter using highlight colours
	position = margin + answerDetails.letterIndex;
	letters[0] = OriginalCharSet[index]; // Put the new letter into a printable string
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(ROW_NUMBER, position, __FI, letters);
	
	// Reset default text colours
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);	
}

// User pressed DOWN
void joystickDown() {
	int index = 0;
	int position = 0;
	//char newLetter;
	unsigned char letters[2] = {'\0', '\0'}; // Short string used to display letters
	
	char character = answerDetails.answerString[answerDetails.letterIndex]; // Get the current letter from the answerString
	
	// Find the current character within the original character set. If found, characters index will be in index
  for(index = 0; index < CHARSET_LENGTH && (character != OriginalCharSet[index]); index++) ; 
	
	if(index == 0 || index >= CHARSET_LENGTH) // At fist character in list OR character not found (must be LETTER_PLACEHOLDER)
		index = CHARSET_LENGTH -1; // Set to last character of original character set
	else 
		index -= 1; // Set to previous letter from the original character set
	
	answerDetails.answerString[answerDetails.letterIndex] = OriginalCharSet[index];
	
	// Display the letter using highlight colours
	position = margin + answerDetails.letterIndex;
	letters[0] = OriginalCharSet[index]; // Put the new letter into a printable string
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(ROW_NUMBER, position, __FI, letters);
	
	// Reset default text colours
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
}

// User pressed ACCEPT button
void acceptPressed() {
	int t;
	int position;
	unsigned char letters[2] = {'\0', '\0'}; // Short string used to display letters
	
	if(!getAnswerState) // Not expecting an answer so do nothing
		return;
	
  GLCD_SetTextColor(White);
	
	// Compare the correct answer with the users answer and highlight correct/incorrect letters

	for(t = 0; answerString[t] != 0; t++) {
		position = margin + t;
		
		letters[0] = answerString[t]; // Get the letter
		
		if(answerString[t] == questionString[t]) { // Correct letter
			GLCD_SetBackColor(Green); // Highlight colour for correct letter
			
			currentScore += 10; // Update score
		}
		else { // Incorrect letter
			GLCD_SetBackColor(Red); // Highlight colour for incorrect letter
		}

		GLCD_DisplayString(ROW_NUMBER, position + t, __FI, letters);
		
	}
	
	updateScoreAndDifficulty(currentScore, currentDifficulty, nextDifficulty);
	
	getAnswerState = 0; // Answer accepted no longer taking input
}



