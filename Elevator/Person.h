#pragma once
#include "Global.h"

class Person
{
public:
	Person(void);
	~Person(void);
public:
    int x;                 //�������϶���ĺ�����
	int y;                 //�������϶����������
	int step;              //�˶����ڼ���ͼƬ
	int Start_Floor;       //�������ɵ�¥��
    int End_Floor;         //���ﵽ���¥��
	int status;            //����������״̬
	int direct;            //�ж���������¥������¥
	int IsCall;            //�ж����Ƿ�����˵���
	int IsSelect;          //�ж����Ƿ�ѡ����Ŀ��¥��
	int In_Lift;           //�˽���ĵ��� 
	int Height;            //�˴��ڵĸ߶�
	int towards;           //����ĳ���
	int IsAlive;           //���Ƿ����
	int character;         //�����ɫ���  
	int p_number;          //�������ɵı��
public:
	void MoveUp();
	void MoveDown();
	void MoveLeft(int);
	void MoveRight(int);
	void MoveBack(int);
	void Wait();
	
};

