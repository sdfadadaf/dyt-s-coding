// ShowD.cpp : 实现文件
//

#include "stdafx.h"
#include "Elevator.h"
#include "ShowD.h"
#include "afxdialogex.h"


// CShowD 对话框

IMPLEMENT_DYNAMIC(CShowD, CDialogEx)

CShowD::CShowD(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowD::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	m_s1 = _T("");
	m_s2 = _T("");
	m_s4 = _T("");
}

CShowD::~CShowD()
{
}

void CShowD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_s1);
	DDV_MaxChars(pDX, m_s1, 20);
	DDX_Text(pDX, IDC_EDIT2, m_s2);
	DDV_MaxChars(pDX, m_s2, 20);
	DDX_Text(pDX, IDC_EDIT4, m_s4);
	DDV_MaxChars(pDX, m_s4, 20);
}


BEGIN_MESSAGE_MAP(CShowD, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &CShowD::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &CShowD::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CShowD::OnBnClickedOk)
END_MESSAGE_MAP()


// CShowD 消息处理程序


void CShowD::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CShowD::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CShowD::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
