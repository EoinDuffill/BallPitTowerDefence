#include "header.h"

#include "BaseEngine.h"

#include "TileManager.h"




// Override this to draw tiles.
void TileManager::DrawTileAt( 
		BaseEngine* pEngine, 
		SDL_Surface* pSurface, 
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY ) const
{
	// Base class implementation just draws some grey tiles
	unsigned int iColour = 0x101010 * ((iMapX+iMapY+GetValue(iMapX,iMapY))%16);
	printf("colour from tilemanager = %08u\n", iColour);
	pEngine->DrawRectangle( 
		iStartPositionScreenX,
		iStartPositionScreenY, 
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		iColour,
		pSurface );
}





// Draw all tiles, from start to end position
void TileManager::DrawAllTilesAt( 
	BaseEngine* pEngine, 
	SDL_Surface* pSurface, 
	int iMapXStart, int iMapYStart,
	int iMapXEnd, int iMapYEnd,
	int iStartPositionScreenX, int iStartPositionScreenY ) const
{
	for ( int iTX = iMapXStart ; iTX <= iMapXEnd ; iTX++ )
		for ( int iTY = iMapYStart ; iTY <= iMapYEnd ; iTY++ )
		{
			DrawTileAt( pEngine, pSurface, 
				iTX, iTY, 
				iStartPositionScreenX+GetTileWidth()*(iTX-iMapXStart),
				iStartPositionScreenY+GetTileHeight()*(iTY-iMapYStart) );
		}
}

// Draw all tiles, from start to end position
void TileManager::UpdateTileAt( 
	BaseEngine* pEngine, 
	int iMapX, int iMapY,
	int iNewTileValue,
	int iScreenLeftTilePosition, 
	int iScreenTopTilePosition )
{
	// Set the new Tile value
	SetValue( iMapX, iMapY, iNewTileValue );
	// Draw the tile to the background
	DrawTileAt( pEngine, pEngine->GetBackground(), 
		iMapX, iMapY,
		iScreenLeftTilePosition, iScreenTopTilePosition );
	// Copy the background to the foreground
	pEngine->CopyBackgroundPixels( 
		iScreenLeftTilePosition, iScreenTopTilePosition, 
		GetTileWidth(), GetTileHeight() );
}

