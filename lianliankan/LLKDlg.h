
// LLKDlg.h : 头文件
//

#pragma once
#include "Global.h"
#include "GameLogic.h"



// CLLKDlg 对话框
class CLLKDlg : public CDialogEx
{
// 构造
public:
	CLLKDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CRect m_rtGame;
	CRect m_rtGame2;
	CGameLogic m_GameLogic;
	CDC m_dcMem;
	CDC m_dcBG;
	CDC m_dcBG2;
	CDC m_dcElement; 
	BOOL m_IsFirstPoint;
	BOOL m_IsPlaying;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	void UpdateWindow(void);                    //调整窗口大小
	void InitElement();                         //初始化图片元素
	void InitBackground();                      //初始化窗口景背
   
	void UpdateMap();                           //更新地图
	void DrawTipFrame(int x, int y);            //绘制提示框
	void DrawTipLine(Vertex nVexPath[4], int nVexNum);
	afx_msg void OnClickedBtnStart();
	
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnComplete();
};
