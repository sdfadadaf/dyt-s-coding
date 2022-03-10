#pragma once
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <windows.h>
using namespace std;
class CTimer
{
public:
	CTimer(void);
	~CTimer(void);
	long start_time;
	long pause_time;
		//两个bool值标记四种状态 
		bool is_pause; //记录计时器的状态 （是否处于暂停状态）
		bool is_stop;//是否处于停止状态 
public:
		bool isPause(); //返回计时器状态 
		bool isStop();
		//计时器的三种动作（功能） 
		void Start(); 
		void Pause();
		void Stop();
		inline long getStartTime() {return start_time;}
};

