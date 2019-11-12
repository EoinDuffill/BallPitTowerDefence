#pragma once
#include "DisplayableObject.h"

class Game;
class GameMain;

class ProjectileSniper :
	public ProjectileBasic
{
public:
	ProjectileSniper(Game* pEngine, GameMain* play, Enemy* target, int XPos, int YPos, int range, int rad, int spd);
	~ProjectileSniper();

	void Draw();

	int getDamage() {
		return damage;
	}

	void hit(int resistance, int targetID) {
		enemiesHit.push_back(targetID);
		penetration -= resistance;
		if (penetration <= 0) {
			SetVisible(false);
		}
	}

private:

	std::vector<int> enemiesHit;

	//Projectile Damage
	int damage = 6;
	//Penetration factor, (enemies it can go through)
	int penetration = 1;

	//Target in X/Y to fly towards
	int targetX;
	int targetY;
	//Colour of projectile
	int m_iColour;
	//Projectiles radius
	int radius = 0;
	//Overall distance to travel from start to finish
	int maxDistance;
	//X and Y components of the above value
	int maxXDistance;
	int maxYDistance;
	//Speed 
	float speed = 0;
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

