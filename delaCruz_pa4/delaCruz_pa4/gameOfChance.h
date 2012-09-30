#ifndef GAME_OF_CHANCE_H
#define GAME_OF_CHANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> /* System () */
#include <conio.h>
#include <math.h>	/* floor () */

#define TRUE	1
#define FALSE	0

#define ONE		1
#define TWO		2
#define THREE	3
#define FOUR	4
#define	FIVE	5
#define SIX		6

#define CRAPS	0
#define WINS	1
#define POINT	-1

#define WINNING_PERCENT_FROM_WAGER 0.5
#define DICE_NUMBER_OF_ROTATION	   8

#define ERROR_1	"Wager exceeds balance of "
#define ERROR_2 "Amount cannot be less than or equal to 0"

void play (void);
double adjustBankBalance (double balance, double wager, int addOrSubtract);
int isPointLossOrNeither (int sumDice, int playerPoint);
int isWinLossOrPoint (int sumDice);
int calculateSumDice (int dieOne, int dieTwo);
int rollDie (void);
int checkWagerAmount (double wager, double balance);
double getWagerAmount (void);
double getBankBalance (void);

void animateDices (int dieOne, int dieTwo);
void drawDie (int number);
void diceOne (void);
void diceTwo (void);
void diceThree (void);
void diceFour (void);
void diceFive (void);
void diceSix (void);
int getRandomNumber (int maxNumber);

int playANewGame (void);

void setup (void);
void printGameRules (void);		// needs to be implemented
void printTitle (void);
void introScreen (void);

#endif