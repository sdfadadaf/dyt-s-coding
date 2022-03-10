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
	void Eliminate_In(int);      //消除内部指令
	void Eliminate_Out(int);     //消除外部指令
	void Priority_Judge(Person &);    //电用电梯的优先级的判断

	int IsIn(int,Person &);
	int IsOut(int, Person &);

public:
	Person person[P_Number];
	Lift lift[3];
	int show;                    //用于判断输出的类型
	int person_number;
	int floor_number;
	int lift_number;
    int judge[3];
	CTimer time0,timer[3];
	CTimer TT[3];
	long Time0,Timer[3];
};

