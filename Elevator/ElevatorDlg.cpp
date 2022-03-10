
// ElevatorDlg.cpp : ʵ���ļ�
//
/*********************************************************************/
#include "stdafx.h"
#include "Elevator.h"
#include "ElevatorDlg.h"
#include "afxdialogex.h"
#include  "string.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//��ʱ��
#define TIME_PAINT 5000
#define TIME_PERSONMOVE 5001
#define TIME_GENERATE 5002

//��png��ͼ͸��
void TransparentPNG(CImage *png)
{
	for(int i = 0; i <png->GetWidth(); i++)
	{
		for(int j = 0; j <png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(png->GetPixelAddress(i , j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}

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
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// CElevatorDlg �Ի���




CElevatorDlg::CElevatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CElevatorDlg::IDD, pParent)
{
	IsStart=false;
	LS=1;
	PS=2;
	T[0]=1;T[1]=1;T[2]=1;
	{
			CFile file(_T("d:\\ElevatorInit.txt"),CFile::modeCreate|CFile::modeWrite);
			file.Write((char*)this,sizeof(CElevatorDlg));
			file.Close();

	}
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CElevatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CElevatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CElevatorDlg ��Ϣ�������

BOOL CElevatorDlg::OnInitDialog()
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

	CWnd::SetWindowPos(NULL,0,0,900,738,SWP_NOZORDER|SWP_NOMOVE);
	

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	//

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	set.DoModal();
	LS=set.m_L;
	PS=set.m_P;
	MessageBoxA(NULL,"��P����ʼ",MB_OK);
	line = 20;
	//��һ�Ի���ĳ�ʼ��
	Dlg2.Create(IDD_ELE_DIALOG,this );
	Dlg2.ShowWindow(SW_SHOW); 
	Dlg2.MoveWindow(763, 0, 200, 720);
	//����͸����
	Dlg2.ModifyStyleEx(0, WS_EX_LAYERED);
	Dlg2.SetLayeredWindowAttributes(RGB(0,0,0),150,LWA_ALPHA);
	//////////////////////////////////////////////
	
	//show.MoveWindow(0, 0, 150, 400);
	//����͸����
	//show.ModifyStyleEx(0, WS_EX_LAYERED);
	//show.SetLayeredWindowAttributes(RGB(0,0,0),150,LWA_ALPHA);
	//������������е�����
	srand(time(NULL));
	//������ʼ��
	m_Number = 0;
	i=0;
	
	for(int k=0;k<15;k++)
	    {str[k]="";}


	  for(int k=0;k<4;k++)
	{
		Ctime+="\r\n";
		Ctime+="00:00:00";
		Ctime+="\r\n";
     }
  Dlg2.SetDlgItemText(IDC_EDIT2, Ctime); 
  //��ʱ����ʼ��ʱ
	//���ر�����ͼƬ
	m_bg.Load("image\\BG.png");
	m_dt.Load("image\\dianti.png");
	m_person[0].Load("image\\character1.png");
	m_person[1].Load("image\\character2.png");
	m_person[2].Load("image\\character3.png");
	m_person[3].Load("image\\character4.png");
	m_person[4].Load("image\\character5.png");
	m_person[5].Load("image\\character6.png");
	m_person[6].Load("image\\character7.png");
	m_person[7].Load("image\\character8.png");
	m_person[8].Load("image\\character9.png");
	m_person[9].Load("image\\character10.png");
	m_door[0].Load("image\\diantimen1.png");
	m_door[1].Load("image\\diantimen2.png");
	m_door[2].Load("image\\diantimen3.png");
	m_door[3].Load("image\\diantimen4.png");
	m_arrow[0].Load("image\\arrow up0.png");
	m_arrow[1].Load("image\\arrow down0.png");
	m_arrow[2].Load("image\\arrow up1.png");
	m_arrow[3].Load("image\\arrow down1.png");
	TransparentPNG(&m_dt);
	for(int x = 0; x < 10; x++)
	{
		TransparentPNG(&m_person[x]);
	}
	for(int y = 0; y < 4; y++)
	{
	    TransparentPNG(&m_arrow[y]);
	}
	for(int a = 0; a < 4; a++)
	{
	    TransparentPNG(&m_door[a]);
	}
	
	for(int g = 0; g < 10; g++)
	{
	    m_arrowPosDown[g].bottom = 690 - FloorHeight*g;
		m_arrowPosDown[g].top = m_arrowPosDown[g].bottom - 10;
		m_arrowPosDown[g].left = WaitPoint - 30;
		m_arrowPosDown[g].right = m_arrowPosDown[g].left + 10;
		m_arrowPosUp[g].bottom = 675 - FloorHeight*g;
		m_arrowPosUp[g].top = m_arrowPosUp[g].bottom - 10;
		m_arrowPosUp[g].left = WaitPoint - 30;
		m_arrowPosUp[g].right = m_arrowPosUp[g].left + 10;
	}
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CElevatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CElevatorDlg::OnPaint()
{
	if (IsIconic())
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
		CDC *cDC = this -> GetDC();
		GetClientRect(&m_client);
		//��������DC
		m_BufferDC.CreateCompatibleDC(NULL);
		m_BufferBitmap.CreateCompatibleBitmap(cDC, m_client.Width(), m_client.Height());
		m_BufferDC.SelectObject(&m_BufferBitmap);
		//---------------��ʼ����----------------
		m_bg.Draw(m_BufferDC, m_client);
		//�����ݻ��뻺��DC��
		for(int i = 0; i < 3; i++)
		{
			m_dtPos[i].bottom = 735 - logic.lift[i].Height;
			m_dtPos[i].top = m_dtPos[i].bottom - L_HEIGHT;
			m_dtPos[i].left = L_DISTANCE*i + 25;
			m_dtPos[i].right = m_dtPos[i].left + L_WIDTH;
			m_dt.Draw(m_BufferDC, m_dtPos[i]);
		}
		//���Ƶ���ǰ�ļ�ͷָʾ��
		for(int d = 0; d < 10; d++)
		{
			if(logic.lift[0].instruction[d][0] || logic.lift[1].instruction[d][0] || logic.lift[2].instruction[d][0])
			{
			    m_arrow[2].Draw(m_BufferDC, m_arrowPosUp[d]); 
			}
			else
			{
			    m_arrow[0].Draw(m_BufferDC, m_arrowPosUp[d]); 
			}
			if(logic.lift[0].instruction[d][1] || logic.lift[1].instruction[d][1] || logic.lift[2].instruction[d][1])
			{
			    m_arrow[3].Draw(m_BufferDC, m_arrowPosDown[d]); 
			}
			else
			{
			    m_arrow[1].Draw(m_BufferDC, m_arrowPosDown[d]); 
			}
		}
		//��������뻺��DC��
		for(int z = 0; z < P_Number; z++)
		{
			if(logic.person[z].IsAlive == YES)
			{
				logic.person[z].y = 722 - logic.person[z].Height - P_HEIGHT;
				m_person[logic.person[z].character].Draw(m_BufferDC, logic.person[z].x, logic.person[z].y, P_WIDTH, P_HEIGHT, logic.person[z].step*32, logic.person[z].towards*48, 32, 48);
			}
		}
		//�������Ż��뻺��DC
		for(int j = 0; j < 3; j++)
		{
			if(logic.lift [j].door )
			{
				m_door[logic.lift [j].door - 1].Draw(m_BufferDC, m_dtPos[j]);
			}
		}
		char tap[]="��P����ʼ/��ͣ����L���浵����R������,��S������,��Q���鿴����C�����ã�";
		m_BufferDC.TextOutA(10,40,tap);
		//����DC����������DC
		cDC -> BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_BufferDC, 0, 0, SRCCOPY);
		
		//---------------���ƽ���----------------
		ValidateRect(&m_client);
		m_BufferDC.DeleteDC();
		m_BufferBitmap.DeleteObject();
		ReleaseDC(cDC);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CElevatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CElevatorDlg::Process()
{
	for(int z = 0; z < P_Number; z++)
	{
	    if(logic.person[z].IsAlive == YES)
	{
	    switch(logic.person[z].status)
	    {
	        case P_Left: 
		    case P_Right:
			case P_Back:
		    case P_GetIn: logic.person[z].step++;
			              if(logic.person[z].step == 4) 
					      {
						      logic.person[z].step = 0;
					      }
					      break;
		    case P_Take:
		    case P_Wait: logic.person[z].step = 0; 
	    }
	}
	}
}


void CElevatorDlg::Generate()
{
	for(int z = 0; z < P_Number; z++)
	{
	    if(logic.person[z].IsAlive == NO)
		{
			logic.person[z].Start_Floor = rand()%10+1;
			do{
				logic.person[z].End_Floor = rand()%10+1;
			}while(logic.person[z].Start_Floor == logic.person[z].End_Floor);
			if(logic.person[z].End_Floor > logic.person[z].Start_Floor)
			{
				logic.person[z].direct = UP;
			}
			else
			{
				logic.person[z].direct = DOWN;
			}
			logic.person[z].character = rand()%10;
			logic.person[z].IsAlive = YES;
			logic.person[z].x = StartPoint;
			logic.person[z].Height = (logic.person[z].Start_Floor - 1)*FloorHeight;
			logic.person[z].status = P_Left;
			logic.person[z].towards = _LEFT;
			m_Number++;
			logic.person[z].p_number = m_Number;
			
			logic.person_number = m_Number;
			logic.floor_number = logic.person[z].Start_Floor;
			Show(3);
			/////////////////////////////////////////////////////////////////////////////////////
			int t=time(0);
			for(int j=0;j<3;j++)
					{
						if((logic.lift[j].TTime)>=10)
						{
							IsStart=!IsStart;
							logic.TT[j].Stop();
							CString str;
							str="��";
							sprintf(s,"%d",j+1);
								str+=s;
								str+="�����ݷ����˹��ϣ�";
							MessageBoxA(str,"warning",MB_OK);
							IsStart=!IsStart;
							logic.TT[j].Start();
							logic.lift[j].TTime=0;
							
						}
					}
					
					/////////////////////////////////////////////////////////////////////////////
			return;
		}
	}
}

void CElevatorDlg::Run()
{
	logic.Lift_Move(LS);
	for(int z = 0; z < P_Number; z++)
	{
	    if(logic.person[z].IsAlive == YES)
	{
		logic.Person_Move(z,PS);		
	}
	}
	
}


void CElevatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(IsStart)
	{
	switch(nIDEvent){    
		case TIME_PAINT: Run(); Show(logic.show);OnPaint();
			break;
		case TIME_PERSONMOVE: Process();Show_time();break; 
		case TIME_GENERATE: 
			               //���ֳ˿͵ĸ��ʣ��߷��Ǹ߸���Ϊ7��ˢ�£��͸��ʶ�Ӧ��3��
						//line��Χ20-85��
						//ˢ�¶��ٸ���Ҳ���ݸߡ��͸���
						int probability = rand() % 10 + 1;
						int n;
						if (line >= 70)
						{
							if (probability > 3)
							{
								n = probability / 2;//ˢ�³�2-5����
								while (n >= 0)
								{
									Generate();
									n--;
								}
							}
							if (line <= 82)
								line += 1;
							else
								line = 20;
						}
						else
						{
							if (probability > 9)
							{
								Generate();
							}
							if (line >= 20)
								line += 1;
						}
					}
	}
}




int CElevatorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
  
	//������ʱ��
	SetTimer(TIME_PAINT, 10, NULL);
	SetTimer(TIME_PERSONMOVE, 100, NULL);
	SetTimer(TIME_GENERATE, 1000, NULL);
	return 0;
}


void CElevatorDlg::Show(int a)
{
   if(a == 0)
   {
       return;
   }
    if(i>=14)
	{
		str[0]="";
	    for(int j=0;j<14;j++)
	   {
	    str[j]=str[j+1];
	   }
	   str[14]="";
    }
	
   switch(a)
   {
     
case 1:
		 {
				sprintf(s,"%d",logic.person_number);
				sprintf(m,"%d",logic.floor_number);
				str[i]+="��";
				str[i]+=s;
				str[i]+="�����ѵ����";
				str[i]+=m;
				str[i]+="��";
				//str[i]+="\r\n";
				logic.show = 0;
			    str1="";
				for(int k=0;k<15;k++)
				{
					if(str[k]!="")
					{
						str1+=str[k];
						str1+="\r\n";
						}
				}
				Dlg2.SetDlgItemText(IDC_EDIT1, str1);
				i++;                      
				if(i==15)
				i=14;
						}
						break;
	   case 2:
		    {
				sprintf(s,"%d",logic.person_number);
				sprintf(m,"%d",logic.lift_number+1);
				str[i]+="��";
				str[i]+=s;
				str[i]+="�����ѽ����";
				str[i]+=m;
				str[i]+="������";
				//str[i]+="\r\n";
				logic.show = 0;
				 str1="";
				for(int k=0;k<15;k++)
				{
					if(str[k]!="")
					{
						str1+=str[k];
						str1+="\r\n";
						}
				}
				Dlg2.SetDlgItemText(IDC_EDIT1, str1);
				i++;                      
				if(i==15)
				i=14;
						}
						break;
			case 3:
//�����Ϣ
		   {
				sprintf(s,"%d",logic.person_number);
				sprintf(m,"%d",logic.floor_number);
				str[i]+="��";
				str[i]+=s;
				str[i]+="���˳����ڵ�";
				str[i]+=m;
				str[i]+="��";
				 str1="";
				for(int k=0;k<15;k++)
				{
					if(str[k]!="")
					{
						str1+=str[k];
						str1+="\r\n";
						}
				}
				Dlg2.SetDlgItemText(IDC_EDIT1, str1);
				i++;                      
				if(i==15)
				i=14;
				}break;
			case 4:
			{
			    sprintf(m,"%d",logic.lift_number+1);
				str[i]+="��";
				str[i] += m;
				str[i]+="�ŵ��ݳ��أ�";
				logic.show = 0;
				 str1=""; 
				for(int k=0;k<15;k++)
				{
					if(str[k]!="")
					{
						str1+=str[k];
						str1+="\r\n";
						}
				}
				Dlg2.SetDlgItemText(IDC_EDIT1, str1);
				i++;                      
				if(i==15)
				i=14;	
			}break;
	
		}
}


void CElevatorDlg::Show_time()
{
	t[0] = time(0) - logic.time0.start_time;
	sprintf(h,"%d",t[0]/60/60);
	sprintf(m,"%d",t[0]/60);
	sprintf(r,"%d",t[0]);
	Ctime="\r\n";
	if(t[0]/60/60<10)
	{Ctime+="0";}
	Ctime+=h;
	Ctime+=":";
	if(t[0]/60<10)
	{Ctime+="0";}
	Ctime+=m;
	Ctime+=":";
	if(t[0]%60<10)
	{Ctime+="0";}
	Ctime+=r;
	Ctime+="\r\n";


	for(int i=0;i<3;i++)
		{
			if(logic.judge[i])
	//��һ������
   {
	   Ctime+="\r\n";
    t[i] = time(0) - logic.timer[i].start_time;
	sprintf(h,"%d", ((int)logic.lift[i].TotalTime)/60/60);
	sprintf(m,"%d", ((int)logic.lift[i].TotalTime)/60);
	sprintf(r,"%d", ((int)logic.lift[i].TotalTime)%60);
	if( ((int)logic.lift[i].TotalTime)/60/60<10)
	{Ctime+="0";}
	Ctime+=h;
	Ctime+=":";
	if( ((int)logic.lift[i].TotalTime)/60<10)
	{Ctime+="0";}
	Ctime+=m;
	Ctime+=":";
	if( ((int)logic.lift[i].TotalTime)%60<10)
	{Ctime+="0";}
	Ctime+=r;
	Ctime+="\r\n";
	}
		else{
			    Ctime+="\r\n";
				Ctime+="00:00:00";
				Ctime+="\r\n";
			}
	}
	 Dlg2.SetDlgItemText(IDC_EDIT2, Ctime); 

}
void CElevatorDlg::Read()
{
			IsStart=!IsStart;
			MessageBoxA(NULL,"��ʼ����",MB_OK);
			CLogic *logic1=&logic;
			CFile file(_T("d:\\Elevator.txt"),CFile::modeRead);
			file.Read((char*)&logic,sizeof(CLogic));
			file.Close();
			long t=time(0);
			logic.time0.start_time=t-logic.Time0;
			logic.time0.is_pause=true;
			logic.time0.pause_time=t;
			logic.Time0=0;
			IsStart=!IsStart;
}
void CElevatorDlg::Load()
{
			IsStart=!IsStart;
			MessageBoxA(NULL,"��ʼ�浵",MB_OK);
			long t=time(0);
			logic.time0.is_pause=true;
			logic.Time0=logic.time0.start_time;
			CFile file(_T("d:\\Elevator.txt"),CFile::modeCreate|CFile::modeWrite);
			file.Write((char*)&logic,sizeof(CLogic));
			file.Close();
			IsStart=!IsStart;
}



void CElevatorDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nChar)
	{
	case 'r':
	case 'R':
		Read();break;
	case 'p':
	case 'P':
		IsStart=!IsStart;
		logic.time0.Pause();
		if(IsStart)
			{
				str1="������ʼ";
				MessageBoxA(str1,"ע�⣡",MB_OK);
			}
		else MessageBoxA("ֹͣ","ע�⣡",MB_OK);
		logic.time0.Start();
		break;
	case 'l':
	case 'L':
		Load();
		break;
	case 's':
	case 'S':
		logic.time0.Pause();
		IsStart=!IsStart;
		set.DoModal();
		LS=set.m_L;
		PS=set.m_P;
		IsStart=!IsStart;
		logic.time0.Start();
		break;
	case 'q':
	case'Q':
		IsStart=!IsStart;
		logic.time0.Pause();
		for(int j=0;j<3;j++)
		{
		sprintf(s,"%d",logic.lift[j].load);
		sprintf(m,"%d",j);
		str1="��";
		str1+=m;
		str1+="̨�����س˿�";
		str1+=s;
		str1+="�ˣ�";
		switch(j)
		{
		case 0:
			show.m_s1=str1;break;
		case 1:
			show.m_s2=str1;break;
		case 2:
			show.m_s4=str1;
		}
		}
		show.DoModal();
		IsStart=!IsStart;
		logic.time0.Start();
		break;
	case 'c':
	case 'C':
		MessageBoxA(_T("������������"),"ע�⣡",MB_OK);
		IsStart=!IsStart;
		logic=CLogic();
		logic.time0.start_time=time(0);
		IsStart=!IsStart;
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}
