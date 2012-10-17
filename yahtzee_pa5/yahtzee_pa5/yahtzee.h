/*************************************************************************
 * Filename: yahtzee.h                                                   *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012 ; Lab Section 7                            *
 * Programming Assignment 4: A Game of Yahtzee!                          *
 * Date: October 6, 2012                                                 *
 *                                                                       *
 * Description: This program implements the Yahtzee game. This file      *
 *              includes all the required standard libraries, constant   *
 *              macros and user-defined function prototypes. Function    *
 *              definitions are located at the file yahtzee.c            *
 *************************************************************************/
#ifndef YAHTZEE_H
#define YAHTZEE_H

#include <stdio.h>
#include <Windows.h>	/* system() */
#include <conio.h>      /* getch() */

#define TRUE  1         /* boolean value for true */
#define FALSE 0         /* boolean value for false */

#define START_GAME   1         /* value to identify start game */
#define GAME_RULES   2         /* value to identify game rules */
#define EXIT_GAME    3         /* value to identify exit game */

#define SCREEN_BORDER_UPPER_X   1     /* predefined top left x position of border */
#define SCREEN_BORDER_UPPER_Y   1     /* predefined top left y position of border */
#define SCREEN_BORDER_LOWER_X  78     /* predefined lower right x position of border */
#define SCREEN_BORDER_LOWER_Y  23     /* predefined lower right y position of border */

#define MENU_X  30              /* predefined top left x position of menu */
#define MENU_Y  12              /* predefined top left y position of menu */

#define ARROW_KEY_UP    72      /* value for arrow key up */
#define ARROW_KEY_DOWN  80      /* value for arrow key down */
#define SPACE_BAR       32      /* value for space bar */

#define CURSOR_SYMBOL  219      /* ASCII value of a block */

#define NUMBER_OF_DICE  5       /* defines number of dice used */

/* Categories */
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
#define NUMBER_OF_CATEGORIES  13

#define BONUS_RANGE   63
#define BONUS_POINTS  35

void startNewGame (void);
void setupGameBoard (void);
void rollDice (int dice [], int holdDice []);
void drawDie (int dieValue, int x, int y);
void chooseDiceToHold (int holdDice []);
void updateDiceArea (int dice [], int holdDice [], int rolls);
void finalizeScoreBoard (int scoreBoard [][14]);
void printMessageBox (char msgLine1[], char msgLine2[], int number);
void updateScoreBoard (int playerNumber, int category, int score);
void computeCategoryScore (int dice [], int category, int *score);
int checkCategory (int dice [], int category);
void chooseCategory (int *category);

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