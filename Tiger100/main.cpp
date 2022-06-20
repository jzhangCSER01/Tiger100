/*
开发环境 microsoft visual studio 2022 + EasyX 图形库
*/

#include<stdio.h>
#include<easyx.h>
#include<time.h>
#pragma comment(lib, "winmm.lib")

#define MAX_BOARD 11	//板子数量

/*@玩家 小球(坐标, 颜色, 半径)*/
struct Gamer
{
	int x;
	int y;
	int r;	//半径
	int index;	//玩家所在板子的下标
	int vy;	//y方向速度变化量
	COLORREF color;	//颜色
};

void gamer_init(Gamer* gm, int x, int y, int r) {
	gm->x = x;
	gm->y = y - r;
	gm->r = r;
	gm->color = RGB(rand() % 256, rand() % 256, rand() % 256);
	gm->index = -1;
	gm->vy = 1;
}

void gamer_draw(Gamer* gm) {

	setfillcolor(gm->color);
	//玩家 绘制小球
	solidcircle(gm->x, gm->y, gm->r);
}

/*
* 控制玩家移动
*/
void gamer_keyMsg(Gamer* gm) {
	//获取键盘按键
	if (GetAsyncKeyState(VK_LEFT))	//左键按下
	{
		gm->x -= 2;
	}
	if (GetAsyncKeyState(VK_RIGHT))	//右键按下
	{
		gm->x += 2;
	}
}

/*@板子 坐标 宽度 高度 颜色*/
struct Board
{
	int x;
	int y;
	int w;
	int h;
	COLORREF color;
};

void board_init(Board* b, int x, int y, int w) {
	b->x = x;
	b->y = y;
	b->w = w;
	b->h = 10;	//固定高度
	b->color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void board_draw(Board* b) {
	setfillcolor(b->color);
	//绘制矩形
	solidroundrect(b->x, b->y, b->x + b->w, b->y + b->h, 5, 5);
}

void board_move(Board* b) {
	//上升 y 减小
	b->y -= 1;
}

Gamer gamer;	//玩家
Board board[MAX_BOARD];	//板子数组
void init() {
	
	//初始化板子
	for (int i = 0; i < MAX_BOARD; i++)
	{
		int w = rand() % 100 + 50;	//从 50 到 150 [50, 150)
		int x = rand() % (getwidth() - w);	//[0, 760)
		if (i == 0)	//第一块板子
		{
			board[i].y = 100;
		}
		else
		{
			board[i].y = board[i - 1].y + 60;	//其它板子
		}
		board_init(board + i, x, board[i].y, w);
	}
	//初始化玩家
	int x = board[0].x + rand() % (board->w - gamer.r);
	int y = board[0].y;
	gamer_init(&gamer, x, y, 10);
}

void draw() {
	gamer_draw(&gamer);
	//绘制板子
	for (int i = 0; i < MAX_BOARD; i++)
	{
		board_draw(board + i);
	}
}

//数据更新
void update() {
	for (int i = 0; i < MAX_BOARD; i++)
	{
		board_move(board + i);
		//如果板子超出了窗口范围(看不到了) 让它从下面重新往上升
		if (board[i].y + board[i].h <= 0)
		{
			board[i].y = MAX_BOARD * 60;
			int w = rand() % 100 + 50;	//从 50 到 150 [50, 150)
			int x = rand() % (getwidth() - w);	//[0, 760)
			board_init(board + i, x, board[i].y, w);
		}
	}
	Sleep(10);
}

//让玩家随着板子的移动而移动
void followBoard() {
	//找到玩家在哪个板子上
	for (int i = 0; i < MAX_BOARD; i++)
	{
		if (gamer.x >= board[i].x && gamer.x <= board[i].x + board[i].w && gamer.y + gamer.r >= board[i].y - 5 && gamer.y + gamer.r <= board[i].y + 5)
		{
			gamer.index = i;	//记录所在板子下标
			break;
		}
		else
		{
			gamer.index = -1;	//不在板子上
		}
	}
	//判断是不是在板子上
	if (gamer.index == -1)	//下落中
	{
		gamer.y += gamer.vy;
		//逐渐变快
		if (gamer.vy < 10)
		{
			gamer.vy++;
		}
		
	}
	else
	{
		gamer.vy = 1;	//重置速度变化
		gamer.y = board[gamer.index].y - gamer.r;	//跟随板子移动
	}
}

int main()
{
	//创建窗口（绘制图形，图片...）
	initgraph(760, 640);
	//设置随机数种子
	srand(time(NULL));

	/*
	* solidrectangle 这个函数用于画无边框的填充矩形
	* void solidrectangle(
	*	int left,
	*	int top,
	*	int right,
	*	int bottom
	* );
	* left 矩形左部 x 坐标
	* top 矩形顶部 y 坐标
	* right 矩形右部 x 坐标
	* bottom 矩形底部 y 坐标
	*/
	//绘制图形
	//设置填充颜色 三原色 r g b
	setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//solidrectangle(10, 10, 10 + 20, 10 + 20);

	init();
	draw();
	getchar();
	//PlaySound(L"res/go.wav", NULL, SND_ASYNC | SND_FILENAME);
	//Sleep(1000);	//延迟一秒
	//循环中
	while (true)
	{
		BeginBatchDraw();	//双缓冲
		cleardevice();	//先清屏
		draw();
		EndBatchDraw();	//结束双缓冲
		update();
		followBoard();
		gamer_keyMsg(&gamer);
	}
	getchar();
	return 0;
}