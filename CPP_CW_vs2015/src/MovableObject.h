#pragma once
#include "displayableobject.h"

#include "MapTileManager.h"

#include "MovableObject.h"

class Game;

class MovableObject :
	public DisplayableObject
{
public:
	MovableObject(Game* pEngine);
	~MovableObject(void);

	//Handle drawing of the object
	void Draw();
	//Updating the Object, apply movement etc
	void DoUpdate(int iCurrentTime);

	//Set X of Object
	void setXPosition(int XPos) {
		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iCurrentScreenX = XPos;
		ensureOnScreenX(XPos);
	}

	//Set Y of Object
	void setYPosition(int YPos) {
		m_iPreviousScreenY = m_iCurrentScreenY;
		m_iCurrentScreenY = YPos;
		ensureOnScreenY(YPos);
	}

	//Functions to keep the movable object in its defined X and Y area
	void ensureOnScreenX(int XPos) {
		if (m_iCurrentScreenX < 0 + (m_iDrawWidth / 2)) {
			m_iCurrentScreenX = m_iDrawWidth / 2;
		}

		if (m_iCurrentScreenX >= 200 - (m_iDrawWidth / 2)) {
			m_iCurrentScreenX = 200 - (m_iDrawWidth / 2);
		}
	}
	//See above
	void ensureOnScreenY(int YPos) {
		if (m_iCurrentScreenY >= 580 - (m_iDrawHeight / 2)) {
			m_iCurrentScreenY = 580 - (m_iDrawHeight / 2);
		}

		if (m_iCurrentScreenY <= 201 + (m_iDrawHeight / 2)) {
			m_iCurrentScreenY = 201 + (m_iDrawHeight / 2);
		}
	}

	//Setters for the booleans for each direction
	void setMoveLeft(bool lft) {
		left = lft;
	}

	void setMoveRight(bool rght) {
		right = rght;
	}

	void setMoveUp(bool u) {
		up = u;
	}

	void setMoveDown(bool dwn) {
		down = dwn;
	}

private:
	
	//Direction booleans
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;

	//Colour of object
	int m_iColour;
	//direction, initialised to up
	int dir = 0;
	//Radius
	int radius = 8;
	//Pointer to engine
	Game* m_pMainEngine;
};

