#pragma once


// CShowD �Ի���

class CShowD : public CDialogEx
{
	DECLARE_DYNAMIC(CShowD)

public:
	CShowD(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowD();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	CString m_s1;
	CString m_s2;
	CString m_s4;
};
