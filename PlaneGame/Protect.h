#pragma once
#include "GameObject.h"
#include "MyPlane.h"
class CProtect :
	public CGameObject
{
public:
	CProtect();
	~CProtect();
	BOOL Draw(CDC* pDC, BOOL bPause, CPoint & pPoint, BOOL bPro);
	static BOOL LoadImage();
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + PROTECT_WIDTH, m_ptPos.y + PROTECT_HEIGHT));
	}
private:
	static CImageList m_Images;
public:
	static const int PROTECT_WIDTH = 128;
	static const int PROTECT_HEIGHT = 128;
};

