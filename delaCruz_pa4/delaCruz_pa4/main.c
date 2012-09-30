#include "gameOfChance.h"



int main (void)
{	
	int playGame = 0;

	do
	{
		setup ();
		playGame = playANewGame ();

		if (playGame == 1)
			play ();

	} while (playGame);

	return 0;
}


	
	/* As the game progresses, print various messages to create some "chatter" such as, 
	   "Sorry, you busted!", 
	   or "Oh, you're going for broke, huh?", 
	   or "Aw cmon, take a chance!", 
	   or "You're up big, now's the time to cash in your chips!" */