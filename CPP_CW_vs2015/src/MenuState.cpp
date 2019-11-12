#include "header.h"

#include "MenuState.h"

void MenuState::drawMenu() {

	//Copy background pixels in area in which text is drawn
	engine->CopyBackgroundPixels(50, 50, engine->GetScreenWidth(), 549);

	//Bars holding up title
	engine->DrawBackgroundRectangle(265, 0, 280, 50, 0);
	engine->DrawBackgroundRectangle(520, 0, 535, 50, 0);

	//Black Bar Segments
	engine->DrawScreenRectangle(0, 180, 220, 200, 0);
	engine->DrawScreenRectangle(200, 200, 220, 600, 0);
	engine->DrawScreenRectangle(0, 580, 220, 600, 0);

	//Background Rectangle
	engine->DrawBackgroundRectangle(210, 200, 800, 580, 0xc3c3c3);
	//Background Decoration triangle & line 0
	//Separation line
	engine->DrawBackgroundRectangle(221, 200, 800, 200, 0);
	engine->DrawBackgroundTriangle(221, 180, 300, 200, 221, 200, 0);


	//Background Decoration triangles & line 1
	//Background drawn inbetween selections
	engine->DrawBackgroundRectangle(221, 280, 800, 300, 0x4b5c77);
	//Upper triangle
	engine->DrawBackgroundTriangle(221, 280, 257, 280, 221, 290, 0);
	engine->DrawBackgroundTriangle(221, 281, 255, 280, 221, 289, 0x333333);
	//Separation line
	engine->DrawBackgroundRectangle(221, 280, 800, 280, 0x333333);

	//Lower triangle
	engine->DrawBackgroundTriangle(221, 290, 257, 300, 221, 300, 0);
	engine->DrawBackgroundTriangle(221, 291, 255, 300, 221, 299, 0x333333);
	//Separation line
	engine->DrawBackgroundRectangle(221, 300, 800, 300, 0x333333);


	//Background Decoration triangles & line 2
	//Background drawn inbetween selections
	engine->DrawBackgroundRectangle(221, 380, 800, 400, 0x4b5c77);
	//Upper triangle
	engine->DrawBackgroundTriangle(221, 380, 257, 380, 221, 390, 0);
	engine->DrawBackgroundTriangle(221, 381, 255, 380, 221, 389, 0x333333);
	//Separation line
	engine->DrawBackgroundRectangle(221, 380, 800, 380, 0x333333);

	//Lower triangle
	engine->DrawBackgroundTriangle(221, 390, 257, 400, 221, 400, 0);
	engine->DrawBackgroundTriangle(221, 391, 255, 400, 221, 399, 0x333333);
	//Separation line
	engine->DrawBackgroundRectangle(221, 400, 800, 400, 0x333333);


	//Background Decoration triangles & line 3
	//Background drawn inbetween selections
	engine->DrawBackgroundRectangle(221, 480, 800, 500, 0x4b5c77);
	//Upper triangle
	engine->DrawBackgroundTriangle(221, 480, 257, 480, 221, 490, 0);
	engine->DrawBackgroundTriangle(221, 481, 255, 480, 221, 489, 0x333333);
	//Separation line
	engine->DrawBackgroundRectangle(221, 480, 800, 480, 0x333333);

	//Lower Triangle
	engine->DrawBackgroundTriangle(221, 490, 257, 500, 221, 500, 0);
	engine->DrawBackgroundTriangle(221, 491, 255, 500, 221, 499, 0x333333);

	//Separation line
	engine->DrawBackgroundRectangle(221, 500, 800, 500, 0x333333);


	//Background Decoration triangle & line 4
	//Separation line
	engine->DrawBackgroundRectangle(221, 580, 800, 580, 0);
	engine->DrawBackgroundTriangle(221, 580, 300, 580, 221, 600, 0);


	//Highlighter triangles
	for (int i = 0; i < 4; i++) {
		//If current i equals the selection then change the colour to the highlighter colour
		selection == i ? hLightTriCol = 0x009900 : hLightTriCol = 0x990000;
		//All tick values adjusted between 0-899
		//Draw chevron 1 between 0-449
		if (tick % 900 >= 0 && tick % 900 < 450) {
			//Polygons to Make up Chevron 1
			engine->DrawBackgroundPolygon(240, 220 + (i * 100), 250, 210 + (i * 100), 280, 240 + (i * 100), 270, 250 + (i * 100), hLightTriCol);
			engine->DrawBackgroundPolygon(270, 230 + (i * 100), 280, 240 + (i * 100), 250, 270 + (i * 100), 240, 260 + (i * 100), hLightTriCol);
		}
		//Draw chevron 150 between 0-599
		if (tick % 900 >= 150 && tick % 900 < 600) {
			//Chevron 2
			engine->DrawBackgroundPolygon(265, 220 + (i * 100), 275, 210 + (i * 100), 305, 240 + (i * 100), 295, 250 + (i * 100), hLightTriCol);
			engine->DrawBackgroundPolygon(295, 230 + (i * 100), 305, 240 + (i * 100), 275, 270 + (i * 100), 265, 260 + (i * 100), hLightTriCol);
		}
		//Draw chevron 300 between 0-749
		if (tick % 900 >= 300 && tick % 900 < 750) {
			//Chevron 3
			engine->DrawBackgroundPolygon(290, 220 + (i * 100), 300, 210 + (i * 100), 330, 240 + (i * 100), 320, 250 + (i * 100), hLightTriCol);
			engine->DrawBackgroundPolygon(320, 230 + (i * 100), 330, 240 + (i * 100), 300, 270 + (i * 100), 290, 260 + (i * 100), hLightTriCol);
		}
		
	}


	//Title frame and outline
	engine->DrawBackgroundRectangle(69, 49, 731, 141, 0);
	engine->DrawBackgroundRectangle(70, 50, 730, 140, 0xc3c3c3);
	//Draw Title
	engine->DrawScreenString(100, 60, "Ball Pit Tower Defence", 0x333333, engine->GetFont("LemonMilk.otf", 48));

	//Calculate a position on a sin wave based on the current tick
	//waveSpeed controls how fast we move through the sin wave
	//negative sin wave so we go up initially
	//multiply by an int do get the MAX pixel +/- offset
	//Add int sinwave to current selected strings Y start pos
	float waveSpeed = 2.0/3;
	int sinwave = -7*sin((waveSpeed*tick)/(2*M_PI));

	//Level 1:
	selection == 0 ?
		engine->DrawScreenString(340, 223 + sinwave, "Level 1", 0x009900, engine->GetFont("LemonMilk.otf", 24))
		: engine->DrawScreenString(340, 223, "Level 1", 0x333333, engine->GetFont("LemonMilk.otf", 24));

	//Level 2:
	selection == 1 ?
		engine->DrawScreenString(340, 323 + sinwave, "Level 2", 0x009900, engine->GetFont("LemonMilk.otf", 24))
		: engine->DrawScreenString(340, 323, "Level 2", 0x333333, engine->GetFont("LemonMilk.otf", 24));

	//Level 3:
	selection == 2 ?
		engine->DrawScreenString(340, 423 + sinwave, "Level 3", 0x009900, engine->GetFont("LemonMilk.otf", 24))
		: engine->DrawScreenString(340, 423, "Level 3", 0x333333, engine->GetFont("LemonMilk.otf", 24));

	//Highscores:
	selection == 3 ?
		engine->DrawScreenString(340, 523 + sinwave, "HighScores", 0x009900, engine->GetFont("LemonMilk.otf", 24))
		: engine->DrawScreenString(340, 523, "HighScores", 0x333333, engine->GetFont("LemonMilk.otf", 24));

}

void MenuState::selectionFromGrid() {
	//Calls the menuTileManager with the pointers X and Y values to update the current selection
	selection = menuTileManager->getSelection(menuPointer->GetXCentre(), menuPointer->GetYCentre());
}

bool MenuState::selectionChanged() {
	//Simple comparison
	return prevSelection != selection;
}