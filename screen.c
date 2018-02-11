#include "base.h"
#include "screen.h"
#include <conio.h>
#include <stdio.h>

static HANDLE hOut;		//标准输出句柄
static COORD coord;		//光标坐标


void initScreen()   //初始化屏幕
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//屏幕句柄
	coord.X = coord.Y = 0;						//光标坐标
	hideCursor();								//隐藏光标
}

void gotoXY(int x, int y)	//改变光标坐标到(x, y)
{
	coord.X = x, coord.Y = y;
	SetConsoleCursorPosition(hOut, coord);
}

void gotoCoord(COORD coord)
{
	SetConsoleCursorPosition(hOut, coord);
}

void box(COORD lu, COORD rd, BoxStyle *style, char title[])	//边框
{
	int i;

	gotoCoord(lu);								//上边框
	printf("%s", style->left_up);
	for (i = lu.X + 1; i < rd.X; i++) {
		gotoXY(i, lu.Y);
		printf("%s", style->up_line);
	}
	gotoXY(rd.X, lu.Y);
	printf("%s", style->right_up);

	gotoXY(lu.X, rd.Y);							//下边框
	printf("%s", style->left_down);
	for (i = lu.X + 1; i < rd.X; i++) {
		gotoXY(i, rd.Y);
		printf("%s", style->down_line);
	}
	gotoCoord(rd);
	printf("%s", style->right_down);

	for (i = lu.Y + 1; i < rd.Y; i++) {			//左边框
		gotoXY(lu.X, i);
		printf("%s", style->left_line);
	}

	for (i = lu.Y + 1; i < rd.Y; i++) {			//右边框
		gotoXY(rd.X, i);
		printf("%s", style->right_line);
	}

	if (title != NULL){							//标题
		gotoXY(lu.X + 2, lu.Y);
		printf("%s", title);
	}
}

static void hideCursor()		// 隐藏光标
{
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOut, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = 0; //隐藏控制台光标
	SetConsoleCursorInfo(hOut, &CursorInfo);//设置控制台光标状态
}

void refreshRegion(COORD a, COORD b)	//刷新以a为左上角，b为右下角的区域
{
	int tmp;
	if (a.X < b.X && a.Y < b.Y) {		//有效区域
		int lenW = b.X - a.X;
		for (; a.Y < b.Y; a.Y++) {
			FillConsoleOutputCharacterA(hOut, ' ', lenW, a, &tmp);
		}
	}
}


void chPoint(int x, int y, unsigned char c) {
	//改变一个点的内容，
	//可能不是ascii
	gotoXY(x, y);
	printf("%c", c);
}
