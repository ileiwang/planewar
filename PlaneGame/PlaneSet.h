#pragma once


// CPlaneSet 对话框

class CPlaneSet : public CDialogEx
{
	DECLARE_DYNAMIC(CPlaneSet)

public:
	CPlaneSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPlaneSet();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLANESET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int planespeed;
	int planelife;
	int planelifenum;
};
