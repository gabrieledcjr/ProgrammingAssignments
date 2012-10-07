#ifndef YAHTZEE_H
#define YAHTZEE_H

#include <stdio.h>
#include <Windows.h>	/* system() */

#define TRUE  1
#define FALSE 0

#define START_GAME   1
#define GAME_RULES   2
#define EXIT_GAME    3

#define SCREEN_BORDER_UPPER_X   1
#define SCREEN_BORDER_UPPER_Y   1
#define SCREEN_BORDER_LOWER_X  78
#define SCREEN_BORDER_LOWER_Y  23

#define MENU_X  30
#define MENU_Y  12

#define ARROW_KEY_UP    72
#define ARROW_KEY_DOWN  80

#define CURSOR_SYMBOL  219

#define NUMBER_OF_DICE  5

#define ONES              1 
#define TWOS              2 
#define THREES            3 
#define FOURS             4 
#define FIVES             5 
#define SIXES             6 
#define THREE_OF_A_KIND   7 
#define FOUR_OF_A_KIND    8 
#define FULL_HOUSE        9 
#define SMALL_STRAIGHT   10 
#define LARGE_STRAIGHT   11 
#define YAHTZEE          12 
#define CHANCE           13



void startNewGame (void);
void chooseDiceToHold (int *holdDie1, int *holdDie2, int *holdDie3, int *holdDie4, int *holdDie5);
void updateDiceArea (int die1, int die2, int die3, int die4, int die5, 
	                 int holdDie1, int holdDie2, int holdDie3, int holdDie4, int holdDie5, int rolls);
void drawDie (int dieValue, int x, int y);
void rollDice (int *die1, int *die2, int *die3, int *die4, int *die5,
	           int holdDie1, int holdDie2, int holdDie3, int holdDie4, int holdDie5);
void setupGameBoard (void);

void printGameRules (void);
void printGoodbye (void);
void init (void);

int chooseMenuItem (void);
void printMainScreen (void);
void printScreenBorder (void);
void printMenu (int x, int y);
void printTitle (int x, int y);
void borderScreen (int upperLeftCornerX, int upperLeftCornerY,
				   int lowerRightCornerX, int lowerRightCornerY);

void gotoxy(int x, int y);
void pressEnter (void);
int getRandomNumber (int maxNumber);

void dieBlank (int x, int y);
void dieOne (int x, int y);
void dieTwo (int x, int y);
void dieThree (int x, int y);
void dieFour (int x, int y);
void dieFive (int x, int y);
void dieSix (int x, int y);

#endif