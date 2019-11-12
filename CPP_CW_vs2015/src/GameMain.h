#include "header.h"

#include "WaveManager.h"

#include "MapTileManager.h"

#include "Enemy.h"

#include "ProjectileBasic.h"

#include "GameState.h"

#include "Game.h"

#include "TurretBasic.h"

#include "TurretSniper.h"

#include "TurretCannon.h"


//Number of tiles in X
#define X_CUBE_AMOUNT 16
//Number of tiles in Y
#define Y_CUBE_AMOUNT 10
//Tile pixel width and height
#define TILE_SIZE 50
//Lives available to player before game over
#define MAX_LIVES 50
//TurretBasic Price
#define TURRETBASIC_PRICE 500
//Sniper Turret Price
#define TURRETSNIPER_PRICE 1000
//Cannon Turret Price
#define TURRETCANNON_PRICE 2500
//Starting Money
#define STARTING_MONEY 500

// Class definition for GameMain
// Subclasses a class called BaseEngine
class GameMain :
	public GameState
{


public:
	/*
	Constructor
	*/
	GameMain(Game* gameEngine, int lvl)
		: GameState()
	{
		engine = gameEngine;
		level = lvl;
	}
	~GameMain();

	virtual void initialise() {
		//background
		engine->ResetObjectVector();

		engine->FillBackground(0x4b5c77);

		//Local integer array for defining each level, selected based on value in from constructor

		int grid[Y_CUBE_AMOUNT * X_CUBE_AMOUNT] = {
			1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
			1,1,0,0,0,0,0,0,0,0,0,2,2,2,1,1,
			1,0,2,2,2,2,2,2,0,0,0,2,0,2,0,1,
			1,0,2,0,0,0,0,2,0,0,0,2,0,2,0,1,
			1,0,2,2,2,2,0,2,2,2,0,2,0,2,0,1,
			1,0,0,0,0,2,0,0,0,2,2,2,0,2,0,1,
			1,0,0,2,2,2,0,0,0,0,0,0,0,2,0,1,
			1,1,0,2,0,0,0,0,0,0,0,0,0,2,1,1,
			1,1,0,2,2,2,2,0,0,2,2,2,2,2,1,1,
			1,1,0,0,0,0,3,0,0,4,1,1,1,1,1,1 };
		
		if (level == 1) {
			int tempGrid[Y_CUBE_AMOUNT * X_CUBE_AMOUNT] = {
				1,1,0,0,0,0,1,1,1,1,4,1,1,1,1,1,
				1,1,0,0,0,0,0,0,1,1,2,1,1,1,1,1,
				1,0,0,0,2,2,2,2,0,0,2,2,2,1,1,1,
				1,0,2,2,2,0,0,2,0,0,0,0,2,1,1,1,
				1,0,2,0,0,0,0,2,2,0,0,0,2,1,1,1,
				1,0,2,0,0,0,0,0,2,2,2,2,2,1,1,1,
				1,1,2,2,2,2,0,0,0,0,0,0,0,1,1,1,
				1,1,0,0,0,2,0,0,0,1,0,0,1,1,1,1,
				3,2,2,2,2,2,0,0,1,1,1,1,1,1,1,1,
				1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1 };

			memcpy(grid, tempGrid, sizeof(int)*Y_CUBE_AMOUNT * X_CUBE_AMOUNT);

		}
		else if (level == 2){
			int tempGrid[Y_CUBE_AMOUNT * X_CUBE_AMOUNT] = {
				1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,
				1,1,1,0,1,1,1,0,0,0,0,0,0,0,1,1,
				1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,
				1,1,0,0,0,1,1,1,2,2,2,2,1,0,0,1,
				1,0,0,0,0,1,0,0,2,0,0,2,1,1,0,0,
				1,0,2,2,2,2,0,0,2,0,1,4,1,1,1,0,
				1,0,2,0,0,2,2,2,2,0,1,1,1,1,1,1,
				1,1,2,2,0,0,0,0,0,0,0,1,1,0,0,1,
				1,1,1,2,0,0,0,1,0,0,1,1,1,1,0,0,
				3,2,2,2,0,0,1,1,1,1,1,1,1,1,0,0 };
			memcpy(grid, tempGrid, sizeof(int)*Y_CUBE_AMOUNT * X_CUBE_AMOUNT);
		}


		//Transfered into pointer array
		drawGrid = new int[X_CUBE_AMOUNT * Y_CUBE_AMOUNT];
		for (int i = 0; i < X_CUBE_AMOUNT * Y_CUBE_AMOUNT; i++) {
			drawGrid[i] = grid[i];
			printf("drawGrid[%d] = %d\n", i, drawGrid[i]);
		}

		mapTileManager = new MapTileManager();
		//Set tile size into the TileManager
		mapTileManager->SetSize(X_CUBE_AMOUNT, Y_CUBE_AMOUNT);

		//Set the values of the background based on drawGrid
		for (int i = 0; i < X_CUBE_AMOUNT * Y_CUBE_AMOUNT; i++) {
			//Set value at x, y with value drawGrid[i]. taking advantage of modulus and integer division
			mapTileManager->SetValue(i % X_CUBE_AMOUNT, i / X_CUBE_AMOUNT, drawGrid[i]);
		}

		mapTileManager->DrawAllTiles(engine, engine->GetBackground(), 0, 0, X_CUBE_AMOUNT - 1, Y_CUBE_AMOUNT - 1);
		mapTileManager->initialiseBuildableTiles(drawGrid);
		mapTileManager->initialiseTurretGrid();
		waves = new WaveManager(engine, this);
		waves->initialise(*mapTileManager);

		//Initialise turrets to HUD
		turretBasic = new TurretBasic(engine, this, count);
		turretBasic->setXPosition(640);
		turretBasic->setYPosition(525);

		turretSniper = new TurretSniper(engine, this, count);
		turretSniper->setXPosition(704);
		turretSniper->setYPosition(525);

		turretCannon = new TurretCannon(engine, this, count);
		turretCannon->setXPosition(768);
		turretCannon->setYPosition(525);

		//Initialise Prices to draw to HUD
		sprintf(turretBasicPrice, "$%d", TURRETBASIC_PRICE);
		sprintf(turretSniperPrice, "$%d", TURRETSNIPER_PRICE);
		sprintf(turretCannonPrice, "$%d", TURRETCANNON_PRICE);


		engine->Redraw(true);
		paused = true;
	}

	virtual void update() {
		//update WaveManager
		if (lives <= 0) {
			engine->changeState('l', level + 1,score);
			return;
		}
	
		if (!paused) {
			waves->update(count);

			engine->UpdateAllObjects(count);

			if (!projectileVector.empty()) {
				calculateAllCollisions();
			}
		}
		else {
			engine->Redraw(false);
			engine->DrawAllObjects();
			drawRanges();
			
		}
		

		drawHud();

		//tick increase
		if (!paused) count++;

	}

	virtual void MouseInput(int iButton, int iX, int iY) {
		//Check for left Mouse button press
		if (iButton == SDL_BUTTON_LEFT)
		{
			int pixelX = iX;
			int pixelY = iY;
			iX = ((TILE_SIZE / 2) + (iX - (iX % TILE_SIZE)));
			iY = ((TILE_SIZE / 2) + (iY - (iY % TILE_SIZE)));

			if (pixelX <= 604 && pixelX >= 554 && pixelY <= 575 && pixelY >= 525) {
				paused = !paused;
				engine->Redraw(false);
				engine->CopyAllBackgroundBuffer();
			}
			else if (pixelX < 672 && pixelX >= 608 && pixelY >= 500 && pixelY <= 550) {
				selection = 0;
			}
			else if (pixelX < 736 && pixelX >= 672 && pixelY >= 500 && pixelY <= 550) {
				selection = 1;
			}
			else if (pixelX < 800 && pixelX >= 736 && pixelY >= 500 && pixelY <= 550) {
				selection = 2;
			}
			else if (iX > 0 && iY > 0 && iX < 800 && iY < 500) {
				if (mapTileManager->isTileBuildable(iX, iY)) {
					int moneyVal;

					switch (selection)
					{
					case 0: if (money >= TURRETBASIC_PRICE) {
						obj = new TurretBasic(engine, this, count); money -= TURRETBASIC_PRICE;
						break;
					}
							else { return; }
					case 1: if (money >= TURRETSNIPER_PRICE) {
						obj = new TurretSniper(engine, this, count); money -= TURRETSNIPER_PRICE;
						break;
					}
							else { return; }
					case 2: if (money >= TURRETCANNON_PRICE) {
						obj = new TurretCannon(engine, this, count); money -= TURRETCANNON_PRICE;
						break;
					}
							else { return; }
					}
					//Dynamic cast used to get MovableObject from DisplayableObject vector and set its position to the location of the mouse press
					engine->ResizeVector(1);
					engine->StoreObjectInArray(engine->getVectorSize() - 2, obj);

					if (obj != NULL) {
						mapTileManager->setTileBuildable(iX, iY, -(selection + 1));
						mapTileManager->setTurretInGrid(iX, iY, obj);
						obj->setXPosition(iX);
						obj->setYPosition(iY);
						printf("%d %d\n", iX, iY);
					}
				}
				else if (mapTileManager->getTileBuildValue(iX, iY) < 0) {
					TurretBasic* obj = dynamic_cast<TurretBasic*>(mapTileManager->getTurretInGrid(iX, iY));
					if (obj != NULL) {
						if (obj->getRadius()) {
							obj->setShowRadius(false);
						}
						else {
							obj->setShowRadius(true);
						}
					}
				}
				
			}
		}
	}

	virtual void KeyBoardInputDown(int iKeyCode) {
		//Key presses handled
		//Escape closes program
		//Space sets the WaveManager to run if its ready to run.
		switch (iKeyCode)
		{
		case SDLK_ESCAPE: // End program when escape is pressed
			engine->changeState('m');
			break;
		case SDLK_SPACE:
			waves->setRunningIfReady(true);

			break;
		}
	}
	//Function for figuring out the next tile direction, with given current pos, and previous pos. (Pos is relative to Tiles not pixels)
	int GetNextTileDir(int XPos, int YPos, int XPrevPos, int YPrevPos);
	//Function to get a tile value
	int GetTile(int XPos, int YPos);

	//Getter for lives
	int getLives() {
		return lives;
	}
	
	//Reduce lives by 1
	void takeXlives(int n) {
		lives -= n;
	}

	//Responsible for all of the ui
	void drawHud();

	//Draw turret ranges
	void drawRanges();

	//Calculate score and money to add based on incoming int
	void calcScoreAndMoney(int levelsReduced);

	//Same as above except this is used at the end of a wave
	void waveOverScoreMoney(int diff);

	//Returns an enemy Pointer for the best target for a given X,Y and range from that point
	Enemy* getTarget(int XPos, int YPos, int range);

	//Calculates whether two circles intersect or are envoloped by
	bool collision(int x0, int y0, int r0, int x1, int y1, int r1);

	//Figure out what projectiles have hit which enemies
	void calculateAllCollisions();
	//Store a projectile in the vector
	void storeInProjectileVector(ProjectileBasic* proj);
	//get a value from the vector
	ProjectileBasic* getFromProjectileVector(int index);
	//Delete a projectile from the vector
	void eraseFromProjectileVector(ProjectileBasic* proj);

private:

	Game* engine;
	// MapTileManager and WaveManager Objects defined initially
	MapTileManager* mapTileManager;
	WaveManager* waves;
	TurretBasic* obj;
	//Turret Pointers to be drawn on the HUD
	TurretBasic* turretBasic;
	TurretSniper* turretSniper;
	TurretCannon* turretCannon;
	//Projectile Vector to make accesing projectiles faster
	std::vector<ProjectileBasic*> projectileVector;

	//Strings to Draw
	char tick[64];
	char waveNumber[64];
	char lifeCount[64];
	char moneyTotal[64];
	char scoreTotal[64];
	char turretBasicPrice[64];
	char turretSniperPrice[64];
	char turretCannonPrice[64];


	//Turret Selection
	int selection = 0;
	//Score
	int score = 0;
	//Money
	int money = STARTING_MONEY;
	//Level to play
	int level = 0;
	//integer array to hold the map after it has been defined locally
	int* drawGrid;
	//local integer value initiliased to MAX_LIVES, can be reduced and increased as lives change. Also used to display lives to screen.
	int lives = MAX_LIVES;
	//Integer to store current tick number
	int count = 0;
	//Bool paused
	bool paused = false;
};


