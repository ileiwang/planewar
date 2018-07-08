#include "StdAfx.h"
#include "Bomb.h"
#include "resource.h"


CImageList CBomb::m_Images;


CBomb::CBomb(int x,int y,int Flag):CGameObject(x,y),flag(Flag)
{

}

CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BOMB,RGB(0,0,0), BOMB_WIDTH, BOMB_HEIGHT, 5);
}
BOOL CBomb::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y - BOMB_SPEED;
	}

	if(m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBomb::Draw(CDC* pDC, BOOL bPause, int level, BOOL bUpdate)
{
	if (!bPause)
	{
		if (bUpdate == TRUE)
		{
			if (flag == 1)
			{
				m_ptPos.y = m_ptPos.y - BOMB_SPEED;
				if (m_ptPos.y < -BOMB_HEIGHT)
					return FALSE;
				m_Images.Draw(pDC, level%5, m_ptPos, ILD_TRANSPARENT);
				return TRUE;
			}
			else if (flag == 2)
			{
				m_ptPos.y -= (int)BOMB_SPEED*sin(45);
				m_ptPos.x += (int)BOMB_SPEED*cos(45);
				if (m_ptPos.x > GAME_WIDTH || m_ptPos.y < 0)
					return FALSE;
				//m_Images.Draw(pDC, level%5, m_ptPos, ILD_TRANSPARENT);
			}
			else if (flag == 3)
			{
				m_ptPos.y += (int)BOMB_SPEED*sin(45);
				m_ptPos.x += (int)BOMB_SPEED*cos(45);
				if (m_ptPos.x > GAME_WIDTH || m_ptPos.y > GAME_HEIGHT)
					return FALSE;
				//m_Images.Draw(pDC, level%5, m_ptPos, ILD_TRANSPARENT);
			}
			else if (flag == 4)
			{
				m_ptPos.y += BOMB_SPEED;
				if (m_ptPos.y > GAME_HEIGHT)
					return FALSE;
				//m_Images.Draw(pDC, level%5, m_ptPos, ILD_TRANSPARENT);
			}
			else if (flag == 5)
			{
				m_ptPos.y += (int)BOMB_SPEED*sin(45);
				m_ptPos.x -= (int)BOMB_SPEED*cos(45);
				if (m_ptPos.x <-BOMB_WIDTH || m_ptPos.y > GAME_WIDTH)
					return FALSE;
				//m_Images.Draw(pDC, level%5, m_ptPos, ILD_TRANSPARENT);
			}
			else if (flag == 6)
			{
				m_ptPos.y -= (int)BOMB_SPEED*sin(45);
				m_ptPos.x -= (int)BOMB_SPEED*cos(45);
				if (m_ptPos.x < -BOMB_WIDTH || m_ptPos.y < -BOMB_HEIGHT)
					return FALSE;
				//m_Images.Draw(pDC, level%5, m_ptPos, ILD_TRANSPARENT);
			}
		}
		else
		{
			m_ptPos.y -= BOMB_SPEED;
			if (m_ptPos.y < -BOMB_HEIGHT)
				return FALSE;
			//m_Images.Draw(pDC, level%5, m_ptPos, ILD_TRANSPARENT);
			//return TRUE;
		}
	}
	m_Images.Draw(pDC, level % 5, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

void CBomb::SetSpeed(int Speed)
{
	BOMB_SPEED = Speed;
}

int CBomb::GetSpeed()
{
	return BOMB_SPEED;
}