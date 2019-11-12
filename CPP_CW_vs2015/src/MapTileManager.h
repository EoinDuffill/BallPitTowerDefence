#pragma once
#include "tilemanager.h"

#include "MapTileManager.h"
class MapTileManager :
	public TileManager
{
public:
	MapTileManager();
	~MapTileManager();



	// Draw a tile at a location on the screen determined by the tile
	// position and the base X and Y co-ordinates
	// Draw a tile
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;


	// Get the size of a tile - width
	int GetMapWidth() const
	{
		return m_iMapWidth;
	}

	// Get the size of a tile - height
	int GetMapHeight() const
	{
		return m_iMapHeight;
	}
	//Initialise grid to hold values for buildable 
	void initialiseBuildableTiles(int* grid);
	//Grid for where turrets are
	void initialiseTurretGrid();
	//Place a turret in the grid
	void setTurretInGrid(int x, int y, DisplayableObject* obj);
	//Getter for the above
	DisplayableObject* getTurretInGrid(int x, int y);
	//Getter but from absolute index
	DisplayableObject* getTurretInGridIndex(int i);
	//Boolean for if you can build on that tile
	bool isTileBuildable(int x, int y);
	//Get the exact value for that tile
	int getTileBuildValue(int x, int y);
	//Setter for buildable grid
	void setTileBuildable(int x, int y, int build);

private:

	int* buildableGrid;

	DisplayableObject** turretGrid;
};

