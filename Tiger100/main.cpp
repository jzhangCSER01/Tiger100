/*
�������� microsoft visual studio 2022 + EasyX ͼ�ο�
*/

#include<stdio.h>
#include<easyx.h>
int main()
{
	//�������ڣ�����ͼ�Σ�ͼƬ...��
	initgraph(760, 640);

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
	//���������ɫ
	setfillcolor(RED);
	solidrectangle(10, 10, 10 + 20, 10 + 20);

	getchar();
	return 0;
}