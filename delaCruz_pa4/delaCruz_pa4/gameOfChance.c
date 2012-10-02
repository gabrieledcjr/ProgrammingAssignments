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
 * Rules of the Game:                                                    *
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
	int dieOne = 0, dieTwo = 0,     /* values for two dice */
		sumDice = 0,                /* sum of two dice */
		playerPoint = 0,            /* player's point */
		gameStatus = 0,             /* status of game */
		numberOfRolls = 0,          /* tracks number of rolls */
		playMore = 0;               /* status indicator for more game */

	double initialBankBalance = 0.0,	/* value for initial bank balance */
		   balance = 0.0,               /* value for current bank balance */
		   wager = 0.0;                 /* value for wager or bet */


	/* Prompts user for inital bank balance */
	initialBankBalance = getBankBalance ();
	balance = initialBankBalance;
	
	do
	{
		do
		{
			/* Before each rool, prompt user for a wager */
			wager = getWagerAmount ();
		} while (!(checkWagerAmount (wager, balance)));


		/* A player rolls two dice. */
		printf ("<Press ENTER to roll the dice>");
		pressEnter ();

		/* Gets two random values from 1-6, and are 
		   saved on the variables dieOne and dieTwo */
		dieOne = rollDie ();
		dieTwo = rollDie ();

		/* Shows in the screen two animated die and 
		   then the the actual values of the dice */
		animateDices (dieOne, dieTwo);

		/* After the dice have come to rest, the sum 
		   of the spots on the two upward faces is 
		   calculated. */
		sumDice = calculateSumDice (dieOne, dieTwo);

		switch (isWinLossOrPoint (sumDice))
		{
			case WINS:
				/* If the sum is 7 or 11 on the first throw, 
				   the player wins. */
				gameStatus = WINS;
				break;

			case POINT:
				/* If the sum is 4, 5, 6, 8, 9, or 10 on the 
				   first throw, then the sum becomes the player's 
				   "point." */
				gameStatus = POINT;
				playerPoint = sumDice;

				do
				{
					/* Prompts player to roll die until player gets the point or craps */
					printf ("Continue rolling the dice until you get a sum of %d\n", playerPoint);
					printf ("<Press ENTER to roll the dice>");
					pressEnter ();

					/* gets two random values for dieOne and dieTwo */
					dieOne = rollDie ();
					dieTwo = rollDie ();

					/* animates two dice on the screen */
					animateDices (dieOne, dieTwo);

					/* gets the sum of the two dice */
					sumDice = calculateSumDice (dieOne, dieTwo);

					/* checks if user wins, craps or neither */
					gameStatus = isPointLossOrNeither (sumDice, playerPoint);

				} while (gameStatus == POINT);

				break;

			case CRAPS:
				/* If the sum is 2, 3, or 12 on the first throw 
				   (called "craps"), the player loses (i.e. the 
				   "house" wins). */
				gameStatus = CRAPS;
				break;
		}

		/* Once a game is loss or won, the bank 
		   balance should be adjusted. */
		balance = adjustBankBalance (balance, wager, gameStatus);
		
		/* Keeps track of the number of plays */
		numberOfRolls++;

		/* Prints out messages on screen */
		chatterMessages (numberOfRolls, gameStatus, initialBankBalance, balance);
		printf ("<Press ENTER to continue>");
		pressEnter ();

		if (balance > 0)
		{
			/* If balance is greater than 0,
			   Prompts player to play more or not */
			playMore = playAgain (balance);
		}
		else
		{
			playMore = 0;
		}

	} while (playMore);
	
}



/* PLAY FUNCTIONS */

/*************************************************************
 * Function: adjustBankBalance ()                            *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function, if addOrSubtract is 1, then   *
 *              the wager amount is added to the balance. If *
 *              addOrSubtract is 0, then the wager amount is *
 *              subtracted from the balance. Otherwise, the  *
 *              balance remains the same. The balance result *
 *              is returned.                                 *
 * Input parameters: current balance, wager, indicator if    *
 *                   player wins or craps                    *
 * Returns: adjusted balance                                 *
 * Preconditions: balance is non-zero, wager is not bigger   *
 *                than balance, correct value if player won  *
 *                or loss.                                   *
 * Postconditions: adjusted balanced is returned             *
 *************************************************************/
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

/*************************************************************
 * Function: adjustBankBalance ()                            *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function determines the result of any   *
 *              successive roll after the first roll. If the *
 *              sum of the roll is the playerPoint, then 1   *
 *              is returned. If the sum of the roll is a 7,  *
 *              then 0 is returned. Otherwise, -1 is         *
 *              returned.                                    *
 * Input parameters: sum of the two die, sum of the first    *
 *                   roll known as the "point"               *
 * Returns: indicator if player loss or wins or neither      *
 * Preconditions: sum of the two die rolled are computed     *
 *                with correct values and the sum of the     *
 *                first roll or point is accurate            *
 * Postconditions: indicator if it's a point, loss or win    *
 *************************************************************/
int isPointLossOrNeither (int sumDice, int playerPoint)
{
	int status = POINT;		/* status indicator */

	if (sumDice == 7)
	{
		status = CRAPS;
	}
	else if (sumDice == playerPoint)
	{
		status = WINS;
	}

	return status;
}

/*************************************************************
 * Function: isWinLossOrPoint ()                             *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function determines the result of the   *
 *              first dice roll. If the sum is 7 or 11 on    *
 *              the roll, the player wins and 1 is returned. *
 *              If the sum is 2, 3, or 12 on the first throw *
 *              (called "craps"), the player loses (i.e. the *
 *              "house" wins) and 0 is returned. If the sum  *
 *              is 4, 5, 6, 8, 9, or 10 on the first throw,  *
 *              then the sum becomes the player's "point"    *
 *              and -1 is returned.                          *
 * Input parameters: sum of the two die                      *
 * Returns: indicator if player loss, wins or neither        *
 * Preconditions: sum of the two die rolled are computed     *
 *                with correct values                        *
 * Postconditions: indicator if it's a point, loss or win    *
 *************************************************************/
int isWinLossOrPoint (int sumDice)
{
	int status = CRAPS;		/* status indicator */

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

/*************************************************************
 * Function: calculateSumDice ()                             *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function calculates sum of the values   *
 *              of two dice                                  *
 * Input parameters: die one and die two                     *
 * Returns: sum of two dice                                  *
 * Preconditions: None                                       *
 * Postconditions: Sum of two dice returned                  *
 *************************************************************/
int calculateSumDice (int dieOne, int dieTwo)
{
	return (dieOne + dieTwo);
}

/*************************************************************
 * Function: rollDie ()                                      *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function gets a random value for a die  *
 *              between 1 to 6                               *
 * Input parameters: void                                    *
 * Returns: random value of a die                            *
 * Preconditions: getRandomNumber () is defined              *
 * Postconditions: Value of a die returned                   *
 *************************************************************/
int rollDie (void)
{
	int dieValue = 0;		/* value for a die */

	dieValue = getRandomNumber (6);

	return dieValue;
}

/*************************************************************
 * Function: checkWagerAmount ()                             *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function checks if the wager amount is  *
 *              within the current balance of the player     *
 * Input parameters: wager, current balance                  *
 * Returns: indicator if wager is acceptable                 *
 * Preconditions: None                                       *
 * Postconditions: Indicator of valid wager returned         *
 *************************************************************/
int checkWagerAmount (double wager, double balance)
{
	int check = 0;			/* status indicator */

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

/*************************************************************
 * Function: getWagerAmount ()                               *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function prompts player to enter a      *
 *              wager.                                       *
 * Input parameters: void                                    *
 * Returns: value for wager                                  *
 * Preconditions: None                                       *
 * Postconditions: Wager is returned                         *
 *************************************************************/
double getWagerAmount (void)
{
	double wager = 0.0;		/* wager value */

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

/*************************************************************
 * Function: getBankBalance ()                               *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function prompts player to enter a      *
 *              amount in the bank                           *
 * Input parameters: void                                    *
 * Returns: value indicating amount of money in the bank     *
 * Preconditions: None                                       *
 * Postconditions: Bank balance returned                     *
 *************************************************************/
double getBankBalance (void)
{
	double initBankBalance = 0.0;	/* initial bank balance */

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

/*************************************************************
 * Function: chatterMessages ()                              *
 * Date Created: September 30, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function prints an appropriate message  *
 *              dependent on the number of rolls taken so    *
 *              far by the player, the current balance, and  *
 *              whether or not the player just won his roll. *
 *              The parameter winLossNeither indicates the   *
 *              result of the previous roll.                 *
 * Input parameters: number of rolls, indicator of the       *
 *                   result of previous roll, initial and    *
 *                   current bank balance                    *
 * Returns: void                                             *
 * Preconditions: None                                       *
 * Postconditions: Chatter message will or will not be       *
 *                 printed out on screen. Depends if         *
 *                 conditions are met.                       *
 *************************************************************/
void chatterMessages (int numberRolls, int winLossNeither, 
	                  double initialBankBalance, double currentBankBalance)
{
	if (winLossNeither == WINS)
	{
		printf ("ROMNEY: You are a lucky bastard! I need you in my election committee.\n");

	}
	else 
	{
		printf ("OBAMA: Your such a Loser! Your bad luck, stay away from me...\n");
	}

	if (winLossNeither == 0 && 
		currentBankBalance == 0)
	{
		printf ("Sorry, you busted!\n");
	}
	else if (winLossNeither == 0 && 
		     currentBankBalance < (initialBankBalance * .5))
	{
		printf ("Oh, you're going for broke, huh?\n");
	}
	else if (winLossNeither == 1 && 
		     currentBankBalance > (initialBankBalance * .5) && 
			 currentBankBalance < initialBankBalance)
	{
		printf ("Aw c'mon, take a chance!\n");
	}
	else if (winLossNeither == 0 && 
		     currentBankBalance > initialBankBalance)
	{
		printf ("You're up big, now's the time to cash in your chips!\n");
	}
}

/* UTILITY FUNCTIONS */

/*************************************************************
 * Function: playAgain ()                                    *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function prints out the current balance *
 *              and prompts player to play more or not.      *
 * Input parameters: player's current balance on hand        *
 * Returns: status indicator, 1 for play more & 0 otherwise  *
 * Preconditions: current balance is not equal to zero,      *
 *                function should not be called if player    *
 *                does not have any money on hand            *
 * Postconditions: Status indicator returned                 *
 *************************************************************/
int playAgain (double currentBalance)
{
	char ch = '\0';        /* input for Y/N option */
	int playMore = -1;	   /* status indicator to play again */

	do {
		/* clears the screen */
		system ("cls");

		/* prints title on top of the screen */
		printTitle ();

		/* prints current balance */
		printf ("Current Balance: $%.2lf\n", currentBalance);

		/* prompts user if he wants to play more or not */
		printf ("Do you want to play more (Y/N)? ");
		fflush (stdin);  /* flushes previous escape characters */
		scanf ("%c", &ch);

		if (ch == 'y' || ch == 'Y')
		{
			/* indicates player chooses to play more */
			playMore = TRUE;
		}
		else if (ch == 'n' || ch == 'N')
		{
			/* indicates player doesn't want to play any more */
			playMore = FALSE;
		}
		else
		{
			/* warns user of invalid input */
			printf ("Invalid Input! Press ENTER to continue.\n");
			pressEnter ();
		}

	} while (playMore == -1);

	return playMore;
}

/*************************************************************
 * Function: getRandomNumber ()                              *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 29, 2012                    *
 * Description: This function generates a random number from *
 *              1 to a number specified by the input param-  *
 *              eter, maxNumber.                             *
 * Input parameters: Upper bound of the range of numbers to  *
 *                   from randomly                           *
 * Returns: Randomly selected number between 1 to maxNumber  *
 * Preconditions: srand () is initiated before this function *
 *                is called to get better random numbers     *
 * Postconditions: A random number was returned              *
 *************************************************************/
int getRandomNumber (int maxNumber)
{
	int number = 0;    /* output random number */

	number = (rand () % maxNumber) + 1;

	return number;
}

/*************************************************************
 * Function: animateDices ()                                 *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 29, 2012                    *
 * Description: This function simulates the two dices being  *
 *              rolled and prints out random dices on screen *
 * Input parameters: values for die one and die two          *
 * Returns: void                                             *
 * Preconditions: Random function is working properly and    *
 *                values for die one and two to be received  *
 *                were randomly selected. Windows.h must be  *
 *                included for Sleep () and Beep ()          *
 * Postconditions: Outputs selected two dices on the screen  *
 *************************************************************/
void animateDices (int dieOne, int dieTwo)
{
	int i = 0;	   /* counter */

	for (i = 0; i < DICE_NUMBER_OF_ROTATION; i++)
	{
		/* Clears the screen */
		system ("cls");

		/* Prints the title on top of the screen */
		printTitle ();

		/* Outputs 2 simulated dice on the screen 
		   based from the generated random number */
		drawDie (getRandomNumber (6));
		printf ("\n");
		drawDie (getRandomNumber (6));

		/* Makes a beep sound */
		Beep (523, 300);

		/* Pauses the program */
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

/*************************************************************
 * Function: drawDie ()                                      *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 29, 2012                    *
 * Description: This function accepts a number as argument   *
 *              and number determines which die to output on *
 *              the screen.                                  *
 * Input parameters: number from 1 to 6 (faces of a die)     *
 * Returns: void                                             *
 * Preconditions: None                                       *
 * Postconditions: Outputs selected die on screen            *
 *************************************************************/
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

/*************************************************************
 * Function: diceOne ()                                      *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 29, 2012                    *
 * Description: This function prints out a simulated picture *
 *              of a die with an upward face of 1 using '*'  *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: None                                       *
 * Postconditions: Outputs on screen die 1                   *
 *************************************************************/
void diceOne (void)
{
	printf ("              ***********\n");
	printf ("              *         *\n");
	printf ("              *    *    *\n");
	printf ("              *         *\n");
	printf ("              ***********\n");
}

/*************************************************************
 * Function: diceTwo ()                                      *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 29, 2012                    *
 * Description: This function prints out a simulated picture *
 *              of a die with an upward face of 2 using '*'  *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: None                                       *
 * Postconditions: Outputs on screen die 2                   *
 *************************************************************/
void diceTwo (void)
{
	printf ("              ***********\n");
	printf ("              *  *      *\n");
	printf ("              *         *\n");
	printf ("              *      *  *\n");
	printf ("              ***********\n");
}

/*************************************************************
 * Function: diceThree ()                                    *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 29, 2012                    *
 * Description: This function prints out a simulated picture *
 *              of a die with an upward face of 3 using '*'  *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: None                                       *
 * Postconditions: Outputs on screen die 3                   *
 *************************************************************/
void diceThree (void)
{
	printf ("              ***********\n");
	printf ("              *  *      *\n");
	printf ("              *    *    *\n");
	printf ("              *      *  *\n");
	printf ("              ***********\n");
}

/*************************************************************
 * Function: diceFour ()                                     *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 29, 2012                    *
 * Description: This function prints out a simulated picture *
 *              of a die with an upward face of 4 using '*'  *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: None                                       *
 * Postconditions: Outputs on screen die 4                   *
 *************************************************************/
void diceFour (void)
{
	printf ("              ***********\n");
	printf ("              *  *   *  *\n");
	printf ("              *         *\n");
	printf ("              *  *   *  *\n");
	printf ("              ***********\n");
}

/*************************************************************
 * Function: diceFive ()                                     *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 29, 2012                    *
 * Description: This function prints out a simulated picture *
 *              of a die with an upward face of 5 using '*'  *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: None                                       *
 * Postconditions: Outputs on screen die 5                   *
 *************************************************************/
void diceFive (void)
{ 
	printf ("              ***********\n");
	printf ("              *  *   *  *\n");
	printf ("              *    *    *\n");
	printf ("              *  *   *  *\n");
	printf ("              ***********\n");
}

/*************************************************************
 * Function: diceSix ()                                      *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 29, 2012                    *
 * Description: This function prints out a simulated picture *
 *              of a die with an upward face of 6 using '*'  *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: None                                       *
 * Postconditions: Outputs on screen die 6                   *
 *************************************************************/
void diceSix (void)
{
	printf ("              ***********\n");
	printf ("              *  *   *  *\n");
	printf ("              *  *   *  *\n");
	printf ("              *  *   *  *\n");
	printf ("              ***********\n");
}

/*************************************************************
 * Function: pressEnter ()                                   *
 * Date Created: October 1, 2012                             *
 * Date Last Modified: October 1, 2012                       *
 * Description: This function requires the user press the    *
 *              Enter key only. If input is invalid, it will *
 *              wait and ask user to press the Enter key.    *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: None                                       *
 * Postconditions: User pressed the Enter key. Program       *
 *                 continues to execute where it left off    *
 *************************************************************/
void pressEnter (void)
{
	char ch = '\0';

	do
	{
		fflush (stdin);
		scanf ("%c", &ch);
	} while (ch != '\n');
}

/* SETUP FUNCTIONS */

/*************************************************************
 * Function: setup ()                                        *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function initializes the srand () to be *
 *              to get random numbers to simulate values     *
 *              rolling a die. It also calls introScreen ()  *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: time.h included for time ()                *
 * Postconditions: srand () initiated and title shown on     *
 *                 screen                                    *
 *************************************************************/
void setup (void)
{
	/* initiates srand () function necessary for rand () */
	srand ((unsigned int) time (NULL));

	/* Animated welcome screen is displayed on the screen  */
	introScreen ();
}

/*************************************************************
 * Function: printMenu ()                                    *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function clears the screen and prints   *
 *              the title and awaits user to pick a menu     *
 *              item. Input error check implemented.         *
 * Input parameters: void                                    *
 * Returns: menu item chosen, 1 to start new game, 2 to      *
 *          show rules of the game & 3 to exit game          *
 * Preconditions: system () is part of the compiler's        *
 *                library and user using Windows OS          *
 * Postconditions: menu item chosen returned                 *
 *************************************************************/
char printMenu (void)
{
	char option = '\0';    /* menu option */

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

/*************************************************************
 * Function: printGameRules ()                               *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function clears the screen then jprints *
 *              the title of the game and prints the rules   *
 *              on how to play the game.                     *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: system () is part of the compiler's        *
 *                library and user using Windows OS          *
 * Postconditions: User understand the rules of the game     *
 *************************************************************/
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
	printf ("       <Press ENTER to continue>");
	pressEnter ();
}

/*************************************************************
 * Function: printTitle ()                                   *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function clears the screen then prompts *
 *              the title of CRAPS on screen.                *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: system () is part of the compiler's        *
 *                library and user using Windows OS          *
 * Postconditions: Prints the word CRAPS using * on screen   *
 *************************************************************/
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

/*************************************************************
 * Function: introScreen ()                                  *
 * Date Created: September 29, 2012                          *
 * Date Last Modified: September 30, 2012                    *
 * Description: This function clears the screen then prompts *
 *              an animated title of CRAPS on screen.        *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: Windows.h must be included for Sleep ()    *
 *                and Beep (). Also, it is defaulted to a    *
 *                Windows OS                                 *
 * Postconditions: Prints the word CRAPS using * on screen   *
 *************************************************************/
void introScreen (void)
{
	/* Clears the screen */
	system ("cls"); /* for MAC change to system("clear"); */
    printf ("******************************************\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("*                                        *\n");
	printf ("******************************************\n");
	/* Pauses the program for x-value in millilseconds */
	Sleep (1000);

	system ("cls");
	printf ("******************************************\n");
	printf ("* ******                                 *\n");
	printf ("* *                                      *\n");
	printf ("* *                                      *\n");
	printf ("* *                                      *\n");
	printf ("* ******                                 *\n");
	printf ("******************************************\n");
	/* Gives off a beeping sound */
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