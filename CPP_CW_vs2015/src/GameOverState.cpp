#include "header.h"

#include "GameOverState.h"

GameOverState::~GameOverState()
{
}

void GameOverState::initialise() {

	//Reset the object vector
	engine->ResetObjectVector();
	engine->Redraw(false);
}

void GameOverState::update() {

	engine->Redraw(false);
	
	if (window == 0) {

		engine->CopyBackgroundPixels(275, 225, 250, 150);
		engine->CopyBackgroundPixels(350, 320, 100, 45);

		//Main Window
		engine->DrawScreenRectangle(
			274, 224, 526, 376, 0
		);

		engine->DrawScreenRectangle(
			275, 225, 525, 375, 0x4b5c77
		);

		engine->DrawScreenString(285, 250, "GAME OVER!", 0xd3d3d3, engine->GetFont("LemonMilk.otf", 36));

		//Continue Box Outline
		engine->DrawScreenRectangle(
			349, 319, 451, 366, 0
		);
		//Continue Box 
		engine->DrawScreenRectangle(
			350, 320, 450, 365, 0xc3c3c3
		);

		engine->DrawScreenString(355, 330, "Continue", 0x333333, engine->GetFont("LemonMilk.otf", 18));
		
	}
	else if (window == 1) {
		engine->CopyBackgroundPixels(225, 200, 350, 250);

		//Main Window
		engine->DrawScreenRectangle(
			224, 199, 576, 426, 0
		);

		engine->DrawScreenRectangle(
			225, 200, 575, 425, 0x4b5c77
		);

		
		//String responsible for displaying the score
		sprintf(scoreString, "SCORE: %d", score);
		engine->DrawScreenString(250, 210, scoreString, 0xd3d3d3,engine->GetFont("LemonMilk.otf", 24));

		engine->DrawScreenString(250, 250, "Enter Name:", 0xd3d3d3, engine->GetFont("LemonMilk.otf", 24));

		//Tpying box Outline
		engine->DrawScreenRectangle(
			249, 299, 501, 341, 0
		);
		//Typing Box
		engine->DrawScreenRectangle(
			250, 300, 500, 340, 0xe3e3e3
		);
		//Current Name typed in
		engine->DrawScreenString(255, 305, highscoreName, 0x333333, engine->GetFont("LemonMilk.otf", 24));

		//Continue Box Outline
		engine->DrawScreenRectangle(
			349, 359, 451, 406, 0
		);
		//Continue Box 
		engine->DrawScreenRectangle(
			350, 360, 450, 405, 0xc3c3c3
		);
		engine->DrawScreenString(355, 370, "Continue", 0x333333, engine->GetFont("LemonMilk.otf", 18));
		

	}
	
	
	//engine->UndrawObjects();

}

void GameOverState::KeyBoardInputDown(int iKeyCode) {

	if (window == 1 && hscrNameIndex <= MAX_NAME_LENGTH - 1) {

		//Register input for letters and number
		//Place the char in, increment index
		if (iKeyCode >= (Uint16)'0' && iKeyCode <= (Uint16)'9') {
			highscoreName[hscrNameIndex] = (char)iKeyCode;
			hscrNameIndex++;
		}
		else if (iKeyCode >= (Uint16)'A' && iKeyCode <= (Uint16)'Z') {
			highscoreName[hscrNameIndex] = (char)iKeyCode;
			hscrNameIndex++;
		}
		else if (iKeyCode >= (Uint16)'a' && iKeyCode <= (Uint16)'z') {
			highscoreName[hscrNameIndex] = (char)iKeyCode;
			hscrNameIndex++;
		}
			
	}
	//backspace, reduces index by one and nulls the value (needs to be erased)
	if (iKeyCode == SDLK_BACKSPACE && hscrNameIndex > 0) {
		hscrNameIndex--;
		highscoreName[hscrNameIndex] = NULL;
	}
}

void GameOverState::MouseInput(int iButton, int iX, int iY) {

	if (iButton == SDL_BUTTON_LEFT) {

		if (window == 0) {
			if (iX <= 450 && iX >= 350 && iY <= 365 && iY >= 320) {
				window = 1;
			}
		}
		else if (window == 1) {
			if (iX <= 450 && iX >= 350 && iY <= 405 && iY >= 360 && hscrNameIndex > 0) {

				//read in all the highscores, into vector
				allPairs = readInHighscores();

				//Place our new highscore into a new struct and place into the vector
				highscorePair pairToAdd;
				strcpy(pairToAdd.name, highscoreName);
				pairToAdd.score = score;
				pairToAdd.level = level;
				allPairs.push_back(pairToAdd);
				//Sort the vector by score
				std::sort(allPairs.begin(), allPairs.end(), compareScores());

				//All values written into file
				std::ofstream highscoresSorted;
				highscoresSorted.open("highscores.txt");
				for (int i = 0; i < allPairs.size(); i++) {
					highscore.clear();
					//Place into file in correct way, spaces between variables and new line to finish
					highscore += allPairs[i].name;
					highscore += " ";
					highscore += std::to_string(allPairs[i].score);
					highscore += " ";
					highscore += std::to_string(allPairs[i].level);
					highscore += "\n";

					highscoresSorted << highscore;
				}
				//close file
				highscoresSorted.close();
				
				//Go to Menu
				engine->changeState('m');
			}
		}
		


	}


}