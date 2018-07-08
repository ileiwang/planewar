#include "StdAfx.h"
#include "Ball.h"
#include "resource.h"
#include <cmath>

CImageList CBall::m_Images;

CBall::CBall(int x,int y,int nMontion,int Flag):CGameObject(x,y),m_nMotion(nMontion),flag(Flag)
{

}

CBall::CBall(int x, int y, int nMontion) : CGameObject(x, y), m_nMotion(nMontion)
{

}

CBall::~CBall(void)
{
}

//绘制敌机子弹
BOOL CBall::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		//m_ptPos.y = m_ptPos.y + m_nMotion * 8;
		m_ptPos.y = m_ptPos.y + m_nMotion * BALL_SPEED;
	}

	if(m_ptPos.y > GAME_HEIGHT+BALL_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -BALL_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}

//绘制敌机发射子弹
//BOOL CBall::Draw(CDC* pDC, BOOL bPause, int level)
//{
//	if (!bPause)
//	{
//		m_ptPos.y = m_ptPos.y + m_nMotion * BALL_SPEED;
//	}
//
//	if (m_ptPos.y > GAME_HEIGHT + BALL_HEIGHT)
//		return FALSE;
//	if (m_ptPos.y < -BALL_HEIGHT)
//		return FALSE;
//	m_Images.Draw(pDC, level, m_ptPos, ILD_TRANSPARENT);
//
//	return TRUE;
//}

//绘制BOSS发射子弹
BOOL CBall::Draw(CDC *pDC, BOOL bPause, BOOL isBoss)
{
	if (!bPause&&isBoss)
	{
		if (flag == 1)
		{
			m_ptPos.y = m_ptPos.y -  BALL_SPEED;
			if (m_ptPos.y > GAME_HEIGHT)
				return FALSE;
		}
		else if (flag == 2)
		{
			m_ptPos.y -= (int)BALL_SPEED*sin(60);
			m_ptPos.x += (int)BALL_SPEED*cos(60);
			if (m_ptPos.x > GAME_WIDTH || m_ptPos.y <-BALL_HEIGHT)
				return FALSE;
		}
		else if (flag == 3)
		{
			m_ptPos.y += (int)BALL_SPEED*sin(60);
			m_ptPos.x += (int)BALL_SPEED*cos(60);
			if (m_ptPos.x > GAME_WIDTH || m_ptPos.y > GAME_HEIGHT)
				return FALSE;
		}
		else if (flag == 4)
		{
			m_ptPos.y += BALL_SPEED;
			if (m_ptPos.y > GAME_HEIGHT)
				return FALSE;
		}
		else if (flag == 5)
		{
			m_ptPos.y += (int)BALL_SPEED*sin(60);
			m_ptPos.x -= (int)BALL_SPEED*cos(60);
			if (m_ptPos.x<-GAME_WIDTH || m_ptPos.y>GAME_HEIGHT)
				return FALSE;
		}
		else if (flag == 6)
		{
			m_ptPos.y -= (int)BALL_SPEED*sin(60);
			m_ptPos.x -= (int)BALL_SPEED*cos(60);
			if (m_ptPos.x < -GAME_WIDTH || m_ptPos.y < -BALL_HEIGHT)
				return FALSE;
		}
	}
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL CBall::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BALL,RGB(0,0,0),8,8,1);
}