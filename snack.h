#pragma once
#ifndef _SNACK_H
#define _SNACK_H
#include "base.h"

void initSnack();
Atom *createAtom();  //����һ���ߵĽڵ�
void addToHead(Atom *);  //��һ���ڵ���ӵ���ͷ
Atom *cutTail();    /*ɾ����β���������ٽڵ㣬����ɾ��
					�Ľڵ�ָ�룬��������ʹ�ã�����Ϊ��һ�ε���ͷ*/

Food *randFood(int value, unsigned char c);  // ������ֵΪvalue����ʽΪc�����ʳ��
int eatIt(Food *);   //�жϴ�������food�Ƿ񱻳Ե�

void step();  //����һ��
int dead();     //�Ƿ�����
void chDirection(enum direction); //�ı䷽��
int destorySnack();

void gameMessage(char s[]);			//����Ϸ���ڴ�ӡ��ʾ��Ϣ
void pgame(Box *);
void pmenu(Box *);								//��ӡ�˵�
void ptip(Box *, int);								//��ӡ��ʾ

void refreshGameRegion();				//ˢ����Ϸ����

#endif
