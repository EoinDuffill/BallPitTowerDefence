#include "header.h"

#include "BaseEngine.h"

#include "WaveManager.h"

#include "MovableObject.h"

#include "displayableobject.h"

#include "Game.h"

#include "GameMain.h"

#include "Enemy.h"

WaveManager::WaveManager(Game* engine, GameMain* play)
{
	//store the values from the constructor
	enemyCount = 0;
	spawnRate = 50;
	downTime = 0;
	maxObjects = 10;
	game_engine = engine;
	playState = play;
	printf("INITIAL Current size of vector = %d\n", game_engine->getVectorSize());
}


WaveManager::~WaveManager()
{
}

void WaveManager::update(int count) {

	manageWaves(count);

}

void WaveManager::manageWaves(int count) {
	//If wave is not running but it has finished, we are ready for the next wave
	if (!running && isWaveOver()) {
		if (readyLock == false) {
			playState->waveOverScoreMoney(difficulty);
			ready = true;
			readyLock = true;
		}
		
	}

	//run the following code when 1) wave is running and 2) if it has been long enough to spawn the next object e.g. count % 50 == 0 is true every 50 counts
	if (running && (count % spawnRate == 0)) {


		for (int i = 0; i < game_engine->getVectorSize(); i++) {
			Enemy* obj1 = dynamic_cast<Enemy*>(game_engine->GetDisplayableObject(i));
			if (obj1 != NULL && !obj1->isSpawned() && !obj1->IsVisible() && obj1->getHealth() > 0) {
				//Put the object at the start, make it visible, set it to be declared as spawned
				obj1->setXPosition(XStartPos);
				obj1->setYPosition(YStartPos);
				obj1->SetVisible(true);
				obj1->setSpawned(true, count);
				currEnemies++;
				printf("count = %d, waveSpawned = %d, lvl = %d, health = %d, currEnemies = %d, tot = %d\n", count, obj1->getWaveSpawned(), obj1->getLvl(), obj1->getHealth(), currEnemies, enemyCount);
				return;
			}
		}

		//increment the index through the displayableObect vector aslong as we have spawned less the waves max enemyCount
		if (currEnemies >= enemyCount) {
			//wave has just finished, set running to false
			running = false;
			//Store the size of the previous wave
			lastWaveSize = enemyCount;
			//increment next wave number, as this is the number needed when calculating the enemies for the next wave
			nextWaveNumber++;
			//reset enemy count
			currEnemies = 0;
			//Calculate the next wave, then initialise into memory
			setupNextWave();
		}
	}

}

void WaveManager::setupNextWave() {
	
	//Array to hold number of each level of enemy (+1 so that the index represents the level of the enemy).
	//First it will contain a percentage, this dictates the percentage of the next waves enemies to be given to this Level of enemy
	//Secondaly it will be replaced with the actual number of enemies at that level to spawn in the next wave
	float enemyPercentiles[HIGHESTLEVEL_ENEMY + 1] = { 0 };
	
	//Function to calculate the difficulty of the next wave
	difficulty = ceil(10 * pow(getNextWaveNumber() , 1.5));
	//Find highest level enemy to spawn in next wave
	int highestLvl = getHighestLevelEnemy(getNextWaveNumber() ,0);
	//Number of waves since the last highest level enemy increase
	int wavesSinceIncrease = getHighestLevelEnemy(getNextWaveNumber() , 1);
	//Level counter to count down from
	int lvlCount = highestLvl;
	//counter to ensure a certain number of loop iterations
	int count = 0;
	//initialise percentage at 100%, to count down from 
	float startPercentile = 1;
	
	//Highest Level enemy, depending on how many waves it has been since it's been spawned will be assigned a different percentage
	if (wavesSinceIncrease == 0) {
		startPercentile -= 0.1;
		enemyPercentiles[lvlCount] += 0.1;
	}
	else if (wavesSinceIncrease == 1) {
		startPercentile -= 0.25;
		enemyPercentiles[lvlCount] += 0.25;
	}
	else {
		spawnRate = ceil(spawnRate * 0.9);
		startPercentile /= 2;
		enemyPercentiles[lvlCount] += startPercentile;
	}
	//Decrease lvl to calculate percentage, aslong as its > 1
	if (lvlCount - 1) {
		lvlCount--;
	}

	//Do While loop to assign percentages to rest of enemies
	//It will do up to a further 4 more Lvls of enemy
	//Each Subsequent enemy recieves half the percentage as the enemy level above it, unless its the last in line, 
	//then it will recieve the left over (which equals the perentage of the second last enemy level)
	do {
		count++;

		if ( count < 4) {
			//halving the percentile
			startPercentile /= 2;
			enemyPercentiles[lvlCount] += startPercentile;
		}
		else if (count == 4){
			//assigning the left over percentile
			enemyPercentiles[lvlCount] += startPercentile;
		}

		//reducing the level being calculated if > 1
		if (lvlCount - 1) {
			lvlCount--;
		}
	} while (count < 4);

	//Declaring the minimum enemy spawned
	int minimumLvl = lvlCount;
	//Var to hold the sum of all ratios for each enemy level
	float ratioSum = 0;

	//Sum of all the percentages * their level 
	for (int i = 1; i < HIGHESTLEVEL_ENEMY + 1; i++) {
		ratioSum += enemyPercentiles[i] * i;
	}
	//Now divide it by the difficulty, and round up, Now when multiplied against each percentage and round it the number of enemies at each tier is defined (almost, it may be a couple above or below due to rounding)
	ratioSum = ceil(difficulty / ratioSum);

	int checkTotal = 0;
	enemyCount = 0;
	//Enemy Count at each level defined
	for (int i = 1; i < HIGHESTLEVEL_ENEMY + 1; i++) {
		enemyPercentiles[i] = round(enemyPercentiles[i] * ratioSum);
		printf("Number of Enemies at index %d = %f\n",i, enemyPercentiles[i]);
		//checkTotal will end up a close estimate to the value of difficulty, this is used to compensate for rounding making the wave to hard or easy
		checkTotal += (i * enemyPercentiles[i]);
		//Summing all enemies, for a wave size
		enemyCount += enemyPercentiles[i];
	}
	
	//Find the loweest non-zero enemy
	int i = 0;
	while (enemyPercentiles[i] == 0) {
		i++;
	}
	//If wave is slightly too hard
	if (checkTotal > difficulty) {	
		//Amount to reduce the wave difficulty by
		float takeAway = (checkTotal - difficulty);
		while (takeAway > 0) {
			//If the takeAway amount is larger than the number of enemies at the level take all of the enemies away, and reduce takeAway by that amount
			if (enemyPercentiles[i] < ceil(takeAway / i)) {
				enemyCount -= enemyPercentiles[i];
				takeAway = takeAway - enemyPercentiles[i] * i;
				enemyPercentiles[i] = 0;
				//Move on to next enemy
				i++;
			}
			//There are enough enemies to take away the takeAway, so enemies is reduced by that amount
			else {
				enemyPercentiles[i] -= ceil(takeAway / i);
				enemyCount -= ceil(takeAway / i);
				takeAway = 0;
			}
		}
		printf("New Number of Enemies at index %d = %f\n", i, enemyPercentiles[i]);
	}
	//If wave too easy, add on the deficit to the lowest amount 
	else if (checkTotal < difficulty) {
		enemyPercentiles[i] += floor((difficulty - checkTotal) * 1.0 / i);
		enemyCount += floor((difficulty - checkTotal) * 1.0 / i);
		printf("New Number of Enemies at index %d = %f\n", i, enemyPercentiles[i]);
	}
	
	
	printf("Attempting to add %d new objects\n", enemyCount);
	printf("TEST Current size of vector = %d\n", game_engine->getVectorSize());
	//Initialise these enemies in memory
	initNewEnemies(enemyCount, enemyPercentiles);

}

void WaveManager::initNewEnemies(int noOfEnemies, float enemyArray[]) {
	//Position of the last element in the vector
	int initSize = game_engine->getVectorSize() - 1;
	int count = 0;

	printf("Current size of vector = %d\n", game_engine->getVectorSize());

	//increase the vector by the size of the number of enemies we are going to add
	game_engine->ResizeVector(noOfEnemies);

	printf("%d new enemies added, new vector size = %d\n", noOfEnemies, game_engine->getVectorSize());

	//For each Index (Enemy level), spawn as many enemies as the number that the index points to
	for (int i = 0; i < HIGHESTLEVEL_ENEMY + 1; i++) {
		printf("enemyArray[%d] = %f\n", i, enemyArray[i]);
		while (enemyArray[i] > 0) {
			//New object, placed at the start, invisible
			Enemy* obj = new Enemy(game_engine, playState, i, getNextWaveNumber());
			obj->SetVisible(false);
			//Stored at the end of the Vector + count (number of enemies spawned before this one)
			game_engine->StoreObjectInArray(initSize + count, obj);
			//increment count, and decrease value at index
			enemyArray[i]--;
			count++;
		}
	}

}

bool WaveManager::isWaveOver() {
	//Start by saying that the wave is over
	bool isOver = true;

	//If the for loop finds a single Visible Enemy the wave is not over
	for (int i = 0; i <= lastWaveSize; i++) {
		Enemy* enemy = dynamic_cast<Enemy*>(game_engine->GetDisplayableObject(i));
		if (enemy != NULL && enemy->IsVisible()) {
			isOver = false;
		}
	}
	

	return isOver;
}

void WaveManager::setRunningIfReady(bool run) {
	//If the wavemanager is ready to go with the next wave, it can be set to start
	printf("ready = %d\n", ready);
	if (ready) {
		running = run;
		ready = !run;
		readyLock = !run;
		waveNumber++;
	}
}


void WaveManager::initialise(MapTileManager tiles) {

	//Find the starting point and the Ending point
	//Iterate through the TileManager to find a value of 3 to start, and 4 for end
	for (int i = 0; i < tiles.GetMapHeight(); i++) {
		for (int j = 0; j < tiles.GetMapWidth(); j++) {
			if (tiles.GetValue(i, j) == 3) {
				XStartPos = i;
				YStartPos = j;
			}
			else if (tiles.GetValue(i, j) == 4) {
				XEndPos = i;
				YEndPos = j;
			}
		}
	}

	//Convert the Co-ordinates relative to the tiles to pixel values
	XStartPos = XStartPos*TILE_SIZE + TILE_SIZE / 2;
	YStartPos = YStartPos*TILE_SIZE + TILE_SIZE / 2;

	XEndPos = XEndPos*TILE_SIZE + TILE_SIZE / 2;
	YEndPos = YEndPos*TILE_SIZE + TILE_SIZE / 2;

	//First wave creation
	setupNextWave();

}