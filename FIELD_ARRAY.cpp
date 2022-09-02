#include "FIELD_ARRAY.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

/*
*コンストラクタ
*/
FIELD_ARRAY::FIELD_ARRAY() {
	for (int i = 0; i < FIELD_HEIGHT * FIELD_WIDTH; ++i) {
		field[i] = ' ';
	}
}

char FIELD_ARRAY::at(int x, int y) {
	return field[y * FIELD_WIDTH + x];
}

/*
*コンソールに色付きで出力する
*/
void FIELD_ARRAY::showColor(char x) {
	if ('A' <= x && x <= 'Z') x += 32;
	if (x == '@') printf("\033[37m%c \033[m", x); // お邪魔ぷよ
	else if (x == 'r' || x == 'R') printf("\033[31m●\033[m"); // RED
	else if (x == 'g') printf("\033[32m●\033[m"); // GREEN
	else if (x == 'y') printf("\033[33m●\033[m"); // YELLOW
	else if (x == 'b') printf("\033[34m●\033[m"); // BLUE, but cyan(m36) could be better to watch
	else if (x == 'p') printf("\033[35m●\033[m"); // magenta(purple)
	else if (x == '*') printf("\033[37m* \033[m"); // "*" for discribe cursol position
	else printf("%c ", x);
	/* cout << "\033[30m black \033[m" << endl;
	cout << "\033[31m red \033[m" << endl;
	cout << "\033[32m green \033[m" << endl;
	cout << "\033[33m yellow \033[m" << endl;
	cout << "\033[34m blue \033[m" << endl;
	cout << "\033[35m magenta \033[m" << endl;
	cout << "\033[36m cyan \033[m" << endl;
	cout << "\033[37m white \033[m" << endl; */
	return;
}

/*
*フィールドを描画する
*/

void FIELD_ARRAY::show() {
	system("cls"); // コンソールをクリアする
	for (int i = 0; i < FIELD_HEIGHT * FIELD_WIDTH; ++i) {
		if (i % FIELD_WIDTH == 0) printf("||");
		FIELD_ARRAY::showColor(field[i]);
		if (i % FIELD_WIDTH == 5) printf("||\n"); // フィールドの幅で改行
	}
	for (int i = 0; i < 2 * FIELD_WIDTH + 4; ++i) printf("=");
	printf("\n");
	std::cout << std::endl;
}

void FIELD_ARRAY::show(bool isFlush = true) {
	if (isFlush) system("cls"); // コンソールをクリアする
	for (int i = 0; i < FIELD_HEIGHT * FIELD_WIDTH; ++i) {
		if (i % FIELD_WIDTH == 0) printf("||");
		FIELD_ARRAY::showColor(field[i]);
		if (i % FIELD_WIDTH == 5) printf("||\n"); // フィールドの幅で改行
	}
	for (int i = 0; i < 2 * FIELD_WIDTH + 4; ++i) printf("=");
	printf("\n");
	std::cout << std::endl;
}

/*
*フィールドを描画する
* マウスカーソルの位置ならばアスタリスクを表示する
*/
void FIELD_ARRAY::show_with_cursol(int x, int y) {
	system("cls"); // コンソールをクリアする
	int nowPos = y * FIELD_WIDTH + x;
	for (int i = 0; i < FIELD_HEIGHT * FIELD_WIDTH; ++i) {
		if (i % FIELD_WIDTH == 0) printf("||");
		if(i == nowPos) FIELD_ARRAY::showColor('*');
		else FIELD_ARRAY::showColor(field[i]);
		if (i % FIELD_WIDTH == 5) printf("||\n"); // フィールドの幅で改行
	}
	for (int i = 0; i < 2 * FIELD_WIDTH + 4; ++i) printf("=");
	printf("\n");
	std::cout << std::endl;
}

/*
*フィールドにぷよを設置する
*/
void FIELD_ARRAY::set_puyo(int x, int y, char puyoColor) {
	int nowPos = y * FIELD_WIDTH + x;
	if (nowPos > FIELD_HEIGHT * FIELD_WIDTH) {
		printf("(%d, %d) is out of array\n", x, y);
		return;
	}
	field[nowPos] = puyoColor;
}

void FIELD_ARRAY::pop_top(int x) {
	for (int i = 0; i < FIELD_HEIGHT; ++i) {
		if (at(x, i) == ' ' || at(x, i) == '@') continue;
		else {
			FIELD_ARRAY::set_puyo(x, i, ' ');
			break;
		}
	}

}




void FIELD_ARRAY::set_template(std::string key) {
	if (key == "0") return;
	else if (key == "fallTest") {
		for (int j = 0; j < FIELD_WIDTH; ++j) FIELD_ARRAY::set_puyo(j, 0, 'r');
		for (int j = 0; j < FIELD_WIDTH; ++j) FIELD_ARRAY::set_puyo(j, 3, 'b');
		for (int j = 0; j < FIELD_WIDTH; ++j) FIELD_ARRAY::set_puyo(j, 5, 'g');
	}
	else if (key == "test4") { // テスト用の4手謎ぷよ
		FIELD_ARRAY::set_puyo(1, 12, 'r');
		FIELD_ARRAY::set_puyo(1, 11, 'r');
		FIELD_ARRAY::set_puyo(1, 10, 'b');
		FIELD_ARRAY::set_puyo(1, 9, 'b');

		FIELD_ARRAY::set_puyo(2, 12, 'y');
		FIELD_ARRAY::set_puyo(2, 11, 'y');
		FIELD_ARRAY::set_puyo(2, 10, 'b');
		FIELD_ARRAY::set_puyo(2, 9, 'y');

		FIELD_ARRAY::set_puyo(3, 12, 'r');
		FIELD_ARRAY::set_puyo(3, 11, 'r');
		FIELD_ARRAY::set_puyo(3, 10, 'g');
		FIELD_ARRAY::set_puyo(3, 9, 'g');

		FIELD_ARRAY::set_puyo(4, 12, 'b');
		FIELD_ARRAY::set_puyo(4, 11, 'b');
		FIELD_ARRAY::set_puyo(4, 10, 'g');
		FIELD_ARRAY::set_puyo(4,  9, 'r');
	}
	else if (key == "test5") {
		FIELD_ARRAY::set_puyo(2, 12, 'g');
		FIELD_ARRAY::set_puyo(2, 11, 'g');
		FIELD_ARRAY::set_puyo(2, 10, 'y');

		FIELD_ARRAY::set_puyo(3, 12, 'r');
		FIELD_ARRAY::set_puyo(3, 11, 'y');
		FIELD_ARRAY::set_puyo(3, 10, 'y');
		FIELD_ARRAY::set_puyo(3,  9, 'g');

		FIELD_ARRAY::set_puyo(4, 12, 'r');
		FIELD_ARRAY::set_puyo(4, 11, 'r');
		FIELD_ARRAY::set_puyo(4, 10, 'b');
		FIELD_ARRAY::set_puyo(4,  9, 'b');
		FIELD_ARRAY::set_puyo(4,  8, 'r');
		FIELD_ARRAY::set_puyo(4,  7, 'r');

		FIELD_ARRAY::set_puyo(5, 12, 'g');
		FIELD_ARRAY::set_puyo(5, 11, 'g');
		FIELD_ARRAY::set_puyo(5, 10, 'g');
		FIELD_ARRAY::set_puyo(5,  9, 'b');
		FIELD_ARRAY::set_puyo(5,  8, 'g');
	}
	else if (key == "kenny") {
		std::vector<std::vector<char>> kenny = {
{' ', ' ', 'y', 'p', 'g', 'g'},
{'y', 'b', 'b', 'y', 'p', 'b'},
{'p', 'b', 'y', 'p', 'g', 'g'},
{'y', 'b', 'y', 'p', 'g', 'b'},
{'p', 'g', 'b', 'y', 'p', 'b'},
{'g', 'b', 'y', 'p', 'g', 'b'},
{'p', 'g', 'b', 'y', 'p', 'g'},
{'p', 'g', 'b', 'y', 'p', 'g'},
{'p', 'y', 'y', 'b', 'y', 'b'},
{'y', 'g', 'b', 'p', 'b', 'b'},
{'p', 'y', 'g', 'b', 'p', 'y'},
{'p', 'y', 'g', 'b', 'p', 'y'},
{'p', 'y', 'g', 'b', 'p', 'y'},
		};
		for (int i = 0; i < FIELD_HEIGHT; ++i) {
			for (int j = 0; j < FIELD_WIDTH; ++j) {
				FIELD_ARRAY::set_puyo(j, i, kenny[i][j]);
			}
		}
	}
	else {
		std::cout << "no such keyword as " << key << std::endl;
	}
}
