#pragma once

typedef struct VertexInformation{
    int mX;
	int mY;
	int mPicNum;
}Vertex;

#define MAX_ROW 10
#define MAX_COL 16
#define WIDTH 1280          //�ͻ������
#define HEIGHT 720          //�ͻ����߶�
#define MAP_TOP 60          //��Ϸ��ͼ��ʼ��Y����
#define MAP_LEFT 60         //��Ϸ��ͼ��ʼ��X����
#define PIC_WIDTH 60       //��ϷԪ��ͼƬ���
#define PIC_HEIGHT 60       //��ϷԪ��ͼƬ�߶�
#define BLANK -1            //��ͼƬ��ֵ