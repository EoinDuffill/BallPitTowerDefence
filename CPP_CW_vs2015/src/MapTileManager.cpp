#include "header.h"

#include "GameMain.h"

#include "Enemy.h"

#include "MapTileManager.h"

#include "DisplayableObject.h"

MapTileManager::MapTileManager()
	: TileManager(TILE_SIZE, TILE_SIZE)
{
}


MapTileManager::~MapTileManager(void)
{
}

// Draw a tile at a location on the screen determined by the tile
void MapTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	//colours to use based on values in the grid
	unsigned int colorArray[] = { 0x737373, 0x000000, 0xffffff, 0xcc0000, 0x0000ff };

	pEngine->DrawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		colorArray[GetValue(iMapX, iMapY)],
		pSurface);
}

void MapTileManager::initialiseBuildableTiles(int* grid) {
	//Create array
	buildableGrid = new int[X_CUBE_AMOUNT * Y_CUBE_AMOUNT];

	//If the tile has value 0 it is buildable, otherwise not
	for (int i = 0; i < (X_CUBE_AMOUNT * Y_CUBE_AMOUNT); i++) {
		if (grid[i] == 0) {
			buildableGrid[i] = 1;
		}
		else {
			buildableGrid[i] = 0;
		}
	}
}

void MapTileManager::initialiseTurretGrid() {

	//Create DisplayableObject pointer array
	turretGrid = new DisplayableObject*[X_CUBE_AMOUNT * Y_CUBE_AMOUNT]();
}

void MapTileManager::setTurretInGrid(int x, int y, DisplayableObject* obj) {
	//Set an index to contain DisplayableObject pointer
	//Index turned into tile X and Y
	x = x / TILE_SIZE;
	y = y / TILE_SIZE;
	//Index then at Y rows down + offset in the row by X, hence the maths below
	turretGrid[x + (y * X_CUBE_AMOUNT)] = obj;
}

DisplayableObject* MapTileManager::getTurretInGrid(int x, int y) {
	//Maths for indexing same as setTurretInGrid
	x = x / TILE_SIZE;
	y = y / TILE_SIZE;

	return turretGrid[x + (y * X_CUBE_AMOUNT)];
}

DisplayableObject* MapTileManager::getTurretInGridIndex(int i) {
	return turretGrid[i];
}

int MapTileManager::getTileBuildValue(int x, int y) {
	//Maths for indexing same as setTurretInGrid
	x = x / TILE_SIZE;
	y = y / TILE_SIZE;

	return buildableGrid[x + (y * X_CUBE_AMOUNT)];

}

bool MapTileManager::isTileBuildable(int x, int y) {
	//Maths for indexing same as setTurretInGrid
	//Followed by returning a boolean
	x = x / TILE_SIZE;
	y = y / TILE_SIZE;

	int index = x + (y * X_CUBE_AMOUNT);

	if (buildableGrid[index] == 1) {
		return true;
	}
	else {
		return false;
	}
}

void MapTileManager::setTileBuildable(int x, int y, int build) {
	//Maths for indexing same as setTurretInGrid
	x = x / TILE_SIZE;
	y = y / TILE_SIZE;

	buildableGrid[x + (y * X_CUBE_AMOUNT)] = build;

}