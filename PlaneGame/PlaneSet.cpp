// PlaneSet.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "PlaneSet.h"
#include "afxdialogex.h"


// CPlaneSet 对话框

IMPLEMENT_DYNAMIC(CPlaneSet, CDialogEx)

CPlaneSet::CPlaneSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PLANESET, pParent)
	, planespeed(6)
	, planelife(10)
	, planelifenum(3)
{

}

CPlaneSet::~CPlaneSet()
{
}

void CPlaneSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, planespeed);
	DDX_Text(pDX, IDC_EDIT2, planelife);
	DDX_Text(pDX, IDC_EDIT3, planelifenum);
}


BEGIN_MESSAGE_MAP(CPlaneSet, CDialogEx)
END_MESSAGE_MAP()


// CPlaneSet 消息处理程序
