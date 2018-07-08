#pragma once
#include "gameobject.h"

class CEnemy :public CGameObject
{
public:
	CEnemy(int Montion);
	~CEnemy(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	BOOL Draw(CDC* pDC, BOOL bPause, int level);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+ENEMY_HEIGHT,m_ptPos.y+ENEMY_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}

	void SetMontion(int Dir)
	{
		m_nMotion = Dir;
	}

	void setSpeed(int Speed)
	{
		ENEMY_SPEED = Speed;
	}

	BOOL isAlive()
	{
		if (ENEMY_LIFE > 0)
			return TRUE;
		else
			return FALSE;
	}

	int GetLife()
	{
		return ENEMY_LIFE;
	}
	void SetLife(int life)
	{
		ENEMY_LIFE = life;
	}

	//是否可以开火发射子弹
	BOOL Fired();
public:
	//static const int ENEMY_HEIGHT = 35;
	static CImageList m_Imagesup;
	static CImageList m_Imagesdown;
	static CImageList m_Imagesleft;
	static CImageList m_Imagesright;

	static const int ENEMY_WIDTH = 75;
	static const int ENEMY_HEIGHT = 75;

	int    m_nMotion;//方向 1->向下 0->停止 -1->向上    2向右，3向左
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	int ENEMY_SPEED=1;
	int ENEMY_LIFE;
	int    m_nWait;//发射延时
};
