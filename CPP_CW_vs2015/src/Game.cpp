#include "header.h"

#include "Game.h"


void Game::SetupBackgroundBuffer() {

	//background
	//FillBackground(0x434343);

}

int Game::InitialiseObjects() {
	DrawableObjectsChanged();
	DestroyOldObjects();

	// Creates DisplayableObject array (vector)
	CreateObjectArray(1);

	//last value set to NULL
	StoreObjectInArray(0, NULL);


	gsm = new GameStateManager(this);

	return 0;
}

void Game::GameAction() {
	if (!IsTimeToAct()) // No sleep, will just keep polling constantly 
		return;

	gsm->update();

	SetTimeToAct(4);
}

void Game::MouseDown(int iButton, int iX, int iY) {

	gsm->MouseInput(iButton, iX, iY);
}

void Game::KeyDown(int iKeyCode) {
	gsm->KeyBoardDown(iKeyCode);
}

void Game::KeyUp(int iKeyCode) {
	gsm->KeyBoardUp(iKeyCode);
}