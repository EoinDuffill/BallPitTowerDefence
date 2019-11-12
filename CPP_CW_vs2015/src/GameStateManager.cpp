#include "header.h"

#include "Game.h"

#include "GameStateManager.h"

#include "GameMain.h"

#include "MenuState.h"

#include "GameOverState.h"

#include "HighscoresState.h"

GameStateManager::GameStateManager(Game* gameEngine)
{
	engine = gameEngine;
	currentState = new MenuState(engine);
	currentState->initialise();
}


GameStateManager::~GameStateManager()
{
}

void GameStateManager::update() {
	currentState->update();
}

void GameStateManager::KeyBoardDown(int iKeyCode) {
	currentState->KeyBoardInputDown(iKeyCode);
}
void GameStateManager::KeyBoardUp(int iKeyCode) {
	currentState->KeyBoardInputUp(iKeyCode);
}

void GameStateManager::MouseInput(int iButton, int iX, int iY) {
	currentState->MouseInput(iButton, iX, iY);
}

void GameStateManager::changeState(char s) {

	switch (s)
	{
	case 'm':currentState = new MenuState(engine); currentState->initialise(); break;
	case 'g':currentState = new GameMain(engine, 0); currentState->initialise(); break;
	case 'h':currentState = new HighscoresState(engine); currentState->initialise(); break;
	}


}


void GameStateManager::changeState(char s, int lvl) {
	switch (s)
	{
	case 'g':currentState = new GameMain(engine, lvl); currentState->initialise(); break;
	default: break;
	}

}

void GameStateManager::changeState(char s, int lvl, int scr) {
	switch (s)
	{
	case 'l':currentState = new GameOverState(engine, lvl, scr); currentState->initialise(); break;
	default: break;
	}

}
