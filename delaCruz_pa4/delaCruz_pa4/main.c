#include "gameOfChance.h"


int main (void)
{	
	int isPlay = FALSE;
	char option = '\0';

	setup ();

	do
	{
		option = printMenu ();

		switch (option)
		{
			case START_NEW_GAME:
				play ();
				isPlay = TRUE;
				break;

			case HOW_TO_PLAY:
				printGameRules ();
				isPlay = TRUE;
				break;

			case EXIT_GAME:
				isPlay = FALSE;
				break;
		}

	} while (isPlay);

	return 0;
}