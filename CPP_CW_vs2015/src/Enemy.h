#pragma once
#include "displayableobject.h"

#include "Enemy.h"

class Game;
class GameMain;

class Enemy :
	public DisplayableObject
{
public:
	Enemy(Game* pEngine, GameMain* playState, int lvl, int wave);
	~Enemy(void);

	void Draw();
	void DoUpdate(int iCurrentTime);

	//Set X position of Object
	void setXPosition(int XPos) {
		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iCurrentScreenX = XPos;
	}

	//Set Y position of Object
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

	int getLvl() {
		return level;
	}

	int getHealth() {
		return health;
	}
	//Setter for when the object is spawned
	void setSpawned(bool spawn, int tick) {
		spawned = spawn;
		level = initLevel;
		updateEnemy();
		totalDistance = 0;
		spawnedTick = tick;
	}

	//Getter for if it is spawned
	bool isSpawned() {
		return spawned;
	}

	int getDistanceTravelled() {
		return totalDistance;
	}

	int getRadius() {
		return radius;
	}

	int getWaveSpawned() {
		return waveSpawned;
	}

	//Return spawned tick, this number will always be unique as only MAX 1 enemy can be spawned per tick
	int getSpawnedTick() {
		return spawnedTick;
	}
	//Recalculate speed
	void calcSpeed();
	//Do damage to the enemy
	void damageRecieved(int dmg);
	//Update the values that can change in this enemy
	void updateEnemy();

	//Calculate the numerator and denomanator for speed float value
	//Numerator and denomanator Required for non-integer speed of DisplayableObject
	void calcFrac(double input)
	{
		//reset
		denomCount = 0;
		speedTotal = 0;
		avgSpeed = 0;

		double integral = floor(input);
		double frac = input - integral;

		const long precision = 1000000000; //accuracy.

		long gcd_ = gcd(round(frac * precision), precision); 

		speedDenom = precision / gcd_;
		speedNum = round(frac * precision) / gcd_;
	}

	//greatest common devisor, used in calculating numertors and denomantors
	long gcd(long a, long b)
	{
		if (a == 0)
			return b;
		else if (b == 0)
			return a;

		if (a < b)
			return gcd(a, b % a);
		else
			return gcd(b, a % b);
	}

private:
	//Colour of object
	int m_iColour;
	//Tick enemy was spawned on
	int spawnedTick;
	//Radius 
	int radius = 15;
	//Direction of Object
	int dir = 0;
	//Total distance travelled
	int totalDistance = 0;
	//Initial level of enemy
	int initLevel;
	//Level of the enemy
	int level;
	//Health of the enemy
	int health;
	//Wave that the enemy was spawned on
	int waveSpawned;
	//Non-integer speed value
	float speedF;
	//Numerator of speed
	int speedNum;
	//Denomanator of speed
	int speedDenom;
	//Value of speed to be used in THIS frame
	int speedFinal = 0;
	//Counter used to count up to the denomanator value
	int denomCount = 0;
	//Running total of speed in current counter
	int speedTotal = 0;
	//Average speed so far in the current counter
	float avgSpeed = 0;
	//X Value of previous Tile, initialised to a negative
	int XPrevTile = -1;
	//Y Value of previous Tile
	int YPrevTile = -1;
	//X Value of the current Tile, Values are relative to tile position not Pixel number
	int XCurrTile = 0;
	//Y Value of the current Tile
	int YCurrTile = 0;
	//Direction to be next used, when that change is required
	int nextDir = 0;
	//Boolean to determine whether to set current direction to the next direction
	bool dirChange = false;
	//Boolean to for if the object has been spawned
	bool spawned = false;

	Game* m_pMainEngine;
	GameMain* playState;
};
