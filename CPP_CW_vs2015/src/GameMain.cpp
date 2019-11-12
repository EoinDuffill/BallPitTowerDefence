#include "header.h"

#include "GameMain.h"

#include "MapTileManager.h"

#include "Enemy.h"

#include "MovableObject.h"

#include "WaveManager.h"

#include "TurretBasic.h"

#include "ProjectileBasic.h"

GameMain::~GameMain() {
}

void GameMain::drawHud() {

	

	//Sprintf to form a string with variables inside
	sprintf(tick, "count =  %d", count);
	sprintf(waveNumber, "wave: %d", waves->getWaveNumber());
	sprintf(lifeCount, "lives left: %d", lives);
	sprintf(moneyTotal, "Money: %d", money);
	sprintf(scoreTotal, "Score: %d", score);


	//Put the background over the screen
	engine->CopyBackgroundPixels(0, 500, engine->GetScreenWidth(), 100);

	//Draw strings

	engine->DrawScreenString(25, 510, moneyTotal, 0xd3d3d3, NULL);
	engine->DrawScreenString(25, 560, scoreTotal, 0xd3d3d3, NULL);
	engine->DrawScreenString(350, 510, waveNumber, 0xd3d3d3, NULL);
	engine->DrawScreenString(350, 560, lifeCount, 0xd3d3d3, NULL);

	engine->DrawScreenRectangle(550, 500, 800, 600, 0xc3c3c3);

	//Turret Select
	engine->DrawScreenLine(608, 551, 800, 551, 0);
	engine->DrawScreenLine(608, 500, 608, 600, 0);
	engine->DrawScreenLine(672, 500, 672, 600, 0);
	engine->DrawScreenLine(736, 500, 736, 600, 0);
	engine->DrawScreenLine(800, 500, 800, 600, 0);

	//Current Selected Turret Highlight
	engine->DrawScreenRectangle((609 + 64 * (selection)), 500, (624 + 64 * (selection)), 505, 0x12a000);
	engine->DrawScreenRectangle((609 + 64 * (selection)), 500, (614 + 64 * (selection)), 515, 0x12a000);

	engine->DrawScreenRectangle((656 + 64 * (selection)), 500, (671 + 64 * (selection)), 505, 0x12a000);
	engine->DrawScreenRectangle((666 + 64 * (selection)), 500, (671 + 64 * (selection)), 515, 0x12a000);

	engine->DrawScreenRectangle((609 + 64 * (selection)), 545, (624 + 64 * (selection)), 550, 0x12a000);
	engine->DrawScreenRectangle((609 + 64 * (selection)), 535, (614 + 64 * (selection)), 550, 0x12a000);

	engine->DrawScreenRectangle((656 + 64 * (selection)), 545, (671 + 64 * (selection)), 550, 0x12a000);
	engine->DrawScreenRectangle((666 + 64 * (selection)), 535, (671 + 64 * (selection)), 550, 0x12a000);

	//Draw Display Turrets to screen
	turretBasic->Draw();
	engine->DrawScreenString(613, 562, turretBasicPrice, 0x333333, engine->GetFont("LemonMilk.otf", 18));
	turretSniper->Draw();
	engine->DrawScreenString(677, 562, turretSniperPrice, 0x333333, engine->GetFont("LemonMilk.otf", 18));
	turretCannon->Draw();
	engine->DrawScreenString(741, 562, turretCannonPrice, 0x333333, engine->GetFont("LemonMilk.otf", 18));

	//Pause/Play Button
	engine->DrawScreenLine(549, 500, 549, 600, 0);
	engine->DrawScreenRectangle(554, 525, 604, 575, 0);
	
	if (!paused) {
		//engine->DrawScreenRectangle(551, 500, 608, 600, 0x333333);
		engine->DrawScreenRectangle(555, 526, 603, 574, 0x840000);
		engine->DrawScreenRectangle(565, 537, 575, 563, 0);
		engine->DrawScreenRectangle(583, 537, 593, 563, 0);
	}
	else {
		//engine->DrawScreenRectangle(551, 500, 608, 600, 0x333333);
		engine->DrawScreenRectangle(555, 526, 603, 574, 0x12a000);
		engine->DrawScreenTriangle(565, 535, 595, 550, 565, 565, 0);
	}
	
}

void GameMain::drawRanges() {
	for (int i = 0; i < X_CUBE_AMOUNT * Y_CUBE_AMOUNT; i++) {
		
		if (mapTileManager->getTurretInGridIndex(i) != NULL ) {
			TurretBasic* obj = dynamic_cast<TurretBasic*>(mapTileManager->getTurretInGridIndex(i));
			
			if (obj->getRadius()) {
				int range = obj->getRange();
				int XPos = obj->getXPosition();
				int YPos = obj->getYPosition();
				engine->DrawScreenHollowOval(
					XPos - range,
					YPos - range,
					XPos + range,
					YPos + range,
					XPos - (range - 1),
					YPos - (range - 1),
					XPos + (range - 1),
					YPos + (range - 1),
					0);


			}
		}
	}
}


int GameMain::GetTile(int XPos, int YPos) {
	//Return index of map from a given x and y pos (range of x and y vary from 0-> X/Y_CUBE_AMOUNT)
	int xIndex = XPos;
	int yIndex = YPos * X_CUBE_AMOUNT;
	int index = xIndex + yIndex;

	return drawGrid[index];
}

int GameMain::GetNextTileDir(int XPos, int YPos, int XPrevPos, int YPrevPos) {
	//Calculate direction to move in when entering the next tile
	//dir0 = up, 1 = right, 2 = down, 3 = left
	//prev pos needed to ensure new direction isn't where it has just come from
	int dir0 = -1;
	int dir1 = -1;
	int dir2 = -1;
	int dir3 = -1;

	//assign the tile value in each direction, IF inBounds and isn't the previous direction
	if ((XPos + 1) != XPrevPos && (XPos + 1 < X_CUBE_AMOUNT)) {
		dir1 = GetTile(XPos + 1, YPos);
	}
	if ((XPos - 1) != XPrevPos && (XPos - 1 >= 0)) {
		dir3 = GetTile(XPos - 1, YPos);
	}
	if ((YPos - 1) != YPrevPos && (YPos - 1 >= 0)) {
		dir0 = GetTile(XPos, YPos - 1);
	}
	if ((YPos + 1) != YPrevPos && (YPos + 1 < Y_CUBE_AMOUNT)) {
		dir2 = GetTile(XPos, YPos + 1);
	}

	//Debug
	//printf("\n dir0 = %d, dir1 = %d, dir2 = %d, dir3 = %d\n\n", dir0, dir1, dir2, dir3);

	//return first direction that == 2 or 4 as these are viable paths, 4 being the end
	//returning -1 means no viable direction and something has gone wrong
	if (dir0 == 2 || dir0 == 4) {
		return 0;
	}
	else if (dir1 == 2 || dir1 == 4) {
		return 1;
	}
	else if (dir2 == 2 || dir2 == 4) {
		return 2;
	}
	else if (dir3 == 2 || dir3 == 4) {
		return 3;
	}
	else {
		return -1;
	}
}

Enemy* GameMain::getTarget(int XPos, int YPos, int range) {

	Enemy* obj = NULL;
	Enemy* objTemp = NULL;
	int objDist = 0;

	//Check each enemy for "collision" with the given circle from the parameters, Also store the object with the highest distance travelled, and filter through all the enemies, return the enemy that collides with the highest distance travelled
	for (int i = 0; i < engine->getVectorSize(); i++) {
		obj = dynamic_cast<Enemy*>(engine->GetDisplayableObject(i));
		if (obj != NULL) {
			if (   collision(XPos, YPos, range, obj->getXPosition(), obj->getYPosition(), obj->getRadius()) && obj->getDistanceTravelled() >= objDist && obj->IsVisible()) {
				objDist = obj->getDistanceTravelled();
				objTemp = obj;
			}
		}
	}

	return objTemp;
}


bool GameMain::collision(int x0, int y0, int r0, int x1, int y1, int r1) {

	//circle0 = x0,y0,r0 , circle1 = x1,y1,r1
	//if (x0 - x1)^2 + (y0 - y1)^2 <= (r0 + r1)^2 then the two circles itersect or one envelopes the other
	int radialDiff = (pow(x0 - x1, 2) + pow(y0 - y1, 2));
	int upperRadSqrd = pow(r0 + r1, 2);

	if (radialDiff <= upperRadSqrd) {
		return true;
	}
	else {
		return false;
	}
	
}

void GameMain::calculateAllCollisions() {

	//For each projectile in the projectile vector(for faster lookup compared to the big vector) check to see if it collides with each enemy using the collide function
	for (int i = 0; i < projectileVector.size(); i++) {
		ProjectileBasic* proj = getFromProjectileVector(i);
		for (int j = 0; j < engine->getVectorSize(); j++) {
			Enemy* enemy = dynamic_cast<Enemy*>(engine->GetDisplayableObject(j));
			if (enemy != NULL && proj != NULL && proj->IsVisible() && enemy->IsVisible() && enemy->isSpawned() && !proj->checkIfPrevHit(enemy->getSpawnedTick()) && collision(enemy->getXPosition(), enemy->getYPosition(), enemy->getRadius(), proj->getXPosition(), proj->getYPosition(), proj->getRadius())) {
				int prevLevel = enemy->getLvl();
				enemy->damageRecieved(proj->getDamage());
				calcScoreAndMoney(prevLevel - enemy->getLvl());
				proj->hit(1, enemy->getSpawnedTick() );
			}
		}
		
	}

}

void GameMain::calcScoreAndMoney(int levelsReduced) {
	//handling score for enemy kills
	score += 5 * levelsReduced;
	money += 2 * levelsReduced;
}

void GameMain::waveOverScoreMoney(int diff) {
	//handle score for wave ending
	score += 10 * diff;
	money += 100 + floor(0.5 * diff);
}

//Store at the end of the vector
void GameMain::storeInProjectileVector(ProjectileBasic* proj) {
	projectileVector.push_back(proj);
}

//Return the projectile at the index if it exists
ProjectileBasic* GameMain::getFromProjectileVector(int index) {

	if (!projectileVector.empty())
	{
		return projectileVector[index];
	}
	else
		return NULL;
}

//erase a projectile from object pointer
void GameMain::eraseFromProjectileVector(ProjectileBasic* proj) {
	projectileVector.erase(std::remove(projectileVector.begin(), projectileVector.end(), proj));
}