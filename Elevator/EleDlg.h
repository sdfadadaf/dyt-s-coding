#pragma once
#include "afxwin.h"


// CEleDlg �Ի���

class CEleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEleDlg)

public:
	CEleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEleDlg();
	//void UpDateWindow(void);//�������ڴ�С
// �Ի�������
	enum { IDD = IDD_ELE_DIALOG };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit2();
	CEdit m_Edit2;
//	afx_msg void OnEnChangeEdit3();
};
