#pragma once
//////////////////////////////////////////////////////////////////////////

// CSetDlg �Ի���

class CSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	CSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_L;
	int m_P;
};
