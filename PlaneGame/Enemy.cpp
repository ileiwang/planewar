#include "StdAfx.h"
#include "Enemy.h"
#include "resource.h"

CImageList CEnemy::m_Imagesup;
CImageList CEnemy::m_Imagesdown;
CImageList CEnemy::m_Imagesleft;
CImageList CEnemy::m_Imagesright;

CEnemy::CEnemy(int Montion)
{
	m_nMotion = Montion;
	//���ȷ��Xλ��
	m_ptPos.x = rand()%(GAME_WIDTH-ENEMY_HEIGHT)+1;

	//���ȷ��ͼ������
	//m_nImgIndex = rand()%2;

	//����ͼ������ȷ������
	//m_nMotion=1;
	//m_ptPos.y=-ENEMY_HEIGHT;
	//if (m_nImgIndex%2!=0)//�����ͼ��������ż��
	//{
	//	m_nMotion=-1;
	//	m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	//}

	if (m_nMotion == 1)//����
	{
		m_ptPos.y = -ENEMY_HEIGHT;
	}
	else if (m_nMotion == -1)//����
	{
		m_ptPos.y = GAME_HEIGHT + ENEMY_HEIGHT;
	}
	else if (m_nMotion == 2)//����
	{
		m_ptPos.x = 0;
		m_ptPos.y = rand() % (GAME_HEIGHT / 2);
	}
	else if (m_nMotion == 3)//����
	{
		m_ptPos.x = GAME_WIDTH;
		m_ptPos.y = rand() % (GAME_HEIGHT / 2);
	}



	//���ȷ���ٶ�
	m_V = rand()%6+2;

	m_nWait=0;
}

CEnemy::~CEnemy(void)
{
}
BOOL CEnemy::LoadImage()
{
	CGameObject::LoadImage(m_Imagesup,IDB_ENEMYUP,RGB(0,0,0), ENEMY_WIDTH,ENEMY_HEIGHT,2);
	CGameObject::LoadImage(m_Imagesdown, IDB_ENEMYDOWN, RGB(0, 0, 0), ENEMY_WIDTH, ENEMY_HEIGHT, 2);
	CGameObject::LoadImage(m_Imagesleft, IDB_ENEMYLEFT, RGB(0, 0, 0), ENEMY_WIDTH, ENEMY_HEIGHT, 2);
	CGameObject::LoadImage(m_Imagesright, IDB_ENEMYRIGHT, RGB(0, 0, 0), ENEMY_WIDTH, ENEMY_HEIGHT, 2);
	return TRUE;
}
BOOL CEnemy::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>20)
		m_nWait=0;

	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if(m_ptPos.y > GAME_HEIGHT+ENEMY_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -ENEMY_HEIGHT)
		return FALSE;

	m_Imagesup.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}

BOOL CEnemy::Draw(CDC *pDC, BOOL bPause, int level)
{

	if (!bPause)
	{
		if (m_nMotion == 1 || m_nMotion == -1)
		{
			m_ptPos.y = m_ptPos.y + m_nMotion * ENEMY_SPEED;
		}
		else if (m_nMotion == 2)
		{
			m_ptPos.x = m_ptPos.x + ENEMY_SPEED;
		}
		else
		{
			m_ptPos.x = m_ptPos.x - ENEMY_SPEED;
		}
	}

	if (m_nMotion == 1 || m_nMotion == -1)
	{
		if (m_ptPos.y > GAME_HEIGHT + ENEMY_HEIGHT)
			return FALSE;
		if (m_ptPos.y < -ENEMY_HEIGHT)
			return FALSE;
	}
	else
	{
		if (m_ptPos.x > GAME_WIDTH + ENEMY_WIDTH)
			return FALSE;
		if (m_ptPos.x < -ENEMY_WIDTH)
			return FALSE;
	}
	if (m_nMotion == 1)
		m_Imagesdown.Draw(pDC, level, m_ptPos, ILD_TRANSPARENT);
	else if (m_nMotion == -1)
		m_Imagesup.Draw(pDC, level, m_ptPos, ILD_TRANSPARENT);
	else if (m_nMotion == 2)
		m_Imagesright.Draw(pDC, level, m_ptPos, ILD_TRANSPARENT);
	else if (m_nMotion == 3)
		m_Imagesleft.Draw(pDC, level, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}
BOOL CEnemy::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}