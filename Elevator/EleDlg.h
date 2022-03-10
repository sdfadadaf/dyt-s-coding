#pragma once
#include "afxwin.h"


// CEleDlg 对话框

class CEleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEleDlg)

public:
	CEleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEleDlg();
	//void UpDateWindow(void);//调整窗口大小
// 对话框数据
	enum { IDD = IDD_ELE_DIALOG };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit2();
	CEdit m_Edit2;
//	afx_msg void OnEnChangeEdit3();
};
