/*************************************************************************
 * Filename: yahtzee.c                                                   *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012 ; Lab Section 7                            *
 * Programming Assignment 4: A Game of Yahtzee!                          *
 * Date: October 6, 2012                                                 *
 *                                                                       *
 * Description: This program implements the Yahtzee game. This file      *
 *              includes all the function definitions whose prototypes,  *
 *              standard libraries and constant macros are declared in   *
 *              the file yahtzee.h                                       *
 *************************************************************************/
#include "yahtzee.h"

/*************************************************************
 * Function: startNewGame ()                                 *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 7, 2012                       *
 * Description: This function is the main function to start  *
 *              a game of Yahtzee.                           *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: system (), gotoxy (), pressEnter must be   *
 *                defined and Windows.h must be included     *
 * Postconditions: Game ended                                *
 *************************************************************/
void startNewGame (void)
{
	int dice[5] = {0};                      /* tracks dice values every play */
	int holdDice[5] = {0};                  /* tracks what dice player wants to hold or unhold */

	int categorySelected [2][13] = {{0}};   /* tracks the category already selected */
	int scoreBoard [2][14] = {{0}};         /* tracks the score for every category */

	int i = 0;                              /* generic counter for loops */
	int numberOfRolls = 0;                  /* tracks number of rolls */
	int playerNumber = 1;                   /* identifies which player is playing */
	int category = 0;                       /* category chosen by player on a play */
	int score = 0;                          /* score of a category chosen by a player on a play */
	int numberOfPlay = 0;                   /* tracks number of play */
	int isGameOver = FALSE;                 /* a flag that determines if game has ended */

	char isRollAgain = '\0';                /* a flag that determines if player wants to roll dice again */

	/* clears the screen */
	system ("cls");	

	/* sets up the game board */
	setupGameBoard ();

	do
	{
		for (i = 0; i < NUMBER_OF_DICE; i++)
		{
			/* resets values for dice to zero */
			dice[i] = 0;				

			/* resets values for hold dice to none */
			holdDice[i] = 0;            
		}

		/* reset number of rolls to zero */
		numberOfRolls = 0;		

		/* alternate players */
		playerNumber = !playerNumber;	

		/* resets the dice area to blank */
		updateDiceArea (dice, holdDice, numberOfRolls);
            
		/* Prompts user to press ENTER key to roll the dice */
		printMessageBox ("Press <ENTER> to roll the dice", "", playerNumber + 1);
		pressEnter ();

		do
		{
			/* Get random values for the dice also considering
			   if a die was held by player or not */
			rollDice (dice, holdDice);

			/* Increments number of rolls */
			numberOfRolls++;

			/* Updates the dice area on screen */
			updateDiceArea (dice, holdDice, numberOfRolls);

			/* breaks out of loop if user has rolled 3 times  */
			if (numberOfRolls == 3) break; 

			/* Prompts if player wants to hold or unhold a die  */
			printMessageBox ("Press <SPACEBAR> to hold or unhold a die", 
                             "          Press <ENTER> to roll the dice", playerNumber + 1);

			/* Waits for user input to what dice to hold or unhold */
			chooseDiceToHold (holdDice);


			printMessageBox ("Roll Again? [Y/N]:", "", playerNumber + 1);

			do {
				/* Input Validation Loop */
				/* Waits for user to input 'Y' or 'N' */
				gotoxy (50, 21);
				isRollAgain = getche ();

				if (tolower (isRollAgain) != 'y' && tolower (isRollAgain) != 'n')
				{
					/* Alerts user at the message box for invalid input */
					printMessageBox ("Roll Again? [Y/N]:", 
                                     "          Invalid input!", playerNumber + 1);
				}
				else break; /* breaks out of loop if user input is valid */

			} while (1);

			/* breaks out of loop if user don't want to roll again */
			if (tolower (isRollAgain) == 'n') break;

		} while (1);

		do {
			/* Input Validation Loop */
			/* Prompts user at the message box to pick a category */
			printMessageBox ("Choose a category and press <ENTER>", "", playerNumber + 1);
			
			/* Waits for user to select a category */
			chooseCategory (&category);

			if (categorySelected [playerNumber][category - 1] == 1)
			{
				/* Alets user at the message box that category has already been selected */
				printMessageBox ("ERROR! Category already selected", 
                                 "          Press <ENTER> to select a new category", playerNumber + 1);
				pressEnter ();
			}
			else break;

		} while (1);	
		
		/* Computes score for the category selected */
		computeCategoryScore (dice, category, &score);

		/* Updates scoreBoard array with category score */
		scoreBoard [playerNumber][category - 1] = score;
		
		/* Category flagged that it has been selected */
		categorySelected [playerNumber][category - 1] = 1;  
		
		/* Updates the score board on screen */
		updateScoreBoard (playerNumber, category, score);

		/* Counts number of play */
		numberOfPlay++;

		if (numberOfPlay < 26)
		{
			/* Prompts current player that his turn has ended */
			printMessageBox ("Your turn is over. Next player!", 
                             "          Press <ENTER> to continue", playerNumber + 1);
			pressEnter ();
		}
		
		if (numberOfPlay == 26)	
		{
			/* All categories were selected, game is over */
			isGameOver = TRUE;
		}

	} while (!isGameOver);

	/* Totals upper score and determines if player
	   earned a bonus and prints the total score */
	finalizeScoreBoard (scoreBoard);

	/* Prompts user 'Thans for playing' */
	printMessageBox ("THANKS FOR PLAYING YAHTZEE!", 
                     "Press <ENTER> to return to MAIN MENU", 0);
	pressEnter ();
}


/*************************************************************
 * Function: setupGameBoard ()                               *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function sets up the board for the area *
 *              for dices and categories to play with border *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: borderScreen (), printScreenBorder () and  *
 *                gotoxy () must be defined                  *
 * Postconditions: Board successfully set up                 *
 *************************************************************/
void setupGameBoard (void)
{
	printf ("\n\n");
	printf ("             ROLL:0             CATEGORY            PLAYER 1   PLAYER 2\n\n");
	printf ("                          [   ] ONES                [      ]   [      ]\n");
	printf ("                          [   ] TWOS                [      ]   [      ]\n");
	printf ("                          [   ] THREES              [      ]   [      ]\n");
	printf ("                          [   ] FOURS               [      ]   [      ]\n");
	printf ("                          [   ] FIVES               [      ]   [      ]\n");
	printf ("                          [   ] SIXES               [      ]   [      ]\n");

	printf ("                          [   ]  THREE OF A KIND    [      ]   [      ]\n");
	printf ("                          [   ]  FOUR OF A KIND     [      ]   [      ]\n");
	printf ("                          [   ]  FULL HOUSE(25)     [      ]   [      ]\n");
	printf ("                          [   ]  SMALL STRAIGHT(30) [      ]   [      ]\n");
	printf ("                          [   ]  LARGE STRAIGHT(40) [      ]   [      ]\n");
	printf ("                          [   ]  YAHTZEE!(50)       [      ]   [      ]\n");
	printf ("                          [   ]  CHANCE             [      ]   [      ]\n\n\n");

	printf ("                                TOTAL               [      ]   [      ]\n");

	/* 'Dice and category' borders */
	borderScreen (20, 1, 78, 20);
	/* 'Prompt' border */
	borderScreen (20, 20, 78, 23);

	/* 'Screen' border */
	printScreenBorder ();

	/* correct corner for category upper left */
	gotoxy (20, 1);
	printf ("%c", 203);

	/* correct intersecting corner for category lower left */
	gotoxy (20, 20);
	printf ("%c", 204);

	/* correct corner for prompt upper right */
	gotoxy (78, 20);
	printf ("%c", 185);

	/* correct corner for prompt lower left */
	gotoxy (20, 23);
	printf ("%c", 202);
}

/*************************************************************
 * Function: rollDice ()                                     *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function simulates rolling a dice and   *
 *              retrieve random numbers for the array that   *
 *              holds the values for the 5 dice              *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: getRandomNumber () must be defined         *
 * Postconditions: Randomly selected values for the dice     *
 *                 successfully retrieved                    *
 *************************************************************/
void rollDice (int dice [], int holdDice [])
{
	int i = 0;

	for (i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (!holdDice [i]) dice [i] = getRandomNumber (6);
	}
}

/*************************************************************
 * Function: drawDie ()                                      *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function draws a dice on the screen     *
 *              specified with the face value and top left   *
 *              x and y position                             *
 * Input parameters: face value of a die and top left x and  *
 *                   y position                              *
 * Returns: void                                             *
 * Preconditions: die<NAME> () functions are defined         *
 * Postconditions: A specified die is drawn on the screen    *
 *************************************************************/
void drawDie (int dieValue, int x, int y)
{
	switch (dieValue)
	{
		case 0:
			dieBlank (x, y);
			break;

		case 1:
			dieOne (x, y);
			break;

		case 2:
			dieTwo (x, y);
			break;

		case 3:
			dieThree (x, y);
			break;

		case 4:
			dieFour (x, y);
			break;

		case 5:
			dieFive (x, y);
			break;

		case 6:
			dieSix (x, y);
			break;
	}
}

/*************************************************************
 * Function: chooseDiceToHold ()                             *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 7, 2012                       *
 * Description: This function lets user choose what dice to  *
 *              hold or unhold                               *
 * Input parameters: flag for dice to hold or unhold         *
 * Returns: void                                             *
 * Preconditions: gotoxy () must be defined                  *
 * Postconditions: Dice could either be held or not          *
 *************************************************************/
void chooseDiceToHold (int holdDice [])
{
	int cursorX = 15,
		cursorY = 4;
	char ch = '\0';

	gotoxy (cursorX, cursorY);

	do {
		ch = getch ();
		switch(ch) 
		{ 
			case ARROW_KEY_UP: 
				/* UP arrow key is pressed */
				if (cursorY == 4) 
				{
					cursorY = cursorY + 16;
					gotoxy (cursorX, cursorY);
				}	
				else if (cursorY > 4) 
				{
					cursorY -= 4;
					gotoxy (cursorX, cursorY);
				} 		
				break;

			case ARROW_KEY_DOWN: 
				/* DOWN arrow key is pressed */
				if (cursorY < 20) 
				{
					cursorY += 4;
					gotoxy (cursorX, cursorY);
				} 
				else if (cursorY == 20) 
				{
					cursorY = 4;
					gotoxy (cursorX, cursorY);
				}
				break; 

			case SPACE_BAR:
				/* SPACEBAR key is pressed */
				if (!(holdDice [(cursorY / 4) - 1]))
				{
					printf ("X");
					gotoxy (cursorX, cursorY);
				}
				else
				{
					printf (" ");
					gotoxy (cursorX, cursorY);
				}

				holdDice [(cursorY / 4) - 1] = !(holdDice [(cursorY / 4) - 1]);
				break;
		}
	} while (ch != 13);
}

/*************************************************************
 * Function: updateDiceArea ()                               *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 7, 2012                       *
 * Description: This function updates the dices on screen    *
 *              based on the new values of the dice while    *
 *              considering if member wants to hold some of  *
 *              the dice                                     *
 * Input parameters: value of the dice, what dice player     *
 *                   wants to hold and number of rolls       *
 * Returns: void                                             *
 * Preconditions: gotoxy () must be defined                  *
 * Postconditions: Dice area on screen updated               *
 *************************************************************/
void updateDiceArea (int dice[], int holdDice[], int rolls)
{
	int i = 0;

	for (i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (!holdDice [i]) drawDie (dice [i], 3, 2 + (i * 4));
	}

	gotoxy (18, 2);
	printf ("%d", rolls);
}

/*************************************************************
 * Function: finalizeScoreBoard ()                           *
 * Date Created: October 16, 2012                            *
 * Date Last Modified: October 16, 2012                      *
 * Description: This function updates scoreboard with the    *
 *              upper score total, if player earns bonus and *
 *              prints it on screen and each player's total  *
 *              score on screen                              *
 * Input parameters: score for both players for every        *
 *                   category                                *
 * Returns: void                                             *
 * Preconditions: gotoxy () must be defined                  *
 * Postconditions: Scoreboard completely filled with scores  *
 *************************************************************/
void finalizeScoreBoard (int scoreBoard [][14])
{
	int playerNumber = 0, i = 0;

	gotoxy (40, 17);
	printf ("UPPER SCORE:");
	gotoxy (40, 18);
	printf ("      BONUS:");

	for (playerNumber = 0; playerNumber < 2; playerNumber++)
	{
		scoreBoard [playerNumber][13] = 0;

		for (i = 0; i < NUMBER_OF_CATEGORIES; i++)
		{
			scoreBoard [playerNumber][13] += scoreBoard [playerNumber][i];
			if (i == SIXES - 1)
			{
				gotoxy (54 + (playerNumber * 11), 17);
				printf ("%4d", scoreBoard [playerNumber][13]);

				if (scoreBoard [playerNumber][13] >= BONUS_RANGE)
				{
					scoreBoard [playerNumber][13] += BONUS_POINTS;
					gotoxy (54 + (playerNumber * 11), 18);
					printf ("+%3d", BONUS_POINTS);					
				}
			}
		}
	}

	gotoxy (54, 19);
	printf ("%4d", scoreBoard [0][13]);
	gotoxy (54 + 11, 19);
	printf ("%4d", scoreBoard [1][13]);
}

/*************************************************************
 * Function: printMessageBox ()                              *
 * Date Created: October 15, 2012                            *
 * Date Last Modified: October 15, 2012                      *
 * Description: This function updates the message box        *
 * Input parameters: message for line 1 and line 2 and a     *
 *                   number that either specifies the player *
 *                   or 0 for special message                *
 * Returns: void                                             *
 * Preconditions: gotoxy () must be defined                  *
 * Postconditions: Message box updated                       *
 *************************************************************/
void printMessageBox (char msgLine1[], char msgLine2[], int number)
{
	/* Clears message box */
	gotoxy (21, 21);
	printf ("                                                         ");
	gotoxy (21, 22);
	printf ("                                                         ");

	/* Prints message */
	gotoxy (21, 21);
	if (number == 0) 
		printf ("%s", msgLine1);
	else 
		printf ("PLAYER %d: %s", number, msgLine1);
	gotoxy (21, 22);
	printf ("%s", msgLine2);
}

/*************************************************************
 * Function: updateScoreBoard ()                             *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 7, 2012                       *
 * Description: This function updates the score board on     *
 *              screen                                       *
 * Input parameters: player number, category to update and   *
 *                   score earned                            *
 * Returns: void                                             *
 * Preconditions: system () and gotoxy () must be defined    *
 *                and Windows.h must be included             *
 * Postconditions: Scoreboard updated on screen              *
 *************************************************************/
void updateScoreBoard (int playerNumber, int category, int score)
{
	int cursorX = 54, cursorY = 3;

	switch (category)
	{
		case ONES:
			gotoxy (cursorX + (playerNumber * 11), cursorY + ONES);
			printf ("%4d", score);
			break;

		case TWOS:
			gotoxy (cursorX + (playerNumber * 11), cursorY + TWOS);
			printf ("%4d", score);
			break;

		case THREES:
			gotoxy (cursorX + (playerNumber * 11), cursorY + THREES);
			printf ("%4d", score);
			break;

		case FOURS:
			gotoxy (cursorX + (playerNumber * 11), cursorY + FOURS);
			printf ("%4d", score);
			break;

		case FIVES:
			gotoxy (cursorX + (playerNumber * 11), cursorY + FIVES);
			printf ("%4d", score);
			break;

		case SIXES:
			gotoxy (cursorX + (playerNumber * 11), cursorY + SIXES);
			printf ("%4d", score);
			break;

		case THREE_OF_A_KIND:
			gotoxy (cursorX + (playerNumber * 11), cursorY + THREE_OF_A_KIND);
			printf ("%4d", score);
			break;

		case FOUR_OF_A_KIND:
			gotoxy (cursorX + (playerNumber * 11), cursorY + FOUR_OF_A_KIND);
			printf ("%4d", score);
			break;		

		case FULL_HOUSE:
			gotoxy (cursorX + (playerNumber * 11), cursorY + FULL_HOUSE);
			printf ("%4d", score);
			break;

		case SMALL_STRAIGHT:
			gotoxy (cursorX + (playerNumber * 11), cursorY + SMALL_STRAIGHT);
			printf ("%4d", score);
			break;

		case LARGE_STRAIGHT:
			gotoxy (cursorX + (playerNumber * 11), cursorY + LARGE_STRAIGHT);
			printf ("%4d", score);
			break;

		case YAHTZEE:
			gotoxy (cursorX + (playerNumber * 11), cursorY + YAHTZEE);
			printf ("%4d", score);
			break;

		case CHANCE:
			gotoxy (cursorX + (playerNumber * 11), cursorY + CHANCE);
			printf ("%4d", score);
			break;
	}
}

/*************************************************************
 * Function: computeCategoryScore ()                         *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 7, 2012                       *
 * Description: This function computes the score for the     *
 *              specified category                           *
 * Input parameters: dice array, category, score as result   *
 * Returns: void                                             *
 * Preconditions: system () and gotoxy () must be defined    *
 *                and Windows.h must be included             *
 * Postconditions: score value is updated from the calling   *
 *                 function.                                 *
 *************************************************************/
void computeCategoryScore (int dice [], int category, int *score)
{
	int i = 0;
	*score = 0;

	switch (category)
	{
		case ONES:
		case TWOS:
		case THREES:
		case FOURS:
		case FIVES:
		case SIXES:
			/* Just the sum of the dice with the same 
			   value of the category selected */
			for (i = 0; i < NUMBER_OF_DICE; i++)
			{
				if (dice [i] == category)
				{
					*score += category;
				}
			}
			break;

		case THREE_OF_A_KIND:
		case FOUR_OF_A_KIND:
		case CHANCE:
			/* The sum of all five dice */
			if (checkCategory (dice, category) || category == CHANCE)
			{
				for (i = 0; i < NUMBER_OF_DICE; i++)
				{
					*score += dice [i];
				}
			}
			break;

		case FULL_HOUSE:
			if (checkCategory (dice, category)) *score = 25;
			break;

		case SMALL_STRAIGHT:
			if (checkCategory (dice, category)) *score = 30;
			break;

		case LARGE_STRAIGHT:
			if (checkCategory (dice, category)) *score = 40;
			break;

		case YAHTZEE:
			if (checkCategory (dice, category)) *score = 50;
			break;
	}
}

/*************************************************************
 * Function: checkCategory ()                                *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 15, 2012                      *
 * Description: This function checks the category of the     *
 *              rolled dice                                  *
 * Input parameters: dice array, category, score as result   *
 * Returns: void                                             *
 * Preconditions: none                                       *
 * Postconditions: Returned a boolean value if category was  *
 *                 true or false                             *
 *************************************************************/
int checkCategory (int dice [], int category)
{
	int isACategory = FALSE;
	int checker [6] = {0, 0, 0, 0, 0, 0};
	int i = 0, j = 0;

	for (i = 0; i < NUMBER_OF_DICE; i++)
	{
		/* Tracks die with the same value */
		checker [dice [i] - 1]++;
	}

	if (category == THREE_OF_A_KIND) 
	{
		/* Three of a Kind selected */
		for (i = 0; i < 6; i++) 
		{
			if (checker[i] >= 3) 
			{
				isACategory = TRUE;
				break;
			}
		}
	} 
	else if (category == FOUR_OF_A_KIND) 
	{
		/* Four of a Kind selected */
		for (i = 0; i < 6; i++) 
		{
			if (checker[i] >= 4) 
			{
				isACategory = TRUE;
				break;
			}
		}			
	} 
	else if (category == YAHTZEE) 
	{
		/* Yahtzee selected */
		for (i = 0; i < 6; i++) 
		{
			if (checker[i] == 5) 
			{
				isACategory = TRUE;
				break;
			}
		}				
	} 
	else if (category == FULL_HOUSE) 
	{
		/* Full house selected */
		for (i = 0; i < 6; i++) 
		{
			if (checker[i] == 3 || checker[i] == 2) 
			{
				for (j = i + 1; j < 6; j++) 
				{
					if (checker[j] == 3 || checker[j] == 2) 
					{
						isACategory = TRUE;
						break;
					}
				}
			}
		}
	} 
	else if (category == LARGE_STRAIGHT) 
	{
		/* Large straight selected */
		if (checker[0] == 0) 
		{
			for (i = 1; i < 6; i++) 
			{
				if (checker[i] == 0) 
				{
					isACategory = FALSE;
					break;
				}
				isACategory = TRUE;
			}
		} 
		else 
		{
			for (i = 1; i < 5; i++) 
			{
				if (checker[i] == 0) 
				{
					isACategory = FALSE;
					break;
				}
				isACategory = TRUE;
			}
		}
	} 
	else if (category == SMALL_STRAIGHT) 
	{
		/* Small straight selected */
		if ((checker[0] == 0 && checker[1] == 0) ||
			(checker[0] == 1 && checker[1] == 0)) 
		{
			for (i = 2; i < 6; i++) 
			{
				if (checker[i] == 0) 
				{
					isACategory = FALSE;
					break;
				}
				isACategory = TRUE;
			}
		} 
		else if (checker[0] == 0) 
		{
			for (i = 1; i < 5; i++) 
			{
				if (checker[i] == 0) 
				{
					isACategory = FALSE;
					break;
				}
				isACategory = TRUE;
			}
		} 
		else 
		{
			for (i = 0; i < 4; i++) 
			{
				if (checker[i] == 0) 
				{
					isACategory = FALSE;
					break;
				}
				isACategory = TRUE;
			}		
		}
	}

	return isACategory;
}

/*************************************************************
 * Function: chooseCategory ()                               *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 7, 2012                       *
 * Description: This function lets user choose a category on *
 *              screen using arrow keys                      *
 * Input parameters: address to a category                   *
 * Returns: void                                             *
 * Preconditions: gotoxy () must be defined                  *
 * Postconditions: A category is selected by user            *
 *************************************************************/
void chooseCategory (int *category)
{
	int cursorX = 28,
        cursorY = 4;
	char ch = '\0';

	gotoxy (cursorX, cursorY);
	printf ("%c", CURSOR_SYMBOL);
	gotoxy (cursorX, cursorY);

	do {
		ch = getch ();
		switch(ch) 
		{ 
			case ARROW_KEY_UP: 
				/* UP arrow key is pressed */
				if (cursorY == 4) 
				{
					gotoxy (cursorX, cursorY);
					printf (" ");
					cursorY = 16;
					gotoxy (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					gotoxy (cursorX, cursorY);
				}	
				else if (cursorY > 4) 
				{
					gotoxy (cursorX, cursorY);
					printf (" ");
					cursorY--;
					gotoxy (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					gotoxy (cursorX, cursorY);
				} 		
				break;

			case ARROW_KEY_DOWN: 
				/* DOWN arrow key is pressed */
				if (cursorY < 16) 
				{
					gotoxy (cursorX, cursorY);
					printf (" ");
					cursorY++;
					gotoxy (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					gotoxy (cursorX, cursorY);
				} 
				else if (cursorY == 16) 
				{
					gotoxy (cursorX, cursorY);
					printf (" ");
					cursorY = 4;
					gotoxy (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					gotoxy (cursorX, cursorY);
				}
				break;
		}
		*category = cursorY - 3;
	} while (ch != 13);	

	gotoxy (cursorX, cursorY);
	printf (" ");
}



/*************************************************************
 * Function: printGameRules ()                               *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function clears the screen then prints  *
 *              prints the rules on how to play the game.    *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: system () is part of the compiler's        *
 *                library and user using Windows OS,         *
 *                printScreenBorder () must be defined       *
 * Postconditions: User understood the rules of the game     *
 *************************************************************/
void printGameRules (void)
{
	system ("cls");

	printf ("\n\n\n");
	printf ("   THE RULES OF YAHTZEE:\n\n");
	printf ("   The scorecard used for Yahtzee is composed of two sections. A upper       \n");
	printf ("   section and a lower section. A total of thirteen boxes or thirteen scoring\n");
	printf ("   combinations are divided amongst the sections. The upper section consists \n");
	printf ("   of boxes that are scored by summing the value of the dice matching the    \n");
	printf ("   faces of the box. If a player rolls four 3's, then the score placed in the\n");
	printf ("   3's box is the sum of the dice which is 12. Once a player has chosen to   \n");
	printf ("   score a box, it may not be changed and the combination is no longer in    \n");
	printf ("   play for future rounds. If the sum of the scores in the upper section is  \n");
	printf ("   greater than or equal to 63, then 35 more points are added to the players \n");
	printf ("   overall score as a bonus. The lower section contains a number of poker    \n");
	printf ("   like combinations. See the table provided below:                          \n");
	printf ("\n\n");
	printf ("                        << Press <ENTER> to continue... >>                     ");
	printScreenBorder ();
	pressEnter ();

	system ("cls");

	printf ("\n\n");
	printf ("         NAME       |           COMBINATION          |          SCORE\n");
	printf ("   -----------------+--------------------------------+-----------------------\n");
	printf ("   Three-of-a-kind  | Three dice with the same face  | Sum of all face values\n"); 
	printf ("                    |                                |     on the 5 dice     \n");
	printf ("   -----------------+--------------------------------+-----------------------\n");
	printf ("   Four-of-a-kind   |  Four dice with the same face  | Sum of all face values\n");
	printf ("                    |                                |     on the 5 dice     \n");
	printf ("   -----------------+--------------------------------+-----------------------\n");
	printf ("   Full house       | One pair and a three-of-a-kind |            25         \n");
	printf ("   -----------------+--------------------------------+-----------------------\n");
	printf ("   Small straight   |     A sequence of four dice    |            30         \n");
	printf ("   -----------------+--------------------------------+-----------------------\n");
	printf ("   Large straight   |     A sequence of five dice    |            40         \n");
	printf ("   -----------------+--------------------------------+-----------------------\n");
	printf ("\n\n");
	printf ("                        << Press <ENTER> to continue... >>                     ");
	printScreenBorder ();
	pressEnter ();

	system ("cls");
	printf ("\n\n");
	printf ("         NAME       |           COMBINATION          |          SCORE\n");
	printf ("   -----------------+--------------------------------+-----------------------\n");
	printf ("   Yahtzee (think   |  Five dice with the same face  |            50         \n");
	printf ("   five-of-a-kind)  |                                |                       \n");
	printf ("   -----------------+--------------------------------+-----------------------\n");
	printf ("   Chance           |  May be used for any sequence  | Sum of all face values\n");
	printf ("                    | of dice; this is the catch all |       on the 5 dice   \n");
	printf ("                    |           combination          |                       \n");
	printf ("   -----------------+--------------------------------+-----------------------\n");
	printf ("\n\n");
	printf ("                    << Press <ENTER> to return to MAIN MENU >>                 ");
	printScreenBorder ();
	pressEnter ();
}

/*************************************************************
 * Function: printGoodbye ()                                 *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function clears the screen then prints  *
 *              the a message saying thanks for playing.     *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: system () is part of the compiler's        *
 *                library and user using Windows OS,         *
 *                printScreenBorder () must be defined       *
 * Postconditions: Goodbye message printed                   *
 *************************************************************/
void printGoodbye (void)
{
	system ("cls");

	gotoxy (((SCREEN_BORDER_LOWER_X - SCREEN_BORDER_UPPER_X) / 2) - 16,
		     (SCREEN_BORDER_LOWER_Y - SCREEN_BORDER_UPPER_Y) / 2);
	printf ("Thanks for playing Yahtzee! Goodbye!");
	printScreenBorder ();
	pressEnter ();
	system ("cls");
}


/*************************************************************
 * Function: init ()                                         *
 * Date Created: October 7, 2012                             *
 * Date Last Modified: October 7, 2012                       *
 * Description: This function is used for initializing       *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: none                                       *
 * Postconditions: none                                      *
 *************************************************************/
void init (void)
{
	srand ((unsigned int) time (NULL));
}

/*************************************************************
 * Function: chooseMenuItem ()                               *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function lets the user pick a menu item *
 * Input parameters: void                                    *
 * Returns: chosen menu item                                 *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Value of menu item chosen is returned     *
 *************************************************************/
int chooseMenuItem (void)
{
	int cursorX = MENU_X + 2,
        cursorY = MENU_Y,
        menuItem = START_GAME;
	char ch = '\0';

	gotoxy (cursorX, cursorY);
	printf ("%c", CURSOR_SYMBOL);
	gotoxy (cursorX, cursorY);

	do {
		ch = getch ();
		switch(ch) 
		{ 
			case ARROW_KEY_UP: 
				/* UP arrow key is pressed */
				if (cursorY == MENU_Y) 
				{
					gotoxy (cursorX, cursorY);
					printf (" ");
					cursorY = MENU_Y + 2;
					gotoxy (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					gotoxy (cursorX, cursorY);

					menuItem = EXIT_GAME;
				}	
				else if (cursorY > MENU_Y) 
				{
					gotoxy (cursorX, cursorY);
					printf (" ");
					cursorY--;
					gotoxy (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					gotoxy (cursorX, cursorY);

					menuItem--;
				} 		
				break;

			case ARROW_KEY_DOWN: 
				/* DOWN arrow key is pressed */
				if (cursorY < MENU_Y + 2)
				{
					gotoxy (cursorX, cursorY);
					printf (" ");
					cursorY++;
					gotoxy (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					gotoxy (cursorX, cursorY);

					menuItem++;
				} 
				else if (cursorY == MENU_Y + 2) 
				{
					gotoxy (cursorX, cursorY);
					printf (" ");
					cursorY = MENU_Y;
					gotoxy (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					gotoxy (cursorX, cursorY);

					menuItem = START_GAME;
				}
				break; 
		}
	} while (ch != 13);

	return menuItem;
}

/*************************************************************
 * Function: mainScreen ()                                   *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function clears the screen then sets up *
 *              the main screen of the game                  *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: system () is part of the compiler's        *
 *                library and user using Windows OS,         *
 *                printScreenBorder (), borderScreen (),     *
 *                printTitle () and printMenu () must be     *
 *                defined                                    *
 * Postconditions: Printed the title and menu with border    *
 *************************************************************/
void printMainScreen (void)
{
	system ("cls");
	printScreenBorder ();
	/* prints main title on screen */
	
	printTitle (((SCREEN_BORDER_LOWER_X - SCREEN_BORDER_UPPER_X) / 2) - 27, 
                  SCREEN_BORDER_UPPER_Y + 2);

	/* draws border for the menu */
	borderScreen (((SCREEN_BORDER_LOWER_X - SCREEN_BORDER_UPPER_X) / 2) - 11, 
                    SCREEN_BORDER_UPPER_Y + 9, 
                  ((SCREEN_BORDER_LOWER_X - SCREEN_BORDER_UPPER_X) / 2) + 17, 
                    SCREEN_BORDER_UPPER_Y + 15);

	/* prints menu on screen */
	printMenu (MENU_X, MENU_Y);
}

/*************************************************************
 * Function: printScreenBorder ()                            *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function prints border screen           *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: none                                       *
 * Postconditions: Printed a screen border                   *
 *************************************************************/
void printScreenBorder (void)
{
	/* draws border for the window */
	borderScreen (SCREEN_BORDER_UPPER_X, SCREEN_BORDER_UPPER_Y, 
                  SCREEN_BORDER_LOWER_X, SCREEN_BORDER_LOWER_Y);
}

/*************************************************************
 * Function: printMenu ()                                    *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function prints the main menu           *
 * Input parameters: upper left corner x, y values           *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Printed the main menu on screen           *
 *************************************************************/
void printMenu (int x, int y)
{
	gotoxy (x, y);
	printf ("[   ] START GAME");
	gotoxy (x, y + 1);
	printf ("[   ] RULES OF THE GAME");
	gotoxy (x, y + 2);
	printf ("[   ] EXIT GAME");

	gotoxy (x - 7, y + 9);
	printf ("<< CHOOSE A MENU AND PRESS <ENTER> >>");
}

/*************************************************************
 * Function: printTitle ()                                   *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function clears the screen then prompts *
 *              the title of YAHTZEE! on screen.             *
 * Input parameters: upper left corner x, y values           *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Printed the word YAHTZEE using X on       *
 *                 screen                                    *
 *************************************************************/
void printTitle (int x, int y)
{
	gotoxy (x, y);
	printf ("XX  XX    XX    XX  XX  XXXXXX  XXXXXX  XXXXXX  XXXXXX  XX");
	gotoxy (x, y + 1);
	printf ("XX  XX  XX  XX  XX  XX    XX        X   XX      XX      XX");
	gotoxy (x, y + 2);
	printf (" XXXX   XXXXXX  XXXXXX    XX      XX    XXXX    XXXX    XX");
	gotoxy (x, y + 3);
	printf ("  XX    XX  XX  XX  XX    XX     X      XX      XX"); 
	gotoxy (x, y + 4);
	printf ("  XX    XX  XX  XX  XX    XX    XXXXXX  XXXXXX  XXXXXX  XX");
}

/*************************************************************
 * Function: borderScreen ()                                 *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function draws a border on the screen   *
 * Input parameters: upper left corner x and y value, and    *
 *                   lower right corner x and y value        *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Border with specified coordinates drawn   *
 *************************************************************/
void borderScreen (int upperLeftCornerX, int upperLeftCornerY,
				   int lowerRightCornerX, int lowerRightCornerY)
{
	int x = upperLeftCornerX;
	int y = upperLeftCornerY;

	gotoxy (upperLeftCornerX, upperLeftCornerY);
	printf ("%c", 201);
	gotoxy (lowerRightCornerX, upperLeftCornerY);
	printf ("%c", 187);

	gotoxy (upperLeftCornerX, lowerRightCornerY);
	printf ("%c", 200);
	gotoxy (lowerRightCornerX, lowerRightCornerY);
	printf ("%c", 188);

	while (x < lowerRightCornerX - 1)
	{
		gotoxy (++x, upperLeftCornerY);
		printf ("%c", 205);
		gotoxy (x, lowerRightCornerY);
		printf ("%c", 205);
	}

	while (y < lowerRightCornerY - 1)
	{
		gotoxy (upperLeftCornerX, ++y);
		printf ("%c", 186);
		gotoxy (lowerRightCornerX, y);
		printf ("%c", 186);
	}
}

/*************************************************************
 * Function: gotoxy ()                                       *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function moves to specified x, y coord- *
 *              inate on a windows screen console            *
 * Code source: http://www.dreamincode.net/                  *
 * Subfolder: forums/topic/92792-problem-with-gotoxy-in-     *
 *            visual-studio-professional-2008/               *
 * Posted by: bsaunders                                      *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: Must include Windows.h                     *
 * Postconditions: Cursor moved to specified x, y coordinate *
 *************************************************************/
void gotoxy(int x, int y)
{
    HANDLE stdOutput;
    COORD pos;

    stdOutput = GetStdHandle (STD_OUTPUT_HANDLE);

    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition (stdOutput, pos);
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

/*************************************************************
 * Function: getRandomNumber ()                              *
 * Date Created: October 7, 2012                             *
 * Date Last Modified: October 7, 2012                       *
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
 * Function: dieBlank ()                                     *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function draws a blank die              *
 * Input parameters: upper left x, y position of the die     *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Blank die is drawn                        *
 *************************************************************/
void dieBlank (int x, int y)
{
	gotoxy (x, y);
	printf ("+-------+");
	gotoxy (x, y + 1);
	printf ("|       |");
	gotoxy (x, y + 2);
	printf ("|   ?   | [   ]");
	gotoxy (x, y + 3);
	printf ("|       |");
	gotoxy (x, y + 4);
	printf ("+-------+");
}

/*************************************************************
 * Function: dieOne ()                                       *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function draws a die with a value 1     *
 * Input parameters: upper left x, y position of the die     *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Die with value 1 is drawn                 *
 *************************************************************/
void dieOne (int x, int y)
{
	gotoxy (x, y);
	printf ("+-------+");
	gotoxy (x, y + 1);
	printf ("|       |");
	gotoxy (x, y + 2);
	printf ("|   o   |");
	gotoxy (x, y + 3);
	printf ("|       |");
	gotoxy (x, y + 4);
	printf ("+-------+");
}

/*************************************************************
 * Function: dieTwo ()                                       *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function draws a die with a value 2     *
 * Input parameters: upper left x, y position of the die     *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Die with value 2 is drawn                 *
 *************************************************************/
void dieTwo (int x, int y)
{
	gotoxy (x, y);
	printf ("+-------+");
	gotoxy (x, y + 1);
	printf ("|     o |");
	gotoxy (x, y + 2);
	printf ("|       |");
	gotoxy (x, y + 3);
	printf ("| o     |");
	gotoxy (x, y + 4);
	printf ("+-------+");
}

/*************************************************************
 * Function: dieThree ()                                     *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function draws a die with a value 3     *
 * Input parameters: upper left x, y position of the die     *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Die with value 3 is drawn                 *
 *************************************************************/
void dieThree (int x, int y)
{
	gotoxy (x, y);
	printf ("+-------+");
	gotoxy (x, y + 1);
	printf ("|     o |");
	gotoxy (x, y + 2);
	printf ("|   o   |");
	gotoxy (x, y + 3);
	printf ("| o     |");
	gotoxy (x, y + 4);
	printf ("+-------+");
}

/*************************************************************
 * Function: dieFour ()                                      *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function draws a die with a value 4     *
 * Input parameters: upper left x, y position of the die     *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Die with value 4 is drawn                 *
 *************************************************************/
void dieFour (int x, int y)
{
	gotoxy (x, y);
	printf ("+-------+");
	gotoxy (x, y + 1);
	printf ("| o   o |");
	gotoxy (x, y + 2);
	printf ("|       |");
	gotoxy (x, y + 3);
	printf ("| o   o |");
	gotoxy (x, y + 4);
	printf ("+-------+");
}

/*************************************************************
 * Function: dieFive ()                                      *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function draws a die with a value 5     *
 * Input parameters: upper left x, y position of the die     *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Die with value 5 is drawn                 *
 *************************************************************/
void dieFive (int x, int y)
{
	gotoxy (x, y);
	printf ("+-------+");
	gotoxy (x, y + 1);
	printf ("| o   o |");
	gotoxy (x, y + 2);
	printf ("|   o   |");
	gotoxy (x, y + 3);
	printf ("| o   o |");
	gotoxy (x, y + 4);
	printf ("+-------+");
}

/*************************************************************
 * Function: dieSix ()                                       *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function draws a die with a value 6     *
 * Input parameters: upper left x, y position of the die     *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Die with value 6 is drawn                 *
 *************************************************************/
void dieSix (int x, int y)
{
	gotoxy (x, y);
	printf ("+-------+");
	gotoxy (x, y + 1);
	printf ("| o   o |");
	gotoxy (x, y + 2);
	printf ("| o   o |");
	gotoxy (x, y + 3);
	printf ("| o   o |");
	gotoxy (x, y + 4);
	printf ("+-------+");
}