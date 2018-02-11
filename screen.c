#include "base.h"
#include "screen.h"
#include <conio.h>
#include <stdio.h>

static HANDLE hOut;		//��׼������
static COORD coord;		//�������


void initScreen()   //��ʼ����Ļ
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//��Ļ���
	coord.X = coord.Y = 0;						//�������
	hideCursor();								//���ع��
}

void gotoXY(int x, int y)	//�ı������굽(x, y)
{
	coord.X = x, coord.Y = y;
	SetConsoleCursorPosition(hOut, coord);
}

void gotoCoord(COORD coord)
{
	SetConsoleCursorPosition(hOut, coord);
}

void box(COORD lu, COORD rd, BoxStyle *style, char title[])	//�߿�
{
	int i;

	gotoCoord(lu);								//�ϱ߿�
	printf("%s", style->left_up);
	for (i = lu.X + 1; i < rd.X; i++) {
		gotoXY(i, lu.Y);
		printf("%s", style->up_line);
	}
	gotoXY(rd.X, lu.Y);
	printf("%s", style->right_up);

	gotoXY(lu.X, rd.Y);							//�±߿�
	printf("%s", style->left_down);
	for (i = lu.X + 1; i < rd.X; i++) {
		gotoXY(i, rd.Y);
		printf("%s", style->down_line);
	}
	gotoCoord(rd);
	printf("%s", style->right_down);

	for (i = lu.Y + 1; i < rd.Y; i++) {			//��߿�
		gotoXY(lu.X, i);
		printf("%s", style->left_line);
	}

	for (i = lu.Y + 1; i < rd.Y; i++) {			//�ұ߿�
		gotoXY(rd.X, i);
		printf("%s", style->right_line);
	}

	if (title != NULL){							//����
		gotoXY(lu.X + 2, lu.Y);
		printf("%s", title);
	}
}

static void hideCursor()		// ���ع��
{
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOut, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = 0; //���ؿ���̨���
	SetConsoleCursorInfo(hOut, &CursorInfo);//���ÿ���̨���״̬
}

void refreshRegion(COORD a, COORD b)	//ˢ����aΪ���Ͻǣ�bΪ���½ǵ�����
{
	int tmp;
	if (a.X < b.X && a.Y < b.Y) {		//��Ч����
		int lenW = b.X - a.X;
		for (; a.Y < b.Y; a.Y++) {
			FillConsoleOutputCharacterA(hOut, ' ', lenW, a, &tmp);
		}
	}
}


void chPoint(int x, int y, unsigned char c) {
	//�ı�һ��������ݣ�
	//���ܲ���ascii
	gotoXY(x, y);
	printf("%c", c);
}
