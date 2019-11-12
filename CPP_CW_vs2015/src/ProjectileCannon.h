#pragma once
#include "DisplayableObject.h"

#include "ProjectileCannonFrag.h"


class Game;
class GameMain;


class ProjectileCannon :
	public ProjectileBasic
{
public:
	ProjectileCannon(Game* pEngine, GameMain* play, Enemy* target, int XPos, int YPos, int range, int rad, float spd);
	~ProjectileCannon();

	void Draw();

	int getDamage() {
		return damage;
	}

	int getRadius() {
		return radius;
	}

	int getSpeed() {
		return speed;
	}

	int getSpeedX() {
		return speedX;
	}

	int getSpeedY() {
		return speedY;
	}

	//If hit initialise fragmentation 
	void hit(int resistance, int targetID) {
		enemiesHit.push_back(targetID);
		penetration -= resistance;
		if (penetration <= 0) {
			fragment();
		}
	}

	//Check if hitting previously hit target
	bool checkIfPrevHit(int targetID) {
		bool prevHit = false;
		for (int i = 0; i < enemiesHit.size(); i++) {
			if (enemiesHit[i] == targetID) {
				prevHit = true;
			}
		}
		return prevHit;
	}

	std::vector<int> getEnemiesHit() {
		return enemiesHit;
	}

	void addHitEnemy(int enemyID) {
		enemiesHit.push_back(enemyID);
	}

	void fragment() {
		//Number of fragment projectiles to spawn
		int fragmentations = 1 + (rand() % 6);
		m_pMainEngine->ResizeVector(fragmentations);

		for (int i = fragmentations; i > 0; i--) {

			int fragVariationX;
			int fragVariationY;

			do {
				//Place them in a random area around intitial hit
				fragVariationX = m_iCurrentScreenX + (rand() % 32) - 16;
				fragVariationY = m_iCurrentScreenY + (rand() % 32) - 16;

			} while (fragVariationX < 1 || fragVariationY < 1);
			//printf("frag vary = %d\n", fragVariationY);

			//Create fragment object and add fragment to vectors 
			ProjectileCannonFrag* frag = new ProjectileCannonFrag(m_pMainEngine, playState, fragVariationX, fragVariationY, 5 + (rand() % 5), enemiesHit);
			m_pMainEngine->StoreObjectInArray(m_pMainEngine->getVectorSize() - i - 1, frag);
			playState->storeInProjectileVector(frag);
			fragments.push_back(frag);
		}
		destroySelf();
	}

	virtual void destroySelf() {
		

		SetVisible(false);
	}

private:
	std::vector<int> enemiesHit;
	std::vector<ProjectileCannonFrag*> fragments;

	//Projectile Damage
	int damage = 1;
	//Penetration factor, (enemies it can go through)
	int penetration = 1;

	//Target in X/Y to fly towards
	int targetX;
	int targetY;
	//Colour of projectile
	int m_iColour;
	//Projectiles radius
	int radius;
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

