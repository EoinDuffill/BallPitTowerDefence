#include "header.h"

#include "Game.h"

#include "GameMain.h"

#include "ProjectileSniper.h"

#include "TurretSniper.h"



TurretSniper::TurretSniper(Game* pEngine, GameMain* play, int countS)
	: TurretBasic(pEngine, play, countS)
{
	m_pMainEngine = pEngine;
	playState = play;

	//Initialise Relative coords
	initialiseRelativeCoords();
}


TurretSniper::~TurretSniper()
{
}

void TurretSniper::Draw() {


	if (!IsVisible())
		return;
	//Circle outline
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - 20,
		m_iCurrentScreenY - 20,
		m_iCurrentScreenX + 19,
		m_iCurrentScreenY + 19,
		0
	);

	//Main circle
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - 19,
		m_iCurrentScreenY - 19,
		m_iCurrentScreenX + 18,
		m_iCurrentScreenY + 18,
		0x565656
	);

	//Center circle
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - 8,
		m_iCurrentScreenY - 8,
		m_iCurrentScreenX + 7,
		m_iCurrentScreenY + 7,
		0
	);

	//Turret parts to rotate
	m_pMainEngine->DrawScreenPolygon(
		m_iCurrentScreenX + rail[0],
		m_iCurrentScreenY + rail[1],
		m_iCurrentScreenX + rail[2],
		m_iCurrentScreenY + rail[3],
		m_iCurrentScreenX + rail[4],
		m_iCurrentScreenY + rail[5],
		m_iCurrentScreenX + rail[6],
		m_iCurrentScreenY + rail[7],
		0);

	m_pMainEngine->DrawScreenPolygon(
		m_iCurrentScreenX + barrel[0],
		m_iCurrentScreenY + barrel[1],
		m_iCurrentScreenX + barrel[2],
		m_iCurrentScreenY + barrel[3],
		m_iCurrentScreenX + barrel[4],
		m_iCurrentScreenY + barrel[5],
		m_iCurrentScreenX + barrel[6],
		m_iCurrentScreenY + barrel[7],
		0x840000);

	m_pMainEngine->DrawScreenTriangle(
		m_iCurrentScreenX + stock[0],
		m_iCurrentScreenY + stock[1],
		m_iCurrentScreenX + stock[2],
		m_iCurrentScreenY + stock[3],
		m_iCurrentScreenX + stock[4],
		m_iCurrentScreenY + stock[5],
		0x840000
	);

	StoreLastScreenPositionForUndraw();
}

void TurretSniper::DoUpdate(int iCurrentTime) {
	//Can shoot every 'x' ticks
	if ((spawnedTick + iCurrentTime) % atkSpd == 0) {
		//Finds a target
		Enemy* target = playState->getTarget(m_iCurrentScreenX, m_iCurrentScreenY, range);
		//If it exists fire at it
		if (target != NULL) {

			//Shoot projectile
			fire(target);
			//Angle to target
			float angle = angleToTarget(m_iCurrentScreenX, m_iCurrentScreenY, target->getXPosition(), target->getYPosition());
			//Initialise rotational matrix
			calcRotationalMatrix(angle);
			//Reset relative coords to their intial value
			initialiseRelativeCoords();
			//Rotate the co-ordinates that move
			rotateCoords(rail, 8);
			rotateCoords(barrel, 8);
			rotateCoords(stock, 6);
			//printf("angle = %f\n", angle);
		}

	}
	RedrawObjects();
}

void TurretSniper::fire(Enemy* target) {
	//printf("target level = %d, distance travelled = %d\n", target->getLvl(), target->getDistanceTravelled());
	//Create new projectile
	ProjectileSniper* projectile = new ProjectileSniper(m_pMainEngine, playState, target, m_iCurrentScreenX, m_iCurrentScreenY, range, 3, 12);
	//Resize the vector to make space
	m_pMainEngine->ResizeVector(1);
	//Store in main vector and separate projectile vector
	m_pMainEngine->StoreObjectInArray(m_pMainEngine->getVectorSize() - 2, projectile);
	playState->storeInProjectileVector(projectile);
}

void TurretSniper::initialiseRelativeCoords() {

	//List of all "relative" coords that can rotate

	rail[0] = 0;	//Top Left
	rail[1] = -2;
	rail[2] = 19;	//Top Right
	rail[3] = -2;
	rail[4] = 19;	//Bottom Right
	rail[5] = 2;
	rail[6] = 0;	//Bottom Left
	rail[7] = 2;

	barrel[0] = -17;	//Top Left
	barrel[1] = -1;
	barrel[2] = 0;	//Top Right
	barrel[3] = -1;
	barrel[4] = 0;	//Bottom Right
	barrel[5] = 1;
	barrel[6] = -17;	//Bottom Left
	barrel[7] = 1;

	stock[0] = -10;	//Middle Left
	stock[1] = 0;
	stock[2] = 12;	//Top Right
	stock[3] = 5;	
	stock[4] = 12;	//Bottom Right
	stock[5] = -5;
}