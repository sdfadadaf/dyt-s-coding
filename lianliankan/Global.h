#pragma once

typedef struct VertexInformation{
    int mX;
	int mY;
	int mPicNum;
}Vertex;

#define MAX_ROW 10
#define MAX_COL 16
#define WIDTH 1280          //客户区宽度
#define HEIGHT 720          //客户区高度
#define MAP_TOP 60          //游戏地图起始点Y坐标
#define MAP_LEFT 60         //游戏地图起始点X坐标
#define PIC_WIDTH 60       //游戏元素图片宽度
#define PIC_HEIGHT 60       //游戏元素图片高度
#define BLANK -1            //空图片的值