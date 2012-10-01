/*************************************************************************
 * Filename: gameOfChance.c                                              *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012  ; Lab Section 7                           *
 * Programming Assignment 4: A Game of Chance "Craps"                    *
 * Date: September 30, 2012                                              *
 *                                                                       *
 * Description: This program implements a craps game according to the    *
 *              rules below. This file includes all the function         *
 *              definitions whose prototypes, standard libraries and     *
 *              constant macros are declared in the file gameOfChance.h  *
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
#include "gameOfChance.h"

/*************************************************************
 * Function: play ()                                         *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function is the main function called to *
 *              start a game of craps.                       *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: User knows the rules of the game of craps  *
 * Postconditions: User has doesn't want to continue playing *
 *                 or player is bankrupt.                    *
 *************************************************************/
void play (void)
{
	int dieOne = 0, dieTwo = 0,
		sumDice = 0, 
		playerPoint = 0,
		gameStatus = 0, 
		numberOfRolls = 0,
		playMore = 0;

	double initialBankBalance = 0.0,
		   balance = 0.0,
		   wager = 0.0;

	char escape = '\0';

	/* The game should allow for wagering. */
	/* This means that you need to prompt that user for an initial bank balance 
	   from which wagers will be added or subtracted. Before each roll prompt the 
	   user for a wager. */
	initialBankBalance = getBankBalance ();
	balance = initialBankBalance;
	
	do
	{
		do
		{
			wager = getWagerAmount ();
		} while (!(checkWagerAmount (wager, balance)));


		/* A player rolls two dice. */
		printf ("<Press Enter to roll the dice>");
		getch ();

		/* Gets two random values from 1-6, and are saved on the variables dieOne and dieTwo */
		dieOne = rollDie ();
		dieTwo = rollDie ();

		/* Shows in the screen two animated die and then the the actual values of the dice */
		animateDices (dieOne, dieTwo);

		/* After the dice have come to rest, the sum of the spots on the two upward faces is calculated. */
		sumDice = calculateSumDice (dieOne, dieTwo);

		switch (isWinLossOrPoint (sumDice))
		{
			case WINS:
				/* If the sum is 7 or 11 on the first throw, the player wins. */
				gameStatus = WINS;
				break;

			case POINT:
				/* If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's "point." */
				gameStatus = POINT;
				playerPoint = sumDice;

				do
				{
					printf ("Continue rolling the dice until you get a sum of %d\n", playerPoint);
					printf ("<Press Enter to roll the dice>");
					escape = getchar ();
					dieOne = rollDie ();
					dieTwo = rollDie ();
					animateDices (dieOne, dieTwo);

					sumDice = calculateSumDice (dieOne, dieTwo);

					gameStatus = isPointLossOrNeither (sumDice, playerPoint);

				} while (gameStatus == POINT);

				break;

			case CRAPS:
				/* If the sum is 2, 3, or 12 on the first throw (called "craps"), the player loses (i.e. the "house" wins). */
				gameStatus = CRAPS;
				break;
		}

		/* Once a game is lost or won, the bank balance should be adjusted. */
		balance = adjustBankBalance (balance, wager, gameStatus);
		
		/* Keeps track of the number of plays */
		numberOfRolls++;

		chatterMessages (numberOfRolls, gameStatus, initialBankBalance, balance);
		printf ("<Press Enter to continue>");
		getch ();

		if (balance > 0)
		{
			playMore = playAgain (balance);
		}
		else
		{
			playMore = 0;
		}

	} while (playMore);
	
}



/* PLAY FUNCTIONS */

/*
If add_or_subtract is 1, then the wager amount is added to the bank_balance. 
If add_or_subtract is 0, then the wager amount is subtracted from the bank_balance. 
Otherwise, the bank_balance remains the same. The bank_balance result is returned.
*/
double adjustBankBalance (double balance, double wager, int addOrSubtract) 
{
	switch (addOrSubtract)
	{
		case WINS:
			balance += (wager * WINNING_WAGER_MULTIPLIER);
			break;
		case CRAPS:
			balance -= wager;
			break;
	}

	return balance;
}

/*
Determines the result of any successive roll after the first roll. 
If the sum of the roll is the point_value, then 1 is returned. 
If the sum of the roll is a 7, then 0 is returned. Otherwise, -1 is returned.
*/
int isPointLossOrNeither (int sumDice, int playerPoint)
{
	int status = POINT;

	if (sumDice == 7)
	{
		/* The player loses by rolling a 7 before making the point. */
		status = CRAPS;
	}
	else if (sumDice == playerPoint)
	{
		/* To win, you must continue rolling the dice until you "make your point."  */
		status = WINS;
	}

	return status;
}

/* 
Determines the result of the first dice roll. 
If the sum is 7 or 11 on the roll, the player 
wins and 1 is returned. If the sum is 2, 3, or 12 
on the first throw (called "craps"), the player loses 
(i.e. the "house" wins) and 0 is returned. 
If the sum is 4, 5, 6, 8, 9, or 10 on the first throw,
then the sum becomes the player's "point" and -1 is returned. 
 */
int isWinLossOrPoint (int sumDice)
{
	int status = CRAPS;

	if (sumDice == 7 || sumDice == 11)
	{
		status = WINS;
	}
	else if (sumDice == 4 || sumDice == 5 || 
			 sumDice == 6 || sumDice == 8 ||
			 sumDice == 9 || sumDice == 10)
	{
		status = POINT;
	}

	return status;
}

int calculateSumDice (int dieOne, int dieTwo)
{
	return (dieOne + dieTwo);
}

int rollDie (void)
{
	int dieValue = 0;

	dieValue = getRandomNumber (6);

	return dieValue;
}

int checkWagerAmount (double wager, double balance)
{
	int check = 0;

	if (wager <= balance) 
	{
		/* Checks that amount is not less than or equal to zero */
		if (wager <= 0) 
		{
			printf ("ERROR: %s, Try Again!\n", ERROR_2); 
			check = 0;
		}
		else
		{
			check = 1;
		}
	}
	else
	{
		printf ("ERROR: %s $%.2lf, Try Again!\n", ERROR_1, balance); 
	}

	return check;
}

double getWagerAmount (void)
{
	double wager = 0.0;

	while (TRUE)
	{
		printf ("Enter wager: $");
		scanf ("%lf", &wager);

		/* Checks that amount is not less than or equal to zero */
		if (wager > 0) 
			break;
		else 
			printf ("ERROR: %s, Try Again!\n", ERROR_2); 
	}

	return wager;
}

double getBankBalance (void)
{
	double initBankBalance = 0.0;

	printTitle ();

	while (TRUE)
	{
		printf ("Enter Initial Bank Balance: $");
		scanf ("%lf", &initBankBalance);

		/* Checks that amount is not less than or equal to zero */
		if (initBankBalance > 0) 
			break;
		else 
			printf ("ERROR: %s, Try Again!\n", ERROR_2); 
	}

	return initBankBalance;
}

/*
Prints an appropriate message dependent on the number of 
rolls taken so far by the player, the current balance, 
and whether or not the player just won his roll. The 
parameter win_loss_neither indicates the result of the 
previous roll.
*/
void chatterMessages (int numberRolls, int winLossNeither, 
	                  double initialBankBalance, double currentBankBalance)
{
	/* As the game progresses, print various messages to create some "chatter" such as, 
	   "Sorry, you busted!",					winLossNeither = 0 && currentBalance == 0
	   or "Oh, you're going for broke, huh?",	winLossNeight = 0  && currentBankBalance < initialBalance * .5
	   or "Aw cmon, take a chance!",			winLossNeither = 1 && currentBankBalance > initialBalance * .5 && currentBankBalance < initialBalance
	   or "You're up big, now's the time to cash in your chips!", (winLossNeither = 0) && currentBankBalance > initialBankBalance */
	if (winLossNeither == WINS)
	{
		printf ("ROMNEY: You are a lucky bastard! I need you in my election committee.\n");

	}
	else 
	{
		printf ("OBAMA: Your such a Loser! Your bad luck, stay away from me...\n");
	}

	if (winLossNeither == 0 && currentBankBalance == 0)
	{
		printf ("Sorry, you busted!\n");
	}
	else if (winLossNeither == 0 && currentBankBalance < (initialBankBalance * .5))
	{
		printf ("Oh, you're going for broke, huh?\n");
	}
	else if (winLossNeither == 1 && currentBankBalance > (initialBankBalance * .5) && currentBankBalance < initialBankBalance)
	{
		printf ("Aw c'mon, take a chance!\n");
	}
	else if (winLossNeither == 0 && currentBankBalance > initialBankBalance)
	{
		printf ("You're up big, now's the time to cash in your chips!\n");
	}
}

/* UTILITY FUNCTIONS */

int playAgain (double currentBalance)
{
	char ch = '\0';
	int playMore = 0;

	system ("cls");
	printTitle ();
	printf ("Current Balance: $%.2lf\n", currentBalance);
	printf ("Do you want to play more (Y/N)? ");
	scanf ("\n\n\n%c", &ch);

	if (ch == 'y' || ch == 'Y')
		playMore = 1;

	return playMore;
}

void animateDices (int dieOne, int dieTwo)
{
	int i = 0;

	for (i = 0; i < DICE_NUMBER_OF_ROTATION; i++)
	{
		system ("cls");
		printTitle ();
		drawDie (getRandomNumber (6));
		printf ("\n");
		drawDie (getRandomNumber (6));
		Beep (523, 300);
		Sleep (300);
	}

	system ("cls");
	printTitle ();
	drawDie (dieOne);
	printf ("\n");
	drawDie (dieTwo);
	printf ("\n");
	Beep (659, 200);
}

void drawDie (int number)
{
	switch (number)
	{
		case ONE:
			diceOne ();
			break;

		case TWO:
			diceTwo ();
			break;

		case THREE:
			diceThree ();
			break;

		case FOUR:
			diceFour ();
			break;

		case FIVE:
			diceFive ();
			break;

		case SIX:
			diceSix ();
			break;
	}
}

void diceOne (void)
{
	printf ("              ***********\n");
	printf ("              *         *\n");
	printf ("              *    *    *\n");
	printf ("              *         *\n");
	printf ("              ***********\n");
}

void diceTwo (void)
{
	printf ("              ***********\n");
	printf ("              *  *      *\n");
	printf ("              *         *\n");
	printf ("              *      *  *\n");
	printf ("              ***********\n");
}

void diceThree (void)
{
	printf ("              ***********\n");
	printf ("              *  *      *\n");
	printf ("              *    *    *\n");
	printf ("              *      *  *\n");
	printf ("              ***********\n");
}

void diceFour (void)
{
	printf ("              ***********\n");
	printf ("              *  *   *  *\n");
	printf ("              *         *\n");
	printf ("              *  *   *  *\n");
	printf ("              ***********\n");
}

void diceFive (void)
{ 
	printf ("              ***********\n");
	printf ("              *  *   *  *\n");
	printf ("              *    *    *\n");
	printf ("              *  *   *  *\n");
	printf ("              ***********\n");
}

void diceSix (void)
{
	printf ("              ***********\n");
	printf ("              *  *   *  *\n");
	printf ("              *  *   *  *\n");
	printf ("              *  *   *  *\n");
	printf ("              ***********\n");
}

int getRandomNumber (int maxNumber)
{
	int number = 0;

	number = (rand () % maxNumber) + 1;

	return number;
}

/* SETUP FUNCTIONS */

void setup (void)
{
	srand ((unsigned int) time (NULL));

	/* Animated welcome screen is displayed on the screen  */
	introScreen ();
}

char printMenu (void)
{
	char option = '\0';

	do {
		system ("cls");
		printTitle ();
		printf ("       [ 1 ] START A NEW GAME\n");
		printf ("       [ 2 ] HOW TO PLAY CRAPS\n");
		printf ("       [ 3 ] EXIT GAME\n\n");
		printf ("       CHOOSE OPTION: ");
		option = getchar ();
	} while (option < '1' || option > '3');

	return option;
}

void printGameRules (void)
{
	system ("cls");
	printTitle ();
	printf ("              HOW TO PLAY\n");
	printf ("> Player rolls two dice\n");
	printf ("> After the dice have come to rest, the\n  sum of the spots on the two upward faces\n  is calculated.\n");
	printf ("> If the sum is 7 or 11 on the first throw,\n  the PLAYER WINS!\n");
	printf ("> If the sum is 2, 3 or 12 on the first\n  throw, CRAPS... The PLAYER LOSES!\n");
	printf ("> If the sum is 4, 5, 6, 8, 9, or 10 on\n  the first throw, then the sum becomes\n  the PLAYER'S POINT.\n");
	printf ("> To win, you must continue rolling the\n  dice until you make your POINT. The\n  player loses by rolling a 7 before\n  making the point.\n");
	printf ("       <Press Enter to continue>");
	getch ();
}

void printTitle (void)
{
	system ("cls");
	printf ("******************************************\n");
	printf ("* ******  *****    ****   *****    ***** *\n");
	printf ("* *       *    *  *    *  *    *  *      *\n");
	printf ("* *       *****   ******  *****    ****  *\n");
	printf ("* *       *    *  *    *  *            * *\n");
	printf ("* ******  *    *  *    *  *       *****  *\n");
	printf ("******************************************\n");
	printf ("\n");
}

void introScreen (void)
{
	system ("cls"); /* for MAC change to system("clear"); */
    printf ("******************************************\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("******************************************\n");
	Sleep (1000);
	system ("cls");
	printf ("******************************************\n");
	printf ("* ******                                 *\n");
	printf ("* *                                      *\n");
	printf ("* *                                      *\n");
	printf ("* *                                      *\n");
	printf ("* ******                                 *\n");
	printf ("******************************************\n");
	Beep (523, 200);
	Sleep (200);
	system ("cls");
	printf ("******************************************\n");
	printf ("* ******  *****                          *\n");
	printf ("* *       *    *                         *\n");
	printf ("* *       *****                          *\n");
	printf ("* *       *    *                         *\n");
	printf ("* ******  *    *                         *\n");
	printf ("******************************************\n");
	Beep (587, 200);
	Sleep (200);
	system ("cls");
	printf ("******************************************\n");
	printf ("* ******  *****    ****                  *\n");
	printf ("* *       *    *  *    *                 *\n");
	printf ("* *       *****   ******                 *\n");
	printf ("* *       *    *  *    *                 *\n");
	printf ("* ******  *    *  *    *                 *\n");
	printf ("******************************************\n");
	Beep (659, 200);
	Sleep (200);
	system ("cls");
	printf ("******************************************\n");
	printf ("* ******  *****    ****   *****          *\n");
	printf ("* *       *    *  *    *  *    *         *\n");
	printf ("* *       *****   ******  *****          *\n");
	printf ("* *       *    *  *    *  *              *\n");
	printf ("* ******  *    *  *    *  *              *\n");
	printf ("******************************************\n");
	Beep (698, 200);
	Sleep (200);
	system ("cls");
	printf ("******************************************\n");
	printf ("* ******  *****    ****   *****    ***** *\n");
	printf ("* *       *    *  *    *  *    *  *      *\n");
	printf ("* *       *****   ******  *****    ****  *\n");
	printf ("* *       *    *  *    *  *            * *\n");
	printf ("* ******  *    *  *    *  *       *****  *\n");
	printf ("******************************************\n");
	Beep (784, 200);
	Sleep (200);
	system ("cls");
    printf ("******************************************\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("******************************************\n");
	Beep (698, 200);
	Sleep (150);
	system ("cls");
	printf ("******************************************\n");
	printf ("* ******  *****    ****   *****    ***** *\n");
	printf ("* *       *    *  *    *  *    *  *      *\n");
	printf ("* *       *****   ******  *****    ****  *\n");
	printf ("* *       *    *  *    *  *            * *\n");
	printf ("* ******  *    *  *    *  *       *****  *\n");
	printf ("******************************************\n");
	Beep (784, 200);
	Sleep (200);
	system ("cls");
	printf ("******************************************\n");
	printf ("* ******  *****    ****   *****    ***** *\n");
	printf ("* *       *    *  *    *  *    *  *      *\n");
	printf ("* *       *****   ******  *****    ****  *\n");
	printf ("* *       *    *  *    *  *            * *\n");
	printf ("* ******  *    *  *    *  *       *****  *\n");
	printf ("******************************************\n");
	printf ("\n");
	Beep (698, 200);
}