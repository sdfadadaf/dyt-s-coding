#pragma once
#include "Global.h"

class CGameLogic
{
protected:
	Vertex GetVex(int nRow, int nCol);             //�õ�������Ϣ
	BOOL IsLink(Vertex v1, Vertex v2);             //�ж��Ƿ���ͨ
	BOOL NoCornerLink(Vertex v1, Vertex v2);       //�ж��Ƿ�ֱ����ͨ
	BOOL LinkRow(Vertex v1, Vertex v2);            //�ж�ˮƽ�������Ƿ���ͨ
	BOOL LinkCol(Vertex v1, Vertex v2);            //�ж���ֱ�������Ƿ���ͨ
	void Clear(Vertex v1, Vertex v2);              //����ͼƬ
	void AddVex(Vertex v);                         //���һ��·������
	void DeleteVex();                              //ȡ��һ������
	int GetVexPath(Vertex v[4]);                   //�õ�·��
    

public:
	CGameLogic(void);
	~CGameLogic(void);
	void Initmap();                                //��ʼ����ͼ
	int GetElement(int ROW, int COL);              //�õ�ͼƬ���
	void SetFirstVex(int nRow, int nCol);          //���õ���ĵ�һ��ͼƬ��������Ϣ
	void SetSecondVex(int nRow, int nCol);         //���õ���ĵڶ���ͼƬ��������Ϣ
	BOOL Link(Vertex aPath[4], int &nNum);         //�����ж�
	BOOL OneCornerLink(Vertex v1, Vertex v2);      //�ж�����ֱ������  
	BOOL TwoCornerLink(Vertex v1, Vertex v2);      //�ж�����ֱ������
	BOOL IsWin();

protected:
	int m_Map[12][18];                             //��Ϸ��ͼ����                          
	Vertex m_FirstVex;                             //����ĵ�һ��ͼƬ��������Ϣ
	Vertex m_SecondVex;                            //����ĵڶ���ͼƬ��������Ϣ
	Vertex m_Path[4];                              //�����ڽ��������ж�ʱ�������ĵ�
	int m_VexNum;                                  //������
	int m_RemainNum;
};

