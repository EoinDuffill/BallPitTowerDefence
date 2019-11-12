#include "header.h"

#include "Game.h"

#include "GameMain.h"

#include "ProjectileCannon.h"

#include "TurretCannon.h"



TurretCannon::TurretCannon(Game* pEngine, GameMain* play, int countS)
	: TurretBasic(pEngine, play, countS)
{
	m_pMainEngine = pEngine;
	playState = play;

	initialiseRelativeCoords();
}


TurretCannon::~TurretCannon()
{
}

void TurretCannon::Draw() {


	if (!IsVisible())
		return;
	//Circle base outline
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - 20,
		m_iCurrentScreenY - 20,
		m_iCurrentScreenX + 19,
		m_iCurrentScreenY + 19,
		0
	);
	//circle base
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - 19,
		m_iCurrentScreenY - 19,
		m_iCurrentScreenX + 18,
		m_iCurrentScreenY + 18,
		0x565656
	);
	//Cross 1
	m_pMainEngine->DrawScreenPolygon(
		m_iCurrentScreenX - 18,
		m_iCurrentScreenY - 15,
		m_iCurrentScreenX - 15,
		m_iCurrentScreenY - 18,
		m_iCurrentScreenX + 18,
		m_iCurrentScreenY + 15,
		m_iCurrentScreenX + 15,
		m_iCurrentScreenY + 18,
		0x232323
	);

	//Cross 2
	m_pMainEngine->DrawScreenPolygon(
		m_iCurrentScreenX + 15,
		m_iCurrentScreenY - 18,
		m_iCurrentScreenX + 18,
		m_iCurrentScreenY - 15,
		m_iCurrentScreenX - 15,
		m_iCurrentScreenY + 18,
		m_iCurrentScreenX - 18,
		m_iCurrentScreenY + 15,
		0x232323
	);

	//Turret center rotation
	m_pMainEngine->DrawScreenRectangle(
		m_iCurrentScreenX - 10,
		m_iCurrentScreenY - 10,
		m_iCurrentScreenX + 10,
		m_iCurrentScreenY + 10,
		0x232323
	);

	//Turret parts to rotate
	m_pMainEngine->DrawScreenPolygon(
		m_iCurrentScreenX + rotatingBase[0],
		m_iCurrentScreenY + rotatingBase[1],
		m_iCurrentScreenX + rotatingBase[2],
		m_iCurrentScreenY + rotatingBase[3],
		m_iCurrentScreenX + rotatingBase[4],
		m_iCurrentScreenY + rotatingBase[5],
		m_iCurrentScreenX + rotatingBase[6],
		m_iCurrentScreenY + rotatingBase[7],
		0x00a8a2
	);

	m_pMainEngine->DrawScreenTriangle(
		m_iCurrentScreenX + barrelGuide[0],
		m_iCurrentScreenY + barrelGuide[1],
		m_iCurrentScreenX + barrelGuide[2],
		m_iCurrentScreenY + barrelGuide[3],
		m_iCurrentScreenX + barrelGuide[4],
		m_iCurrentScreenY + barrelGuide[5],
		0x00a8a2
	);

	m_pMainEngine->DrawScreenTriangle(
		m_iCurrentScreenX + barrelGuide2[0],
		m_iCurrentScreenY + barrelGuide2[1],
		m_iCurrentScreenX + barrelGuide2[2],
		m_iCurrentScreenY + barrelGuide2[3],
		m_iCurrentScreenX + barrelGuide2[4],
		m_iCurrentScreenY + barrelGuide2[5],
		0x00a8a2
	);

	StoreLastScreenPositionForUndraw();
}

void TurretCannon::DoUpdate(int iCurrentTime) {
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
			//Rotate the coords that move
			rotateCoords(rotatingBase, 8);
			rotateCoords(barrelGuide, 6);
			rotateCoords(barrelGuide2, 6);
			//printf("angle = %f\n", angle);
		}

	}
	RedrawObjects();
}

void TurretCannon::fire(Enemy* target) {
	//printf("target level = %d, distance travelled = %d\n", target->getLvl(), target->getDistanceTravelled());
	//Create new projectile
	ProjectileCannon* projectile = new ProjectileCannon(m_pMainEngine, playState, target, m_iCurrentScreenX, m_iCurrentScreenY, range, 6 , 3);
	//Resize the vector to make space
	m_pMainEngine->ResizeVector(1);
	//Store in main vector and separate projectile vector
	m_pMainEngine->StoreObjectInArray(m_pMainEngine->getVectorSize() - 2, projectile);
	playState->storeInProjectileVector(projectile);
}

void TurretCannon::initialiseRelativeCoords() {

	//List of all "relative" coords that can rotate

	rotatingBase[0] = 4;	//Top Left
	rotatingBase[1] = -12;
	rotatingBase[2] = 10;	//Top Right
	rotatingBase[3] = -12;
	rotatingBase[4] = 10;	//Bottom Right
	rotatingBase[5] = 12;
	rotatingBase[6] = 4;	//Bottom Left
	rotatingBase[7] = 12;

	barrelGuide[0] = -12;	//Top Left
	barrelGuide[1] = 6;
	barrelGuide[2] = 4;		//Top Right
	barrelGuide[3] = 6;
	barrelGuide[4] = 4;		//Bottom Right
	barrelGuide[5] = 12;


	barrelGuide2[0] = -12;	 //Bottom Left
	barrelGuide2[1] = -6;
	barrelGuide2[2] = 4;		//Top Right
	barrelGuide2[3] = -12;
	barrelGuide2[4] = 4;		//Bottom  Right
	barrelGuide2[5] = -6;

}