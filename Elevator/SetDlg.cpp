// SetDlg.cpp : ʵ���ļ�
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Elevator.h"
#include "SetDlg.h"
#include "afxdialogex.h"


// CSetDlg �Ի���

IMPLEMENT_DYNAMIC(CSetDlg, CDialogEx)

CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetDlg::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	m_L = 1;
	m_P = 2;
}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_L);
	DDV_MinMaxInt(pDX, m_L, 1, 20);
	DDX_Text(pDX, IDC_EDIT2, m_P);
	DDV_MinMaxInt(pDX, m_P, 1, 20);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialogEx)
END_MESSAGE_MAP()


// CSetDlg ��Ϣ�������
