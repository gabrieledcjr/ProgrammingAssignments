/*************************************************************************
 * Filename: gameOfChance.h                                              *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012  ; Lab Section 7                           *
 * Programming Assignment 4: A Game of Chance "Craps"                    *
 * Date: September 30, 2012                                              *
 *                                                                       *
 * Description: This program implements a craps game according to the    *
 *              rules below. This file includes all the required         *
 *              standard libraries, constant macros and user-defined     *
 *              function prototypes. Function definitions are located    *
 *              at the file gameOfChance.c                               *
 *                                                                       *
 * Rules of the Game:													 *
 *   1) A player rolls two dice.                                         *
 *   2) Each die has six faces. These faces contain 1, 2, 3, 4, 5, and   *
 *      6 spots.                                                         *
 *   3) After the dice have come to rest, the sum of the spots on the    *
 *      two upward faces is calculated.                                  *
 *   4) If the sum is 7 or 11 on the first throw, the player wins.       *
 *   5) If the sum is 2, 3, or 12 on the first throw (called "craps"),   *
 *      the player loses (i.e. the "house" wins).                        *
 *   6) If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the  *
 *      sum becomes the player's "point."                                *
 *   7) To win, you must continue rolling the dice until you "make your  *
 *      point." The player loses by rolling a 7 before making the point. *
 *************************************************************************/
#ifndef GAME_OF_CHANCE_H
#define GAME_OF_CHANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>	/* Sleep () */
#include <conio.h>		/* getch () */

#define TRUE	1		/* Boolean constant for True */
#define FALSE	0       /* Boolean constant for False */

#define START_NEW_GAME  '1'		/* Menu option 1 */
#define HOW_TO_PLAY		'2'		/* Menu option 2 */
#define EXIT_GAME       '3'     /* Menu option 3 */

#define ONE		1
#define TWO		2
#define THREE	3
#define FOUR	4
#define	FIVE	5
#define SIX		6		/* 6 faces of a die */

#define CRAPS	0		/* Indicator of losing a play or craps */
#define WINS	1       /* Indicator of winning a play */
#define POINT	-1      /* Indicator of getting a point on first throw */

#define WINNING_WAGER_MULTIPLIER	2		/* Bet or wager is multiplied by this number if player wins */
#define DICE_NUMBER_OF_ROTATION		5       /* Number of times dice is rolled during animation */

#define ERROR_1	"Wager exceeds balance of "						/* Error message 1 */
#define ERROR_2 "Amount cannot be less than or equal to 0"		/* Error message 2 */

                        
void play (void);
double adjustBankBalance (double balance, double wager, int addOrSubtract);
int isPointLossOrNeither (int sumDice, int playerPoint);
int isWinLossOrPoint (int sumDice);
int calculateSumDice (int dieOne, int dieTwo);
int rollDie (void);
int checkWagerAmount (double wager, double balance);
double getWagerAmount (void);
double getBankBalance (void);
void chatterMessages (int numberRolls, int winLossNeither, 
	                  double initialBankBalance, double currentBankBalance);

void animateDices (int dieOne, int dieTwo);
void drawDie (int number);
void diceOne (void);
void diceTwo (void);
void diceThree (void);
void diceFour (void);
void diceFive (void);
void diceSix (void);
int getRandomNumber (int maxNumber);

void setup (void);
char printMenu (void);
void printGameRules (void);		
void printTitle (void);
void introScreen (void);

#endif