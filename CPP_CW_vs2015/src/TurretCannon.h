#pragma once
#include "DisplayableObject.h"

#define CANNONTURRETWIDTH 50

class GameMain;
class Game;

class TurretCannon :
	public TurretBasic
{
public:
	TurretCannon(Game* pEngine, GameMain* play, int countS);
	~TurretCannon(void);

	void Draw();
	void DoUpdate(int iCurrentTime);

	bool getRadius() {
		return showRadius;
	}

	void setShowRadius(bool rad) {
		showRadius = rad;
		RedrawWholeScreen();
	}

	//get range
	int getRange() {
		return range;
	}


	//fire projectile
	void fire(Enemy* target);

	void initialiseRelativeCoords();

private:

	float rotMatrix[4];

	int rotatingBase[8];
	int barrelGuide[6];
	int barrelGuide2[6];

	//show radius to screen
	bool showRadius = false;
	//Attack speed - attacks every N ticks
	int atkSpd = 350;
	//turret range
	int range = 100;
	//Tick turret spawn on
	int spawnedTick;
	//Main turret colour
	int m_iColour;
	GameMain* playState;
	Game* m_pMainEngine;
};

