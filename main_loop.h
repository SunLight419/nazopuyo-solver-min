#pragma once
#include <iostream>
#include <conio.h> // for _getch()
#include <stdlib.h>  // for system("slc")
#include <Windows.h>
#include <chrono>
#include <unordered_set>
#include <map>
#include <string>
#include "FIELD_ARRAY.h"
#include "CHAIN.h"
#include "CHAIN_BITSET.h"
#include "nazopuyo_single.h"

// CUIŒn‚Ì‚ ‚ê‚±‚ê

class main_loop
{
public:
	std::unordered_set<char> uset_puyocolor{ ' ', 'r', 'g', 'b', 'y', 'p', '@' };
	std::unordered_set<char> uset_move{ 'w', 'a', 's', 'd' };
	std::map<char, std::string> menu;
	main_loop();
	void show_menu();
	void move_cursol(nazopuyo_single& nazo, int& x, int& y, char& user_opr);
	void main_show(nazopuyo_single& nazo, int x, int y);
	void main_setpuyo(nazopuyo_single& nazo, int& x, int& y, char& user_opr);
	void main_chainSim(nazopuyo_single& nazo);
	void main_solve_nazopuyo(nazopuyo_single& nazo);

	void main_operation(nazopuyo_single& nazo, int& cur_x, int& cur_y, char& user_opr);
};

