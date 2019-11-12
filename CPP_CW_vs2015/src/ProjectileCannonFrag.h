#pragma once
#include "DisplayableObject.h"


class ProjectileCannonFrag :
	public ProjectileBasic
{
public:
	ProjectileCannonFrag(Game* pEngine, GameMain* play, int XPos, int YPos, int rad, std::vector<int> enemies);
	~ProjectileCannonFrag();

	void Draw();

	void hit(int resistance, int targetID);

	void destroySelf() {
		SetVisible(false);
	}

	void updateSubClass();

	int getRadius() {
		return radius;
	}

	int getDamage() {
		return damage;
	}


private:
	std::vector<int> enemiesHit;

	//Projectile Damage
	int damage = 1;
	//Penetration factor, (enemies it can go through)
	int penetration = 1;

	//Projectiles radius
	int radius = 0;
	//Destruction counter
	int dCount = 0;

	Game* m_pMainEngine;
	GameMain* playState;
};

