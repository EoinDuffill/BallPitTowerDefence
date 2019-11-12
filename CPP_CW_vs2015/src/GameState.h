#pragma once

#define MAX_NAME_LENGTH 12


class GameState
{
public:
	GameState();
	~GameState();

	virtual void update(){}

	virtual void initialise(){}

	virtual void MouseInput(int iButton, int iX, int iY){}

	virtual void KeyBoardInputDown(int iKeyCode){}

	virtual void KeyBoardInputUp(int iKeyCode) {}

	//Struct for gamestates that interact with scores
	struct highscorePair {
		char name[MAX_NAME_LENGTH + 1] = "";
		int score = -1;
		int level = -1;
	};

	//Function to be used by gameStates that need to read in the highscores
	std::vector<highscorePair> readInHighscores() {
		//Buffers
		int lvlTemp;
		int scoreTemp;
		char nameTemp[MAX_NAME_LENGTH + 1];
		//New vector
		std::vector<highscorePair> allPairs;

		//Read in 
		std::ifstream highscores("highscores.txt");

		while (highscores >> nameTemp >> scoreTemp >> lvlTemp) {
			//printf("name = %s, score = %d, level = %d\n", nameTemp, scoreTemp, lvlTemp);

			//New struct, place values in
			highscorePair pair;
			strcpy(pair.name, nameTemp);
			pair.score = scoreTemp;
			pair.level = lvlTemp;

			//Place struct at the back of the vector
			allPairs.push_back(pair);

			//reset vals
			memset(nameTemp, 0, sizeof(nameTemp));
			scoreTemp = 0;
			lvlTemp = 0;
		}

		//Close file and return vector
		highscores.close();
		return allPairs;
	}

};

