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
		//����boolֵ�������״̬ 
		bool is_pause; //��¼��ʱ����״̬ ���Ƿ�����ͣ״̬��
		bool is_stop;//�Ƿ���ֹͣ״̬ 
public:
		bool isPause(); //���ؼ�ʱ��״̬ 
		bool isStop();
		//��ʱ�������ֶ��������ܣ� 
		void Start(); 
		void Pause();
		void Stop();
		inline long getStartTime() {return start_time;}
};

