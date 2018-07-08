#include "stdafx.h"
#include "Tool.h"
#include "resource.h"
CImageList CTool::m_Images;

CTool::CTool(int x,int y)
{
	m_ptPos.x = rand() % x;
	m_ptPos.y = rand() % y;
	flagy = 1;//向下
	if (rand() % 2)
	{
		flagx = 1;//向右
	}
	else
	{
		flagx = -1;//向左
	}
}


CTool::~CTool()
{
}

BOOL CTool::LoadImage()
{
	CGameObject::LoadImage(m_Images, IDB_TOOL, RGB(0, 0, 0), TOOL_WIDTH, TOOL_HEIGHT, 2);
	return TRUE;
}

BOOL CTool::Draw(CDC *pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y += TOOL_SPEED * flagy;
		m_ptPos.x += TOOL_SPEED * flagx;
		//边缘检测
		EdgeDetect();	
	}
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL CTool::Draw(CDC *pDC, BOOL bPause, CMyPlane* plane, int level)
{
	double x = (plane->GetPoint().x - m_ptPos.x);
	double y = (plane->GetPoint().y - m_ptPos.y);
	double angle;
	if (x == 0)
	{
		if (plane->GetPoint().y >= m_ptPos.y)
		{
			x = 0.0000001;
		}
		else
		{
			x = -0.0000001;
		}
	}

	if (y == 0)
	{
		if (plane->GetPoint().x >= m_ptPos.x)
		{
			y = 0.0000001;
		}
		else
		{
			y = -0.0000001;
		}
	}

	if (x > 0 && y > 0)
		angle = atan(fabs(y / x));

	else if (x < 0 && y < 0)
		angle = PI - atan(fabs(y / x));

	else if (x < 0 && y < 0)
		angle = PI + atan(fabs(y / x));
	else
		angle = 2 * PI - atan(fabs(y / x));
	int speed = TOOL_SPEED * 10;
	m_ptPos.x += speed*cos(angle) * 2;
	m_ptPos.y += speed*sin(angle) * 2;
	EdgeDetect();
	m_Images.Draw(pDC, level, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}