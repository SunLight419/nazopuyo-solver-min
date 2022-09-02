#include <iostream>
#include <conio.h> // for _getch()
#include <Windows.h>
#include <chrono>
#include <unordered_set>
#include "FIELD_ARRAY.h"
#include "CHAIN.h"
#include "CHAIN_BITSET.h"
#include "nazopuyo_single.h"
#include "main_loop.h"
using namespace std;


int main() {
	
	nazopuyo_single nazo;
	main_loop mp;

	nazo.set_template("test5");
	
	char user_opr;
	int cur_x = 0, cur_y = 0;
	while (true) {
		nazo.show();
		mp.show_menu();
		user_opr = _getch();
		if (user_opr == '0') break;
		else {
			mp.main_operation(nazo, cur_x, cur_y, user_opr);
		}
	}

	return 0;
}

int kennytest()
{

	cout << "Hello, world!" << endl;

    CHAIN field;

	field.set_template("kenny");
	field.show();
	cout << "kenny" << endl;
	cout << "Kenny bench start!" << endl;

	auto t_start = std::chrono::system_clock::now();
	int loopCount = 10000;

	for (int i = 0; i < loopCount; ++i) {
		field.set_template("kenny");
		field.chain_loop(false);
	}
	
	auto t_end = std::chrono::system_clock::now();
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
	cout << loopCount << " loop time of calc kenny 19 chain: ";
	cout << msec << " [ms]" << endl;
	cout << "AVERAGE: " << (double)msec / loopCount << " [ms]" << endl;

	
	getchar();

	return 0;
}

