#pragma once
#include "Global.h"

class Lift
{
public:
	Lift(void);
	~Lift(void);

public:
	int Init_Floor;          //初始化时电梯的楼层
	int Now_Floor;           //当前所在楼层
	int Height;              //电梯的高度
	int status;              //电梯所处的状态
	int load;                //电梯的载重
	int time;                //用于计算Wait()函数执行的次数
	int direct;              //电梯运行的方向
	int door;                //控制电梯门
	int IsOpen;              //是否开门
	int priority;            //用于优先级的判断
	int IsFull;              //用于判断电梯是否超载
	double TotalTime;
	double TTime;
public:
	void MoveUp(int);  
	void MoveDown(int);
	void Wait();             //电梯开关门等待
	void Off();              //电梯处于未工作状态
	void NextMove();         //判断电梯下一步的工作状态

public:	
	int instruction[10][2];     //各楼层人物的指令
	int lift_destination[10];     //电梯内乘客要到达i的楼层

public:
	int IsWait();            //判断电梯是否要停下来等待
	int IsOff();             //判断电梯是否会停止工作
	
};


