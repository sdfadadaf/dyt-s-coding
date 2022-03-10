#pragma once
#include "Global.h"
#include "Lift.h"
#include "Person.h"
#include "math.h"
#include "Timer.h"

class CLogic
{
public:
	CLogic(void);
	~CLogic(void);

public:
	void Lift_Move(int);
	void Person_Move(int,int);
	void Person_GetIn(Person &,int);
	void Order1(Person &);
	void Order2(Person &);
	void Status_Judge(int);
	void InOut_Judge(int);
	void Off_Judge(int);
	void Eliminate_In(int);      //�����ڲ�ָ��
	void Eliminate_Out(int);     //�����ⲿָ��
	void Priority_Judge(Person &);    //���õ��ݵ����ȼ����ж�

	int IsIn(int,Person &);
	int IsOut(int, Person &);

public:
	Person person[P_Number];
	Lift lift[3];
	int show;                    //�����ж����������
	int person_number;
	int floor_number;
	int lift_number;
    int judge[3];
	CTimer time0,timer[3];
	CTimer TT[3];
	long Time0,Timer[3];
};

