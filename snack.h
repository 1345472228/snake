#pragma once
#ifndef _SNACK_H
#define _SNACK_H
#include "base.h"

void initSnack();
Atom *createAtom();  //创建一个蛇的节点
void addToHead(Atom *);  //将一个节点添加到蛇头
Atom *cutTail();    /*删除蛇尾，但不销毁节点，返回删除
					的节点指针，可以重新使用，如作为下一次的蛇头*/

Food *randFood(int value, unsigned char c);  // 创建价值为value，样式为c的随机食物
int eatIt(Food *);   //判断传进来的food是否被吃到

void step();  //行走一步
int dead();     //是否碰死
void chDirection(enum direction); //改变方向
int destorySnack();

void gameMessage(char s[]);			//向游戏框内打印提示信息
void pgame(Box *);
void pmenu(Box *);								//打印菜单
void ptip(Box *, int);								//打印提示

void refreshGameRegion();				//刷新游戏区域

#endif
