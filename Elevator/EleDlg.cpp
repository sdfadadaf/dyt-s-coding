// EleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Elevator.h"
#include "EleDlg.h"
#include "afxdialogex.h"


// CEleDlg �Ի���

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


// CEleDlg ��Ϣ�������

	   

   


//void CEleDlg::OnEnChangeEdit2()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}

//void CEleDlg::OnEnChangeEdit3()
//
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}
