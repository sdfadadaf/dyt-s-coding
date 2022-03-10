
// ElevatorDlg.h : 头文件
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
// CElevatorDlg 对话框
class CElevatorDlg : public CDialogEx
{
// 构造
public:
	CElevatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ELEVATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

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
	int m_Number;                 //生成过的人数
	CString str[15];                  //编辑框内的显示内容
	CString Ctime;                  //显示时间
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
	float T[3];//计时次数
	int line;
	
public:
	void Load();
	void Read();
	void Process();               //对人物的动作进行处理
	void Generate();              //生成新的人物
	void Run();                   //人和电梯运行
	void Show(int);                  //显示信息
	void Show1();                 //显示
	void Show_time();               //显示时间
	//void TimeCol();                //时间统计

	
// 实现
protected:
	HICON m_hIcon;
	 CEleDlg Dlg2;

	// 生成的消息映射函数
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
