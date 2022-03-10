#include "StdAfx.h"
#include "Timer.h"


CTimer::CTimer(void)
{
	is_pause = false; //��ʼ����ʱ��״̬ 
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
void CTimer::Start() //��ʼ 
{
	if(is_stop)
	{
		start_time = time(0);
		is_stop = false;
	}
	else if(is_pause)
	{
		is_pause = false;
		start_time += time(0)-pause_time; //���¿�ʼʱ�䣺�ô�ʱ��ʱ�� - ��ͣʱ���õ�ʱ�� + ��һ�ο�ʼ��ʱ�� = ��ʱ�Ŀ�ʼʱ�� 
	}
}
void CTimer::Pause() //��ͣ 
{
	if(is_stop||is_pause) //�������ֹͣ/��ͣ״̬,�˶��������κδ���ֱ�ӷ��� 
		return; 
	else    //�������Ϊ��ͣ״̬
	{

		is_pause = true;
		pause_time = time(0); //��ȡ��ͣʱ�� 

	}

}
void CTimer::Stop()  //ֹͣ 

{
	if(is_stop) //���������ֹͣ״̬��������ͣ״̬���������κδ��� 
		return ; 
	else if(is_pause) //�ı��ʱ��״̬ 
	{
		is_pause = false;
		is_stop = true;
	}
	else if(!is_stop)
	{

		is_stop = true;
	} 
}