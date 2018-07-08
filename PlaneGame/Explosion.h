#pragma once
#include "gameobject.h"

class CExplosion :public CGameObject
{
public:
	CExplosion(int x,int y);
	~CExplosion(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+EXPLOSION_WIDTH,m_ptPos.y+EXPLOSION_WIDTH));
	}
	void SetBossDie(BOOL Flag)
	{
		flag = Flag;
	}
	BOOL GetBossDie()
	{
		return flag;
	}

private:
	//ը����ͼƬ�б�
	static CImageList m_Images;
	//ͼ�������Ĳ�������
	int   m_nProcess;
	//����Ƿ���BOSS��ը
	BOOL flag;

public:
	static const int  EXPLOSION_WIDTH = 66;
	static const int EXPLOSION_HEIGHT = 66;

};
