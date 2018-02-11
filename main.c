#include "base.h"
#include "snack.h"
#include "screen.h"
#include <stdio.h>
#include <conio.h>

void pause(unsigned char begin, int *);

Box Game_Box = {            //游戏框的信息
	{ "-", "=", "|", "|", "+", "+", "+", "+" },
	{ BOX_LEFT, BOX_TOP },
	{ BOX_LEFT + GAME_MAP_WIDTH + 1, BOX_TOP + GAME_MAP_HEIGHT + 1 }
};

Box Menu_Box = {            //菜单框
	{ "*", "*", "*", "*", "*", "*", "*", "*" },
	{ MENU_LEFT, MENU_TOP },
	{ MENU_LEFT + 30 + 1, MENU_TOP + 13 }
};

Box Tip_Box = {             //提示框
	{ "x", "x", "\\", "\\", "x", "x", "x", "x" },
	{ TIP_LEFT, TIP_TOP },
	{ TIP_LEFT + 30 + 1, TIP_TOP + 6 }
};

int main()
{
	/* 初始化一些参数 */
	extern Snack snack;

	while (1) {
		initSnack();
		initScreen();
		box(Game_Box.lu, Game_Box.rd, &Game_Box.style, "贪食蛇");
		pmenu(&Menu_Box);
		ptip(&Tip_Box, 0);
		pgame(&Game_Box);

		gameMessage("按任意键开始");
		_getch();

		int paused = 0;
		unsigned char c = KEY_RIGHT;
		while (1) {
			if (_kbhit()) {
				c = _getch();
				if (c == 224)   //如果为方向键，会产生两个字符，第一个为224
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
					gameMessage("已暂停，按space继续");
					pause(' ', &paused);
					break;
				}
			}

			pgame(&Game_Box);		//运行并打印游戏界面
			pmenu(&Menu_Box);		//
#ifndef GODMODE
			if (dead())				//死亡
                break;
#endif

			Sleep(snack.speed);
			//fflush(stdin);
		}

		destorySnack();

		gameMessage("游戏结束，按空格重新开始");
		while(_getch() != ' ');
	}
	return 0;
}

void pause(unsigned char begin, int *paused)   //暂停，接受到begin继续
{
	while (1)
		if (_kbhit())
			if (_getch() == begin) {
				ptip(&Tip_Box, *paused = !*paused);
				break;
			}
}
