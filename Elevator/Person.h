#pragma once
#include "Global.h"

class Person
{
public:
	Person(void);
	~Person(void);
public:
    int x;                 //人物左上顶点的横坐标
	int y;                 //人物左上顶点的纵坐标
	int step;              //运动到第几张图片
	int Start_Floor;       //人物生成的楼层
    int End_Floor;         //人物到达的楼层
	int status;            //人物所处的状态
	int direct;            //判断人物是上楼还是下楼
	int IsCall;            //判断人是否呼叫了电梯
	int IsSelect;          //判断人是否选择了目的楼层
	int In_Lift;           //人进入的电梯 
	int Height;            //人处于的高度
	int towards;           //人物的朝向
	int IsAlive;           //人是否存在
	int character;         //人物角色编号  
	int p_number;          //人物生成的编号
public:
	void MoveUp();
	void MoveDown();
	void MoveLeft(int);
	void MoveRight(int);
	void MoveBack(int);
	void Wait();
	
};

