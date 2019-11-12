#include "header.h"

#include "MapTileManager.h"

#include "MovableObject.h"

#include "Game.h"

MovableObject::MovableObject(Game* pEngine)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
{

	//Starting draw position
	m_iStartDrawPosX = -radius + 1;
	m_iStartDrawPosY = -radius + 1;

	//Size of drawn Object
	m_iDrawWidth = 2 * (radius - 1);
	m_iDrawHeight = 2 * (radius - 1);

	//Put in the centre of the middle boundary
	m_iPreviousScreenX = m_iCurrentScreenX = 100;
	m_iPreviousScreenY = m_iCurrentScreenY = 390;

	//Colour of Object
	m_iColour = 0x00dd00;

	//Visible!
	SetVisible(true);
}


MovableObject::~MovableObject()
{
}

void MovableObject::Draw() {

	if (!IsVisible())
		return;

	//Circle outline

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - radius,
		m_iCurrentScreenY - radius,
		m_iCurrentScreenX + (radius - 1),
		m_iCurrentScreenY + (radius - 1),
		0
	);

	//Coloured Circle

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - (radius - 1),
		m_iCurrentScreenY - (radius - 1),
		m_iCurrentScreenX + (radius - 2),
		m_iCurrentScreenY + (radius - 2),
		m_iColour
	);

	
	StoreLastScreenPositionForUndraw();
}

void MovableObject::DoUpdate(int iCurrentTime) {
	//Prev positions is the now the current position
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	//Change current screen position based on the booleans for direction
	if (left) { m_iCurrentScreenX -= 2; }
	if (right) { m_iCurrentScreenX += 2; }
	if (up) { m_iCurrentScreenY -= 2; }
	if (down) { m_iCurrentScreenY += 2; }


	// Ensure not off the screen
	ensureOnScreenX(m_iCurrentScreenX);
	ensureOnScreenY(m_iCurrentScreenY);

	RedrawObjects();
}

