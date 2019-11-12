#include "header.h"

#include "WaveManager.h"

#include "Enemy.h"

#include "GameMain.h"

#include "Game.h"

Enemy::Enemy(Game* pEngine, GameMain* play, int lvl, int wave)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
{
	playState = play;
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -radius;
	m_iStartDrawPosY = -radius;

	// Record the ball size as both height and width
	m_iDrawWidth = 2 * radius;
	m_iDrawHeight = 2 * radius;

	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = 50;
	m_iPreviousScreenY = m_iCurrentScreenY = 50;

	waveSpawned = wave;
	initLevel = level = lvl;

	switch (level) {
	case 1: health = 1; break;
	case 2: health = 2; break;
	case 3: health = 3; break;
	case 4: health = 4; break;
	case 5: health = 5; break;
	case 6: health = 15; break;
	default: health = 0; break;
	}


	m_iColour = GetEngine()->GetColour(level);

	calcSpeed();

	//printf("numerator = %d, denom = %d\n\n", speedNum, speedDenom);
	// And make it visible
	SetVisible(true);
}

Enemy::~Enemy()
{
}

void Enemy::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	//Black outline

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - radius,
		m_iCurrentScreenY - radius,
		m_iCurrentScreenX + (radius - 1),
		m_iCurrentScreenY + (radius - 1),
		0);

	//Smaller circle inside, colour determined by level

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - (radius - 1),
		m_iCurrentScreenY - (radius - 1),
		m_iCurrentScreenX + (radius - 2),
		m_iCurrentScreenY + (radius - 2),
		m_iColour );

	if (level == 6) {
		m_pMainEngine->DrawScreenPolygon(
			m_iCurrentScreenX - (radius - 3),
			m_iCurrentScreenY - (radius - 6),
			m_iCurrentScreenX - (radius - 6),
			m_iCurrentScreenY - (radius - 3),
			m_iCurrentScreenX + (radius - 4),
			m_iCurrentScreenY + (radius - 7),
			m_iCurrentScreenX + (radius - 7),
			m_iCurrentScreenY + (radius - 4),
			0x232323
		);


		m_pMainEngine->DrawScreenPolygon(
			m_iCurrentScreenX + (radius - 7),
			m_iCurrentScreenY - (radius - 4),
			m_iCurrentScreenX + (radius - 4),
			m_iCurrentScreenY - (radius - 7),
			m_iCurrentScreenX - (radius - 7),
			m_iCurrentScreenY + (radius - 4),
			m_iCurrentScreenX - (radius - 4),
			m_iCurrentScreenY + (radius - 7),
			0x232323
		);

	}

	// Store the position at which the object was last drawn
	StoreLastScreenPositionForUndraw();
}


void Enemy::DoUpdate(int iCurrentTime)
{
	if (health <= 0) {
		m_pMainEngine->eraseFromVector(this);
		return;
	}

	//only update the Enemy if it has spawned
	if (spawned) {
		//If the enemy is over the End tile and isVisible, not-visible, 1 life taken, spawned now not true
		if (playState->GetTile(m_iCurrentScreenX / TILE_SIZE, m_iCurrentScreenY / TILE_SIZE) == 4 && IsVisible()) {
			//printf("removing enemy\n");
			
			SetVisible(false);
			spawned = false;
			playState->takeXlives(health);
			health = 0;
			RedrawObjects();
			return;
		}

		//Store Screen position
		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iPreviousScreenY = m_iCurrentScreenY;

		//Same again but for Tile position
		XPrevTile = XCurrTile;
		YPrevTile = YCurrTile;

		//if the count is less than denomanator we are still working towards the average, else start over and reset. 
		//e.g. the goal for speed 5/2 is 5 pixels in 2 frames, first frame is 3, and second is 2, at which point we start over and go again
		if (denomCount < speedDenom) {
			//if our current average of speed in this run is less than the speed then we have a speed this frame which is the ceiling of the speed. 
			//It is added to running total to calculate the next average
			if (avgSpeed <= speedF) {
				speedFinal = ceil(speedF);
				speedTotal += speedFinal;
			}
			//else we will use the floor of the speed as currently our average speed is above the desired speed. speed added to the total again.
			else {
				speedFinal = floor(speedF);
				speedTotal += speedFinal;
			}
			//increment
			denomCount++;
			//calculate the average speed to be used next iteration if required
			avgSpeed = ((speedTotal * 1.0 )/ denomCount);
		}
		else {
			//reset
			denomCount = 0;
			speedTotal = 0;
			avgSpeed = 0;
		}

		//each case reflects each dir
		switch (dir % 4) {
		case 0: m_iCurrentScreenY -= speedFinal; totalDistance += speedFinal; break;
		case 1: m_iCurrentScreenX += speedFinal; totalDistance += speedFinal; break;
		case 2: m_iCurrentScreenY += speedFinal; totalDistance += speedFinal; break;
		case 3: m_iCurrentScreenX -= speedFinal; totalDistance += speedFinal; break;
		}

		// Ensure not off the screen
		if (m_iCurrentScreenX < radius) {
			m_iCurrentScreenX = radius;
		}

		if (m_iCurrentScreenX >= 800 - radius) {
			m_iCurrentScreenX = 800 - radius;
		}

		if (m_iCurrentScreenY >= 500 - radius) {
			m_iCurrentScreenY = 500 - radius;
		}

		if (m_iCurrentScreenY < radius) {
			m_iCurrentScreenY = radius;
		}

		//Current Tile calculated based on current pixel and TILE_SIZE
		XCurrTile = m_iCurrentScreenX / TILE_SIZE;
		YCurrTile = m_iCurrentScreenY / TILE_SIZE;

		//calc center of tile

		int tileCenterX = XCurrTile * TILE_SIZE + TILE_SIZE / 2;
		int tileCenterY = YCurrTile * TILE_SIZE + TILE_SIZE / 2;

		//When either X or Y Changes to a new tile, calculate the direction to take when conditions are met inside that tile
		if (XCurrTile != XPrevTile || YCurrTile != YPrevTile) {
			nextDir = playState->GetNextTileDir(XCurrTile, YCurrTile, XPrevTile, YPrevTile);
		}

		//Boolean dirChange set to true, IF the enemy has moves past the center point of the Current Tile
		switch (dir % 4) {
		case 0: if (tileCenterY - m_iCurrentScreenY >= 0) { dirChange = true; } break;
		case 1: if (tileCenterX - m_iCurrentScreenX <= 0) { dirChange = true; } break;
		case 2: if (tileCenterY - m_iCurrentScreenY <= 0) { dirChange = true; } break;
		case 3: if (tileCenterX - m_iCurrentScreenX >= 0) { dirChange = true; } break;
		}

		//Result of dirChange being true sets actual direction to the next Direction calculated earlier
		if (nextDir >= 0 && dirChange) {
			dir = nextDir;
		}
		//dirChange set to false as the direction just changed and doesnt need to be changed again until a new tile is found
		dirChange = false;

		// Ensure that the object gets redrawn on the display, if something changed
		RedrawObjects();
	}
}

void Enemy::calcSpeed() {
	speedF = 0.15 + 0.1*(level); //speed value based off of enemy level
	calcFrac(speedF);	//Recalculate speed numerators and denominators 
}

void Enemy::damageRecieved(int dmg) {
	//Subtract the dmg from the health
	health -= dmg;
	//printf("%d damage taken\n", dmg);
	//Update this enemy (colour might change, level might change, speed might change etc)
	updateEnemy();
}

void Enemy::updateEnemy() {

	//Health defining what current level the enemy is
	if (health >= 6) {
		level = 6;
	}
	else if (health == 5) {
		level = 5;
	}
	else if (health == 4) {
		level = 4;
	}
	else if (health == 3) {
		level = 3;
	}
	else if (health == 2) {
		level = 2;
	}
	else if (health == 1) {
		level = 1;
	}
	else {
		level = -1;
	}

	//recalculate speed
	calcSpeed();

	//If health <= 0 it is dead and will be destroyed next update, if still alive update speed
	if (health <= 0) {
		spawned = false;
		SetVisible(false);

	}
	else {
		m_iColour = GetEngine()->GetColour(level);
	}
}