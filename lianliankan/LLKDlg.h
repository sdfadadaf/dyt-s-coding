
// LLKDlg.h : ͷ�ļ�
//

#pragma once
#include "Global.h"
#include "GameLogic.h"



// CLLKDlg �Ի���
class CLLKDlg : public CDialogEx
{
// ����
public:
	CLLKDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
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

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	void UpdateWindow(void);                    //�������ڴ�С
	void InitElement();                         //��ʼ��ͼƬԪ��
	void InitBackground();                      //��ʼ�����ھ���
   
	void UpdateMap();                           //���µ�ͼ
	void DrawTipFrame(int x, int y);            //������ʾ��
	void DrawTipLine(Vertex nVexPath[4], int nVexNum);
	afx_msg void OnClickedBtnStart();
	
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnComplete();
};
