#pragma once
#include "GameState.h"

#include "Game.h"

#define HIGHSCORES_TO_SHOW 10

class HighscoresState :
	public GameState
{
public:
	HighscoresState(Game* gameEngine) 
		: GameState() 
	{
		engine = gameEngine;
	}
	~HighscoresState();


	void initialise();

	void update();

	void MouseInput(int iButton, int iX, int iY);

	void KeyBoardInputDown(int iKeyCode);

private:

	//Handles which level highscores to display
	int selection = 0;

	//Data structure to hold name and score pairs
	

	//Array of highscorePair struct pointers, these will be displayed
	std::vector<highscorePair> allPairs;
	std::vector<highscorePair>::iterator it;

	//Buffer to hold information to print to screen
	char buff[64] = { NULL };

	Game* engine;
};

