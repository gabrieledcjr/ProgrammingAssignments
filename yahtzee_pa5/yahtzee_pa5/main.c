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

	printMainScreen ();
	menu = chooseMenuItem ();

	getchar ();

	return 0;
}