#pragma once
#include "DisplayableObject.h"

class Game;

class BouncingObject :
	public DisplayableObject
{
public:
	BouncingObject(Game* pEngine);
	~BouncingObject();

	void Draw();

	void DoUpdate(int iCurrentTime);

private:
	//Object radius
	int radius = 5;
	//Current direction
	int dir = 1;

	Game* m_pMainEngine;
};

