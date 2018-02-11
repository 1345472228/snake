#pragma once
#ifndef _SCREEN_H
#define _SCREEN_H

#include <windows.h>
#include "base.h"

void initScreen();
static void hideCursor();
void gotoXY(int x, int y);						//移动光标

void refreshRegion(COORD a, COORD b);			//刷新区域
void refreshGameRegion();						//刷新游戏区域

void chPoint(int x, int y, unsigned char c);	//改变一个点的内容
void box(COORD lu, COORD rd, BoxStyle *style, char title[]);	//打印周围的框
void gotoCoord(COORD coord);

#endif
