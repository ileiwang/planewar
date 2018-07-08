// PlaneGameView.h : CPlaneGameView 类的接口
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

protected: // 仅从序列化创建
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// 属性
public:
	CPlaneGameDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//内存DC
	CDC*        m_pMemDC;
	//设备DC
	CClientDC*  m_pDC;
	//内存位图
	CBitmap*    m_pMemBitmap;


protected:
	//初始化游戏
	BOOL InitGame();
	//结束游戏
	void StopGame();

	void Over();
	//刷新游戏的帧画面
	void UpdateFrame(CDC* pMemDC);


	void AI();

	//获得键的状态1->down
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


	int speed;//战机速度
	int life;//战机生命值
	int lifenum;//战机命条数
	int scoresum;//战机总得分
	int score;//记录每关得分
	int bossLife;//BOSS初始生命值
	int level;//记录当前关卡
	int hp;//活力值
	int passscore;//通关分数
	int index;//标记背景图片滚动

	BOOL GetTool;//拾取道具标记
	BOOL bTool;//道具存在标记
	BOOL bBoss;//BOSS进入标记
	BOOL bossLoaded;//BOSS加载完毕
	BOOL bPause;//暂停标记
	BOOL bStop;//停止标记 2为通关停止，3为死亡停止
	BOOL bPass;//每关通关标记
	BOOL bStart;//游戏开始标记
	BOOL bProtect;//保护罩标记
	BOOL bUpdate;//导弹升级标记
	BOOL bWuDi;//无敌模式标记

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



// 生成的消息映射函数
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

#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

