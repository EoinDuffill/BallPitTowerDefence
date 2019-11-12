#pragma once
#include "GameState.h"

#include "MovableObject.h"

#include "BouncingObject.h"

#include "MenuTileManager.h"

#include "Game.h"

class MenuState :
	public GameState
{
public:
	/*
	Constructor
	*/
	MenuState(Game* gameEngine)
		: GameState()
	{
		engine = gameEngine;
	}

	void initialise() {
		engine->FillBackground(0x4b5c77);

		//Reset the vector
		engine->ResetObjectVector();

		engine->Redraw(true);

		//Place new Displayable in object vector
		engine->ResizeVector(2);
		menuPointer = new MovableObject(engine);
		engine->StoreObjectInArray(0, menuPointer);

		//Place bouncing object in vector
		bouncingObj = new BouncingObject(engine);
		engine->StoreObjectInArray(1, bouncingObj);

		//Initialise the tile manager for the menu
		menuTileManager = new MenuTileManager(20, engine);


	}

	void update() {
		tick++;

		//Update Displayables
		engine->UpdateAllObjects(engine->GetTime());

		//Draw entire menu (many many Draw calls)
		drawMenu();

		//update value for selection (via menutilemanager)
		selectionFromGrid();

		//if the selection has changed we need to draw the new group
		if (selectionChanged()) {
			menuTileManager->drawGroup(menuPointer->GetXCentre(), menuPointer->GetYCentre(), tick);
		}

		//Handles tile animation
		menuTileManager->updateGroup(tick);

		//Leave this last
		prevSelection = selection;
	}

	void MouseInput(int iButton, int iX, int iY) {
		if (iButton == SDL_BUTTON_LEFT) {
			//If within certain y vals  move the menuPointer
			if (iY >= 200 && iY <= 580) {
				//Keep track of the previous selection (pre-move)
				prevSelection = selection;
				//Set the position to the mouse pos, the set funcs will keep it in it's bounds
				menuPointer->setXPosition(iX);
				menuPointer->setYPosition(iY);
				//Get new selection, post move
				selectionFromGrid();
				//If the selection changed reset the tiles
				if (selectionChanged()) {
					menuTileManager->resetGroups();
				}
			}
				
		}
		

	}


	void KeyBoardInputDown(int iKeyCode) {
		//Key presses handled
		//Escape closes program
		//Space sets the WaveManager to run if its ready to run.
		switch (iKeyCode)
		{
			//Arrow keys down sets movement in appropriate direction to true
		case SDLK_DOWN:
			menuPointer->setMoveDown(true); break;
		case SDLK_UP:
			menuPointer->setMoveUp(true); break;
		case SDLK_RIGHT:
			menuPointer->setMoveRight(true); break;
		case SDLK_LEFT:
			menuPointer->setMoveLeft(true); break;
		case SDLK_RETURN: //Change game state based on selection
			if (selection < 3 && selection >= 0) {
				engine->changeState('g', selection);
			}
			else if (selection == 3){
				engine->changeState('h');
			}
			
			break;

		case SDLK_ESCAPE:// End program when escape is pressed
			engine->SetExitWithCode(0);
			break;
		}
	}

	void KeyBoardInputUp(int iKeyCode) {
		switch (iKeyCode)
		{
			//Arrow keys up sets movement in appropriate direction to false, stoping the movement in that direction
		case SDLK_DOWN:
			menuPointer->setMoveDown(false); break;
		case SDLK_UP:
			menuPointer->setMoveUp(false); break;
		case SDLK_RIGHT:
			menuPointer->setMoveRight(false); break;
		case SDLK_LEFT:
			menuPointer->setMoveLeft(false); break;
		}
	}

	//Func to handle all draw calls
	void drawMenu();

	//Get current selection
	void selectionFromGrid();

	//Handles if selection has changed
	bool selectionChanged(); 

private:
	//Tick values, increases once per frame
	int tick = 0;

	//Colour to handles the highlighting of the chevrons
	unsigned int hLightTriCol;

	//Pointers to the Pointer, and the tilemanager
	MovableObject* menuPointer;
	MenuTileManager* menuTileManager;
	BouncingObject* bouncingObj;
	//Value to hold selection
	int selection = 0;
	//Value for the previous frames selection
	int prevSelection = 0;

	//Engine pointer
	Game* engine;
};

