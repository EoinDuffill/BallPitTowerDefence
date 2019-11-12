#pragma once
#include "TileManager.h"

#define WIDTH 10

#define HEIGHT 19

class MenuTileManager :
	public TileManager
{
public:
	MenuTileManager(int tileSize, Game* gameEngine);
	~MenuTileManager();

	void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;

	//get current selection value at x,y. Input Pixel data
	int getSelection(int x, int y);
	//Draw the column of the current selection in the XPos of the MenuPointer, and reset the animation to start again
	void drawGroup(int x, int y, int tick);
	//Handles animation of the cols left and right of the drawGroup col
	void updateGroup(int tck);
	//Resets the floor values to default floor values
	void resetGroups();

private:

	//Engine pointer, required for changing gamestate etc
	Game* engine;

	//1 int per 1 tile, each represents what the selection should be at a given tile
	int selectionGrid[WIDTH * HEIGHT];
	//TileSize
	int tileSize;
	//Tick that animation started at
	int startTick = 0;
	//Tile XPos that animation is centered around
	int startX = 0;
	//Value to hold the current width drawn by the animation
	int animationCurrWidth = 0;
	//Current selection
	int currSelection = 0;
	bool animationFinished = false;

	//Colours for the floor, selected floor, and the boundaries inbetween selections
	unsigned int boundaryCol = 0x333333;
	unsigned int floorCol = 0xd3d3d3;
	unsigned int selectionCol = 0x009900;
};

