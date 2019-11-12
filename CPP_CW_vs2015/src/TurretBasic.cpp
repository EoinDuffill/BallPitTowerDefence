#include "header.h"

#include "Game.h"

#include "GameMain.h"

#include "TurretBasic.h"

#include "ProjectileBasic.h"

TurretBasic::TurretBasic(Game* pEngine, GameMain* play, int countS) 
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
{
	playState = play;

	spawnedTick = countS;

	m_iStartDrawPosX = -TURRETWIDTH/2;
	m_iStartDrawPosY = -TURRETWIDTH/2;

	m_iDrawWidth = TURRETWIDTH;
	m_iDrawHeight = TURRETWIDTH;

	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = 400;
	m_iPreviousScreenY = m_iCurrentScreenY = 300;

	//Initialise Relative coords
	initialiseRelativeCoords();

	m_iColour = GetEngine()->GetColour(1);

	SetVisible(true);
}


TurretBasic::~TurretBasic()
{
}

void TurretBasic::Draw() {

	if (!IsVisible())
		return;

	//Bottom Circle outline
	
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - 20,
		m_iCurrentScreenY - 20,
		m_iCurrentScreenX + 19,
		m_iCurrentScreenY + 19,
		0
	);

	//Bottom Circle

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - 19,
		m_iCurrentScreenY - 19,
		m_iCurrentScreenX + 18,
		m_iCurrentScreenY + 18,
		0x565656
		);
	
	//Inner Circle

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - 11,
		m_iCurrentScreenY - 11,
		m_iCurrentScreenX + 10,
		m_iCurrentScreenY + 10,
		0
	);


	//Turret Top

	m_pMainEngine->DrawScreenPolygon(
		m_iCurrentScreenX + barrel[0],
		m_iCurrentScreenY + barrel[1],
		m_iCurrentScreenX + barrel[2],
		m_iCurrentScreenY + barrel[3],
		m_iCurrentScreenX + barrel[4],
		m_iCurrentScreenY + barrel[5],
		m_iCurrentScreenX + barrel[6],
		m_iCurrentScreenY + barrel[7],
		0x0063ce);

	StoreLastScreenPositionForUndraw();
}

void TurretBasic::DoUpdate(int iCurrentTime) {

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
			//
			rotateCoords(barrel, BARRELSIZE);
			//printf("angle = %f\n", angle);
		}	
		
	}
	RedrawObjects();
}

void TurretBasic::fire(Enemy* target) {
	//printf("target level = %d, distance travelled = %d\n", target->getLvl(), target->getDistanceTravelled());
	//Create new projectile
	ProjectileBasic* projectile = new ProjectileBasic(m_pMainEngine, playState,target, m_iCurrentScreenX, m_iCurrentScreenY, range, 4, 6);
	//Resize the vector to make space
	m_pMainEngine->ResizeVector(1);
	//Store in main vector and separate projectile vector
	m_pMainEngine->StoreObjectInArray(m_pMainEngine->getVectorSize() - 2, projectile);
	playState->storeInProjectileVector(projectile);
}

float TurretBasic::angleToTarget(int x0, int y0, int x1, int y1) {
	//using trig to find angle to the target, used in conjunction with rotational matrix
	if ((x0 - x1) < 0) {
		return atan((y0 - y1)*1.0 / (x0 - x1)) + M_PI;
	}
	else {
		return atan((y0 - y1)*1.0 / (x0 - x1));
	}
	
}

void TurretBasic::calcRotationalMatrix(float rads) {
	//Standard rotational matrix, but in an array
	rotMatrix[0] = cos(rads);
	rotMatrix[1] = -sin(rads);
	rotMatrix[2] = -rotMatrix[1];
	rotMatrix[3] = rotMatrix[0];

}

void TurretBasic::rotateCoords(int* shape, int shapeSize) {
	//Function to rotate all coords
	int tempX = 0;
	int tempY = 0;

	for (int i = 0; i < shapeSize - 1; i += 2) {
		tempX = shape[i];
		tempY = shape[i + 1];

		shape[i] = round((rotMatrix[0] * tempX) + (rotMatrix[1] * tempY));
		shape[i + 1] = round((rotMatrix[2] * tempX) + (rotMatrix[3] * tempY));
	}

}

void TurretBasic::initialiseRelativeCoords() {

	//List of all "relative" coords that can rotate

	barrel[0] = -barrelHeight - 4;	//Top left Point
	barrel[1] = -3;
	barrel[2] = barrelHeight - 3; //Top right point
	barrel[3] = -barrelWidth;
	barrel[4] = barrelHeight - 3;	 //Bottom right point
	barrel[5] = barrelWidth - 1;
	barrel[6] = -barrelHeight - 4;		//Bottom left point
	barrel[7] = 2;

}