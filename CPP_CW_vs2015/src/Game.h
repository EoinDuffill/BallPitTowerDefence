#pragma once

#include "BaseEngine.h"

#include "GameStateManager.h"

class Game :
	public BaseEngine
{
public:
	/*
	Constructor
	*/
	Game()
		: BaseEngine(1) // Pass OBJECT_COUNT + 1 to superclass constructor
	{
	}
	~Game() {}
	//Initialises the Background, tilemanager and wavemanager
	void SetupBackgroundBuffer();
	//Initialise the vector
	int InitialiseObjects();
	//Run each frame
	void GameAction();

	//handing User input
	void MouseDown(int iButton, int iX, int iY);

	void KeyDown(int iKeyCode);

	void KeyUp(int iKeyCode);

	void changeState(char s) {
		gsm->changeState(s);
	}

	void changeState(char s, int lvl) {
		gsm->changeState(s, lvl);
	}

	void changeState(char s, int lvl, int scr) {
		gsm->changeState(s, lvl, scr);
	}


private:

	GameStateManager* gsm;
};

