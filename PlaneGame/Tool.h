#pragma once
#include "GameObject.h"
#include "MyPlane.h"
#define PI 3.1415926

class CTool :
	public CGameObject
{
public:
	CTool(int x,int y);
	~CTool();
	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC *pDC, BOOL bPause, CMyPlane* plane, int level);
	static BOOL LoadImage();
	static const int TOOL_WIDTH = 30;
	static const int TOOL_HEIGHT = 30;
	int TOOL_SPEED = 3;
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + TOOL_WIDTH, m_ptPos.y + TOOL_HEIGHT));
	}
	void EdgeDetect()//±ßÔµ¼ì²â
	{
		if (m_ptPos.y < 0)
		{
			m_ptPos.y = 0;
			flagy = 1;
		}
		if (m_ptPos.y > GAME_HEIGHT)
		{
			m_ptPos.y = GAME_HEIGHT;
			flagy = -1;
		}
		if (m_ptPos.x > GAME_WIDTH)
		{
			m_ptPos.x = GAME_WIDTH;
			flagx = -1;
		}
		if (m_ptPos.x < 0)
		{
			m_ptPos.x = 0;
			flagx = 1;
		}
	}
private:
	static CImageList m_Images;
	int flagx, flagy;
	BOOL exist = FALSE;
};

