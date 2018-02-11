#include "base.h"
#include "snack.h"
#include "screen.h"
#include <stdio.h>
#include <conio.h>

void pause(unsigned char begin, int *);

Box Game_Box = {            //��Ϸ�����Ϣ
	{ "-", "=", "|", "|", "+", "+", "+", "+" },
	{ BOX_LEFT, BOX_TOP },
	{ BOX_LEFT + GAME_MAP_WIDTH + 1, BOX_TOP + GAME_MAP_HEIGHT + 1 }
};

Box Menu_Box = {            //�˵���
	{ "*", "*", "*", "*", "*", "*", "*", "*" },
	{ MENU_LEFT, MENU_TOP },
	{ MENU_LEFT + 30 + 1, MENU_TOP + 13 }
};

Box Tip_Box = {             //��ʾ��
	{ "x", "x", "\\", "\\", "x", "x", "x", "x" },
	{ TIP_LEFT, TIP_TOP },
	{ TIP_LEFT + 30 + 1, TIP_TOP + 6 }
};

int main()
{
	/* ��ʼ��һЩ���� */
	extern Snack snack;

	while (1) {
		initSnack();
		initScreen();
		box(Game_Box.lu, Game_Box.rd, &Game_Box.style, "̰ʳ��");
		pmenu(&Menu_Box);
		ptip(&Tip_Box, 0);
		pgame(&Game_Box);

		gameMessage("���������ʼ");
		_getch();

		int paused = 0;
		unsigned char c = KEY_RIGHT;
		while (1) {
			if (_kbhit()) {
				c = _getch();
				if (c == 224)   //���Ϊ�����������������ַ�����һ��Ϊ224
					c = _getch();

				switch (c) {
				case 'w':
				case 'W':
				case KEY_UP:
					chDirection(up);
					break;

				case 's':
				case 'S':
				case KEY_DOWN:
					chDirection(down);
					break;

				case 'a':
				case 'A':
				case KEY_LEFT:
					chDirection(left);
					break;

				case 'd':
				case 'D':
				case KEY_RIGHT:
					chDirection(right);
					break;
				case ' ':
					ptip(&Tip_Box, paused = !paused);
					gameMessage("����ͣ����space����");
					pause(' ', &paused);
					break;
				}
			}

			pgame(&Game_Box);		//���в���ӡ��Ϸ����
			pmenu(&Menu_Box);		//
#ifndef GODMODE
			if (dead())				//����
                break;
#endif

			Sleep(snack.speed);
			//fflush(stdin);
		}

		destorySnack();

		gameMessage("��Ϸ���������ո����¿�ʼ");
		while(_getch() != ' ');
	}
	return 0;
}

void pause(unsigned char begin, int *paused)   //��ͣ�����ܵ�begin����
{
	while (1)
		if (_kbhit())
			if (_getch() == begin) {
				ptip(&Tip_Box, *paused = !*paused);
				break;
			}
}
