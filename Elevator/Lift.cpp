#include "StdAfx.h"
#include "Lift.h"
/***************************************************************************/

Lift::Lift(void)
{
	Now_Floor = 1;
	Height = 0;
	status = L_OFF;
	time = 0;
	direct = NO;
	load = 0;
	door = 1;
	IsOpen = NO;
	IsFull = NO;
	priority = 0;
	TotalTime=0;
	TTime=0;
	for(int j = 0;j < 10;j++)
	{
		lift_destination[j] = 0;
		for(int k = 0; k < 2; k++)
		{
		    instruction[j][k] = 0;
		}
	}
}


Lift::~Lift(void)
{
}

void Lift::MoveUp(int LS)
{
	int HeightA;Now_Floor++;
	HeightA = Height+LS;
	if(HeightA/72!=Height/72)
	{
		if(IsWait())
		Height=(Now_Floor-1)*72;
		else Height=HeightA;
	}
	else Height=HeightA;
	Now_Floor=Height/72+1;
	TotalTime+=0.02;
	TTime += 0.02;
}

void Lift::MoveDown(int LS)
{
    int HeightA;
	HeightA = Height-LS;
	if(HeightA/72!=Height/72)
	{
		if(IsWait())
		Height=(Now_Floor-1)*72;
		else Height=HeightA;
	}
	else Height=HeightA;
	Now_Floor=Height/72+1;
	TotalTime+=0.02;
	TTime+=0.02;
}

void Lift::Wait()
{
    time++;
	//控制门的开关
	if(time > 0 && time <= 5)
	{
	    door = 2;
	}
	if(time > 5 && time <= 10)
	{
	    door = 3;
	}
	if(time > 10 &&  time <= 15)
	{
	    door = 4;
	}
	if(time > 15 &&  time <= 185)
	{
	    door = 0;
	}
	if(time > 185 &&  time <= 190)
	{
	    door = 4;
		IsOpen = NO;
	}
	if(time > 190 &&  time <= 195)
	{
	    door = 3;
	}
	if(time > 195 &&  time <= 200)
	{
	    door = 2;
	}
	
	//等待状态结束
	if(time == 200)
	{   
	    IsOpen = NO;
		door = 1;
		time = 0;
		NextMove();
	}
}

void Lift::Off(){}


int Lift::IsWait()
{
    if(lift_destination[Now_Floor - 1])
	{
		return 1;
	}
	if(instruction[Now_Floor - 1][0] || instruction[Now_Floor - 1][1])
	{
        
		if(instruction[Now_Floor - 1][0] == direct || instruction[Now_Floor - 1][1] == direct)
		{
		    return 1;
		}
		if(load == 0)
		{
		    return 1;
		}
	}
	return 0;
}

int Lift::IsOff()
{
    for(int i = 0; i < 10; i++)
	{
	    if(lift_destination[i] || instruction[i][0] || instruction[i][1])
		{
		    return 0;
		}
	}
	return 1;
}

void Lift::NextMove()
{
	for(int i = Now_Floor; i < 10; i++)
	{
	    if(lift_destination[i] == 1)
		{
			status = L_UP;
            direct = UP;
            return;
		}
	}
	for(int i = 0; i < Now_Floor - 1; i++)
	{
		if(lift_destination[i] == 1)
		{  
			status = L_DOWN;
            direct = DOWN;
            return;
		}
	}
	if(direct == UP)
	{
	    for(int i = Now_Floor; i < 10; i++)
		{
			if(instruction[i][0] || instruction[i][1])
			{
				status = L_UP;
				direct = UP;
				return;
			}
		}
		for(int i = 0; i < Now_Floor - 1; i++)
		{
			if(instruction[i][0] || instruction[i][1])
			{
				status = L_DOWN;
				direct = DOWN;
				return;
			}
		}
	}
	else
	{
	    for(int i = 0; i < Now_Floor - 1; i++)
		{
			if(instruction[i][0] || instruction[i][1])
			{
				status = L_DOWN;
				direct = DOWN;
				return;
			}
		}
		for(int i = Now_Floor; i < 10; i++)
		{
			if(instruction[i][0] || instruction[i][1])
			{
				status = L_UP;
				direct = UP;
				return;
			}
		}
	}
	status = L_OFF;
    direct = NO;
    return;
}

