#pragma once
#include "DisplayableObject.h"

class Game;
class GameMain;

class ProjectileBasic :
	public DisplayableObject
{
public:
	ProjectileBasic(Game* pEngine, GameMain* play, Enemy* target, int XPos, int YPos, int range, int rad, float spd);
	ProjectileBasic(Game* pEngine, GameMain* play, int XPos, int YPos, int rad, std::vector<int> enemiesHit);
	~ProjectileBasic(void);

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

	virtual int getRadius() {
		return radius;
	}

	virtual int getDamage() {
		return damage;
	}

	virtual int getSpeed() {
		return speed;
	}

	virtual int getSpeedX() {
		return speedX;
	}

	virtual int getSpeedY() {
		return speedY;
	}

	virtual void setSpeedX(int sX) {
		speedX = sX;
	}

	virtual void setSpeedY(int sY) {
		speedY = sY;
	}

	virtual bool checkIfPrevHit(int targetID) {
		bool prevHit = false;
		for (int i = 0; i < enemiesHit.size(); i++) {
			if (enemiesHit[i] == targetID) {
				prevHit = true;
			}
		}
		return prevHit;
	}

	virtual void hit(int resistance, int targetID) {
		enemiesHit.push_back(targetID);
		penetration -= resistance;
		if (penetration <= 0) {
			destroySelf();
		}
	}

	virtual void destroySelf() {
		SetVisible(false);
	}

	virtual void updateSubClass() {

	}

private:

	std::vector<int> enemiesHit;

	//Projectile Damage
	int damage = 1;
	//Penetration factor, (enemies it can go through)
	int penetration = 2;
	//Stationary?
	const bool stationary;
	//Target in X/Y to fly towards
	int targetX = 0;
	int targetY = 0;
	//Projectiles radius
	int radius = 4;
	//Overall distance to travel from start to finish
	int maxDistance = 0;
	//X and Y components of the above value
	int maxXDistance = 0;
	int maxYDistance = 0;
	//Speed 
	float speed = 6;
	//X and Y component of speed (even if overall speed could be an int, these 2 values will likely be floats)
	float speedX = 0;
	float speedY = 0;
	//Final value for this frames direction moved (used for x, then overwitten for Y)
	int speedFinal;
	//running avg for X and Y
	float avgX = 0;
	float avgY = 0;
	//Running total for X and Y
	int countX = 0;
	int countY = 0;
	//Running totals of distance travelled so far in X and Y
	int totalDistX = 0;
	int totalDistY = 0;
	//Booleans to store if it has reached is destination in X and Y
	bool xReached = false;
	bool yReached = false;
	//Pointer to Game engine
	Game* m_pMainEngine;
	GameMain* playState;
};

