#pragma once
#include "DisplayableObject.h"

#define SNIPERTURRETWIDTH 50

class GameMain;
class Game;

class TurretSniper :
	public TurretBasic
{
public:
	TurretSniper(Game* pEngine, GameMain* play, int countS);
	~TurretSniper(void);

	void Draw();
	void DoUpdate(int iCurrentTime);

	void setXPosition(int XPos) {
		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iCurrentScreenX = XPos;
	}

	//Set Y of Object
	void setYPosition(int YPos) {
		m_iPreviousScreenY = m_iCurrentScreenY;
		m_iCurrentScreenY = YPos;
	}

	int getXPosition() {
		return m_iCurrentScreenX;
	}

	int getYPosition() {
		return m_iCurrentScreenY;
	}
	//set show Radius, will then display it on next draw
	void setShowRadius(bool rad) {
		showRadius = rad;
		RedrawWholeScreen();
	}
	//getter for radius
	bool getRadius() {
		return showRadius;
	}

	//get range
	int getRange() {
		return range;
	}

	//fire projectile
	void fire(Enemy* target);

	//float angleToTarget(int x0, int y0, int x1, int y1);

	//void calcRotationalMatrix(float rads);
	void initialiseRelativeCoords();
	//void rotateCoords(int* shape, int shapeSize);

private:

	float rotMatrix[4];

	int rail[8];
	int barrel[8];
	int stock[6];

	//show radius to screen
	bool showRadius = false;
	//Attack speed - attacks every N ticks
	int atkSpd = 250;
	//turret range
	int range = 225;
	//Tick turret spawn on
	int spawnedTick;
	//Main turret colour
	int m_iColour;

	GameMain* playState;
	Game* m_pMainEngine;
};

