#include "header.h"

#include "BouncingObject.h"

#include "Game.h"



BouncingObject::BouncingObject(Game* pEngine) 
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
	m_iPreviousScreenX = m_iCurrentScreenX = 400;
	m_iPreviousScreenY = m_iCurrentScreenY = 25;

	//Visible!
	SetVisible(true);


}


BouncingObject::~BouncingObject()
{
}

void BouncingObject::Draw() {
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
		0xffffff
	);


	StoreLastScreenPositionForUndraw();
}

void BouncingObject::DoUpdate(int iCurrentTime) {
	//Prev positions is the now the current position
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	//Calculate whether to switch direction
	if (m_pMainEngine->SafeGetBackgroundPixel(m_iCurrentScreenX + (dir * radius), m_iCurrentScreenY) == 0) {
		dir *= -1;
	}


	switch (dir) {
	case 1: m_iCurrentScreenX += 1; break;
	case -1: m_iCurrentScreenX -= 1; break;
	}


}
