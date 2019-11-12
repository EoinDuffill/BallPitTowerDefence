#pragma once

class Game;
class GameState;

class GameStateManager
{


public:
	GameStateManager(Game* gameEngine);
	~GameStateManager();

	void update();

	void KeyBoardDown(int iKeyCode);

	void KeyBoardUp(int iKeyCode);

	void MouseInput(int iButton, int iX, int iY);

	void changeState(char s);

	void changeState(char s, int lvl);

	void changeState(char s, int lvl, int scr);

private:

	GameState* currentState;
	GameState* previousState;
	Game* engine;

};

