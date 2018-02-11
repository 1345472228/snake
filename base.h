#pragma once
#ifndef _BASE_H
#define _BASE_H
#include <windows.h>

#define GODMODE                     //�ϵ�ģʽ

//������Ļ
#define GAME_MAP_HEIGHT		20
#define GAME_MAP_WIDTH		60
#define BOX_TOP				4		//�߿򵽶����ľ���
#define BOX_LEFT			10		//�߿���ߵľ���

#define MENU_LEFT			BOX_LEFT + GAME_MAP_WIDTH + 1 + 5
#define MENU_TOP			BOX_TOP + 1 + 7
#define TIP_LEFT			MENU_LEFT
#define TIP_TOP				BOX_TOP

//�����ߵ�Ĭ�ϲ���
#define LEN					3       //�ߵĳ���
#define SPEED				200     //200msˢ��һ��
#define FACE				right   //����
#define SNACK_TAIL_X		15		//��ʼβ����λ��
#define SNACK_TAIL_Y		10
#define HEAD				'@'
#define TAIL				'q'
#define BODY				'O'
#define FOOD				'X'
#define BIG_FOOD			'%'

//����
#define KEY_UP				72
#define KEY_DOWN			80
#define KEY_RIGHT			77
#define KEY_LEFT			75


/* �ṩһЩ�����Ľṹ�� �� ö���� */
enum direction { up, right, down, left};

typedef struct Atom { //�ߵ�һ��
	char c; //��ʾ���ַ�
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

//���߶����һ������
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
