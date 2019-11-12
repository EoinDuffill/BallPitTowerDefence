#include "header.h"

#include "Game.h"

#include "GameMain.h"

#include "Enemy.h"

#include "ProjectileBasic.h"



ProjectileBasic::ProjectileBasic(Game* pEngine, GameMain* play, Enemy* target, int XPos, int YPos, int range, int rad, float spd)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, stationary(false)
{
	playState = play;
	radius = rad;
	speed = spd;

	int x0 = XPos;
	int y0 = YPos;
	int x1 = target->getXPosition();
	int y1 = target->getYPosition();

	m_iStartDrawPosX = -radius;
	m_iStartDrawPosY = -radius;

	m_iDrawWidth = (2* radius) + 1;
	m_iDrawHeight = (2 * radius) + 1;

	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = XPos;
	m_iPreviousScreenY = m_iCurrentScreenY = YPos;

	//Mathematical formula derived by extrapolating the line between the initial position targeted enemy's position all the way out to the towers radius
	//The following maths was worked out on paper beforehand
	targetX = x0 + (((x1 - x0) * range) / sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
	targetY = y0 + (((y1 - y0) * range) / sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));

	//X Distance between the edge of turret radius
	maxXDistance = targetX - x0;
	//Y Distance between the edhe of the turret radius
	maxYDistance = targetY - y0;
	maxDistance = range;

	//X speed calculated as a function of the percentage of the distance needed to be travelled in X (smaller the percentage of the overall distance is in x the slower the speedX is)
	speedX = ((maxXDistance * 1.0) / maxDistance) * speed;
	//Same again in Y
	speedY = ((maxYDistance * 1.0) / maxDistance) * speed;

	//debug
	//printf("speedX = %f, speedY = %f, maxXDistance = %d, maxYDistance = %d\n", speedX, speedY, maxXDistance, maxYDistance);

	SetVisible(true);
}

ProjectileBasic::ProjectileBasic(Game* pEngine, GameMain* play, int XPos, int YPos, int rad, std::vector<int> enemies )
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine) 
	, stationary(true)
{

	enemiesHit = enemies;

	playState = play;
	radius = rad;
	speed = 0;

	m_iStartDrawPosX = -radius;
	m_iStartDrawPosY = -radius;

	m_iDrawWidth = (2 * radius) + 1;
	m_iDrawHeight = (2 * radius) + 1;

	m_iPreviousScreenX = m_iCurrentScreenX = XPos;
	m_iPreviousScreenY = m_iCurrentScreenY = YPos;


	SetVisible(true);

}

ProjectileBasic::~ProjectileBasic()
{
}

void ProjectileBasic::Draw() {

	if (!IsVisible())
		return;
	//Outline
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - radius,
		m_iCurrentScreenY - radius,
		m_iCurrentScreenX + radius,
		m_iCurrentScreenY + radius,
		0x000000);
	//Inner circle
	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - (radius - 1),
		m_iCurrentScreenY - (radius - 1),
		m_iCurrentScreenX + (radius - 1),
		m_iCurrentScreenY + (radius - 1),
		0xffffff);

	StoreLastScreenPositionForUndraw();
}

void ProjectileBasic::DoUpdate(int iCurrentTime) {

	//Delete projectile is not visible
	if (!IsVisible()) {
		m_pEngine->eraseFromVector(this);
		playState->eraseFromProjectileVector(this);
		return;
	}
	//Storing the previous screen position
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	if (stationary) {
		updateSubClass();
		RedrawObjects();
		return;
	}

	speedFinal = 0;
	float tempSpeed = 0;
	tempSpeed = fabsf(speedX); //float function for absolute value of speedX

	//Movement: Running average of speed each update in X and Y, speedX is a float, can only move integer pixels,
	//To simulate non-integer movement, either use floor(speedX/Y) or ceil(speedX/Y),
	//Running average is used to decide whether to use floor or ceil
	//Finally if speed is +ve add to screenPos, otherwise - from screenPos
	//If it has reached it's target in the given direction x/yReached is triggered, when both ar triggered the projectile is destroyed
	//X Movement
	if (totalDistX < abs(maxXDistance)) {
		if (tempSpeed <= avgX) {
			speedFinal = floor(tempSpeed);
			totalDistX += speedFinal;
		}
		else {
			speedFinal = ceil(tempSpeed);
			totalDistX += speedFinal;
		}
		countX++;
		avgX = totalDistX * 1.0 / countX * 1.0;

		if (speedX >= 0) {
			m_iCurrentScreenX += speedFinal;
		}
		else {
			m_iCurrentScreenX -= speedFinal;
		}
	}
	else {
		xReached = true;
	}
	//Same as X, but applied to Y values, all running averages are separate values etc
	//Y Movement
	tempSpeed = fabsf(speedY);

	if (totalDistY < abs(maxYDistance)) {
		if (tempSpeed <= avgY) {
			speedFinal = floor(tempSpeed);
			totalDistY += speedFinal;
		}
		else {
			speedFinal = ceil(tempSpeed);
			totalDistY += speedFinal;
		}
		countY++;
		avgY = totalDistY * 1.0 / countY  * 1.0;

		if (speedY >= 0) {
			m_iCurrentScreenY += speedFinal;
		}
		else {
			m_iCurrentScreenY -= speedFinal;
		}
	}
	else {
		yReached = true;
	}

	if(xReached && yReached) destroySelf();

	// Ensure not off the screen
	// If it is set invisible (Which will destroy it next update)
	if (m_iCurrentScreenX < m_iDrawWidth/2) {
		destroySelf();
	}

	if (m_iCurrentScreenX >= 800 - m_iDrawWidth / 2) {
		destroySelf();
	}

	if (m_iCurrentScreenY >= 500 - m_iDrawWidth / 2) {
		destroySelf();
	}

	if (m_iCurrentScreenY < m_iDrawWidth / 2) {
		destroySelf();
	}

	RedrawObjects();
}
