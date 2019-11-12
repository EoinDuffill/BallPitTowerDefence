#include "header.h"

#include "Game.h"

#include "GameMain.h"

#include "Enemy.h"

#include "ProjectileSniper.h"



ProjectileSniper::ProjectileSniper(Game* pEngine, GameMain* play, Enemy* target, int XPos, int YPos, int range, int rad, int spd)
	: ProjectileBasic(pEngine, play, target, XPos, YPos, range, rad, spd)
{
	radius = rad;
	speed = spd;

	m_pMainEngine = pEngine;
	playState = play;
}


ProjectileSniper::~ProjectileSniper()
{
}

void ProjectileSniper::Draw() {

	if (!IsVisible())
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
		m_iCurrentScreenX - (radius - 1),
		m_iCurrentScreenY - (radius - 1),
		m_iCurrentScreenX + (radius - 1),
		m_iCurrentScreenY + (radius - 1),
		0xeded00);

	StoreLastScreenPositionForUndraw();

}
