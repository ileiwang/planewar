#include "stdafx.h"
#include "Boss.h"
#include "resource.h"

CImageList CBoss::m_Images;

CBoss::CBoss(int Dir):CEnemy(Dir)
{
	m_ptPos.x = rand() % GAME_WIDTH;
	m_ptPos.y = -BOSS_HEIGHT;
	bLoad = FALSE;
	motiony = 1;
}


CBoss::~CBoss()
{
}


BOOL CBoss::LoadImage()
{
	CGameObject::LoadImage(m_Images, IDB_BOSS, RGB(0, 0, 0), BOSS_WIDTH, BOSS_HEIGHT, 3);
	return TRUE;
}

BOOL CBoss::Draw(CDC * pDC, BOOL bPause)
{
	if (!bPause)
	{
		if (bLoad == FALSE)
		{
			m_ptPos.y += BOSS_SPEED;//还未出场完毕，只改纵坐标
			if (m_ptPos.y >= 120)//0
			{
				bLoad = TRUE;
			}

			m_Images.Draw(pDC, 1, m_ptPos, ILD_TRANSPARENT);
			return TRUE;
		}
		else
		{
			m_ptPos.x += 3 * m_nMotion;//Boss出场完毕，只改横坐标
			m_ptPos.y += 3;
			if (m_ptPos.y >= GAME_HEIGHT / 2)
			{
				m_ptPos.y -= 6;
			}
			if (m_ptPos.y <= 30)
			{
				m_ptPos.y += 3;
			}
			if (m_ptPos.x > GAME_WIDTH - BOSS_WIDTH)
			{
				m_nMotion = -1;
				m_ptPos.x = GAME_WIDTH - BOSS_WIDTH;
			}
			if (m_ptPos.x < 0)
			{
				m_nMotion = 1;
				m_ptPos.x = 0;
			}
			m_Images.Draw(pDC, 1, m_ptPos, ILD_TRANSPARENT);
			return TRUE;
		}
	}
	else
		return FALSE;
}


BOOL CBoss::Draw(CDC * pDC, BOOL bPause, int level)
{
	if (!bPause)
	{
		if (bLoad == FALSE)
		{
			m_ptPos.y += BOSS_SPEED;//还未出场完毕，只改纵坐标
			if (m_ptPos.y >= 0)
				bLoad = TRUE;
			m_Images.Draw(pDC, 1, m_ptPos, ILD_TRANSPARENT);
			return TRUE;
		}
		else
		{
			m_ptPos.x += 3 * m_nMotion;
			m_ptPos.y += 1* motiony;

			if (m_ptPos.x > GAME_WIDTH - BOSS_WIDTH)
			{
				m_nMotion = -1;
				m_ptPos.x = GAME_WIDTH - BOSS_WIDTH;
			}
			if (m_ptPos.x < 0)
			{
				m_nMotion = 1;
				m_ptPos.x = 0;
			}
			if (m_ptPos.y > GAME_HEIGHT/2)
			{
				m_ptPos.y = GAME_HEIGHT / 2;
				motiony = -1;
			}
			if (m_ptPos.y <10)
			{
				m_ptPos.y = 10;
				motiony = 1;
			}
			m_Images.Draw(pDC, level % 3, m_ptPos, ILD_TRANSPARENT);
			return TRUE;
		}
	}
	else
		return FALSE;
}
CRect CBoss::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + BOSS_WIDTH, m_ptPos.y + BOSS_HEIGHT));
}