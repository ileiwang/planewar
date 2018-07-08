#pragma once
#include "Enemy.h"
class CBoss :
	public CEnemy
{
public:
	CBoss(int Dir);
	~CBoss();
	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC* pDC, BOOL bPause, int level);
	static BOOL LoadImage();
	static const int BOSS_WIDTH = 120;
	static const int BOSS_HEIGHT = 120;
	int BOSS_SPEED = 6;
	int BOSS_LIFE;
	CRect GetRect();
	void SetLife(int life)
	{
		BOSS_LIFE = life;
	}

	int GetLife()
	{
		return BOSS_LIFE;
	}
private:
	static CImageList m_Images;
	BOOL bLoad;
	int motiony;
};

