// ShowD.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Elevator.h"
#include "ShowD.h"
#include "afxdialogex.h"


// CShowD �Ի���

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


// CShowD ��Ϣ�������


void CShowD::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CShowD::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CShowD::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
