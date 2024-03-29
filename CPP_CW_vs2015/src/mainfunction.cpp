#include "header.h"

#include <ctime>

#include "templates.h"

// Needs one of the following #includes, to include the class definition
#include "BouncingBallMain.h"
#include "SimpleDemo.h"
#include "Demo1Main.h"
#include "Demo2Main.h"
#include "Demo3Main.h"
#include "Demo4Main.h"
//#include "FirstDemo.h"
#include "Game.h"

#define BASE_SCREEN_WIDTH 800
#define BASE_SCREEN_HEIGHT 600



int main(int argc, char *argv[])
{
	int iResult;

	// Send random number generator with current time
	::srand(time(0));

	//Needs just one of the two following lines:
	//BouncingBallMain oMain;
	//FirstDemo oMain;
	//SimpleDemo oMain;
	//Demo1Main oMain;
	//Demo2Main oMain;
	//Demo3Main oMain;
	//Demo4Main oMain;
	Game oMain;

	char buf[1024];
	sprintf( buf, "Ball Pit Tower Defense" );
	iResult = oMain.Initialise( buf, BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "LemonMilk.otf", 24 );
	iResult = oMain.MainLoop();
	oMain.Deinitialise();

	return iResult;
}
