#include "snack.h"
#include "screen.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

Snack snack;

//��Ϸ��������Ͻ�����
COORD gameLT = { BOX_LEFT + 1, BOX_TOP + 1 };
//���½�
COORD gameRB = { BOX_LEFT + GAME_MAP_WIDTH + 1, BOX_TOP + GAME_MAP_HEIGHT + 1 };


void initSnack()   //��ʼ��
{
	snack.head = 0,
	snack.tail = 0,
	snack.speed = SPEED,
	snack.length = 0,
	snack.face = FACE;
	Atom *tail = createAtom();   //����β���ڵ�
	tail->c = TAIL, tail->x = SNACK_TAIL_X, tail->y = SNACK_TAIL_Y, tail->next = tail->prev = NULL;   //��ʼ��β���ڵ�
	snack.head = snack.tail = tail;  // ͷβΪͬһ���ڵ�

	int i;
	for (i = 0; i < LEN - 1; i++) //����LEN - 1���ڵ�
		addToHead(createAtom());  //����Ϊͷ���
}

Atom *createAtom()   // ����һ���ڵ�
{
	Atom *a = (Atom*)malloc(sizeof(Atom));
	a->c = BODY;
	return a;
}

void addToHead(Atom *a)   //��һ���ڵ�����Ϊͷ���
{
	a->next = snack.head; //��ͷ����ǰ��
	a->prev = NULL;
	a->c = HEAD;
	snack.head->prev = a;  //��ǰ��ͷ���ǰ��ָ���½ڵ�
	if (snack.head != snack.tail)   //Ϊ�˱�֤������ʾ��β�ڵ����ʽ
		snack.head->c = BODY;   //����ǰ����ͷ����Ϊ����

	switch (snack.face) {   //�ж�������
	case right:
		a->x = (snack.head->x + 1) % GAME_MAP_WIDTH;  //��ģ����ʵ��ѭ����ǽ
		a->y = snack.head->y;
		break;

	case left:
		if (snack.head->x == 0) //�Ѿ�����ǽ��
			a->x = GAME_MAP_WIDTH - 1;   //��Ϊ���ұ�
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
	snack.head = a;  //������ͷ
	snack.length++;  //���ȼ�1
}

int eatIt(Food *food)   //�ж��ܷ�Ե�ʳ�����ֱ�ӳԵ�����������ˢ����Ļ������1�����оͷ���0
{
	if (food != NULL) {
		if (food->x == snack.head->x && food->y == snack.head->y) {  //���ԳԵ�
			addToHead(createAtom());   //������ͷ
			snack.score += food->value;   //����������ʳ��ļ�ֵ
			chPoint(food->x, food->y, ' ');   //����ʳ����ַ�
			free(food);  //�ͷ�ʳ����ڴ�
			return 1;
		}
	}
	return 0;
}

Food *randFood(int value, unsigned char c)   //�������λ�õ�ʳ��ַ��ͼ�ֵ�ɲ�������
{
	Food *food = (Food*)malloc(sizeof(Food));
begin:
	srand((unsigned)time(NULL));
	food->x = rand() % (GAME_MAP_WIDTH - 1);
	food->y = rand() % (GAME_MAP_HEIGHT - 1);

	Atom *curr = snack.head;		//�����鿴�Ƿ�������ص�
	while (curr != NULL) {
		if (curr->x == food->x && curr->y == food->y)
			goto begin;
		curr = curr->next;
	}

	food->c = c;
	food->value = value;
	return food;
}

Atom *cutTail()   //����β��
{
	if (snack.tail != snack.head) {
		Atom *temp = snack.tail;   //���ݵ�ǰ��β����������ֵ����������ʹ�ã�����Ϊ��һ�ε���ͷ
		snack.tail->prev->next = NULL;  //��ǰһ���ڵ����Ϊ��β
		snack.tail->prev->c = TAIL;
		snack.tail = snack.tail->prev;

		snack.length--;   //���ȼ�һ
		return temp;
	}
	return NULL;
}

void step()  //����
{
	addToHead(cutTail());   //����β�ͣ������ڵ㣬��Ϊ�µ�ͷ
}

int dead()  //�ж��Ƿ�����
{
	//����X*Y��С�����飬���ߵ�����ͨ��������䵽���棬���ص�������
	char MAP[GAME_MAP_HEIGHT][GAME_MAP_WIDTH] = { {0} };
	Atom *curr = snack.head;
	while (curr != NULL) {  //��������
		if (MAP[curr->y][curr->x] == 0) {
			MAP[curr->y][curr->x]++;
		}
		else
			return 1; //�������Լ������壬����
		curr = curr->next;
	}
	return 0;
}

void chDirection(enum direction i)  //�ı䷽��
{
	if ((i - snack.face) % 2 != 0) {   //ֻ�з������ڲ���ת
		snack.face = i;
	}
}

int destorySnack()   //�ͷ������ڴ�
{
	Atom *curr = snack.head;
	while (curr != NULL) {
		Atom *x = curr->next;
		free(curr);
		curr = x;
	}
	return 1;
}

void printSnack()				//��������ȫ����ӡ
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

void gameMessage(char s[])			//����Ϸ���ڴ�ӡ��ʾ��Ϣ
{
	gotoXY(BOX_LEFT + 10, BOX_TOP + 5);
	printf("%s", s);
}

void pgame(Box *game_box)
{
	static int eated = 0;				//�Ѿ����ӵĳ���

	static Food *food;
	static boxed = 0;
	if (boxed == 0) {
		box(game_box->lu, game_box->rd, &game_box->style, "/̰ʳ��\\");
		boxed = 1;
	}
	// boxed = (boxed + 1) % 10;		//ÿ10��ˢ��һ�α߿�

	if (eated == 0 || eatIt(food)) {	//�Ե�ʳ��
		eated += 1;						//����һ����һ
		if(snack.speed > 20)
			snack.speed -= 5;
		if(eated == 0 || eated % 5 != 0)
			food = randFood(10, FOOD);		//���������һ��
		else {
			food = randFood(20, BIG_FOOD);		//������ɽ���ʳ��
		}
	}

	refreshGameRegion();				//ˢ����Ϸ����
	step();
	printFood(food);
	printSnack();
}

void pmenu(Box *menu_box)
{
	static int boxed = 0;

	if (boxed == 0) {
		box(menu_box->lu, menu_box->rd, &menu_box->style, "�Ƿְ�");
		boxed = 1;
	}
	// boxed = (boxed + 1) % 10;		//ÿ10��ˢ��һ�α߿�

	gotoXY(menu_box->lu.X + 4, menu_box->lu.Y + 3);
	printf("�÷֣�\t%d\t", snack.score);
	gotoXY(menu_box->lu.X + 4, menu_box->lu.Y + 5);
	printf("�ٶȣ�\t%.4lf\t", (1 / (double)snack.speed) * 100);
	gotoXY(menu_box->lu.X + 4, menu_box->lu.Y + 7);
	printf("���ȣ�\t%d\t", snack.length);
	gotoXY(menu_box->lu.X + 4, menu_box->lu.Y + 9);
	printf("����\t%d\t", (snack.length - LEN + 1) / 5 + 1);
}

void ptip(Box *tip_box, int paused)
{
	static boxed = 0;
	if (boxed == 0){
        #ifdef GODMODE
            box(tip_box->lu, tip_box->rd, &tip_box->style, "��ʾ���ϵ�ģʽ��");
        #else
            box(tip_box->lu, tip_box->rd, &tip_box->style, "��ʾ");
        #endif
	}
	boxed = (boxed + 1) % 10;		//ÿ10��ˢ��һ�α߿�

	if (paused) {
		gotoXY(tip_box->lu.X + 3, tip_box->lu.Y + 2);
		printf("*��ͣ��\tspace");
	}
	else {
		gotoXY(tip_box->lu.X + 3, tip_box->lu.Y + 2);
		printf(" ��ͣ��\tspace");
	}

	gotoXY(tip_box->lu.X + 4, tip_box->lu.Y + 4);
	printf("�ƶ���\t�������wasd");
}

void refreshGameRegion()				//ˢ����Ϸ����
{
	refreshRegion(gameLT, gameRB);
}
