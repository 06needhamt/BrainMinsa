// Game constants and stuff


#define TRUE		1
#define FALSE		0

#define LED_NUM     8                   /* Number of user LEDs  */
#define TIMER_LENGTH 5000UL

#define AWAIT_USER_READY 0 //state representing that the program should wait for the user to be ready for the next question
#define AWAIT_USER_ANSWER 1 //state representing that the program should wait for the user to input their answer

#define DIFFICULTY_SCREEN 2 // state representing that the user is currently on the difficulty screen
#define WELCOME_SCREEN 3 // Welcome Screen displayed
#define IN_GAME 10 // Inside the game
#define QUESTION_SCREEN 11 // In Question Screen

#define BAR_X 200
#define BAR_Y (6 * 24)
#define BAR_WIDTH 100
#define BAR_HEIGHT 15
#define BAR_VALUE 1

extern int currentState; // default current state of the program
