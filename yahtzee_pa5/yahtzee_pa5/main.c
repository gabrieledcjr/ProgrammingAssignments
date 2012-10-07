/****************************************************************
 *  XX  XX    XX    XX  XX  XXXXXX  XXXXXX  XXXXXX  XXXXXX  XX  *
 *  XX  XX  XX  XX  XX  XX    XX        X   XX      XX      XX  *
 *	 XXXX   XXXXXX  XXXXXX    XX      XX    XXXX    XXXX    XX  * 
 *	  XX    XX  XX  XX  XX    XX     X      XX      XX          *
 *	  XX    XX  XX  XX  XX    XX    XXXXXX  XXXXXX  XXXXXX  XX  * 
 ****************************************************************/
#include "yahtzee.h"

int main (void)
{
	int menu = 0;

	init ();

	do {
		printMainScreen ();
		menu = chooseMenuItem ();
		
		switch (menu)
		{
			case START_GAME:
				startNewGame ();
				break;
			case GAME_RULES:
				printGameRules ();
				break;
			case EXIT_GAME:
				printGoodbye ();
				break;
		}
	} while (menu != EXIT_GAME);

	return 0;
}