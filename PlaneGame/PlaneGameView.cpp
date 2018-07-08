// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//

#include "stdafx.h"

#include "PlaneGameView.h"

#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()

	ON_COMMAND(ID_START, &CPlaneGameView::Start)
	ON_COMMAND(ID_RESTART, &CPlaneGameView::Restart)
	ON_COMMAND(ID_WUDI, &CPlaneGameView::Wudi)
	ON_COMMAND(ID_GQ1, &CPlaneGameView::set1)
	ON_COMMAND(ID_GQ2, &CPlaneGameView::set2)
	ON_COMMAND(ID_GQ3, &CPlaneGameView::set3)
	ON_COMMAND(ID_GQ4, &CPlaneGameView::set4)
	ON_COMMAND(ID_GQ5, &CPlaneGameView::set5)
	ON_COMMAND(ID_HELP, &CPlaneGameView::Help)
	ON_COMMAND(ID_PLANESET, &CPlaneGameView::PlaneSet)
END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView() :m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������

}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	InitGame();
}

void CPlaneGameView::StopGame()
{
	KillTimer(1);
	//KillTimer(2);
	//KillTimer(3);
	KillTimer(4);
	KillTimer(5);
	KillTimer(6);
	if (m_ObjList[enEnemy].GetCount() > 0)
		m_ObjList[enEnemy].RemoveAll();
	if (m_ObjList[enPlane].GetCount() > 0)
		m_ObjList[enPlane].RemoveAll();
	if (m_ObjList[enBomb].GetCount() > 0)
		m_ObjList[enBomb].RemoveAll();
	if (m_ObjList[enBall].GetCount() > 0)
		m_ObjList[enBall].RemoveAll();
	if (m_ObjList[enExplosion].GetCount() > 0)
		m_ObjList[enExplosion].RemoveAll();
	if (m_ObjList[enTool].GetCount() > 0)
		m_ObjList[enTool].RemoveAll();
	if (m_ObjList[enBossBall].GetCount() > 0)
		m_ObjList[enBossBall].RemoveAll();

	delete boss;
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

BOOL CPlaneGameView::InitGame()
{
	//CRect rc;
	GetClientRect(rect);

	//�������������
	srand((unsigned)time(NULL));

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC, GAME_WIDTH, GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CBoss::LoadImage();
	CTool::LoadImage();
	CProtect::LoadImage();

	//��������(ս��)
	m_pMe = new CMyPlane;

	//����ս���ٶ�
	//m_pMe->SetSpeed(speed);


	//��������
	
	life = 10;//ս��������
	lifenum = 3;//ս����������
	score = 0;//ÿ�ص÷�
	scoresum = 0;//�ܵ÷�
	speed = 6;//ս���ٶ�
	hp = 0;//HPֵ
	level = 1;//�ؿ�
	bossLife = 100;//BOSS������ֵ
	index = 0;//��������
	bossLoaded = FALSE;//BOSS���ر��
	bPass = FALSE;//ͨ�ر��
	bPause = TRUE;//��ͣ���
	bTool = FALSE;//���ڵ��߱��
	bWuDi = FALSE;//�޵�ģʽ���
	bStop = FALSE;//��Ϸֹͣ���
	boss = NULL;//BOSS����
	GetTool = FALSE;//��õ��߱��
	bStart = FALSE;//��Ϸ��ʼ���
	bProtect = FALSE;//�����ֱ��
	bUpdate = FALSE;//�����������
	bBoss = FALSE;//BOSS���ڱ��

	//������Ϸ
	SetTimer(1, 30, NULL);

	//ˢ�µл�Ѫ��
	SetTimer(2, 10, NULL);

	// ����Ball
	//SetTimer(3, 300 - 10 * level, NULL);

	//��������
	SetTimer(4, 80, NULL);

	//ˢ��HP
	SetTimer(5, 200, NULL);

	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//�������
	//pMemDC->FillSolidRect(0,0,GAME_WIDTH,GAME_HEIGHT,RGB(84, 142, 239));

	//���Ƴ�ʼҳ
	if (!bStart)
	{
		//���ƾ�̬����ͼƬ
		CDC dcMem;
		dcMem.CreateCompatibleDC(pMemDC);
		CBitmap welcome;
		welcome.LoadBitmapW(IDB_WELCOME);
		CBitmap *back = dcMem.SelectObject(&welcome);
		pMemDC->StretchBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &dcMem, 0, 0, 1300, 815, SRCCOPY);

		//��ʾ������ʾ
		HFONT font;
		font = CreateFont(24, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		pMemDC->SelectObject(font);
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextColor(RGB(255, 0, 0));
		CString str = _T("�ɻ���ս --- By Lei Wang");
		pMemDC->TextOut(GAME_WIDTH / 4,30, str);
		str = _T("�������Ϸ->��ʼ��Ϸ��������Ϸ");
		pMemDC->TextOut(GAME_WIDTH / 6, 100, str);
		DeleteObject(font);
		font = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		pMemDC->SelectObject(font);
		pMemDC->SetTextColor(RGB(0, 255, 0));
		pMemDC->TextOut(50, GAME_HEIGHT / 2 + 200, _T("Tips:S���������� F�������� P����ͣ W���޵�ģʽ Q���˳�"));
		pMemDC->TextOut(50, GAME_HEIGHT / 2 + 230, _T("�����/�������ƶ����ո��/���������䵼��"));
		//m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
		m_pDC->BitBlt(0, 0, rect.Width(), rect.Height(), m_pMemDC, 0, 0, SRCCOPY);
		DeleteObject(font);
	}

	//���ƹ�������
	else
	{
		CDC dcMem;
		dcMem.CreateCompatibleDC(pMemDC);
		CBitmap welcome;

		if (level == 1)
		{
			welcome.LoadBitmapW(IDB_BG1);
		}
		else if (level == 2)
		{
			welcome.LoadBitmapW(IDB_BG2);
		}
		else if (level == 3)
		{
			welcome.LoadBitmapW(IDB_BG3);
		}
		else if (level == 4)
		{
			welcome.LoadBitmapW(IDB_BG4);
		}
		else if (level == 5)
		{
			welcome.LoadBitmapW(IDB_BG5);
		}
		CBitmap *back = dcMem.SelectObject(&welcome);
		pMemDC->StretchBlt(0, index, GAME_WIDTH, GAME_HEIGHT, &dcMem, 0, 0, 1300, 815, SRCCOPY);
		pMemDC->StretchBlt(0, index - GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT, &dcMem, 0, 0, 1300, 815, SRCCOPY);
	}

	//�����ҷ�ս����������
	if (m_pMe != NULL&&bStart)
	{
		m_pMe->Draw(m_pMemDC, FALSE, level % 6 - 1);
		prot->Draw(m_pMemDC, FALSE, m_pMe->GetPoint(), bProtect);
	}
	//else
	//{   //Game Over
	//	CString str = _T("Game Over!");
	//	pMemDC->SetBkMode(TRANSPARENT);
	//	pMemDC->SetTextAlign(TA_CENTER);
	//	pMemDC->SetTextColor(RGB(255, 0, 0));
	//	pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
	//}

	//���� ��������ը���л����ӵ�
	//for(int i=0;i<6;i++)
	//{
	//	POSITION pos1,pos2;
	//	for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
	//	{
	//		CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
	//		if(!pObj->Draw(pMemDC,FALSE))
	//		{
	//			m_ObjList[i].RemoveAt(pos2);
	//			delete pObj;
	//		}
	//	}
	//}

	//���Ƶл�
	if (m_pMe != NULL && !bPause)
	{
		POSITION pos1, pos2;
		for (pos1 = m_ObjList[enEnemy].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CEnemy* pObj = (CEnemy*)m_ObjList[enEnemy].GetNext(pos1);
			if (!pObj->Draw(pMemDC, FALSE, level % 2))
			{
				m_ObjList[enEnemy].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//�����ӵ�
	if (m_pMe != NULL && !bPause)
	{
		POSITION pos1, pos2;
		for (pos1 = m_ObjList[enBall].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CBall* pObj = (CBall*)m_ObjList[enBall].GetNext(pos1);
			if (!pObj->Draw(pMemDC, FALSE))
			{
				m_ObjList[enBall].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//���Ƶ���
	if (m_pMe != NULL && !bPause)
	{
		POSITION pos1, pos2;
		for (pos1 = m_ObjList[enBomb].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CBomb* pObj = (CBomb*)m_ObjList[enBomb].GetNext(pos1);
			if (!pObj->Draw(pMemDC, FALSE, level, bUpdate))
			{
				m_ObjList[enBomb].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//���Ʊ�ը
	if (m_pMe != NULL && !bPause)
	{
		POSITION pos1, pos2;
		for (pos1 = m_ObjList[enExplosion].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CExplosion* pObj = (CExplosion*)m_ObjList[enExplosion].GetNext(pos1);
			if (!pObj->Draw(pMemDC, FALSE))
			{
				m_ObjList[enExplosion].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//����BOSS
	if (m_pMe != NULL && boss != NULL && !bPause && bBoss)
	{
		if (boss->Draw(m_pMemDC, FALSE, level))
		{
			bossLoaded = TRUE;
		}
	}

	//����BOSS�ӵ�
	if (m_pMe != NULL && !bPause && bBoss)
	{
		POSITION pos1, pos2;
		for (pos1 = m_ObjList[enBossBall].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CBall* pObj = (CBall*)m_ObjList[enBossBall].GetNext(pos1);
			if (!pObj->Draw(pMemDC, FALSE,TRUE))
			{
				m_ObjList[enBossBall].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//���Ƶл�Ѫ��
	if (m_pMe != NULL && !bPause)
	{
		POSITION pos1, pos2;
		for (pos1 = m_ObjList[enEnemy].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CEnemy* pObj = (CEnemy*)m_ObjList[enEnemy].GetNext(pos1);
			if (pObj->isAlive())
			{
				CBrush brush;
				brush.CreateSolidBrush(RGB(255, 0, 0));
				CBrush* brush1 = m_pMemDC->SelectObject(&brush);
				int buttomPos = pObj->GetPoint().y - 5;
				int topPos = buttomPos - 9;
				int leftPos = pObj->GetPoint().x;
				int rightPos = (leftPos + pObj->ENEMY_WIDTH*(pObj->ENEMY_LIFE) / (3 + level) - 10);
				m_pMemDC->Rectangle(leftPos, topPos, rightPos, buttomPos);
				brush.DeleteObject();
				m_pMemDC->SelectObject(&brush1);
			}
		}
	}

	//���Ƶ���
	if (m_pMe != NULL && !bPause)
	{
		POSITION pos1, pos2;
		for (pos1 = m_ObjList[enTool].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CTool* pObj = (CTool*)m_ObjList[enTool].GetNext(pos1);
			//--------------------
			//BOOL flag;
			if (bTool)
			{
				if (GetTool)
				{
					pObj->Draw(m_pMemDC, FALSE, m_pMe, level % 2);
					GetTool = FALSE;
				}
				else
				{
					pObj->Draw(m_pMemDC, FALSE);
				}	
			}
			//if (flag == FALSE)
			//{
				//m_ObjList[enTool].RemoveAt(pos2);
				//delete pObj;
			//}
			//-----------------------------------
			//if (!pObj->Draw(pMemDC, FALSE))
			//{
			//	m_ObjList[enTool].RemoveAt(pos2);
			//	delete pObj;
			//}
			//-----------------------------------
		}
	}
	
	//ͨ�ط���
	passscore = 30 + level * 10;

	//ͨ�سɹ���ʾ
	if (bStop == SUCCESS)//SUCCESS���ͨ�ض���Ϸֹͣ
	{
		HFONT font;
		font = CreateFont(18, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		m_pMemDC->SelectObject(font);
		m_pMemDC->SetBkMode(TRANSPARENT);
		m_pMemDC->SetTextColor(RGB(255, 255, 255));
		m_pMemDC->TextOutW(GAME_WIDTH / 2-100, GAME_HEIGHT / 2, _T("��ͨ��!�Ƿ����¿�ʼ(Y/N)��"));
		DeleteObject(font);
	}

	//ս��������ʾ
	else if (bStop == DIE)//DIE��ʾս����������Ϸֹͣ
	{
		HFONT font;
		font = CreateFont(18, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		m_pMemDC->SelectObject(font);
		m_pMemDC->SetBkMode(TRANSPARENT);
		m_pMemDC->SetTextColor(RGB(255, 255, 255));
		CString str;
		m_pMemDC->TextOutW(GAME_WIDTH / 2-100, GAME_HEIGHT / 2 - 40, _T("GAME OVER!"));
		str.Format(_T("�÷֣�%d"), scoresum);
		m_pMemDC->TextOutW(GAME_WIDTH / 2-100, GAME_HEIGHT / 2 - 20, str);
		m_pMemDC->TextOutW(GAME_WIDTH / 2-100, GAME_HEIGHT / 2, _T("�Ƿ����¿�ʼ(Y/N)��"));
		DeleteObject(font);
	}

	//��ʾ��������
	if (m_pMe != NULL&&bStart)
	{
		HFONT font;
		CBrush brush;
		CString str;
		font = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		m_pMemDC->SelectObject(font);
		m_pMemDC->SetTextColor(RGB(0, 255, 0));
		m_pMemDC->SetBkMode(TRANSPARENT);

		str.Format(_T("�ؿ�:%d"), level);
		m_pMemDC->TextOutW(10, 0, str);
		str.Format(_T("��ǰ/�ܵ÷�(%d/%d)"), score, scoresum + score);
		m_pMemDC->TextOutW(10, 20, str);
		str.Format(_T("����ֵ:%d"), life);
		m_pMemDC->TextOutW(10, 40, str);
		str.Format(_T("������:%d"), lifenum);
		m_pMemDC->TextOutW(10, 60, str);
		str.Format(_T("ս������:(%d,%d)"), m_pMe->GetPoint().x, m_pMe->GetPoint().y);
		m_pMemDC->TextOutW(10, 80, str);
		str.Format(_T("ս���ٶ�:%d"), speed);
		m_pMemDC->TextOutW(10, 100, str);


		if (bWuDi == TRUE)
		{
			m_pMemDC->TextOutW(10, 210, _T("���޵�ģʽ"));
		}

		if (bWuDi == FALSE)
		{
			m_pMemDC->TextOutW(10, 210, _T("W:�޵�ģʽ"));
		}

		if (bProtect == TRUE)
		{
			m_pMemDC->TextOutW(10, 225, _T("�̷�����"));
		}
		if (bProtect == FALSE)
		{
			m_pMemDC->TextOutW(10, 225, _T("F:������"));
		}
		if (bUpdate == TRUE)
		{
			m_pMemDC->TextOutW(10, 240, _T("�̵�������"));
		}
		if (bUpdate == FALSE)
		{
			m_pMemDC->TextOutW(10, 240, _T("S:��������"));
		}
		if (bPause)
		{
			m_pMemDC->TextOutW(GAME_WIDTH / 2, GAME_HEIGHT / 2, _T("��ͣ"));
		}

		DeleteObject(font);

		font = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		m_pMemDC->SelectObject(font);
		m_pMemDC->SetTextColor(RGB(0, 255, 0));//��ɫ
		m_pMemDC->TextOutW(10, 125, _T("HPֵ"));
		brush.CreateSolidBrush(RGB(0, 255, 0));
		m_pMemDC->SelectObject(&brush);

		int leftPos = m_pMe->GetPoint().x, topPos = m_pMe->GetPoint().y - 15, rightPos = leftPos + life*CMyPlane::PLANE_WIDTH / 10, buttomPos = topPos + 5;

		//����ս��������
		m_pMemDC->Rectangle(leftPos, topPos, rightPos, buttomPos);

		//���ƽ�����Ϣ

		//����ܽ��ȣ�Ϊһ��ɫ�ľ�����
		m_pMemDC->Rectangle(150, 0, 650, 10);
		brush.DeleteObject();
		//��ǰ���ȣ�Ϊһ�ƶ��ĺ�ɫ����
		if (score < passscore)
		{
			brush.CreateSolidBrush(RGB(255, 0, 0));
			m_pMemDC->SelectObject(&brush);
			m_pMemDC->Rectangle(150 + score * 400 / passscore, 0, 150 + score * 400 / passscore + 10, 10);
			brush.DeleteObject();
		}
		//����BOSSʱ����ɫ����λ�ò���
		else
		{
			brush.CreateSolidBrush(RGB(255, 0, 0));
			m_pMemDC->SelectObject(&brush);
			m_pMemDC->Rectangle(650, 0, 660, 10);
			brush.DeleteObject();
		}

		brush.CreateSolidBrush(RGB(0, 255, 0));
		m_pMemDC->SelectObject(&brush);
		leftPos = 80, rightPos = leftPos + 12 * hp / 10, topPos = 125, buttomPos = 140;
		m_pMemDC->Rectangle(leftPos, topPos, rightPos, buttomPos);
		m_pMemDC->SetTextColor(RGB(255, 255, 255));
		str.Format(_T("%d/%d"), hp, 100);
		m_pMemDC->TextOutW(123, 127, str);

		brush.DeleteObject();

		DeleteObject(font);

		//����BOSS��������
		if (bBoss&&boss!=NULL)
		{
			font = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
			m_pMemDC->SelectObject(font);
			m_pMemDC->SetTextColor(RGB(0, 255, 0));
			m_pMemDC->TextOutW(10, 155, _T("BOSS"));
			brush.CreateSolidBrush(RGB(255, 0, 0));//��ɫ
			m_pMemDC->SelectObject(&brush);
			leftPos = 80;
			rightPos = leftPos + 100 - 100 * (boss->BOSS_LIFE - bossLife) / (boss->BOSS_LIFE);
			topPos = 155, buttomPos = 170;
			m_pMemDC->Rectangle(leftPos, topPos, rightPos, buttomPos);
			str.Format(_T("%d/%d"), bossLife, boss->BOSS_LIFE);
			m_pMemDC->TextOutW(123, 155, str);
			brush.DeleteObject();
			DeleteObject(font);
		}
	}

	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
}

void CPlaneGameView::AI()
{
	//���Ʋ����л�
	static int nCreator = rand() % 5 + 10;
	//���Ʋ����л��ӵ�
	static int nCreatorball = rand() % 5 + 10;
	//���Ʋ���BOSS�ӵ�
	static int nCreatorboss = rand() % 5 + 10;

	//��������л�
	if (nCreator <= 0)
	{
		//nCreator = rand() % 50 - level * 10;;
		nCreator = 8 * (20 - level);
		if (level == 1)
		{
			CEnemy *enemy = new CEnemy(1);//1��ʾ��������
			enemy->setSpeed(rand() % 2+1);
			enemy->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy);
		}
		if (level == 2)
		{
			CEnemy *enemy1 = new CEnemy(1);
			enemy1->setSpeed(enemy1->ENEMY_SPEED + rand() % 2);
			enemy1->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy1);
			CEnemy *enemy2 = new CEnemy(-1);//-1��ʾ��������
			enemy2->setSpeed(enemy2->ENEMY_SPEED);
			enemy2->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy2);
		}
		if (level == 3)
		{
			CEnemy *enemy1 = new CEnemy(1);
			enemy1->setSpeed(enemy1->ENEMY_SPEED + level);
			enemy1->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy1);
			CEnemy *enemy2 = new CEnemy(2);//2��ʾ��������
			enemy2->setSpeed(rand()%2+1);
			enemy2->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy2);
		}
		if (level == 4)
		{
			CEnemy *enemy1 = new CEnemy(1);
			enemy1->setSpeed(enemy1->ENEMY_SPEED + rand()%level);
			enemy1->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy1);
			CEnemy *enemy2 = new CEnemy(-1);
			enemy2->setSpeed(enemy2->ENEMY_SPEED);
			enemy2->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy2);
			CEnemy *enemy3 = new CEnemy(3);
			enemy3->setSpeed(rand()%2+1);
			enemy3->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy3);//3��ʾ��������
		}
		if (level == 5)
		{
			CEnemy *enemy1 = new CEnemy(1);
			enemy1->setSpeed(enemy1->ENEMY_SPEED + rand() % level);
			enemy1->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy1);
			CEnemy *enemy2 = new CEnemy(-1);
			enemy2->setSpeed(enemy2->ENEMY_SPEED);
			enemy2->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy2);
			CEnemy *enemy3 = new CEnemy(3);
			enemy3->setSpeed(rand() % 2+1);
			enemy3->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy3);
			CEnemy *enemy4 = new CEnemy(2);
			enemy4->setSpeed(rand() % 2+1);
			enemy4->SetLife(3 + level);
			m_ObjList[enEnemy].AddTail(enemy4);
		}
		//m_ObjList[enEnemy].AddTail(new CEnemy(1));
	}
	nCreator--;

	if (m_pMe == NULL)
		return;

	//����ĸ���������ƶ�ս��
	for (int i = 0; i < 4; i++)
	{
		int nMeMotion = 0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(1);

		nMeMotion = GetKey(VK_DOWN);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(-1);
	}

	//����ս������
	if (GetKey(VK_SPACE) == 1 && !bPause)//�����˿ո��
	{
		if (m_pMe != NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			if (bUpdate)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 2, pt.y - 3, 1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + CMyPlane::PLANE_WIDTH + 3, pt.y + CMyPlane::PLANE_HEIGHT / 2, 2));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + CMyPlane::PLANE_WIDTH + 3, pt.y + CMyPlane::PLANE_HEIGHT / 2, 3));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 2, pt.y + CMyPlane::PLANE_HEIGHT + 3, 4));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x - 8, pt.y + CMyPlane::PLANE_HEIGHT / 2, 5));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x - 8, pt.y + CMyPlane::PLANE_HEIGHT / 2, 6));
			}
			else
			{
				if (level == 1)
				{
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 2, pt.y - 10, 1));
				}
				else if (level == 2)
				{
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 3 - 5, pt.y - 4, 1));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 3 * 2 + 5, pt.y - 4, 1));
				}
				else if (level >= 3)
				{
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 4 - 5, pt.y - 4, 1));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 4 * 2, pt.y - 4, 1));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 4 * 3 + 5, pt.y - 4, 1));

				}
			}
			//m_ObjList[enBomb].AddTail(new CBomb(pt.x+10,pt.y+10,1));
			//m_ObjList[enBomb].AddTail(new CBomb(pt.x+30,pt.y+10,1));
		}
	}

	//�����л��ӵ�
	if (nCreatorball <= 0)
	{
		nCreatorball = 2 * (10 - level);
		CPoint PlanePt = m_pMe->GetPoint();
		for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
			if (!pEnemy->Fired())
				continue;
			CPoint  ePt = pEnemy->GetPoint();

			BOOL by = FALSE;

			//�л���ս��ǰ��
			if (pEnemy->GetMontion() == 1 && ePt.y < PlanePt.y)
				by = TRUE;
			//�л���ս������
			if (pEnemy->GetMontion() == -1 && ePt.y > PlanePt.y)
				by = TRUE;

			if (by && ePt.x >= PlanePt.x && ePt.x < PlanePt.x + CMyPlane::PLANE_WIDTH)
			{
				m_ObjList[enBall].AddTail(new CBall(ePt.x + CEnemy::ENEMY_WIDTH/2, ePt.y + CEnemy::ENEMY_HEIGHT+5, pEnemy->GetMontion()));
			}
		}
	}
	nCreatorball--;

	//����BOSS
	if (m_pMe != NULL && score >= passscore && !bPause && !bBoss)
	{
		bBoss = TRUE;
		boss = new CBoss(1);
		boss->setSpeed(3 + level - 1);
		boss->SetLife(100 + (level - 1) * 50);
		bossLife = boss->GetLife();
		bossLoaded = TRUE;
	}

	//����BOSS�ӵ�
	if (nCreatorboss <= 0)
	{
		nCreatorboss = rand() % 5 + 20;
		if (m_pMe != NULL && !bPause && bBoss)
		{
			CPoint pt = CPoint(boss->GetPoint().x + CBoss::BOSS_WIDTH / 2, boss->GetPoint().y + CBoss::BOSS_HEIGHT / 2);

			/*CBall * ball1 = new CBall(boss->GetPoint().x + boss->BOSS_WIDTH / 2, boss->GetPoint().y + boss->BOSS_HEIGHT, 1,1);
			ball1->setSpeed(ball1->BALL_SPEED + (level - 1) * 2);
			m_ObjList[enBall].AddTail(ball1);
			CBall * ball2 = new CBall(boss->GetPoint().x + 5, boss->GetPoint().y + boss->BOSS_HEIGHT, 1,2);
			ball2->setSpeed(ball2->BALL_SPEED + (level - 1) * 2);
			m_ObjList[enBall].AddTail(ball2);
			CBall * ball3 = new CBall(boss->GetPoint().x + boss->BOSS_WIDTH - 5, boss->GetPoint().y + boss->BOSS_HEIGHT, 1,3);
			ball3->setSpeed(ball3->BALL_SPEED + (level - 1) * 2);
			m_ObjList[enBall].AddTail(ball3);
			CBall * ball4 = new CBall(boss->GetPoint().x + boss->BOSS_WIDTH / 2 + 85, boss->GetPoint().y + boss->BOSS_HEIGHT, 1,4);
			ball4->setSpeed(ball4->BALL_SPEED + (level - 1) * 2);
			m_ObjList[enBall].AddTail(ball4);
			CBall * ball5 = new CBall(boss->GetPoint().x + boss->BOSS_WIDTH / 2 - 85, boss->GetPoint().y + boss->BOSS_HEIGHT, 1,5);
			ball5->setSpeed(ball5->BALL_SPEED + (level - 1) * 2);
			m_ObjList[enBall].AddTail(ball5);*/

			//������(�������·���)����BOSS's Ball��Ч�����ĸ�������Ч
			CBall * ball1 = new CBall(pt.x,pt.y, 1, 1);
			ball1->setSpeed(ball1->BALL_SPEED*2);
			m_ObjList[enBossBall].AddTail(ball1);
			CBall * ball2 = new CBall(pt.x,pt.y, 1, 2);
			ball2->setSpeed(ball2->BALL_SPEED*2);
			m_ObjList[enBossBall].AddTail(ball2);
			CBall * ball3 = new CBall(pt.x,pt.y, 1, 3);
			ball3->setSpeed(ball3->BALL_SPEED*2);
			m_ObjList[enBossBall].AddTail(ball3);
			CBall * ball4 = new CBall(pt.x,pt.y, 1, 4);
			ball4->setSpeed(ball4->BALL_SPEED*2);
			m_ObjList[enBossBall].AddTail(ball4);
			CBall * ball5 = new CBall(pt.x,pt.y, 1, 5);
			ball5->setSpeed(ball5->BALL_SPEED*2);
			m_ObjList[enBossBall].AddTail(ball5);
			CBall * ball6 = new CBall(pt.x, pt.y, 1, 6);
			ball6->setSpeed(ball6->BALL_SPEED*2);
			m_ObjList[enBossBall].AddTail(ball6);
		}
	}
	nCreatorboss--;

	//�л��ӵ�ը��ս��
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			if (bWuDi == FALSE && bProtect == FALSE)
			{
				life--;
			}

			//ɾ���ӵ�
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;

			if (life == 0)
			{
				lifenum--;
				if (lifenum <= 0)
				{
					CMyPlane* temp = m_pMe;
					m_pMe = NULL;
					delete  temp;
					temp = NULL;
					Over();
					break;
				}
				else
					life = 10;
			}
			break;
		}
	}

	//ս������ը���л�
	if (m_pMe != NULL && !bPause)
	{
		POSITION mPos1 = NULL, mPos2 = NULL;
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				mRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);
					//ɾ������
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;
					pEnemy->ENEMY_LIFE -= 1;
					if (pEnemy->ENEMY_LIFE <= 0)
					{
						score++;//���ӵ÷�						
						m_ObjList[enEnemy].RemoveAt(ePos2);//ɾ���л�
						delete  pEnemy;
					}
					//m_ObjList[enEnemy].RemoveAt(ePos2);
					//delete pEnemy;
					break;
				}
			}
		}
	}

	//ս��������BOSS��ײ
	if (m_pMe != NULL && !bPause && bBoss == TRUE && boss!=NULL)
	{
		POSITION mPos1 = NULL, mPos2 = NULL;
		CRect bossRect = boss->GetRect();
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();
			CRect tempRect;
			if (tempRect.IntersectRect(&bRect, bossRect))
			{
				CExplosion *explosion = new CExplosion((pBomb->GetPoint().x + 30 / 2 - 66 / 2), (pBomb->GetPoint().y + 60 / 2 - 66 / 2));
				m_ObjList[enExplosion].AddTail(explosion);
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete  pBomb;
				pBomb = NULL;
				bossLife -= 1;
				if (bossLife <= 0)
				{
					bPass = TRUE;
					bBoss = FALSE;
					CExplosion *explosion1 = new CExplosion(boss->GetPoint().x, boss->GetPoint().y);
					m_ObjList[enExplosion].AddTail(explosion1);
					CExplosion *explosion2 = new CExplosion((boss->GetPoint().x + boss->BOSS_WIDTH), (boss->GetPoint().y + boss->BOSS_HEIGHT));
					m_ObjList[enExplosion].AddTail(explosion2);
					CExplosion *explosion3 = new CExplosion((boss->GetPoint().x + boss->BOSS_WIDTH), (boss->GetPoint().y));
					m_ObjList[enExplosion].AddTail(explosion3);
					CExplosion *explosion4 = new CExplosion((boss->GetPoint().x), (boss->GetPoint().y + boss->BOSS_HEIGHT));
					m_ObjList[enExplosion].AddTail(explosion4);
					CExplosion *explosion5 = new CExplosion((boss->GetPoint().x + boss->BOSS_WIDTH / 2 - 66 / 2), (boss->GetPoint().y + boss->BOSS_HEIGHT / 2 - 66 / 2));
					m_ObjList[enExplosion].AddTail(explosion5);
					delete boss;
					boss = NULL;
					delete  m_pMe;
					m_pMe = NULL;
					break;
				}
			}
		}
	}

	//ս���͵л�/BOSS��ײ
	if (m_pMe != NULL && !bPause)
	{
		CRect planerect = m_pMe->GetRect();

		//ս���͵л���ײ
		POSITION enemyPos, enemyTemp;
		for (enemyPos = m_ObjList[enEnemy].GetHeadPosition(); (enemyTemp = enemyPos) != NULL;)
		{
			enemy = (CEnemy *)m_ObjList[enEnemy].GetNext(enemyPos);
			CRect enemyRect = enemy->GetRect();
			CRect tempRect;
			if (tempRect.IntersectRect(&enemyRect, planerect))
			{
				CExplosion *explosion = new CExplosion(m_pMe->GetPoint().x + 120 / 2 - 66 / 2, m_pMe->GetPoint().y + 90 / 2 - 66 / 2);
				m_ObjList[enExplosion].AddTail(explosion);
				if (bWuDi == FALSE && bProtect == FALSE)
				{
					life--;
				}
				enemy->ENEMY_LIFE--;
				if (enemy->ENEMY_LIFE <= 0)
				{
					score++;
					m_ObjList[enEnemy].RemoveAt(enemyTemp);
					delete  enemy;
				}
				if (life == 0)
				{
					lifenum--;
					if (lifenum <= 0)
					{
						CMyPlane* temp = m_pMe;
						m_pMe = NULL;
						delete  temp;
						temp = NULL;
						Over();
						break;
					}
					else
					{
						life = 10;
					}
				}
			}
		}

		//ս����BOSS��ײ
		if (bBoss == TRUE &&m_pMe != NULL)
		{
			planerect = m_pMe->GetRect();
			CRect bossRect = boss->GetRect();
			CRect tempRect;
			if (tempRect.IntersectRect(&planerect, bossRect))
			{
				CExplosion *explosion = new CExplosion(m_pMe->GetPoint().x + 120 / 2 - 66 / 2, m_pMe->GetPoint().y + 90 / 2 - 66 / 2);
				m_ObjList[enExplosion].AddTail(explosion);
				if (bWuDi == FALSE && bProtect == FALSE)
				{
					life--;
				}
				bossLife--;
				if (bossLife <= 0)
				{
					bPass = TRUE;
					bBoss = FALSE;
					CExplosion *explosion1 = new CExplosion(boss->GetPoint().x, boss->GetPoint().y);
					m_ObjList[enExplosion].AddTail(explosion1);
					CExplosion *explosion2 = new CExplosion((boss->GetPoint().x + boss->BOSS_WIDTH), (boss->GetPoint().y + boss->BOSS_HEIGHT));
					m_ObjList[enExplosion].AddTail(explosion2);
					CExplosion *explosion3 = new CExplosion((boss->GetPoint().x + boss->BOSS_WIDTH), (boss->GetPoint().y));
					m_ObjList[enExplosion].AddTail(explosion3);
					CExplosion *explosion4 = new CExplosion((boss->GetPoint().x), (boss->GetPoint().y + boss->BOSS_HEIGHT));
					m_ObjList[enExplosion].AddTail(explosion4);
					CExplosion *explosion5 = new CExplosion((boss->GetPoint().x + boss->BOSS_WIDTH / 2 - 66 / 2), (boss->GetPoint().y + boss->BOSS_HEIGHT / 2 - 66 / 2));
					//explosion5->SetBossDie(TRUE);
					m_ObjList[enExplosion].AddTail(explosion5);
					delete boss;
					boss = NULL;
					delete  m_pMe;
					m_pMe = NULL;
				}
				if (life == 0)
				{
					lifenum--;
					if (lifenum <= 0)
					{
						CMyPlane* temp = m_pMe;
						m_pMe = NULL;
						delete  temp;
						temp = NULL;
						Over();//��Ϸ����
					}
					else
					{
						life = 10;
					}

				}
			}
		}
	}

	//�ӵ��͵�����ײ
	if (m_pMe != NULL && !bPause)
	{
		//����ս������λ�ã��л��ӵ�λ��
		POSITION bombPos, bombTemp, ballPos, ballTemp;
		for (bombPos = m_ObjList[enBomb].GetHeadPosition(); (bombTemp = bombPos) != NULL;)
		{
			bomb = (CBomb *)m_ObjList[enBomb].GetNext(bombPos);
			CRect bombRect = bomb->GetRect();
			for (ballPos = m_ObjList[enBall].GetHeadPosition(); (ballTemp = ballPos) != NULL;)
			{
				ball = (CBall *)m_ObjList[enBall].GetNext(ballPos);
				CRect ballRect = ball->GetRect();
				CRect tempRect;
				if (tempRect.IntersectRect(&bombRect, ballRect))
				{
					CExplosion *explosion = new CExplosion((ball->GetPoint().x + 15 / 2 - 66 / 2), (ball->GetPoint().y + 60 / 2 - 66 / 2));
					m_ObjList[enExplosion].AddTail(explosion);
					m_ObjList[enBomb].RemoveAt(bombTemp);
					delete  bomb;
					m_ObjList[enBall].RemoveAt(ballTemp);
					delete  ball;
					break;
				}
			}
		}
	}

	//ս���͵�����ײ
	if (m_pMe != NULL&& bPause == 0)
	{
		POSITION pos1, pos2;
		for (pos1 = m_ObjList[enTool].GetHeadPosition(); (pos2 = pos1) != NULL;)
		{
			tool = (CTool *)m_ObjList[enTool].GetNext(pos1);
			CRect toolrect = tool->GetRect();
			CRect planerect = m_pMe->GetRect();
			CRect temp;
			if (temp.IntersectRect(&toolrect, planerect))
			{
				life += 2;
				hp += 10;
				if (life > 10)
					life = 10;
				m_ObjList[enTool].RemoveAt(pos2);
				delete  tool;
				break;
				bTool = FALSE;
			}
		}
	}

	//��ǰ�ؿ�ͨ���Ժ�
	if (bPass == TRUE)
	{
		if (level == 5)//�ܹؿ���Ϊ5����ʱͨ��
		{
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			KillTimer(5);
			//m_pMe = new CMyPlane();
			bPause = TRUE;
			bStop = SUCCESS;//���ͨ�ض�ֹͣ
		}

		else if (level<5)//δ�ﵽ��5�أ�������һ��
		{
			m_pMe = new CMyPlane();//��������һ��ս��

			//�������
			if (m_ObjList[enEnemy].GetCount() > 0)
				m_ObjList[enEnemy].RemoveAll();
			if (m_ObjList[enBomb].GetCount() > 0)
				m_ObjList[enBomb].RemoveAll();
			if (m_ObjList[enBall].GetCount() > 0)
				m_ObjList[enBall].RemoveAll();
			if (m_ObjList[enExplosion].GetCount() > 0)
				m_ObjList[enExplosion].RemoveAll();
			if (m_ObjList[enTool].GetCount() > 0)
				m_ObjList[enTool].RemoveAll();

			//��ʼ������
			scoresum += score;
			score = 0;
			level += 1;
			bPause = FALSE;
			bTool = FALSE;
			bPass = FALSE;
			bBoss = FALSE;
			boss = NULL;
			bossLoaded = FALSE;
		}
	}
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{

	//-------------------------------------
	////�����豸DC
	//m_pDC = new CClientDC(this);

	////�����ڴ�DC
	//m_pMemDC = new CDC;
	//m_pMemDC->CreateCompatibleDC(m_pDC);

	////�����ڴ�λͼ
	//m_pMemBitmap = new CBitmap;
	//m_pMemBitmap->CreateCompatibleBitmap(m_pDC, GAME_WIDTH, GAME_HEIGHT);

	////��λͼѡ���ڴ�DC
	//m_pMemDC->SelectObject(m_pMemBitmap);
	//-------------------------------------


	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	UpdateFrame(m_pMemDC);

	//��δ�����ʼ��Ϸ����������
	if (bStart == FALSE)
	{
		return;
	}
	AI();
	if (nIDEvent == 2)
	{

	}

	//��������
	if (nIDEvent == 4)
	{
		if (index != GAME_HEIGHT)
			index += 1;
		else
			index = 0;
	}

	//ˢ��HPֵ
	if (nIDEvent == 5)
	{
		if (bStart)
		{
			hp += 1;
			if (hp > 100)
			{
				hp = 100;
			}
		}
	}

	//��������Чʱ��
	if (nIDEvent == 10)
	{
		bProtect = FALSE;
	}

	//���ɵ���
	if (m_pMe != NULL && !bPause)
	{
		if ((score == (30 + 10 * level) / 3)|| (score == (30 + 10 * level) / 3*2)|| (score == (30 + 10 * level)))//1/3��2/3��3/3�����ɵ���
		{
			if (bTool == FALSE)//ֻ�е������в����ڵ���ʱ�������µĵ���
			{
				bTool = TRUE;
				tool = new CTool(GAME_WIDTH, GAME_HEIGHT);
				m_ObjList[enTool].AddTail(tool);
				SetTimer(6, 10000, NULL);//���õ��ߴݻٶ�ʱ��
			}
		}
	}

	//���ߴݻ�
	if (nIDEvent == 6)
	{
		KillTimer(6);
		bTool = FALSE;
		POSITION pos1, pos2;
		for (pos1 = m_ObjList[enTool].GetHeadPosition(); (pos2 = pos1) != NULL;)
		{
			tool = (CTool *)m_ObjList[enTool].GetNext(pos1);
			m_ObjList[enTool].RemoveAt(pos2);
			delete  tool;
		}
	}

	//m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
	CView::OnTimer(nIDEvent);
}

void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->StopGame();
	// TODO: �ڴ˴������Ϣ����������
}


void CPlaneGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//if (m_pMe != NULL && m_pMe->Fired())
	if (m_pMe != NULL && !bPause)
	{
		CPoint pt = m_pMe->GetPoint();
		if (bUpdate)
		{
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 2, pt.y - 3, 1));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + CMyPlane::PLANE_WIDTH + 3, pt.y + CMyPlane::PLANE_HEIGHT / 2, 2));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + CMyPlane::PLANE_WIDTH + 3, pt.y + CMyPlane::PLANE_HEIGHT / 2, 3));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 2, pt.y + CMyPlane::PLANE_HEIGHT + 3, 4));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x - 8, pt.y + CMyPlane::PLANE_HEIGHT / 2, 5));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x - 8, pt.y + CMyPlane::PLANE_HEIGHT / 2, 6));
		}
		else
		{
			if (level == 1)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 2, pt.y - 10, 1));
			}
			else if (level == 2)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 3 - 5, pt.y - 4, 1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 3 * 2 + 5, pt.y - 4, 1));
			}
			else if (level >= 3)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 4 - 5, pt.y - 4, 1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 4 * 2, pt.y - 4, 1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + (CMyPlane::PLANE_WIDTH - CBomb::BOMB_WIDTH) / 4 * 3 + 5, pt.y - 4, 1));

			}
		}
		//m_ObjList[enBomb].AddTail(new CBomb(pt.x+10,pt.y+10,1));
		//m_ObjList[enBomb].AddTail(new CBomb(pt.x+30,pt.y+10,1));
	}
	CView::OnLButtonDown(nFlags, point);
}


void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//��ͣ
	if (GetKey('P') == 1 && m_pMe != NULL)
	{
		if (bPause == FALSE)
		{
			Sleep(500);
			bPause = TRUE;
		}
		else if (bPause == TRUE)
		{
			bPause = FALSE;
		}
	}

	//��Y���¿�ʼ
	else if (GetKey('Y') == 1 && bStop)
	{
		Restart();
	}

	//��N�˳���Ϸ
	else if (GetKey('N') == 1 && bStop)
	{
		exit(0);
	}

	//��G�Զ���ȡ����
	else if (GetKey('G') == 1 && !bPause && m_pMe != NULL)
	{
		if (bTool)
		{
			GetTool = TRUE;
		}
		if (!bTool)
		{
			GetTool = FALSE;
		}
	}

	//��S��������
	else if (GetKey('S') == 1 && !bPause && m_pMe != NULL)
	{
		if (bUpdate == FALSE)
		{
			bUpdate = TRUE;
		}
		else
		{
			bUpdate = FALSE;
		}
	}
	//��W�޵�ģʽ
	else if (GetKey('W') == 1 && !bPause && m_pMe != NULL)
	{
		if (bWuDi == TRUE)
			bWuDi = FALSE;
		else
			bWuDi = TRUE;
	}
	//��F����������
	else if (GetKey('F') == 1 && !bPause && m_pMe != NULL)
	{
		if (bProtect == FALSE)
		{
			if (hp >= 20)
			{
				hp -= 20;//ʹ��һ�η����ܣ�HP����20
				bProtect = TRUE;
				//��������Чʱ����5��
				SetTimer(10, 5000, NULL);
			}
		}
	}
	//��Q�˳���Ϸ
	else if (GetKey('Q') == 1 && !bPause && m_pMe != NULL)
	{
		exit(0);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CPlaneGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}


//void CPlaneGameView::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	if (m_pMe != NULL && !bPause)
//	{
//		m_pMe->SetPoint(point.x, point.y);
//	}
//	CView::OnMouseMove(nFlags, point);
//}

//��ʼ��Ϸ
void CPlaneGameView::Start()
{
	// TODO: �ڴ���������������
	if (bStart == FALSE)
	{
		bStart = TRUE;
		bPause = FALSE;
	}
}

//���¿�ʼ��Ϸ
void CPlaneGameView::Restart()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	bStop = FALSE;
	bPause = FALSE;
	bStart = TRUE;

	//������ս��
	m_pMe = new CMyPlane();

	//������ж���
	if (m_ObjList[enEnemy].GetCount() > 0)
		m_ObjList[enEnemy].RemoveAll();
	if (m_ObjList[enPlane].GetCount() > 0)
		m_ObjList[enPlane].RemoveAll();
	if (m_ObjList[enBomb].GetCount() > 0)
		m_ObjList[enBomb].RemoveAll();
	if (m_ObjList[enBall].GetCount() > 0)
		m_ObjList[enBall].RemoveAll();
	if (m_ObjList[enExplosion].GetCount() > 0)
		m_ObjList[enExplosion].RemoveAll();
	if (m_ObjList[enTool].GetCount() > 0)
		m_ObjList[enTool].RemoveAll();
	if (m_ObjList[enBossBall].GetCount() > 0)
		m_ObjList[enBossBall].RemoveAll();

	//���³�ʼ������
	life = 10;
	lifenum = 3;
	scoresum = 0;
	hp = 0;
	score = 0;
	level = 1;

	bTool = FALSE;
	bPass = FALSE;
	bBoss = FALSE;
	bWuDi = FALSE;
	bProtect = FALSE;
	bUpdate = FALSE;
	boss = NULL;
	bossLife = 100;
	bossLoaded = FALSE;

	//�������ö�ʱ��
	SetTimer(1, 30, NULL);
	//SetTimer(2, 400 - 30 * level, NULL);
	//SetTimer(3, 300 - 10 * level, NULL);
	SetTimer(5, 200, NULL);
}

//ս������ ����
void CPlaneGameView::Over()
{
	// TODO: �ڴ���������������
	//KillTimer(1);
	//KillTimer(2);
	//KillTimer(3);
	KillTimer(5);
	//KillTimer(4);
	KillTimer(6);
	scoresum += score;
	//��Ϊս������������
	bStop = DIE;
	bPause = TRUE;
}

//ս����������
void CPlaneGameView::PlaneSet()
{
	// TODO: �ڴ���������������
	CPlaneSet dlg;
	dlg.DoModal();
	speed = dlg.planespeed;
	life = dlg.planelife;
	lifenum = dlg.planelifenum;
	m_pMe->SetSpeed(speed);
}

//��Ϸ����
void CPlaneGameView::Help()
{
	// TODO: �ڴ���������������
	CHelp help;
	help.DoModal();
}