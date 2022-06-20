/*
开发环境 microsoft visual studio 2022 + EasyX 图形库
*/

#include<stdio.h>
#include<easyx.h>
int main()
{
	//创建窗口（绘制图形，图片...）
	initgraph(760, 640);

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
	//设置填充颜色
	setfillcolor(RED);
	solidrectangle(10, 10, 10 + 20, 10 + 20);

	getchar();
	return 0;
}