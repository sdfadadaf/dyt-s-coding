
// LLKDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"

#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKDlg �Ի���




CLLKDlg::CLLKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLLKDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_rtGame.left=MAP_LEFT;
	m_rtGame.top=MAP_TOP;
	m_rtGame.right=m_rtGame.left+16*PIC_WIDTH;
	m_rtGame.bottom=m_rtGame.top+10*PIC_HEIGHT;
	m_rtGame2.left=0;
	m_rtGame2.top=0;
	m_rtGame2.right=0+18*PIC_WIDTH;
	m_rtGame2.bottom=0+12*PIC_HEIGHT;
	m_IsPlaying = FALSE;
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CLLKDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_COMPLETE, &CLLKDlg::OnBnClickedBtnComplete)
    END_MESSAGE_MAP()


// CLLKDlg ��Ϣ�������

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	UpdateWindow();
	InitElement();
	InitBackground();
	PlaySound( (LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE   
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

//  �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLLKDlg::OnPaint()
{
	if (IsIconic())        //�жϴ����Ƿ���С��
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{   
	    
		CPaintDC dc(this);    //����DC
		dc.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	 }    
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLLKDlg::UpdateWindow(void)
{
	    //�������ڵĴ�С
	CRect rtWin;
	GetWindowRect(rtWin);    //��ô��ڵĴ�С
	CRect rtClient;
	GetClientRect(rtClient);      //��ÿͻ�����С

	    //����������߿�Ĵ�С
	int nSpanWidth=rtWin.Width()-rtClient.Width();
	int nSpanHeight=rtWin.Height()-rtClient.Height();

	    //���ô��ڵĴ�С
	MoveWindow(0, 0, 1280+nSpanWidth, 720+nSpanHeight);
}


void CLLKDlg::InitElement()
{   
	
	//����λͼ��Դ
    CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP0);
    //��������ƵDC���ݵ��ڴ�DC
    CClientDC dc(this);
    m_dcElement.CreateCompatibleDC(&dc);
    //��λͼ��Դѡ��DC
    m_dcElement.SelectObject(bmp);
}

void CLLKDlg::InitBackground()
{
    //��õ�ǰ�Ի������ƵDC
    CClientDC   dc(this);         
    //��������ƵDC���ݵĿյ�λͼ
	CBitmap  bmp, bmp1, bmp2;
	bmp.CreateCompatibleBitmap(&dc, WIDTH, HEIGHT);
    //��������ƵDC���ݵ��ڴ�DC
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(&bmp);
	//����ͼƬ��Դ
	bmp1.LoadBitmap(IDB_BITMAP00);
	bmp2.LoadBitmap(IDB_BITMAP2);
    //��������ƵDC���ݵı���DC
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(&bmp1); 
	m_dcBG2.CreateCompatibleDC(&dc);
    m_dcBG2.SelectObject(&bmp2);
	//������ͼƬ�������ڴ�DC��
    m_dcMem.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcBG, 0, 0, SRCCOPY);
	
	

}



void CLLKDlg::UpdateMap()
{
    //������ͼƬ�������ڴ�DC��
    m_dcMem.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcBG, 0, 0, SRCCOPY);      
	//������Ϸ��ͼ
	for(int i=0; i<MAX_ROW + 2; i++)
		for(int j=0; j<MAX_COL + 2; j++)
		{
		    int nElementX=MAP_LEFT+(j - 1)*PIC_WIDTH;
			int nElementY=MAP_TOP+(i - 1)*PIC_HEIGHT;
			int nNum=m_GameLogic.GetElement(i,j);
			int nSourceX=0;
			int nSourceY=nNum*PIC_HEIGHT; 
			m_dcMem.TransparentBlt(nElementX, nElementY, PIC_WIDTH, PIC_HEIGHT, &m_dcElement, nSourceX, nSourceY, PIC_WIDTH, PIC_HEIGHT, RGB(255,255,255));
		}
}


void CLLKDlg::OnClickedBtnStart()
{
	m_GameLogic.Initmap();
	UpdateMap();
	InvalidateRect(m_rtGame);
	m_IsFirstPoint=TRUE;
	m_IsPlaying = TRUE;
}


void CLLKDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(!m_IsPlaying)             //�ж���Ϸ�Ƿ��ڽ���
	{
	    //return CDialogEx::OnLButtonUp(nFlags, point);
		m_GameLogic.Initmap();
		UpdateMap();
		InvalidateRect(m_rtGame);
		m_IsFirstPoint = TRUE;
		m_IsPlaying = TRUE;
	}
	// �ж��û�����������Ƿ�����Ϸ������
	if(point.x < m_rtGame.left||point.x > m_rtGame.right||point.y < m_rtGame.top||point.y > m_rtGame.bottom)
	{	
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//ת����ͼƬԪ�ص�����
	int nRow = point.y/PIC_HEIGHT;
	int nCol = point.x/PIC_WIDTH;
	//�жϵ��Ƿ��ڿհ�����
	if(m_GameLogic.GetElement(nRow, nCol) == BLANK)
	{
	    return CDialogEx::OnLButtonUp(nFlags, point);
	}

	DrawTipFrame(nRow, nCol);

	//�ж��Ƿ���ͨ
	if(m_IsFirstPoint)
	{
	    //���õ�һ��ͼƬ����Ϣ
		m_GameLogic.SetFirstVex(nRow, nCol);
	}
	else
	{
	    //���õڶ���ͼƬ����Ϣ
		m_GameLogic.SetSecondVex(nRow, nCol);
		Vertex aPath[4];
		int nNum = 0;
		//�����ж�
		if(m_GameLogic.Link(aPath, nNum))
		{
			DrawTipLine(aPath, nNum);
			UpdateMap(); 
			if(m_GameLogic.IsWin())
			{
			    MessageBox(_T("��Ϸ��ʤ��"));
				m_IsPlaying = FALSE;
				PlaySound(NULL,NULL,SND_ASYNC);//ֹͣ���� 
				m_dcMem.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcBG2, 0, 0, SRCCOPY);   
	            GetDlgItem(IDC_BTN_START)->ShowWindow(SW_HIDE);
	            GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(SW_HIDE);
	            GetDlgItem(IDC_BTN_COMPLETE)->ShowWindow(SW_HIDE);
	            Invalidate();
			}
			Sleep(500);
		    
		}
		
		InvalidateRect(m_rtGame2);
	}
	m_IsFirstPoint = !m_IsFirstPoint;

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CLLKDlg::DrawTipFrame(int x, int y)
{
    CClientDC dc(this);
	//������ˢ
	CBrush brush(RGB(233,43,43));
	CRect rtTipFrame;
	//���þ�������
	rtTipFrame.left=MAP_LEFT + (y-1)*PIC_WIDTH;
	rtTipFrame.top=MAP_TOP + (x-1)*PIC_HEIGHT;
	rtTipFrame.right=rtTipFrame.left+PIC_WIDTH;
	rtTipFrame.bottom=rtTipFrame.top+PIC_HEIGHT;
	//���ƾ��ο�
	dc.FrameRect(rtTipFrame,&brush);
}

void CLLKDlg::DrawTipLine(Vertex nVexPath[4], int nVexNum)
{
    CClientDC dc(this);
	//��������
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//ѡ�뻭��
	CPen *pOldPen = dc.SelectObject(&penLine);
	//�����������
	int nStartX = MAP_LEFT + (nVexPath[0].mY-1) * PIC_WIDTH + PIC_WIDTH/2;
	int nStartY = MAP_TOP + (nVexPath[0].mX-1) * PIC_HEIGHT + PIC_HEIGHT/2;
	//������ʾ��
	dc.MoveTo(nStartX, nStartY);
    //�����յ�����
	for(int i = 1; i < nVexNum; i++)   //ͨ��forѭ��һ�λ��Ƹ��ؼ���֮�������
	{
        int nEndX = MAP_LEFT + (nVexPath[i].mY-1) * PIC_WIDTH + PIC_WIDTH/2;
		int nEndY = MAP_TOP + (nVexPath[i].mX-1) * PIC_HEIGHT + PIC_HEIGHT/2;
		dc.LineTo(nEndX, nEndY);
	}
	//�ָ��ɵĻ���
	dc.SelectObject(pOldPen);
	//�ͷ��µĻ��ʶ���
	DeleteObject(&penLine);
}



void CLLKDlg::OnBnClickedBtnComplete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("��Ϸ��ʤ��"));
	m_IsPlaying = FALSE;
    PlaySound(NULL,NULL,SND_ASYNC);//ֹͣ���� 
	m_dcMem.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcBG2, 0, 0, SRCCOPY);   
	GetDlgItem(IDC_BTN_START)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_COMPLETE)->ShowWindow(SW_HIDE);
	Invalidate();
}
