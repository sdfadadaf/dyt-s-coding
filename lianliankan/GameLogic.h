#pragma once
#include "Global.h"

class CGameLogic
{
protected:
	Vertex GetVex(int nRow, int nCol);             //得到坐标信息
	BOOL IsLink(Vertex v1, Vertex v2);             //判断是否连通
	BOOL NoCornerLink(Vertex v1, Vertex v2);       //判断是否直线连通
	BOOL LinkRow(Vertex v1, Vertex v2);            //判断水平方向上是否连通
	BOOL LinkCol(Vertex v1, Vertex v2);            //判断竖直方向上是否连通
	void Clear(Vertex v1, Vertex v2);              //擦除图片
	void AddVex(Vertex v);                         //添加一个路径顶点
	void DeleteVex();                              //取出一个顶点
	int GetVexPath(Vertex v[4]);                   //得到路径
    

public:
	CGameLogic(void);
	~CGameLogic(void);
	void Initmap();                                //初始化地图
	int GetElement(int ROW, int COL);              //得到图片编号
	void SetFirstVex(int nRow, int nCol);          //设置点击的第一个图片的坐标信息
	void SetSecondVex(int nRow, int nCol);         //设置点击的第二个图片的坐标信息
	BOOL Link(Vertex aPath[4], int &nNum);         //消子判断
	BOOL OneCornerLink(Vertex v1, Vertex v2);      //判断两条直线消子  
	BOOL TwoCornerLink(Vertex v1, Vertex v2);      //判断三条直线消子
	BOOL IsWin();

protected:
	int m_Map[12][18];                             //游戏地图数组                          
	Vertex m_FirstVex;                             //点击的第一个图片的坐标信息
	Vertex m_SecondVex;                            //点击的第二个图片的坐标信息
	Vertex m_Path[4];                              //保存在进行连接判断时所经过的点
	int m_VexNum;                                  //顶点数
	int m_RemainNum;
};

