#ifndef YAHTZEE_H
#define YAHTZEE_H

#include <stdio.h>
#include <Windows.h>	/* system() */

#define START_GAME   1
#define GAME_RULES   2
#define EXIT_GAME    3

#define SCREEN_BORDER_UPPER_X   1
#define SCREEN_BORDER_UPPER_Y   1
#define SCREEN_BORDER_LOWER_X  78
#define SCREEN_BORDER_LOWER_Y  23

#define MENU_X  30
#define MENU_Y  12

#define CURSOR_SYMBOL  219

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


void printGameRules (void);
void printGoodbye (void);

int chooseMenuItem (void);
void printMainScreen (void);
void printScreenBorder (void);
void printMenu (int x, int y);
void printTitle (int x, int y);
void borderScreen (int upperLeftCornerX, int upperLeftCornerY,
				   int lowerRightCornerX, int lowerRightCornerY);

void gotoxy(int x, int y);
void pressEnter (void);

#endif