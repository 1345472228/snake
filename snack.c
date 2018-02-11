#include "snack.h"
#include "screen.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

Snack snack;

//游戏区域的左上角坐标
COORD gameLT = { BOX_LEFT + 1, BOX_TOP + 1 };
//右下角
COORD gameRB = { BOX_LEFT + GAME_MAP_WIDTH + 1, BOX_TOP + GAME_MAP_HEIGHT + 1 };


void initSnack()   //初始化
{
	snack.head = 0,
	snack.tail = 0,
	snack.speed = SPEED,
	snack.length = 0,
	snack.face = FACE;
	Atom *tail = createAtom();   //生成尾部节点
	tail->c = TAIL, tail->x = SNACK_TAIL_X, tail->y = SNACK_TAIL_Y, tail->next = tail->prev = NULL;   //初始化尾部节点
	snack.head = snack.tail = tail;  // 头尾为同一个节点

	int i;
	for (i = 0; i < LEN - 1; i++) //生成LEN - 1个节点
		addToHead(createAtom());  //设置为头结点
}

Atom *createAtom()   // 创建一个节点
{
	Atom *a = (Atom*)malloc(sizeof(Atom));
	a->c = BODY;
	return a;
}

void addToHead(Atom *a)   //将一个节点设置为头结点
{
	a->next = snack.head; //新头连向当前的
	a->prev = NULL;
	a->c = HEAD;
	snack.head->prev = a;  //当前的头结点前驱指向新节点
	if (snack.head != snack.tail)   //为了保证优先显示首尾节点的样式
		snack.head->c = BODY;   //将当前的蛇头设置为蛇身

	switch (snack.face) {   //判断面向方向
	case right:
		a->x = (snack.head->x + 1) % GAME_MAP_WIDTH;  //求模可以实现循环穿墙
		a->y = snack.head->y;
		break;

	case left:
		if (snack.head->x == 0) //已经到了墙边
			a->x = GAME_MAP_WIDTH - 1;   //设为最右边
		else
			a->x = (snack.head->x - 1) % GAME_MAP_WIDTH;

		a->y = snack.head->y;
		break;

	case up:
		if (snack.head->y == 0)
			a->y = GAME_MAP_HEIGHT - 1;
		else
			a->y = (snack.head->y - 1) % GAME_MAP_HEIGHT;
		a->x = snack.head->x;
		break;

	case down:
		a->y = (snack.head->y + 1) % GAME_MAP_HEIGHT;

		a->x = snack.head->x;
		break;
	}
	snack.head = a;  //产生新头
	snack.length++;  //长度加1
}

int eatIt(Food *food)   //判断能否吃到食物，可以直接吃掉增长蛇身，并刷新屏幕，返回1，不行就返回0
{
	if (food != NULL) {
		if (food->x == snack.head->x && food->y == snack.head->y) {  //可以吃到
			addToHead(createAtom());   //创建新头
			snack.score += food->value;   //给分数加上食物的价值
			chPoint(food->x, food->y, ' ');   //清理食物的字符
			free(food);  //释放食物的内存
			return 1;
		}
	}
	return 0;
}

Food *randFood(int value, unsigned char c)   //产生随机位置的食物，字符和价值由参数决定
{
	Food *food = (Food*)malloc(sizeof(Food));
begin:
	srand((unsigned)time(NULL));
	food->x = rand() % (GAME_MAP_WIDTH - 1);
	food->y = rand() % (GAME_MAP_HEIGHT - 1);

	Atom *curr = snack.head;		//遍历查看是否和蛇身重叠
	while (curr != NULL) {
		if (curr->x == food->x && curr->y == food->y)
			goto begin;
		curr = curr->next;
	}

	food->c = c;
	food->value = value;
	return food;
}

Atom *cutTail()   //剪掉尾巴
{
	if (snack.tail != snack.head) {
		Atom *temp = snack.tail;   //备份当前蛇尾，用作返回值，可以重新使用，如作为下一次的蛇头
		snack.tail->prev->next = NULL;  //将前一个节点的作为结尾
		snack.tail->prev->c = TAIL;
		snack.tail = snack.tail->prev;

		snack.length--;   //长度减一
		return temp;
	}
	return NULL;
}

void step()  //步进
{
	addToHead(cutTail());   //剪掉尾巴，保留节点，作为新的头
}

int dead()  //判断是否死亡
{
	//构造X*Y大小的数组，将蛇的身体通过坐标填充到里面，有重叠就死亡
	char MAP[GAME_MAP_HEIGHT][GAME_MAP_WIDTH] = { {0} };
	Atom *curr = snack.head;
	while (curr != NULL) {  //遍历链表
		if (MAP[curr->y][curr->x] == 0) {
			MAP[curr->y][curr->x]++;
		}
		else
			return 1; //碰到了自己的身体，死亡
		curr = curr->next;
	}
	return 0;
}

void chDirection(enum direction i)  //改变方向
{
	if ((i - snack.face) % 2 != 0) {   //只有方向相邻才能转
		snack.face = i;
	}
}

int destorySnack()   //释放整个内存
{
	Atom *curr = snack.head;
	while (curr != NULL) {
		Atom *x = curr->next;
		free(curr);
		curr = x;
	}
	return 1;
}

void printSnack()				//遍历蛇身，全部打印
{
	Atom *curr = snack.head;
	while (curr != NULL) {
		chPoint(curr->x + BOX_LEFT + 1, curr->y + BOX_TOP + 1, curr->c);
		curr = curr->next;
	}
}

void printFood(Food *food)
{
	chPoint(food->x + BOX_LEFT + 1, food->y + BOX_TOP + 1, food->c);
}

void gameMessage(char s[])			//向游戏框内打印提示信息
{
	gotoXY(BOX_LEFT + 10, BOX_TOP + 5);
	printf("%s", s);
}

void pgame(Box *game_box)
{
	static int eated = 0;				//已经增加的长度

	static Food *food;
	static boxed = 0;
	if (boxed == 0) {
		box(game_box->lu, game_box->rd, &game_box->style, "/贪食蛇\\");
		boxed = 1;
	}
	// boxed = (boxed + 1) % 10;		//每10轮刷新一次边框

	if (eated == 0 || eatIt(food)) {	//吃到食物
		eated += 1;						//吃了一个加一
		if(snack.speed > 20)
			snack.speed -= 5;
		if(eated == 0 || eated % 5 != 0)
			food = randFood(10, FOOD);		//随机生成另一个
		else {
			food = randFood(20, BIG_FOOD);		//随机生成奖励食物
		}
	}

	refreshGameRegion();				//刷新游戏区域
	step();
	printFood(food);
	printSnack();
}

void pmenu(Box *menu_box)
{
	static int boxed = 0;

	if (boxed == 0) {
		box(menu_box->lu, menu_box->rd, &menu_box->style, "记分板");
		boxed = 1;
	}
	// boxed = (boxed + 1) % 10;		//每10轮刷新一次边框

	gotoXY(menu_box->lu.X + 4, menu_box->lu.Y + 3);
	printf("得分：\t%d\t", snack.score);
	gotoXY(menu_box->lu.X + 4, menu_box->lu.Y + 5);
	printf("速度：\t%.4lf\t", (1 / (double)snack.speed) * 100);
	gotoXY(menu_box->lu.X + 4, menu_box->lu.Y + 7);
	printf("长度：\t%d\t", snack.length);
	gotoXY(menu_box->lu.X + 4, menu_box->lu.Y + 9);
	printf("级别：\t%d\t", (snack.length - LEN + 1) / 5 + 1);
}

void ptip(Box *tip_box, int paused)
{
	static boxed = 0;
	if (boxed == 0){
        #ifdef GODMODE
            box(tip_box->lu, tip_box->rd, &tip_box->style, "提示（上帝模式）");
        #else
            box(tip_box->lu, tip_box->rd, &tip_box->style, "提示");
        #endif
	}
	boxed = (boxed + 1) % 10;		//每10轮刷新一次边框

	if (paused) {
		gotoXY(tip_box->lu.X + 3, tip_box->lu.Y + 2);
		printf("*暂停：\tspace");
	}
	else {
		gotoXY(tip_box->lu.X + 3, tip_box->lu.Y + 2);
		printf(" 暂停：\tspace");
	}

	gotoXY(tip_box->lu.X + 4, tip_box->lu.Y + 4);
	printf("移动：\t方向键或wasd");
}

void refreshGameRegion()				//刷新游戏区域
{
	refreshRegion(gameLT, gameRB);
}
