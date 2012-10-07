#include "yahtzee.h"

void startNewGame (void)
{
	int die1 = 0, die2 = 0, die3 = 0, die4 = 0, die5 = 0;
	int holdDie1 = FALSE, holdDie2 = FALSE, holdDie3 = FALSE, holdDie4 = FALSE, holdDie5 = FALSE;

	int numberOfRolls = 0;
	int playerNumber = 1;		/* which player is playing */

	system ("cls");	

	setupGameBoard ();

	do
	{
		gotoxy (21, 21);
		printf ("PLAYER %d: Press <ENTER> to roll the dice                 ", playerNumber);
		gotoxy (21, 22);
		printf ("                                                         ");
		pressEnter ();

		do
		{
			rollDice (&die1, &die2, &die3, &die4, &die5, 
					  holdDie1, holdDie2, holdDie3, holdDie4, holdDie5);
			numberOfRolls++;
			updateDiceArea (die1, die2, die3, die4, die5, 
							holdDie1, holdDie2, holdDie3, holdDie4, holdDie5, numberOfRolls);
			gotoxy (21, 21);
			printf ("PLAYER %d: Type 'H' to hold a die and 'U' to unhold a die.", playerNumber);
			gotoxy (21, 22);
			printf ("          Press <ENTER> to roll the dice                 ");

			chooseDiceToHold (&holdDie1, &holdDie2, &holdDie3, &holdDie4, &holdDie5);

		} while (numberOfRolls != 3);

		gotoxy (21, 21);
		printf ("PLAYER %d: Choose a category and press <ENTER>            ", playerNumber);
		gotoxy (21, 22);
		printf ("                                                         ");
		pressEnter ();

		break;
	} while (1);
}

void chooseDiceToHold (int *holdDie1, int *holdDie2, int *holdDie3, int *holdDie4, int *holdDie5)
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
				else if (cursorY > 4) {
					cursorY -= 4;
					gotoxy (cursorX, cursorY);
				} 		
				break;

			case ARROW_KEY_DOWN: 
				/* DOWN arrow key is pressed */
				if (cursorY < 20) {
					cursorY += 4;
					gotoxy (cursorX, cursorY);
				} 
				else if (cursorY == 20) 
				{
					cursorY = 4;
					gotoxy (cursorX, cursorY);
				}
				break; 


			case 'h':
				printf ("H");
				gotoxy (cursorX, cursorY);

				if (cursorY == 4) *holdDie1 = TRUE;
				if (cursorY == 8) *holdDie2 = TRUE;
				if (cursorY == 12) *holdDie3 = TRUE;
				if (cursorY == 16) *holdDie4 = TRUE;
				if (cursorY == 20) *holdDie5 = TRUE;

				break;

			case 'u':
			case 'U':
				printf (" ");
				gotoxy (cursorX, cursorY);

				if (cursorY == 4) *holdDie1 = FALSE;
				if (cursorY == 8) *holdDie2 = FALSE;
				if (cursorY == 12) *holdDie3 = FALSE;
				if (cursorY == 16) *holdDie4 = FALSE;
				if (cursorY == 20) *holdDie5 = FALSE;

				break;
		}
	} while (ch != 13);
}

void updateDiceArea (int die1, int die2, int die3, int die4, int die5, 
	                 int holdDie1, int holdDie2, int holdDie3, int holdDie4, int holdDie5, int rolls)
{
	if (!holdDie1) drawDie (die1, 3, 2);
	if (!holdDie2) drawDie (die2, 3, 2 + 4);
	if (!holdDie3) drawDie (die3, 3, 2 + 8);
	if (!holdDie4) drawDie (die4, 3, 2 + 12);
	if (!holdDie5) drawDie (die5, 3, 2 + 16);

	gotoxy (18, 2);
	printf ("%d", rolls);
}

void drawDie (int dieValue, int x, int y)
{
	switch (dieValue)
	{
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

void rollDice (int *die1, int *die2, int *die3, int *die4, int *die5,
	           int holdDie1, int holdDie2, int holdDie3, int holdDie4, int holdDie5)
{
	if (!holdDie1) *die1 = getRandomNumber (6);
	if (!holdDie2) *die2 = getRandomNumber (6);
	if (!holdDie3) *die3 = getRandomNumber (6);
	if (!holdDie4) *die4 = getRandomNumber (6);
	if (!holdDie5) *die5 = getRandomNumber (6);
}

void setupGameBoard (void)
{
	int dieCounter = 0, yPositionDie = 2;

	printf ("\n\n");
    printf ("             ROLL:0             CATEGORY            PLAYER 1   PLAYER 2\n\n");
	printf ("                          [   ] ONES                [      ]   [      ]\n");
	printf ("                          [   ] TWOS                [      ]   [      ]\n");
	printf ("                          [   ] THREES              [      ]   [      ]\n");
	printf ("                          [   ] FOURS               [      ]   [      ]\n");
	printf ("                          [   ] FIVES               [      ]   [      ]\n");
	printf ("                          [   ] SIXES               [      ]   [      ]\n\n");

	printf ("                          [   ] THREE OF A KIND     [      ]   [      ]\n");
	printf ("                          [   ] FOUR OF A KIND      [      ]   [      ]\n");
	printf ("                          [   ] FULL HOUSE(25)      [      ]   [      ]\n");
	printf ("                          [   ] SMALL STRAIGHT(30)  [      ]   [      ]\n");
	printf ("                          [   ] LARGE STRAIGHT(40)  [      ]   [      ]\n");
	printf ("                          [   ] YAHTZEE!(50)        [      ]   [      ]\n");
	printf ("                          [   ] CHANCE              [      ]   [      ]\n\n");

	printf ("                                TOTAL               [      ]   [      ]\n");

	for (dieCounter = 0; dieCounter < NUMBER_OF_DICE; dieCounter++)
	{
		dieBlank (3, yPositionDie);
		yPositionDie += 4;
	}

	/* dice and category borders */
	borderScreen (20, 1, 
		          78, 20);
	/* Prompt border */
	borderScreen (20, 20, 
		          78, 23);
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
    printf ("   Yahtzee (think   |  Five dice with the same face  |            50         \n");
	printf ("   five-of-a-kind)  |                                |                       \n");
	printf ("   -----------------+--------------------------------+-----------------------\n");
	printf ("   Chance           |  May be used for any sequence  | Sum of all face values\n");
	printf ("                    | of dice; this is the catch all |       on the 5 dice   \n");
	printf ("                    |           combination          |                       \n");
	printf ("                << Press <ENTER> to return to MAIN MENU >>                     ");
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
				else if (cursorY > MENU_Y) {
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
				if (cursorY < MENU_Y + 2) {
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

    stdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(stdOutput, pos);
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