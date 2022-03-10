#include "StdAfx.h"
#include "Person.h"


Person::Person(void)
{
	IsCall = NO;
	IsSelect = NO;
	status = P_Left;
	In_Lift = NO;
	step = 0;
	towards = _LEFT;
	IsAlive = NO;
}


Person::~Person(void)
{
}


void Person::MoveUp()
{
    Height += L_SPEED;
}

void Person::MoveDown()
{
    Height -= L_SPEED;   
}

void Person::MoveLeft(int PS)
{
    x -= PS;
	if(x <= WaitPoint)
	{
	    status = P_Wait;
		IsCall = YES;
		step = 0;
	}
}

void Person::MoveRight(int PS)
{
    x += PS;
	if(x > StartPoint)
	{
	    IsAlive = NO;
	}
}


void Person::Wait(){}

void Person::MoveBack(int PS)
{
    x += PS;
	if(x > WaitPoint)
	{
	    status = P_Left;
		step = 0;
		towards = _LEFT;
	}
}