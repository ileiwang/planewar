#include "stdafx.h"
#include "Protect.h"
#include "resource.h"

CImageList CProtect::m_Images;

CProtect::CProtect()
{
}


CProtect::~CProtect()
{
}

BOOL CProtect::LoadImage()
{
	CGameObject::LoadImage(m_Images, IDB_PROTECT, RGB(0, 0, 0), PROTECT_WIDTH, PROTECT_HEIGHT, 1);
	return  TRUE;
}

BOOL CProtect::Draw(CDC* pDC, BOOL bPause, CPoint & pPoint, BOOL bPro)
{
	if (bPause == FALSE)
	{
		if (bPro)
		{
			CPoint point;
			point.x = pPoint.x - (PROTECT_WIDTH - CMyPlane::PLANE_WIDTH) / 2;
			point.y = pPoint.y - (PROTECT_HEIGHT - CMyPlane::PLANE_HEIGHT) / 2;
			m_Images.Draw(pDC, 0, point, ILD_TRANSPARENT);
		}
	}
	return TRUE;
}