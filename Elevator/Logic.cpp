#include "StdAfx.h"
#include "Logic.h"
/**************************************************************************************/

CLogic::CLogic(void)
{
	int show = 0;
	lift[0].Now_Floor=1;lift[0].Height=0;
	lift[1].Now_Floor=5;lift[1].Height=72*4;
	lift[2].Now_Floor=10;lift[2].Height=72*9;
}


CLogic::~CLogic(void)
{
}


//人物运行
void CLogic::Person_Move(int i,int PS)
{
	switch(person[i].status){
	    case P_Left: person[i].MoveLeft(PS);break;
		case P_Wait: person[i].Wait();break;
		case P_GetIn: Person_GetIn(person[i],PS);
			          break;
		case P_Take:  person[i].Height=lift[person[i].In_Lift].Height;
					  break;
		case P_Right: person[i].MoveRight(PS);break;
		case P_Back: person[i].MoveBack(PS);
	}
}

//电梯运行
void CLogic::Lift_Move(int LS)
{
    //判断是否有指令产生
	for(int z = 0; z < P_Number; z++)
	{
		if(person[z].IsAlive == YES)
		{
		    if(person[z].IsCall == YES)
			{
				Order1(person[z]);
				person[z].IsCall = NO;
			}
			if(person[z].IsSelect == YES)
			{
				Order2(person[z]);
				person[z].IsSelect = NO;
			}
		}
	}
	//3台电梯的运行
	for(int i = 0;i < 3; i++)
	{
	    switch(lift[i].status)
		{
		    case L_UP: lift[i].MoveUp(LS);
				timer[i].Start();
				TT[i].Start();
				Status_Judge(i); break;
			case L_DOWN: lift[i].MoveDown(LS);
				timer[i].Start();
				TT[i].Start();
				Status_Judge(i); break;
			case L_WAIT: timer[i].Pause();
				TT[i].Pause();
				lift[i].Wait();
				
				InOut_Judge(i); break;
			case L_OFF: timer[i].Pause();
				TT[i].Pause();
				lift[i].Off();
				Off_Judge(i);
		}
	    
	}
}

void CLogic::Order1(Person &a)
{
	if(lift[0].status == L_OFF || lift[1].status == L_OFF || lift[2].status == L_OFF)
	{
	    Priority_Judge(a);
	}
	else
	{
	    if(a.direct == UP)
		{
			for(int k =0; k < 3; k++)
			{
				lift[k].instruction[a.Start_Floor - 1][0] = UP;
			}
		}
		if(a.direct == DOWN)
		{
			for(int k =0; k < 3; k++)
			{
				lift[k].instruction[a.Start_Floor - 1][1] = DOWN;
			}
		}
	}
}

void CLogic::Order2(Person &a)
{
    lift[a.In_Lift].lift_destination[a.End_Floor - 1] = 1;
}

int CLogic::IsIn(int i,Person &a)
{
	if(a.Start_Floor == lift[i].Now_Floor && lift[i].IsFull == NO)         //人和电梯在同一层
	{
		if(lift[i].load == 0 || a.direct == lift[i].direct)
		{
		    return 1;
		}
	}
	return 0;
}

int CLogic::IsOut(int i, Person &a)
{
	if(a.In_Lift == i && a.End_Floor == lift[i].Now_Floor)
	{
	    return 1;
	}
	return 0;
}

void CLogic::Status_Judge(int i)
{
    if(lift[i].Height % FloorHeight == 0)
	{
		lift[i].Now_Floor = lift[i].Height / FloorHeight + 1; 
		if(lift[i].Now_Floor == 10)
		{
			lift[i].direct = DOWN;
		}
		if(lift[i].Now_Floor == 0)
		{
		    lift[i].direct = UP;
		}
		if(lift[i].IsWait())                //判断电梯是否要停下来开门
		{   
			lift[i].status = L_WAIT;
			lift[i].IsOpen = YES;
			lift[i].IsFull = NO;
			Eliminate_In(i);
			Eliminate_Out(i);
			return;
		}
		if(lift[i].IsOff())
		{
			lift[i].status = L_OFF;
			lift[i].direct = NO;
			
			return;
		}
		lift[i].NextMove();
	}
}

void CLogic::InOut_Judge(int i)
{
    //人上下电梯
	for(int z = 0; z < P_Number; z++)
	{
		if(person[z].IsAlive == YES)
		{
		    if(person[z].status == P_Take)
			{
				if(IsOut(i,person[z]))
				{
					person[z].status = P_Right;
					person[z].towards = _RIGHT;
					lift[i].load --;
					show = 1;
					person_number = person[z].p_number;
					floor_number = person[z].End_Floor;
				}
			}
			if(person[z].status == P_Wait)
			{
				if(IsIn(i,person[z]))
				{
					if(lift[i].load == 0)
					{
						lift[i].direct = person[z].direct;						
					}
					person[z].In_Lift = i;
					person[z].status = P_GetIn;
					Eliminate_Out(i);
				}
			} 
		}
	}
}

void CLogic::Off_Judge(int i)
{
    if(lift[i].instruction[lift[i].Now_Floor-1][0] == UP|| lift[i].instruction[lift[i].Now_Floor-1][1] == DOWN)
	{
		lift[i].status = L_WAIT;
		lift[i].IsOpen = YES;
		judge[i]=1;
		return;
	}
	for(int j = lift[i].Now_Floor;j < 10; j++)
	{
	    if(lift[i].instruction[j][0] || lift[i].instruction[j][1])
		{
		    lift[i].status = L_UP;
			lift[i].direct = UP;
			judge[i]=1;
			return;
		}
	}
	for(int k = 0;k < lift[i].Now_Floor-1; k++)
	{
	    if(lift[i].instruction[k][0] || lift[i].instruction[k][1])
		{
		    lift[i].status = L_DOWN;
			lift[i].direct = DOWN;
			judge[i]=1;
			return;
		}
	}
}

void CLogic::Eliminate_In(int i)
{ 
	//电梯内指令消失
	lift[i]. lift_destination[lift[i].Now_Floor - 1] = 0;
}

void CLogic::Eliminate_Out(int i)
{
    //电梯外指令的消失
	if(lift[i].direct == UP)
	{
		for(int k =0; k < 3; k++)
		{
			lift[k].instruction[lift[i].Now_Floor - 1][0] = 0;
		}
	}
	if(lift[i].direct == DOWN)
	{
		for(int k =0; k < 3; k++)
		{
			lift[k].instruction[lift[i].Now_Floor - 1][1] = 0;
		}
	}
}

void CLogic::Person_GetIn(Person &a ,int PS)
{
    a.x -= PS;
	if(lift[a.In_Lift].IsOpen == NO)
	{
		a.status = P_Back;
		a.towards = _RIGHT;
	}
	if(a.x <= TakePoint0+a.In_Lift*L_DISTANCE + 15)
	{
		if(lift[a.In_Lift].load >= MAX_LOAD)
		{
		    a.status = P_Back;
		    a.towards = _RIGHT;
			lift[a.In_Lift].IsFull = YES;
			//输出超载的信息
			show = 4;
			lift_number = a.In_Lift;
		}
	}
	if(a.x <= TakePoint0+a.In_Lift*L_DISTANCE)
	{
	    a.status = P_Take;
		a.IsSelect = YES;
		a.towards = _DOWN;
		lift[a.In_Lift].load++;
		//输出人物已进入电梯的信息
		show = 2;
		person_number = a.p_number;
		lift_number = a.In_Lift;
	}
}

void CLogic::Priority_Judge(Person &a)
{
    for(int i = 0; i < 3; i++)
	{
		if(lift[i].status != L_OFF)
		{
			lift[i].priority = 0;
		}
		else
		{
			lift[i].priority = 10 - abs(lift[i].Now_Floor - a.Start_Floor);
		}
	}
	if(lift[0].priority >= lift[1].priority && lift[0].priority >= lift[2].priority)
	{
	    if(a.direct == UP)
		{
			{
				lift[0].instruction[a.Start_Floor - 1][0] = UP;
			}
		}
		if(a.direct == DOWN)
		{
			{
				lift[0].instruction[a.Start_Floor - 1][1] = DOWN;
			}
		}
		return;
	}
	if(lift[1].priority >= lift[0].priority && lift[1].priority >= lift[2].priority)
	{
	    if(a.direct == UP)
		{
			{
				lift[1].instruction[a.Start_Floor - 1][0] = UP;
			}
		}
		if(a.direct == DOWN)
		{
			{
				lift[1].instruction[a.Start_Floor - 1][1] = DOWN;
			}
		}
		return;
	}
	if(lift[2].priority >= lift[1].priority && lift[2].priority >= lift[0].priority)
	{
	    if(a.direct == UP)
		{
			{
				lift[2].instruction[a.Start_Floor - 1][0] = UP;
			}
		}
		if(a.direct == DOWN)
		{
			{
				lift[2].instruction[a.Start_Floor - 1][1] = DOWN;
			}
		}
	}
	return;
}