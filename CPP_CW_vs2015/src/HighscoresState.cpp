#include "header.h"

#include "HighscoresState.h"

HighscoresState::~HighscoresState()
{
}


void HighscoresState::initialise() {
	engine->FillBackground(0x4b5c77);

	engine->ResetObjectVector();
	engine->Redraw(true);

	allPairs = readInHighscores();

	for (int i = 0; i < allPairs.size(); i++) {
		printf("Index %d: name = %s, score = %d, level = %d\n", i, allPairs[i].name, allPairs[i].score, allPairs[i].level);
	}

}

void HighscoresState::update() {
	engine->Redraw(false);

	engine->CopyBackgroundPixels(50, 40, engine->GetScreenWidth(), 540);

	//Highscore frame and outline
	engine->DrawBackgroundRectangle(27, 19, 401, 80, 0);
	engine->DrawBackgroundRectangle(28, 20, 400, 79, 0xc3c3c3);

	engine->DrawScreenString(50, 25, "HighScores:", 0x333333, engine->GetFont("LemonMilk.otf", 36));

	engine->DrawBackgroundPolygon(249 ,89, 351, 89, 402 , 120, 198, 120, 0);
	engine->DrawBackgroundPolygon(250, 90, 350, 90, 400 , 120, 200, 120, 0xc3c3c3);
	engine->DrawScreenString(265, 90, "Level", 0x333333, engine->GetFont("LemonMilk.otf", 24));

	for (int i = 0; i < 3; i++) {
		//Level Tab
		engine->DrawBackgroundRectangle(74 + (i * 150), 119, 226 + (i * 150), 150, 0);
		engine->DrawBackgroundRectangle(75 + (i * 150), 120, 225 + (i * 150), 150, selection == i ? 0xc3c3c3 : 0x737373);
		char levelTabBuff[64];
		sprintf(levelTabBuff, "%d", i + 1);
		engine->DrawScreenString(142 + (i * 150), 118, levelTabBuff, selection == i ? 0x333333 : 0xd3d3d3, engine->GetFont("LemonMilk.otf", 24));

	}
	
	//Highscores display window outline
	engine->DrawBackgroundRectangle(
		74, 149, 726, 551, 0
	);
	//Highscores display window 
	engine->DrawBackgroundRectangle(
		75, 150, 725, 550, 0xc3c3c3
	);




	//Gold, Silver and Bronze backgrounds for 1st 2nd and 3rd
	engine->DrawBackgroundRectangle(75, 150, 725, 190, 0xc98910);
	engine->DrawBackgroundRectangle(75, 190, 725, 230, 0xa8a8a8);
	engine->DrawBackgroundRectangle(75, 230, 725, 270, 0x965a38);

	//Print highscores

	for (int i = 0, j = 0; i < allPairs.size() || j < HIGHSCORES_TO_SHOW; i++) {

		
			if (i < allPairs.size() && j < HIGHSCORES_TO_SHOW ) {
				if (allPairs[i].level == selection + 1) {
					sprintf(buff, "%d:  %s - %d", j + 1, allPairs[i].name, allPairs[i].score);
					engine->DrawScreenString(90, 160 + (j * 40), buff, 0x333333, engine->GetFont("LemonMilk.otf", 18));
					j++;
					
				}
				
			}
			else if (j < HIGHSCORES_TO_SHOW){
				sprintf(buff, "%d:  - ", j + 1);
				engine->DrawScreenString(90, 160 + (j * 40), buff, 0x333333, engine->GetFont("LemonMilk.otf", 18));
				j++;
			}
			

	}

}

void HighscoresState::MouseInput(int iButton, int iX, int iY) {

}

void HighscoresState::KeyBoardInputDown(int iKeyCode) {
	//Key presses handled
	//Escape closes program
	//Space sets the WaveManager to run if its ready to run.
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		engine->changeState('m');
		break;
	case SDLK_RIGHT:	
		if (selection < 2) {
			selection++;
			printf("selection = %d\n", selection);
			
		}
		break;	
	case SDLK_LEFT:
		
		if (selection > 0) {
			selection--;
			printf("selection = %d\n", selection);
		}
		break;
	}
	
}

