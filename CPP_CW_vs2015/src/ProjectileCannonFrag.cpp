#include "header.h"

#include "Game.h"

#include "GameMain.h"

#include "Enemy.h"

#include "ProjectileCannonFrag.h"

#include "ProjectileCannon.h"




ProjectileCannonFrag::ProjectileCannonFrag(Game* pEngine, GameMain* play, int XPos, int YPos, int rad, std::vector<int> enemies)
	: ProjectileBasic(pEngine, play, XPos, YPos, rad, enemies)
{
	//Setup variables and pointers
	enemiesHit = enemies;

	m_pMainEngine = pEngine;
	playState = play;
	radius = rad;

	m_iStartDrawPosX = -radius;
	m_iStartDrawPosY = -radius;

	m_iDrawWidth = (2 * radius) + 1;
	m_iDrawHeight = (2 * radius) + 1;

}


ProjectileCannonFrag::~ProjectileCannonFrag()
{
}

void ProjectileCannonFrag::Draw() {


	if (!IsVisible())
		return;

	//Outline
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - radius,
		m_iCurrentScreenY - radius,
		m_iCurrentScreenX + radius,
		m_iCurrentScreenY + radius,
		0x990000);
	//Inner circle
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - (radius - 1),
		m_iCurrentScreenY - (radius - 1),
		m_iCurrentScreenX + (radius - 1),
		m_iCurrentScreenY + (radius - 1),
		0xff7700);

	StoreLastScreenPositionForUndraw();


}

void ProjectileCannonFrag::hit(int resistance, int targetID) {

	enemiesHit.push_back(targetID);
}

void ProjectileCannonFrag::updateSubClass() {
	//Reduce size of fragmentation, if min size destroyself
	if (radius > 1) {
		dCount++;
		if (dCount % 7 == 0) {
			radius--;
		}

	}
	else {
		destroySelf();
	}
}