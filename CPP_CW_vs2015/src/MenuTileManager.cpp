#include "header.h"

#include "MenuState.h"

#include "MenuTileManager.h"



MenuTileManager::MenuTileManager(int tSize, Game* gameEngine)
	: TileManager(tSize, tSize)
{
	tileSize = tSize;
	engine = gameEngine;

	SetSize(WIDTH, HEIGHT);
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		if ((i / WIDTH) % 5 != 4) {
			//Set the value for the floor, excluding the boundaries
			SetValue(i % WIDTH, i / WIDTH, floorCol);
			selectionGrid[i] = (i / WIDTH) / 5;

		}
		else {
			//values for the boundaries
			SetValue(i % WIDTH, i / WIDTH, boundaryCol);
			selectionGrid[i] = -1;
		}
	}

	SetBaseTilesPositionOnScreen(0, 200);

	//Draw tiles based on their set value above
	DrawAllTilesAt(engine, engine->GetBackground(), 0, 0, WIDTH - 1, HEIGHT - 1, 0, 200);

	

}


MenuTileManager::~MenuTileManager()
{
}

// Override this to draw tiles.
void MenuTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	// Base class implementation just draws some grey tiles
	unsigned int iColour = GetValue(iMapX, iMapY);
	//Black rectangle, 1Pixel larger underneath
	pEngine->DrawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		0,
		pSurface);

	//Coloured pixel on top
	pEngine->DrawRectangle(
		iStartPositionScreenX + 1,
		iStartPositionScreenY + 1,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		iColour,
		pSurface);
}

int MenuTileManager::getSelection(int x, int y) {
	//x and y are raw pixel values
	//y - 200 to make 0,0 be at 0,200
	//Divide by tileSize to get in terms tiles
	//To 1D from 2D by multiplying by width and adding x
	return selectionGrid[(x / tileSize) + (WIDTH*((y - 200) / tileSize))];
}

void MenuTileManager::drawGroup(int x, int y, int tick) {
	//Record the tick at which the animation will start
	//Reset the animation width and finish values
	startTick = tick;
	animationCurrWidth = 0;
	animationFinished = false;

	//Take pixel values and make them relative to tilemanager
	int tileX = (x / tileSize);
	int tileY = ((y - 200) / tileSize);
	//Get value for selection at current point in time
	currSelection = selectionGrid[tileX + (WIDTH*tileY)];

	//Record the starting tile to draw animation at later
	startX = tileX;

	if (currSelection >= 0) {

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (j == tileX) {
					//Fill in the column that the MenuPointer is on
					UpdateTile(engine, tileX, i + (currSelection * 5), selectionCol);
				}
				else {
					//Rest is standard floor (for now)
					UpdateTile(engine, j, i + (currSelection * 5), floorCol);
				}
			}
		}
		
	}
	else {
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (i % 5 != 4) {
					//Reset all, this is when the MenuPointer steps into a boundary area
					UpdateTile(engine, j, i, floorCol);
				}
			}
		}
	}
	
}

void MenuTileManager::updateGroup(int tck) {
	//Animation
	//Only if a valid selection
	//Animating every 6 ticks
	if (currSelection >= 0 && !animationFinished && (tck - startTick) % 6 == 0 ) {
		//Each animation update increases width by 1 (e.g. draw 1 more column on either side)
		animationCurrWidth++;

		//Bools to handle if either side of the initial draw column has finished
		//If both of these values are true then the animation is finished
		bool animMinusFin = false;
		bool animPlusFin = false;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < animationCurrWidth; j++) {
				//Handles drawing to the left of the init col, draws until animCurrWidth is reached
				if (startX - animationCurrWidth >= -1) {
					UpdateTile(engine, startX - j, i + (currSelection * 5), selectionCol);
				}
				else {
					animMinusFin = true;
				}
				//Handles drawing to the right of the init col
				if (startX + animationCurrWidth <= WIDTH) {
					UpdateTile(engine, startX + j, i + (currSelection * 5), selectionCol);
				}
				else {
					animPlusFin = true;
				}

				//And bools for left and right of init col together, animation stops when this is true
				animationFinished = animPlusFin & animMinusFin;
			}
		}


	}


}

void MenuTileManager::resetGroups() {
	//Function to reset the floor tiles to blank floor tiles
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i % 5 != 4) {
				UpdateTile(engine, j, i, floorCol);
			}
		}
	}
}