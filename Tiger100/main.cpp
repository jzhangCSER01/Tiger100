/*
�������� microsoft visual studio 2022 + EasyX ͼ�ο�
*/

#include<stdio.h>
#include<easyx.h>
#include<time.h>
#pragma comment(lib, "winmm.lib")

#define MAX_BOARD 11	//��������

/*@��� С��(����, ��ɫ, �뾶)*/
struct Gamer
{
	int x;
	int y;
	int r;	//�뾶
	int index;	//������ڰ��ӵ��±�
	int vy;	//y�����ٶȱ仯��
	COLORREF color;	//��ɫ
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
	//��� ����С��
	solidcircle(gm->x, gm->y, gm->r);
}

/*
* ��������ƶ�
*/
void gamer_keyMsg(Gamer* gm) {
	//��ȡ���̰���
	if (GetAsyncKeyState(VK_LEFT))	//�������
	{
		gm->x -= 2;
	}
	if (GetAsyncKeyState(VK_RIGHT))	//�Ҽ�����
	{
		gm->x += 2;
	}
}

/*@���� ���� ��� �߶� ��ɫ*/
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
	b->h = 10;	//�̶��߶�
	b->color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void board_draw(Board* b) {
	setfillcolor(b->color);
	//���ƾ���
	solidroundrect(b->x, b->y, b->x + b->w, b->y + b->h, 5, 5);
}

void board_move(Board* b) {
	//���� y ��С
	b->y -= 1;
}

Gamer gamer;	//���
Board board[MAX_BOARD];	//��������
void init() {
	
	//��ʼ������
	for (int i = 0; i < MAX_BOARD; i++)
	{
		int w = rand() % 100 + 50;	//�� 50 �� 150 [50, 150)
		int x = rand() % (getwidth() - w);	//[0, 760)
		if (i == 0)	//��һ�����
		{
			board[i].y = 100;
		}
		else
		{
			board[i].y = board[i - 1].y + 60;	//��������
		}
		board_init(board + i, x, board[i].y, w);
	}
	//��ʼ�����
	int x = board[0].x + rand() % (board->w - gamer.r);
	int y = board[0].y;
	gamer_init(&gamer, x, y, 10);
}

void draw() {
	gamer_draw(&gamer);
	//���ư���
	for (int i = 0; i < MAX_BOARD; i++)
	{
		board_draw(board + i);
	}
}

//���ݸ���
void update() {
	for (int i = 0; i < MAX_BOARD; i++)
	{
		board_move(board + i);
		//������ӳ����˴��ڷ�Χ(��������) ��������������������
		if (board[i].y + board[i].h <= 0)
		{
			board[i].y = MAX_BOARD * 60;
			int w = rand() % 100 + 50;	//�� 50 �� 150 [50, 150)
			int x = rand() % (getwidth() - w);	//[0, 760)
			board_init(board + i, x, board[i].y, w);
		}
	}
	Sleep(10);
}

//��������Ű��ӵ��ƶ����ƶ�
void followBoard() {
	//�ҵ�������ĸ�������
	for (int i = 0; i < MAX_BOARD; i++)
	{
		if (gamer.x >= board[i].x && gamer.x <= board[i].x + board[i].w && gamer.y + gamer.r >= board[i].y - 5 && gamer.y + gamer.r <= board[i].y + 5)
		{
			gamer.index = i;	//��¼���ڰ����±�
			break;
		}
		else
		{
			gamer.index = -1;	//���ڰ�����
		}
	}
	//�ж��ǲ����ڰ�����
	if (gamer.index == -1)	//������
	{
		gamer.y += gamer.vy;
		//�𽥱��
		if (gamer.vy < 10)
		{
			gamer.vy++;
		}
		
	}
	else
	{
		gamer.vy = 1;	//�����ٶȱ仯
		gamer.y = board[gamer.index].y - gamer.r;	//��������ƶ�
	}
}

int main()
{
	//�������ڣ�����ͼ�Σ�ͼƬ...��
	initgraph(760, 640);
	//�������������
	srand(time(NULL));

	/*
	* solidrectangle ����������ڻ��ޱ߿��������
	* void solidrectangle(
	*	int left,
	*	int top,
	*	int right,
	*	int bottom
	* );
	* left ������ x ����
	* top ���ζ��� y ����
	* right �����Ҳ� x ����
	* bottom ���εײ� y ����
	*/
	//����ͼ��
	//���������ɫ ��ԭɫ r g b
	setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//solidrectangle(10, 10, 10 + 20, 10 + 20);

	init();
	draw();
	getchar();
	//PlaySound(L"res/go.wav", NULL, SND_ASYNC | SND_FILENAME);
	//Sleep(1000);	//�ӳ�һ��
	//ѭ����
	while (true)
	{
		BeginBatchDraw();	//˫����
		cleardevice();	//������
		draw();
		EndBatchDraw();	//����˫����
		update();
		followBoard();
		gamer_keyMsg(&gamer);
	}
	getchar();
	return 0;
}