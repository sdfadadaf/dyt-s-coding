#include "StdAfx.h"
#include "Timer.h"


CTimer::CTimer(void)
{
	is_pause = false; //初始化计时器状态 
	is_stop = true;
	start_time=pause_time=time(0);
}


CTimer::~CTimer(void)
{
}
bool CTimer::isPause()
{	
	if(is_pause)
	return true;
	else
	return false;
}
bool CTimer::isStop()
{
	if(is_stop)
		return true;
	return false;
} 
void CTimer::Start() //开始 
{
	if(is_stop)
	{
		start_time = time(0);
		is_stop = false;
	}
	else if(is_pause)
	{
		is_pause = false;
		start_time += time(0)-pause_time; //更新开始时间：用此时的时间 - 暂停时所用的时间 + 上一次开始的时间 = 此时的开始时间 
	}
}
void CTimer::Pause() //暂停 
{
	if(is_stop||is_pause) //如果处于停止/暂停状态,此动作不做任何处理，直接返回 
		return; 
	else    //否则调制为暂停状态
	{

		is_pause = true;
		pause_time = time(0); //获取暂停时间 

	}

}
void CTimer::Stop()  //停止 

{
	if(is_stop) //如果正处于停止状态（不是暂停状态），不做任何处理 
		return ; 
	else if(is_pause) //改变计时器状态 
	{
		is_pause = false;
		is_stop = true;
	}
	else if(!is_stop)
	{

		is_stop = true;
	} 
}