
// LLKDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CLLKDlg 对话框




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


// CLLKDlg 消息处理程序

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	UpdateWindow();
	InitElement();
	InitBackground();
	PlaySound( (LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE   
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

//  如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLLKDlg::OnPaint()
{
	if (IsIconic())        //判断窗口是否最小化
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{   
	    
		CPaintDC dc(this);    //视屏DC
		dc.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	 }    
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLLKDlg::UpdateWindow(void)
{
	    //调整窗口的大小
	CRect rtWin;
	GetWindowRect(rtWin);    //获得窗口的大小
	CRect rtClient;
	GetClientRect(rtClient);      //获得客户区大小

	    //标题栏和外边框的大小
	int nSpanWidth=rtWin.Width()-rtClient.Width();
	int nSpanHeight=rtWin.Height()-rtClient.Height();

	    //设置窗口的大小
	MoveWindow(0, 0, 1280+nSpanWidth, 720+nSpanHeight);
}


void CLLKDlg::InitElement()
{   
	
	//加载位图资源
    CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP0);
    //创建与视频DC兼容的内存DC
    CClientDC dc(this);
    m_dcElement.CreateCompatibleDC(&dc);
    //将位图资源选入DC
    m_dcElement.SelectObject(bmp);
}

void CLLKDlg::InitBackground()
{
    //获得当前对话框的视频DC
    CClientDC   dc(this);         
    //创建与视频DC兼容的空的位图
	CBitmap  bmp, bmp1, bmp2;
	bmp.CreateCompatibleBitmap(&dc, WIDTH, HEIGHT);
    //创建与视频DC兼容的内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(&bmp);
	//加载图片资源
	bmp1.LoadBitmap(IDB_BITMAP00);
	bmp2.LoadBitmap(IDB_BITMAP2);
    //创建与视频DC兼容的背景DC
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(&bmp1); 
	m_dcBG2.CreateCompatibleDC(&dc);
    m_dcBG2.SelectObject(&bmp2);
	//将背景图片拷贝到内存DC中
    m_dcMem.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcBG, 0, 0, SRCCOPY);
	
	

}



void CLLKDlg::UpdateMap()
{
    //将背景图片拷贝到内存DC中
    m_dcMem.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcBG, 0, 0, SRCCOPY);      
	//绘制游戏地图
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
	if(!m_IsPlaying)             //判断游戏是否还在进行
	{
	    //return CDialogEx::OnLButtonUp(nFlags, point);
		m_GameLogic.Initmap();
		UpdateMap();
		InvalidateRect(m_rtGame);
		m_IsFirstPoint = TRUE;
		m_IsPlaying = TRUE;
	}
	// 判断用户点击的坐标是否在游戏区域内
	if(point.x < m_rtGame.left||point.x > m_rtGame.right||point.y < m_rtGame.top||point.y > m_rtGame.bottom)
	{	
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//转换成图片元素的坐标
	int nRow = point.y/PIC_HEIGHT;
	int nCol = point.x/PIC_WIDTH;
	//判断点是否在空白区域
	if(m_GameLogic.GetElement(nRow, nCol) == BLANK)
	{
	    return CDialogEx::OnLButtonUp(nFlags, point);
	}

	DrawTipFrame(nRow, nCol);

	//判断是否连通
	if(m_IsFirstPoint)
	{
	    //设置第一张图片的信息
		m_GameLogic.SetFirstVex(nRow, nCol);
	}
	else
	{
	    //设置第二张图片的信息
		m_GameLogic.SetSecondVex(nRow, nCol);
		Vertex aPath[4];
		int nNum = 0;
		//连子判断
		if(m_GameLogic.Link(aPath, nNum))
		{
			DrawTipLine(aPath, nNum);
			UpdateMap(); 
			if(m_GameLogic.IsWin())
			{
			    MessageBox(_T("游戏获胜！"));
				m_IsPlaying = FALSE;
				PlaySound(NULL,NULL,SND_ASYNC);//停止播放 
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
	//创建笔刷
	CBrush brush(RGB(233,43,43));
	CRect rtTipFrame;
	//设置矩形坐标
	rtTipFrame.left=MAP_LEFT + (y-1)*PIC_WIDTH;
	rtTipFrame.top=MAP_TOP + (x-1)*PIC_HEIGHT;
	rtTipFrame.right=rtTipFrame.left+PIC_WIDTH;
	rtTipFrame.bottom=rtTipFrame.top+PIC_HEIGHT;
	//绘制矩形框
	dc.FrameRect(rtTipFrame,&brush);
}

void CLLKDlg::DrawTipLine(Vertex nVexPath[4], int nVexNum)
{
    CClientDC dc(this);
	//创建画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//选入画笔
	CPen *pOldPen = dc.SelectObject(&penLine);
	//计算起点坐标
	int nStartX = MAP_LEFT + (nVexPath[0].mY-1) * PIC_WIDTH + PIC_WIDTH/2;
	int nStartY = MAP_TOP + (nVexPath[0].mX-1) * PIC_HEIGHT + PIC_HEIGHT/2;
	//绘制提示线
	dc.MoveTo(nStartX, nStartY);
    //计算终点坐标
	for(int i = 1; i < nVexNum; i++)   //通过for循环一次绘制各关键点之间的连线
	{
        int nEndX = MAP_LEFT + (nVexPath[i].mY-1) * PIC_WIDTH + PIC_WIDTH/2;
		int nEndY = MAP_TOP + (nVexPath[i].mX-1) * PIC_HEIGHT + PIC_HEIGHT/2;
		dc.LineTo(nEndX, nEndY);
	}
	//恢复旧的画笔
	dc.SelectObject(pOldPen);
	//释放新的画笔对象
	DeleteObject(&penLine);
}



void CLLKDlg::OnBnClickedBtnComplete()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("游戏获胜！"));
	m_IsPlaying = FALSE;
    PlaySound(NULL,NULL,SND_ASYNC);//停止播放 
	m_dcMem.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcBG2, 0, 0, SRCCOPY);   
	GetDlgItem(IDC_BTN_START)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_COMPLETE)->ShowWindow(SW_HIDE);
	Invalidate();
}
