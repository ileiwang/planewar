#pragma once
#include "GameObject.h"

class CBall :public CGameObject
{
public:
	CBall(int x,int y,int nMontion,int Flag);
	CBall(int x, int y, int nMontion);
	~CBall(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	BOOL Draw(CDC* pDC, BOOL bPause, BOOL isBoss);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+BALL_HEIGHT,m_ptPos.y+BALL_HEIGHT));
	}

	void setSpeed(int speed)
	{
		BALL_SPEED = speed;
	}

	int BALL_SPEED = 3;
private:
	static const int BALL_WIDTH=8;
	static const int BALL_HEIGHT=8;
	static CImageList m_Images;
	int    m_nMotion;
	int flag;//标记六个方向之一
};
