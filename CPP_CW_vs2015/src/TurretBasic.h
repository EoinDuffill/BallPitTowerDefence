#pragma once
#include "DisplayableObject.h"

#define TURRETWIDTH 50
#define BARRELSIZE 8

class GameMain;
class Game;

class TurretBasic :
	public DisplayableObject
{
public:
	TurretBasic(Game* pEngine, GameMain* play, int countS);
	~TurretBasic(void);

	virtual void Draw();
	virtual void DoUpdate(int iCurrentTime);

	//Set X of Object
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
	virtual void setShowRadius(bool rad) {
		showRadius = rad;
		RedrawWholeScreen();
	}
	//getter for radius
	virtual bool getRadius() {
		return showRadius;
	}

	//get range
	virtual int getRange() {
		return range;
	}

	//fire projectile
	virtual void fire(Enemy* target);

	float angleToTarget(int x0, int y0, int x1, int y1);

	void calcRotationalMatrix(float rads);
	virtual void initialiseRelativeCoords();
	void rotateCoords(int* shape, int shapeSize);

private:

	float rotMatrix[4];

	int barrelWidth = 7;
	int barrelHeight = 10;
	//Relative co-ords
	int barrel[BARRELSIZE];


	//show radius to screen
	bool showRadius = false;
	//Attack speed - attacks every N ticks
	int atkSpd = 165;
	//turret range
	int range = 125;
	//Tick turret spawn on
	int spawnedTick;
	//Main turret colour
	int m_iColour;

	GameMain* playState;
	Game* m_pMainEngine;
};

