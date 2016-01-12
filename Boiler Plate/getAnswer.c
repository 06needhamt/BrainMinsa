// Get an answer of length characters from the user
#include <stdio.h>
#include "GLCD.h"
#include "LCD_Functions.h"
#include "Button_Functions.h"
#include "String_Functions.h"


void joystickLeft();
void joystickRight();
void joystickUp();
void joystickDown();
void acceptPressed();

// #defines for switch case
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define ACCEPT 5




// Structure holds the state of entry by the user
static struct entryDetails answerDetails;
static int getAnswerState = 0;
static int length = 0;
static int margin = 0;
static int charsetIndex = 0;

char *initialiseGetAnswer(char *answer, int len) {
	int t;
	
	if(getAnswerState == 1)  // Get answer is is already functioning
		return ""; // <<<<<<<<<<<<<<<<< fix this
	
	getAnswerState = 1; // Signal getAnswerState is active
	
	for(t = 0; t < len; t++)
		answerDetails.answerString[t] = 'Q'; // Fill initial answer string with nulls
	
	answerDetails.answerString[t] = 0; // Null terminate answerDetails
	
	length = len; // Remember the length of the answer
	
	margin= (20 - length) / 2; // The width of the left margin for the answer
	
	// Display the empty answer place holders
	for(t = 0; t < length; t++) {
		GLCD_DisplayString(5, margin + t, __FI, ".");
	}	
	
	//getAnswerState = 0; // No longet in getAnswer
	
	return answer; // Return the address of the answer string
	
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

	if(--answerDetails.letterIndex < 0) {
		answerDetails.letterIndex = length -1;
	}
	
	position = margin + answerDetails.letterIndex;
		
	GLCD_DisplayString(6, position, __FI, "^");
	
}


// User pressed RIGHT
void joystickRight() {
	int position = 0;
	
	if(++answerDetails.letterIndex >= length) {
		answerDetails.letterIndex = 0;
	}
	
	position = margin + answerDetails.letterIndex;
		
	GLCD_DisplayString(6, position, __FI, "^");
}

// User pressed UP
void joystickUp() {
	int t;
	int index = 0;
	int position = 0;
	char newLetter;
	char letter[2] = {'\0', '\0'};
	
	char character = answerDetails.answerString[answerDetails.letterIndex]; // Get the current letter from the answerString
	
	for(t = 0; t < CHARSET_LENGTH && character != OriginalCharSet[t]; t++) ; // Find the current character in the original set
		
	newLetter = t; // Get the appropriate letter from the original character set


	if(++newLetter >= CHARSET_LENGTH) // Gone past the last letter, return to the begining
		newLetter = 0; 
	
		
	answerDetails.answerString[answerDetails.letterIndex] = OriginalCharSet[newLetter];
	
	letter[0] = OriginalCharSet[newLetter]; // Put the new letter into a printable string

	position = margin + answerDetails.letterIndex;	

	GLCD_DisplayString(5, position, __FI, letter);
	
	
}

// User pressed DOWN
void joystickDown() {
	int t;
	int index = 0;
	int position = 0;
	char newLetter;
	char letter[2] = {'\0', '\0'};
	
	char character = answerDetails.answerString[answerDetails.letterIndex]; // Get the current letter from the answerString
	
	for(t = 0; t < CHARSET_LENGTH && character != OriginalCharSet[t]; t++) ; // Find the current character in the original set

	newLetter = t; // Get the appropriate letter from the original character set


	if(--newLetter < 0) // Gone past the last letter, return to the begining
		newLetter = CHARSET_LENGTH -1; 
	
	answerDetails.answerString[answerDetails.letterIndex] = OriginalCharSet[newLetter];
	
	letter[0] = OriginalCharSet[newLetter]; // Put the new letter into a printable string

	position = margin + answerDetails.letterIndex;	

	GLCD_DisplayString(5, position, __FI, letter);


}

// User pressed ACCEPT button
void acceptPressed() {
	getAnswerState = 0; // Answer accepted no longer taking input
}




