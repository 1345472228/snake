#pragma once
#ifndef _BASE_H
#define _BASE_H
#include <windows.h>

#define GODMODE                     //上帝模式

//设置屏幕
#define GAME_MAP_HEIGHT		20
#define GAME_MAP_WIDTH		60
#define BOX_TOP				4		//边框到顶部的距离
#define BOX_LEFT			10		//边框到左边的距离

#define MENU_LEFT			BOX_LEFT + GAME_MAP_WIDTH + 1 + 5
#define MENU_TOP			BOX_TOP + 1 + 7
#define TIP_LEFT			MENU_LEFT
#define TIP_TOP				BOX_TOP

//设置蛇的默认参数
#define LEN					3       //蛇的长度
#define SPEED				200     //200ms刷新一次
#define FACE				right   //朝向
#define SNACK_TAIL_X		15		//初始尾部的位置
#define SNACK_TAIL_Y		10
#define HEAD				'@'
#define TAIL				'q'
#define BODY				'O'
#define FOOD				'X'
#define BIG_FOOD			'%'

//按键
#define KEY_UP				72
#define KEY_DOWN			80
#define KEY_RIGHT			77
#define KEY_LEFT			75


/* 提供一些基本的结构体 和 枚举量 */
enum direction { up, right, down, left};

typedef struct Atom { //蛇的一节
	char c; //显示的字符
	int x;
	int y;
	struct Atom *prev;
	struct Atom *next;
}Atom;

typedef struct Food {
	char c;
	int x;
	int y;
	int value;
} Food;

//将蛇定义成一个链表
typedef struct Snack {
	Atom *head;
	Atom *tail;
	int speed;
	int length;
	int face;
	int score;
} Snack;

typedef struct BoxStyle {
	char up_line[4];
	char down_line[4];
	char left_line[4];
	char right_line[4];
	char left_up[4];
	char right_up[4];
	char left_down[4];
	char right_down[4];
} BoxStyle;

typedef struct Box {
	BoxStyle style;
	COORD lu;
	COORD rd;
} Box;

#endif
