#include <stdio.h>
#include <graphics.h>
#include <string.h>
#include <conio.h>
/*
贪吃蛇项目
知识背景: 结构体, 循环, 函数, 结构体数组, easyX


*/

//做界面, 图形窗口
//用结构体定义蛇的结构
#define SNAKE_NUM 500 //蛇的最大节数

enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct Food
{
	int x;
	int y;
	int size;
	bool flag; //食物是否被吃
	DWORD color; //食物的颜色
}food;

struct Snake
{
	int size; //蛇的节数
	int dir; //蛇的方向
	int speed; //移动数据
	POINT coor[SNAKE_NUM]; //坐标, 已经包含x & y
}snake;

//初始化坐标
void GameInit()
{
	//init 初始化, graph 图形窗口
	initgraph(640, 480); //可以加宏 SHOWCONSOLE展示终端

	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;

	food.x = rand() % 640;
	food.y = rand() % 480;
	food.size = rand() % 10 + 5;
	food.flag = true;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);

	for (int i = snake.size-1; i >= 0 ; i--)
	{
		snake.coor[i].x = 40 - 10*i; //增加长度, 第一个为头, 定义初始位置
		snake.coor[i].y = 10;
	}
}

void GameDraw()
{
	//双缓冲绘图(防卡顿)
	BeginBatchDraw();
	
	//设置背景颜色
	setbkcolor(RGB(28, 115, 119)); //RGB怎么取颜色
	//清空绘图设备
	cleardevice();
	//设置蛇的颜色
	setfillcolor(RED);
	//绘制蛇，用圆绘制
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.size);
	}
	
	EndBatchDraw();

}

//移动蛇, 核心算法, 只移动蛇头, 后一个位置的目标继承前一个位置的坐标
void snakeMove()
{
	//移动就是坐标发生改变
	/*for (int i = 0; i < snake.size; i++)
	{
		switch (snake.dir)
		{
		case RIGHT: snake.coor[i].x++; break;
		case UP: snake.coor[i].y--; break;
		case DOWN: snake.coor[i].y++; break; //注意坐标轴的方向
		case LEFT: snake.coor[i].x--; break;
		}
		
	}	这一片效果类似于俄罗斯方块
	*/

	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	//尾部移动核心

	switch (snake.dir)
	{
	case RIGHT:
		snake.coor[0].x += snake.speed;
		if (snake.coor[0].x + 10 > 640)
		{
			snake.coor[0].x = 0;
		}
		break;
	case UP:
		snake.coor[0].y -= snake.speed;
		if (snake.coor[0].y - 10 < 0)
		{
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.speed;
		if (snake.coor[0].y + 10 > 480)
		{
			snake.coor[0].y = 0;
		}
		break; //注意坐标轴的方向
	case LEFT:
		snake.coor[0].x -= snake.speed;
		if (snake.coor[0].x - 10 < 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	}
	
}

//通过按键改变蛇的移动方向
void keyControl() //这一步没有实现?
{
	//判断有没有键盘键入，有则返回真，否则返回假
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w': 
		case 'W':
		case 72 :
			snake.dir = UP;
			break;
		case 's':
		case 'S':
		case 80:
			snake.dir = DOWN;
			break;
		case 'a':
		case 'A':
		case 75:
			snake.dir = LEFT;
			break;
		case 'd':
		case 'D':
		case 77:
			snake.dir = RIGHT;
			break;
		}
	}
}

//判断食物是否被吃
void getFood()
{
	if (food.flag && snake.coor[0].x <= food.x + food.size && snake.coor[0].x >= food.x - food.size &&
		snake.coor[0].y >= food.y - food.size && snake.coor[0].y <= food.y + food.size)
	{
		food.flag = false;
		snake.size++;
	}

	if(!food.flag) //初始化下一个食物
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.size = rand() % 10 + 5;
		food.flag = true;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}


int main()
{
	GameInit();
	GameDraw();

	while (1)
	{
		GameDraw();
		snakeMove();
		keyControl();
		getFood();
		Sleep(50); //延缓50毫秒
	}

	return 0;
}