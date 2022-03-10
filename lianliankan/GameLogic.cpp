#include "StdAfx.h"
#include "GameLogic.h"



CGameLogic::CGameLogic(void)
{
	for(int i=0;i<10;i++)
		for(int j=0;j<16;j++)
			m_Map[10][16]=BLANK;

	m_VexNum = 0;
	m_RemainNum = MAX_ROW * MAX_COL;
}


CGameLogic::~CGameLogic(void)
{
}

void CGameLogic::Initmap()
{
	int nTempMap[MAX_ROW +2 ][MAX_COL + 2]={-1,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,      
											-1,  11, 14,  3,  3,  7,  0,  7,  7,  5,  8,  1,  6,  4,  9, 11, 14, -1,
											-1,  10, 12,  9, 11,  2,  1,  5, 14,  5,  4,  3,  2,  3, 10, 15, 10, -1,
											-1,   2,  8,  0, 14,  9,  1, 13,  3,  4, 10,  4,  5,  9,  6,  1, 14, -1,
											-1,  11,  3, 13,  9, 15,  6,  5, 10,  5,  9,  8,  8, 12,  6,  8, 11, -1,
											-1,   4,  4,  0,  8, 10,  6,  1,  1,  7,  7,  7,  7,  0,  0,  2,  1, -1,
											-1,  14, 15,  2, 15, 14, 12, 14,  6, 13,  8,  0, 12, 10, 10, 13,  0, -1,
											-1,  14,  9,  6,  9, 13,  8, 10,  4,  2,  0,  9,  0,  8,  3, 11,  2, -1,
											-1,  13,  9, 15,  6, 14, 11, 13, 11,  1, 15, 12, 15,  6,  4,  2, 12, -1,
											-1,  13, 12, 10,  7, 12,  0, 12,  8,  3, 13,  5,  1, 11,  7,  3,  7, -1,
											-1,   1, 12, 14,  5, 11, 14, 13, 15, 15,  6,  2,  3, 15,  5,  5,  2, -1,
											-1,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
   
    
	for(int i=0; i<MAX_ROW + 2; i++)
	{
	   for(int j=0; j<MAX_COL + 2; j++)
		   m_Map[i][j]=nTempMap[i][j];
	}

	m_RemainNum = MAX_ROW * MAX_COL;
}

int CGameLogic::GetElement(int x, int y)
{
    return m_Map[x][y];
}

void CGameLogic::SetFirstVex(int nRow, int nCol)
{
    m_FirstVex=GetVex(nRow, nCol);
}

void CGameLogic::SetSecondVex(int nRow, int nCol)
{
    m_SecondVex=GetVex(nRow, nCol);
}

Vertex CGameLogic::GetVex(int nRow, int nCol)
{
    Vertex v;
	v.mX=nRow;
	v.mY=nCol;
	v.mPicNum=m_Map[nRow][nCol];
	return v;
}

/*************************************************************************************/
BOOL CGameLogic::Link(Vertex aPath[4], int &nNum)
{
    //判断两次是否选择了同一张图片
	if(m_FirstVex.mX == m_SecondVex.mX && m_FirstVex.mY == m_SecondVex.mY)
	{
	    return FALSE;
	}
	//判断两个图片是否同色
	if(m_FirstVex.mPicNum != m_SecondVex.mPicNum)
	{
	    return FALSE;
	}
	//判断是否连通
	if(IsLink(m_FirstVex,  m_SecondVex))
	{
	    Clear(m_FirstVex,  m_SecondVex);
		nNum = GetVexPath(aPath);
		m_VexNum = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL CGameLogic::IsLink(Vertex v1, Vertex v2)
{
    //插入第一个点
	AddVex(v1);
	//一条直线连通
	if(NoCornerLink(v1, v2))
	{
	    //插入最后一个点
		AddVex(v2);
		return TRUE;
	}
	//两条直线连通
	if(OneCornerLink(v1, v2))
	{
	    AddVex(v2);
		return TRUE;
	}
    //三条直线连通
	if(TwoCornerLink(v1, v2))
	{
	    AddVex(v2);
		return TRUE;
	}
	//删除第一个点
	DeleteVex();
	return FALSE;
}

BOOL CGameLogic::NoCornerLink(Vertex v1, Vertex v2)
{
    //水平方向上连通
	if(v1.mX==v2.mX)
	{
	    if(LinkRow(v1, v2))
		{
		    return TRUE;
		}
	}
	//竖直方向上连通
	if(v1.mY==v2.mY)
	{
	    if(LinkCol(v1, v2))
		{
		    return TRUE;
		}
	}
	return FALSE;
}

BOOL CGameLogic::LinkRow(Vertex v1, Vertex v2)
{
    if(v1.mY>v2.mY)
	{
	    int t=v1.mY;
		v1.mY=v2.mY;
		v2.mY=t;
	}
	int X=v1.mX;
	for(int Y = v1.mY; Y < v2.mY; Y++)
	{
	    if(Y+1==v2.mY)
		{
		    return TRUE;
		}
		else if(m_Map[X][Y+1] != BLANK)
		{
		    return FALSE;
		}
	}
	return FALSE;
}
	
BOOL CGameLogic::LinkCol(Vertex v1, Vertex v2)
{
    if(v1.mX>v2.mX)
	{
	    int t=v1.mX;
		v1.mX=v2.mX;
		v2.mX=t;
	}
	int Y=v1.mY;
	for(int X = v1.mX; X < v2.mX; X++)
	{
	    if(X+1==v2.mX)
		{
		    return TRUE;
		}
		else if(m_Map[X+1][Y] != BLANK)
		{
		    return FALSE;
		}
	}
	return FALSE;
}

void CGameLogic::Clear(Vertex v1,Vertex v2)
{
    m_Map[v1.mX][v1.mY]=BLANK;
	m_Map[v2.mX][v2.mY]=BLANK;
	m_RemainNum = m_RemainNum - 2;
}

void CGameLogic::AddVex(Vertex v)
{
    m_Path[m_VexNum] = v;
	m_VexNum++;
}

void CGameLogic::DeleteVex()
{
    m_VexNum--;
}

int CGameLogic::GetVexPath(Vertex v[4])
{
    for(int i = 0; i < m_VexNum; i++ )
		v[i]=m_Path[i];

	return m_VexNum;
}

BOOL CGameLogic::OneCornerLink(Vertex v1, Vertex v2)
{
    //获得拐点
	Vertex v;
	v = GetVex(v1.mX, v2.mY);    //第一个拐点
	//判断拐点是否为空
	if(v.mPicNum == BLANK)
	{
		if(LinkRow(v1, v) && LinkCol(v2, v))
		{   
			AddVex(v);
			return TRUE;
		}
	}
	
	v = GetVex(v2.mX, v1.mY);    //第二个拐点
	//判断拐点是否为空
	if(v.mPicNum == BLANK)
	{
		if(LinkRow(v2, v) && LinkCol(v1, v))
		{
			AddVex(v);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGameLogic::TwoCornerLink(Vertex v1, Vertex v2)
{
    Vertex vv1, vv2;
	//搜索关键路径
	//水平方向上的关键路径
	for(int i = 0; i < MAX_ROW + 2; i++)
	{
	    vv1 = GetVex(i, v1.mY);
		vv2 = GetVex(i, v2.mY);
		if(vv1.mPicNum == BLANK && vv2.mPicNum == BLANK)
		{
		    if(LinkRow(vv1, vv2))
			{
			    if(LinkCol(v1, vv1) && LinkCol(v2, vv2))
				{
				    //满足三条直线连通
					AddVex(vv1);
					AddVex(vv2);
					return TRUE;
				}
			}
		}
	}
	//竖直方向上的关键路径
	for(int j = 0; j < MAX_COL + 2; j++)
	{
		vv1 = GetVex(v1.mX, j);
		vv2 = GetVex(v2.mX, j);
		if(vv1.mPicNum == BLANK && vv2.mPicNum == BLANK)
		{
			if(LinkCol(vv1, vv2))
			{
			    if(LinkRow(v1, vv1) && LinkRow(v2, vv2))
				{
				    //满足三条直线连通
					AddVex(vv1);
					AddVex(vv2);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

BOOL CGameLogic::IsWin()
{
    if(m_RemainNum == 0)
	{
	    return TRUE;
	}
	return FALSE;
}
