#pragma once
#include "Global.h"

class Lift
{
public:
	Lift(void);
	~Lift(void);

public:
	int Init_Floor;          //��ʼ��ʱ���ݵ�¥��
	int Now_Floor;           //��ǰ����¥��
	int Height;              //���ݵĸ߶�
	int status;              //����������״̬
	int load;                //���ݵ�����
	int time;                //���ڼ���Wait()����ִ�еĴ���
	int direct;              //�������еķ���
	int door;                //���Ƶ�����
	int IsOpen;              //�Ƿ���
	int priority;            //�������ȼ����ж�
	int IsFull;              //�����жϵ����Ƿ���
	double TotalTime;
	double TTime;
public:
	void MoveUp(int);  
	void MoveDown(int);
	void Wait();             //���ݿ����ŵȴ�
	void Off();              //���ݴ���δ����״̬
	void NextMove();         //�жϵ�����һ���Ĺ���״̬

public:	
	int instruction[10][2];     //��¥�������ָ��
	int lift_destination[10];     //�����ڳ˿�Ҫ����i��¥��

public:
	int IsWait();            //�жϵ����Ƿ�Ҫͣ�����ȴ�
	int IsOff();             //�жϵ����Ƿ��ֹͣ����
	
};


