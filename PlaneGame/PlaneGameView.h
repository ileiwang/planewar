// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//


#pragma once

#include "PlaneGame.h"

#include "PlaneGameDoc.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include "Boss.h"
#include "Tool.h"
#include "Protect.h"
#include "Help.h"
#include <cmath>
#include "PlaneSet.h"


#define NEXT 1
#define SUCCESS 2
#define DIE 3



class CMyPlane;
class CPlaneGameView : public CView
{

	enum ObjType{enEnemy,enBomb,enBall,enExplosion, enPlane, enTool,enBossBall};

protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// ����
public:
	CPlaneGameDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//�ڴ�DC
	CDC*        m_pMemDC;
	//�豸DC
	CClientDC*  m_pDC;
	//�ڴ�λͼ
	CBitmap*    m_pMemBitmap;


protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();

	void Over();
	//ˢ����Ϸ��֡����
	void UpdateFrame(CDC* pMemDC);


	void AI();

	//��ü���״̬1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;

	CObList    m_ObjList[7];

	CEnemy *enemy;
	CBoss *boss;
	CBomb *bomb;
	CBall *ball;
	CExplosion *explosion;
	CTool* tool;
	CProtect *prot;
	//CBackground backgnd;

	CRect rect;


	int speed;//ս���ٶ�
	int life;//ս������ֵ
	int lifenum;//ս��������
	int scoresum;//ս���ܵ÷�
	int score;//��¼ÿ�ص÷�
	int bossLife;//BOSS��ʼ����ֵ
	int level;//��¼��ǰ�ؿ�
	int hp;//����ֵ
	int passscore;//ͨ�ط���
	int index;//��Ǳ���ͼƬ����

	BOOL GetTool;//ʰȡ���߱��
	BOOL bTool;//���ߴ��ڱ��
	BOOL bBoss;//BOSS������
	BOOL bossLoaded;//BOSS�������
	BOOL bPause;//��ͣ���
	BOOL bStop;//ֹͣ��� 2Ϊͨ��ֹͣ��3Ϊ����ֹͣ
	BOOL bPass;//ÿ��ͨ�ر��
	BOOL bStart;//��Ϸ��ʼ���
	BOOL bProtect;//�����ֱ��
	BOOL bUpdate;//�����������
	BOOL bWuDi;//�޵�ģʽ���

public:
	int GetSpeed()
	{
		return speed;
	}
	void SetSpeed(int Speed)
	{
		speed = Speed;
	}
	void Start();
	void Restart();
	//void PlaneSet();
	void Wudi()
	{
		if (bWuDi == TRUE)
			bWuDi = FALSE;
		else
			bWuDi = TRUE;
	}

	void PlaneSet();
	void set1()
	{
		level = 1;
	}
	void set2()
	{
		level = 2;
	}
	void set3()
	{
		level = 3;
	}
	void set4()
	{
		level = 4;
	}
	void set5()
	{
		level = 5;
	}
	void Help();



// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

