#pragma once
#ifndef _SCREEN_H
#define _SCREEN_H

#include <windows.h>
#include "base.h"

void initScreen();
static void hideCursor();
void gotoXY(int x, int y);						//�ƶ����

void refreshRegion(COORD a, COORD b);			//ˢ������
void refreshGameRegion();						//ˢ����Ϸ����

void chPoint(int x, int y, unsigned char c);	//�ı�һ���������
void box(COORD lu, COORD rd, BoxStyle *style, char title[]);	//��ӡ��Χ�Ŀ�
void gotoCoord(COORD coord);

#endif
