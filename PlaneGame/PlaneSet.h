#pragma once


// CPlaneSet �Ի���

class CPlaneSet : public CDialogEx
{
	DECLARE_DYNAMIC(CPlaneSet)

public:
	CPlaneSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlaneSet();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLANESET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int planespeed;
	int planelife;
	int planelifenum;
};
