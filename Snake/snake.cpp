#include <stdio.h>
#include <graphics.h>
#include <string.h>
#include <conio.h>
/*
̰������Ŀ
֪ʶ����: �ṹ��, ѭ��, ����, �ṹ������, easyX


*/

//������, ͼ�δ���
//�ýṹ�嶨���ߵĽṹ
#define SNAKE_NUM 500 //�ߵ�������

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
	bool flag; //ʳ���Ƿ񱻳�
	DWORD color; //ʳ�����ɫ
}food;

struct Snake
{
	int size; //�ߵĽ���
	int dir; //�ߵķ���
	int speed; //�ƶ�����
	POINT coor[SNAKE_NUM]; //����, �Ѿ�����x & y
}snake;

//��ʼ������
void GameInit()
{
	//init ��ʼ��, graph ͼ�δ���
	initgraph(640, 480); //���ԼӺ� SHOWCONSOLEչʾ�ն�

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
		snake.coor[i].x = 40 - 10*i; //���ӳ���, ��һ��Ϊͷ, �����ʼλ��
		snake.coor[i].y = 10;
	}
}

void GameDraw()
{
	//˫�����ͼ(������)
	BeginBatchDraw();
	
	//���ñ�����ɫ
	setbkcolor(RGB(28, 115, 119)); //RGB��ôȡ��ɫ
	//��ջ�ͼ�豸
	cleardevice();
	//�����ߵ���ɫ
	setfillcolor(RED);
	//�����ߣ���Բ����
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.size);
	}
	
	EndBatchDraw();

}

//�ƶ���, �����㷨, ֻ�ƶ���ͷ, ��һ��λ�õ�Ŀ��̳�ǰһ��λ�õ�����
void snakeMove()
{
	//�ƶ��������귢���ı�
	/*for (int i = 0; i < snake.size; i++)
	{
		switch (snake.dir)
		{
		case RIGHT: snake.coor[i].x++; break;
		case UP: snake.coor[i].y--; break;
		case DOWN: snake.coor[i].y++; break; //ע��������ķ���
		case LEFT: snake.coor[i].x--; break;
		}
		
	}	��һƬЧ�������ڶ���˹����
	*/

	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	//β���ƶ�����

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
		break; //ע��������ķ���
	case LEFT:
		snake.coor[0].x -= snake.speed;
		if (snake.coor[0].x - 10 < 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	}
	
}

//ͨ�������ı��ߵ��ƶ�����
void keyControl() //��һ��û��ʵ��?
{
	//�ж���û�м��̼��룬���򷵻��棬���򷵻ؼ�
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

//�ж�ʳ���Ƿ񱻳�
void getFood()
{
	if (food.flag && snake.coor[0].x <= food.x + food.size && snake.coor[0].x >= food.x - food.size &&
		snake.coor[0].y >= food.y - food.size && snake.coor[0].y <= food.y + food.size)
	{
		food.flag = false;
		snake.size++;
	}

	if(!food.flag) //��ʼ����һ��ʳ��
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
		Sleep(50); //�ӻ�50����
	}

	return 0;
}