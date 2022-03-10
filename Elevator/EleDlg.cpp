// EleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Elevator.h"
#include "EleDlg.h"
#include "afxdialogex.h"


// CEleDlg 对话框

IMPLEMENT_DYNAMIC(CEleDlg, CDialogEx)

CEleDlg::CEleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEleDlg::IDD, pParent)
{

}

CEleDlg::~CEleDlg()
{
}

void CEleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
}


BEGIN_MESSAGE_MAP(CEleDlg, CDialogEx)
//	ON_EN_CHANGE(IDC_EDIT2, &CEleDlg::OnEnChangeEdit2)
//	ON_EN_CHANGE(IDC_EDIT3, &CEleDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CEleDlg 消息处理程序

	   

   


//void CEleDlg::OnEnChangeEdit2()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}

//void CEleDlg::OnEnChangeEdit3()
//
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}
