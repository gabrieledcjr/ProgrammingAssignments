/*************************************************************************
 * Filename: main.c                                                      *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012  ; Lab Section 7                           *
 * Programming Assignment 4: A Game of Chance "Craps"                    *
 * Date: September 30, 2012                                              *
 *                                                                       *
 * Description: This program implements a craps game according to the    *
 *              rules below. The game should allow for wagering. This    *
 *              means that you need to prompt that user for an initial   *
 *              bank balance from which wagers will be added or          *
 *              subtracted. Before each roll prompt the user for a wager.*
 *              Once a game is lost or won, the bank balance should be   *
 *              adjusted. As the game progresses, print various messages *
 *              to create some "chatter."                                *
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


int main (void)
{	
	int isPlay = FALSE;		/* status indicator if player wants to play again */
	char option = '\0';		/* option chosen from the menu */


	/* Shows intro screen and initializes srand() */
	setup ();

	do
	{
		/* Prints menu on the screen */
		option = printMenu ();

		switch (option)
		{
			case START_NEW_GAME:
				/* Plays a new game */
				play ();
				isPlay = TRUE;
				break;

			case HOW_TO_PLAY:
				/* Prints to the screen the rules of the game */
				printGameRules ();
				isPlay = TRUE;
				break;

			case EXIT_GAME:
				/* Exits out from the game */
				isPlay = FALSE;
				break;
		}

	} while (isPlay);

	return 0;
}