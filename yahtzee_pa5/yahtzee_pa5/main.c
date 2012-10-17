/*************************************************************************
 *     XX  XX    XX    XX  XX  XXXXXX  XXXXXX  XXXXXX  XXXXXX  XX        *
 *     XX  XX  XX  XX  XX  XX    XX        X   XX      XX      XX        *
 *      XXXX   XXXXXX  XXXXXX    XX      XX    XXXX    XXXX    XX        * 
 *       XX    XX  XX  XX  XX    XX     X      XX      XX                *
 *       XX    XX  XX  XX  XX    XX    XXXXXX  XXXXXX  XXXXXX  XX        * 
 * Filename: main.c                                                      *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012 ; Lab Section 7                            *
 * Programming Assignment 4: A Game of Yahtzee!                          *
 * Date: October 6, 2012                                                 *
 *                                                                       *
 * Description: This program is a dice game called Yahtzee that was      *
 *              invented by Milton Bradley and Edwin S. Lowe in 1956.    *
 *              The challenge of the game is to outduel the other player *
 *              by scoring the most points. Points are obtained by       *
 *              rolling five 6-sided die across thirteen rounds. During  *
 *              each round, each player may roll the dice up to three    *
 *              times to make one of the possible scoring combinations.  *
 *              Once a combination has been achieved by the player, it   *
 *              may not be used again in future rounds, except for the   *
 *              Yahtzee combination may be used as many times as the     *
 *              player makes the combination. Each scoring combination   *
 *              has different point totals. Some of these totals are     *
 *              achieved through the accumulation of points across rolls *
 *              and some are obtained as fixed sequences of values.      *
 *************************************************************************/
#include "yahtzee.h"

int main (void)
{
	int menu = 0;

	/* initializes srand () */
	init ();

	do {
		/* prints title and menu on screen */
		printMainScreen ();

		/* requires user to choose a menu */
		menu = chooseMenuItem ();
		
		switch (menu)
		{
			case START_GAME:
				startNewGame ();    /* starts a new game */
				break;

			case GAME_RULES:
				printGameRules ();  /* prints the game rules */
				break;

			case EXIT_GAME:
				printGoodbye ();    /* prints a goodbye message */
				break;
		}

	} while (menu != EXIT_GAME);

	return 0;
}