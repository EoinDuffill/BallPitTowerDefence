#pragma once
#include "MapTileManager.h"

#define HIGHESTLEVEL_ENEMY 6

class Game;
class GameMain;

class WaveManager
{
public:
	WaveManager( Game* engine, GameMain* play);
	~WaveManager();

	//Function to be run every frame, updating the waveManager
	void update(int count);

	//initialise the waveManager
	void initialise(MapTileManager tiles);

	//Set the next wave to run if we are ready for it
	void setRunningIfReady(bool run);

	//getter for current waveNumber
	int getWaveNumber() {
		return waveNumber;
	}

	//returns the nextWave to go
	int getNextWaveNumber(){
		return nextWaveNumber;
	}

	//manage spawning and wave starting and ending
	void manageWaves(int count);

	//Initialise enemies in memory
	void initNewEnemies(int noOfEnemies, float enemyArray[]);

	//Runs the algorithm to calculate number of enemies at each tier
	void setupNextWave();

	//Returns either the highest level enemy for a given wave or the time since the last increase is highest level enemy
	int getHighestLevelEnemy(int wave, bool thresh) {
		if (wave >= 13) {
			if(!thresh) return HIGHESTLEVEL_ENEMY;
			else return wave - 13;
		}
		else if (wave >= 10) {
			if (!thresh) return HIGHESTLEVEL_ENEMY - 1;
			else return wave - 10;
		}
		else if (wave >= 8) {
			if (!thresh) return HIGHESTLEVEL_ENEMY - 2;
			else return wave - 8;
		}
		else if (wave >= 5) {
			if (!thresh) return HIGHESTLEVEL_ENEMY - 3;
			else return wave - 5;
		}
		else if (wave >= 3) {
			if (!thresh) return HIGHESTLEVEL_ENEMY - 4;
			else return wave - 3;
		}
		else if (wave >= 1) {
			if (!thresh) return HIGHESTLEVEL_ENEMY - 5;
			else return wave - 1;
		}
		else {
			return -1;
		}
	}

	//function to determine whether the current wave has finished
	bool isWaveOver();
private:

	//Difficulty
	int difficulty = 0;
	//Size of the last wave
	int lastWaveSize = 0;
	//Enemy Count to spawn in the current wave
	int enemyCount;
	//Number of frames between each Enemy Spawn
	int spawnRate;
	//DownTime between waves if appropriate
	int downTime;
	//Maximum number of enemies to spawn (upper bound)
	int maxObjects;

	//Is the wave running
	bool running = true;
	//Are we ready for the next wave to start
	bool ready = false;
	//Bool to only run ready set to true once
	bool readyLock = false;
	//Current wave we are on
	int waveNumber = 1;
	//the next wave, incremented after the current wave has stopped spawning and before the next wave starts
	int nextWaveNumber = 1;
	//Index to start at in the vector of displayable objects
	int indexObjectArray = 0;
	//Enemies spawned so far in current wave
	int currEnemies = 0;

	//Start Position, initialised to 0
	int XStartPos = 0;
	int YStartPos = 0;

	//End Position
	int XEndPos = 0;
	int YEndPos = 0;

	//Pointer to engine
	Game* game_engine;
	GameMain* playState;
};

