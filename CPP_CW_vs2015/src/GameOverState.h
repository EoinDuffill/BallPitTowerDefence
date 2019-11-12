#pragma once
#include "GameState.h"

#include "Game.h"

class GameOverState :
	public GameState
{
public:
	GameOverState(Game* gameEngine, int lvl, int scr) 
		: GameState()
	{
		engine = gameEngine;
		score = scr;
		level = lvl;
	}
	~GameOverState();

	void initialise();

	void update();

	void MouseInput(int iButton, int iX, int iY);

	void KeyBoardInputDown(int iKeyCode);

private: 
	int score = 0;
	int window = 0;
	int level = 0;

	//Array of highscorePair struct pointers, these will be displayed
	std::vector<highscorePair> allPairs;

	//holds the value for score so it can be printed on screen
	char scoreString[64];
	//holds the current name to br printed to screen
	char highscoreName[MAX_NAME_LENGTH + 1] = { NULL };
	//index into highscoreName
	int hscrNameIndex = 0;
	//string to hold the highscore to be put in file
	std::string highscore = "";
	
	//Engine pointer
	Game* engine;

public:

	//functor to compare highscore pair scores, taking in references to two highscore pair structs
	struct compareScores
	{
		bool operator()(const highscorePair& x, const highscorePair& y) const
		{
			return x.score > y.score;
		}
	};

};

