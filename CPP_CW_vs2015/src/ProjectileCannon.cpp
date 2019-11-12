#include "header.h"

#include "Game.h"

#include "GameMain.h"

#include "Enemy.h"


#include "ProjectileCannon.h"



ProjectileCannon::ProjectileCannon(Game* pEngine, GameMain* play, Enemy* target, int XPos, int YPos, int range, int rad, float spd)
	: ProjectileBasic(pEngine, play, target, XPos, YPos, range, rad, spd)
{
	//Setup variables and pointers
	radius = rad;
	speed = spd;

	m_pMainEngine = pEngine;
	playState = play;

	m_iStartDrawPosX = -radius;
	m_iStartDrawPosY = -radius;

	m_iDrawWidth = (2 * radius) + 1;
	m_iDrawHeight = (2 * radius) + 1;

}


ProjectileCannon::~ProjectileCannon()
{
}

void ProjectileCannon::Draw() {

	if (!IsVisible() || radius == 0)
		return;
	//Outline
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - radius,
		m_iCurrentScreenY - radius,
		m_iCurrentScreenX + radius,
		m_iCurrentScreenY + radius,
		0);

	//Inner circle
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - radius + 1,
		m_iCurrentScreenY - radius + 1,
		m_iCurrentScreenX + radius - 1,
		m_iCurrentScreenY + radius - 1,
		0x007a06
	);

	StoreLastScreenPositionForUndraw();

}
