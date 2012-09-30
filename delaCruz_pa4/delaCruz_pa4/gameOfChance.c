#include "gameOfChance.h"

void play (void)
{
	int dieOne = 0, dieTwo = 0,
		sumDice = 0, playerPoint = 0,
		gameStatus = 0, numberOfRolls = 0,
		playMore = 0;
	double initialBankBalance = 0.0,
		   balance = 0.0,
		   wager = 0.0;

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
		printf ("Press any key to roll the dice\n");
		getch();
		dieOne = rollDie ();
		dieTwo = rollDie ();
		animateDices (dieOne, dieTwo);

		//printf ("Die 1: %d, Die 2: %d\n", dieOne, dieTwo);

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
					printf ("<Press any key to roll the dice>\n");
					getch();
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
		printf ("Current Balance: $%.2lf\n", balance);
		numberOfRolls++;

		if (balance > 0 && playAgain ())
		{
			playMore = 1;
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
			balance += wager + (floor (wager) * WINNING_PERCENT_FROM_WAGER);
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


/* UTILITY FUNCTIONS */

int playAgain (void)
{
	char ch = '\0';
	int playMore = 0;

	printf ("Do you want to play more (Y/N)? ");
	scanf (" %c", &ch);

	if (ch == 'y' || ch == 'Y')
		playMore = 1;

	return playMore;
}

void animateDices (int dieOne, int dieTwo)
{
	int i = 0;

	for (i = 0; i < 15; i++)
	{
		system ("cls");
		printTitle ();
		drawDie (getRandomNumber (6));
		printf ("\n");
		drawDie (getRandomNumber (6));
		Sleep (200);
	}

	system ("cls");
	printTitle ();
	drawDie (dieOne);
	printf ("\n");
	drawDie (dieTwo);
	printf ("\n");
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

	/* Prints the Rules of the Game */
	printGameRules ();
}

void printGameRules (void)
{

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
	system ("cls");
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
	printf ("* ******  *****    ****   *****    ***** *\n");
	printf ("* *       *    *  *    *  *    *  *      *\n");
	printf ("* *       *****   ******  *****    ****  *\n");
	printf ("* *       *    *  *    *  *            * *\n");
	printf ("* ******  *    *  *    *  *       *****  *\n");
	printf ("******************************************\n");
	printf ("\n");
	printf ("***  PRESS ANY KEY TO START THE GAME   ***\n");
	Beep (698, 200);
	getch ();
	system ("cls");			/* for MAC change to system("clear"); */
}