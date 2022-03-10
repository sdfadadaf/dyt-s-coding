
// ElevatorDlg.h : ͷ�ļ�
//
/******************************************************************/
#pragma once
#include "Logic.h"
#include "stdlib.h"
#include "time.h"
#include "EleDlg.h"
#include "Timer.h"
#include "SetDlg.h"
#include "ShowD.h"
// CElevatorDlg �Ի���
class CElevatorDlg : public CDialogEx
{
// ����
public:
	CElevatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ELEVATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CRect m_client;
	CRect m_dtPos[3];
	CRect m_arrowPosDown[10];
	CRect m_arrowPosUp[10];
	CImage m_bg;
	CImage m_dt;
	CImage m_door[4];
	CImage m_person[10];
	CImage m_arrow[4];
	CDC m_BufferDC;
	CBitmap m_BufferBitmap;
	CLogic logic;
	int m_Number;                 //���ɹ�������
	CString str[15];                  //�༭���ڵ���ʾ����
	CString Ctime;                  //��ʾʱ��
	CString str2;
	CEdit m_Edit1;
	CEdit m_Edit2;
	int i;
	long t[4];
	char h[20];
	char m[20];
	char r[20];
	char s[20];
	CString str1;
	CString stri[3];
	bool IsStart;
	CSetDlg set;
	CShowD show;
	int LS;
	int PS;
	float T[3];//��ʱ����
	int line;
	
public:
	void Load();
	void Read();
	void Process();               //������Ķ������д���
	void Generate();              //�����µ�����
	void Run();                   //�˺͵�������
	void Show(int);                  //��ʾ��Ϣ
	void Show1();                 //��ʾ
	void Show_time();               //��ʾʱ��
	//void TimeCol();                //ʱ��ͳ��

	
// ʵ��
protected:
	HICON m_hIcon;
	 CEleDlg Dlg2;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
