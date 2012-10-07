#include "yahtzee.h"


/*************************************************************
 * Function: chooseMenuItem ()                               *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function lets the user pick a menu item *
 * Input parameters: void                                    *
 * Returns: chosen menu item                                 *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: value of menu item returned               *
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
			case 72: 
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

			case 80: 
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
 * Description: This function clears the screen then prompts *
 *              the title of YAHTZEE! on screen.             *
 * Input parameters: void                                    *
 * Returns: void                                             *
 * Preconditions: none                                       *
 * Postconditions: Prints the word YAHTZEE using X on screen *
 *************************************************************/
void printMainScreen (void)
{
	system ("cls");
	/* draws border for the window */
	borderScreen (SCREEN_BORDER_UPPER_X, SCREEN_BORDER_UPPER_Y, 
		          SCREEN_BORDER_LOWER_X, SCREEN_BORDER_LOWER_Y);
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
 * Function: printMenu ()                                    *
 * Date Created: October 6, 2012                             *
 * Date Last Modified: October 6, 2012                       *
 * Description: This function prints the main menu           *
 * Input parameters: upper left corner x, y values           *
 * Returns: void                                             *
 * Preconditions: gotoxy () function must be defined         *
 * Postconditions: Prints the main menu on screen            *
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
 * Postconditions: Prints the word YAHTZEE using X on screen *
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
 * Postconditions: Cursor moves to specified x, y coordinate *
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