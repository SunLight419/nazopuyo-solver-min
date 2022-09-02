#include "main_loop.h"
#include <stdlib.h>  // for system("slc")

main_loop::main_loop() {
	//menu.emplace('1', "move");
	//menu.emplace('2', "chain simulator");
	//menu.emplace('3', "solve nazopuyo");
	//menu.emplace('4', "no define");
	//menu.emplace('0', "exit");
}

void main_loop::show_menu() {
	std::cout << "wasd: move, 1: set puyo, 2: chain simulation, 3, solve nazopuyo, 0: exit" << std::endl;
}

void main_loop::move_cursol(nazopuyo_single& nazo, int& x, int& y, char& user_opr) {
	if (uset_move.count(user_opr)) {
		if (user_opr == 'w' && y - 1 >= 0) --y;
		if (user_opr == 'a' && x - 1 >= 0) --x;
		if (user_opr == 's' && y + 1 < FIELD_HEIGHT) ++y;
		if (user_opr == 'd' && x + 1 < FIELD_WIDTH) ++x;
	}
}

void main_loop::main_show(nazopuyo_single& nazo, int x, int y) {
	system("cls");
	nazo.show_with_cursol(x, y);
}

void main_loop::main_setpuyo(nazopuyo_single& nazo, int& x, int& y, char& user_opr) {
	char myopr;
	while (true) {
		myopr = _getch();
		if (myopr == '0') break;
		if (uset_move.count(myopr)) {
			main_loop::move_cursol(nazo, x, y, myopr);
			main_loop::main_show(nazo, x, y);
		}
		if (uset_puyocolor.count(myopr)) {
			nazo.set_puyo(x, y, myopr);
			main_loop::main_show(nazo, x, y);
		}

	}
}

void main_loop::main_chainSim(nazopuyo_single& nazo) {
	int chanNum = 0;
	nazo.fall();
	chanNum = nazo.chain_loop(true);
	std::cout << chanNum << " chain!" << std::endl;
	_getch();
}

void main_loop::main_solve_nazopuyo(nazopuyo_single& nazo) {
	nazo.solve_nazopuyo();
	_getch();
}

void main_loop::main_operation(nazopuyo_single& nazo, int& cur_x, int& cur_y, char& user_opr) {
	if (user_opr == '1') main_loop::main_setpuyo(nazo, cur_x, cur_y, user_opr);
	if (user_opr == '2') main_loop::main_chainSim(nazo);
	if (user_opr == '3') main_loop::main_solve_nazopuyo(nazo);
}


