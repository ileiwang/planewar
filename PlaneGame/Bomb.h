#pragma once
#include "gameobject.h"

class CBomb :
	public CGameObject
{
public:
	CBomb(int x,int y,int Flag);
	~CBomb(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+10,m_ptPos.y+BOMB_HEIGHT));
	}

	BOOL Draw(CDC* pDC, BOOL bPause, int level, BOOL bUpdate);

	void SetSpeed(int Speed);
	int GetSpeed();
private:

	static CImageList m_Images;

public:
	static const int BOMB_WIDTH = 20;
	static const int BOMB_HEIGHT = 40;
	int flag;//标识导弹方向
	int BOMB_SPEED = 8;
};
