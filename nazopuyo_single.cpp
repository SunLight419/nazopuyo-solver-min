#include "nazopuyo_single.h"
#include <chrono>
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

void nazopuyo_single::copy_field(std::array<char, FIELD_WIDTH* FIELD_HEIGHT>& from, std::array<char, FIELD_WIDTH* FIELD_HEIGHT>& to) {
	for (int i = 0; i < FIELD_HEIGHT * FIELD_WIDTH; ++i) {
		to[i] = from[i];
	}
}

void nazopuyo_single::show_nextPuyos() {
	for (int i = 0; i < 10; ++i) {
		cout << "[" << nextPuyos[i * 2] << ", " << nextPuyos[i * 2 + 1] << "], ";
	}
	cout << endl;
}

void nazopuyo_single::set_nextPuyo() {
	cout << "Input Next Puyo number: " << endl;
	int nxpuyo;
	cin >> nxpuyo;
	this->nextPuyoNum = nxpuyo;

	int cnt = 0;
	while (cnt < nxpuyo) {
		nazopuyo_single::show_nextPuyos();
		cout << "Input " << (cnt + 1) << "th next puyo: " << endl;
		string nxpuyos;
		cin >> nxpuyos;
		nextPuyos[cnt * 2] = nxpuyos[0];
		nextPuyos[cnt * 2 + 1] = nxpuyos[1];

		cnt++;
	}
}

void nazopuyo_single::set_goalChainNum() {
	int goalNum;

	cout << "Input goal chain number: " << endl;

	cin >> goalNum;

	goalChainNum = goalNum;
}

void nazopuyo_single::set_totalNodes() {
	int cnt = 0;
	totalNodes = 1;
	while (cnt < nextPuyoNum) {
		cnt++;
		totalNodes *= 22;
	}
}


// ���� DFS(�[���D��T��) �őS�T������
void nazopuyo_single::nazoDFS(int idx) {
	// idx = 0 ����X�^�[�g���A idx = �l�N�X�g�̐� �ɂȂ������A���V�~�����s��
	if (isAnswerFound) return;
	if (idx > nextPuyoNum) return;
	if (idx == nextPuyoNum) {
		// �r���o�ߕ\���p
		visitedNodes++;
		if (visitedNodes % 10000 == 0) {
			show();
			cout << "Now Solving ...   ";
			cout << ((double)visitedNodes / totalNodes * 100) << "[%] end" << endl;
			// �T�������m�[�h/�S�m�[�h
			// ���ۂ͎}��肪����̂ł����܂Ŗڈ��̊���
			cout << (visitedNodes / 1000) << "k Nodes visited" << endl;
		}
		// copy
		std::array<char, FIELD_WIDTH* FIELD_HEIGHT> beforeCopy;
		nazopuyo_single::copy_field(field, beforeCopy);

		int nowChainNum = chain_loop(false);
		if (nowChainNum == goalChainNum) {
			// �A�����ƖڕW�A��������v����ƏI���܂�
			isAnswerFound = true;
			nazopuyo_single::copy_field(beforeCopy, field);
			//nazopuyo_single::copy_field(beforeCopy, ansField);
			return;
		}
		// �T���������ꍇ�A�R�s�[���R�s�[���܂��B
		// chain_loop(), chainSim() �͔j��I�ȑ���ł��B������R�s�[������Ă����K�v����������ł��ˁB
		nazopuyo_single::copy_field(beforeCopy, field);


		return;
	}

	for (int j = 0; j < FIELD_WIDTH; ++j) {
		if (isAnswerFound) return;
		// for���ɂ��ׂ�?�����Ǐ�肭�����Ȃ�����
		if (at(j, 0) == ' ' && at(j, 1) == ' ') { // ������
			// A
			// B
			set_puyo(j, 0, nextPuyos[idx * 2]);
			set_puyo(j, 1, nextPuyos[idx * 2 + 1]);
			// �󔒂����邩���m�F���A�Ղ���Z�b�g����
			// �e�z��̈�ԏ�̔�󔒂̃C���f�b�N�X�������Ă������@�̂ق���������������Ȃ�
			fall(j);
			if (idx + 1 < nextPuyoNum && isChain()) {
				// ADDIE���}���
				// ���ׂĂ̂Ղ��u���ĂȂ����ɘA������������͙̂��莖��
				pop_top(j); // j ��̈�ԏ�̂Ղ�����
				pop_top(j);
			}
			else {
				// push ���đ��삵�� pop ����̂� DFS �̊�{�I�ȗ���
				nazopuyo_single::nazoDFS(idx + 1);
				if (isAnswerFound) return;
				pop_top(j);
				pop_top(j);
			}
		}

		if (j + 1 < FIELD_WIDTH && at(j, 0) == ' ' && at(j+1, 0) == ' ') { // AB
			set_puyo(j, 0, nextPuyos[idx * 2]);
			set_puyo(j+1, 0, nextPuyos[idx * 2 + 1]);
			fall(j);
			fall(j + 1);
			if (idx + 1 < nextPuyoNum && isChain()) {
				pop_top(j);
				pop_top(j+1);
			}
			else {
				nazopuyo_single::nazoDFS(idx + 1);
				if (isAnswerFound) return;
				pop_top(j);
				pop_top(j+1);
			}
		}

		if ((nextPuyos[idx * 2] != nextPuyos[idx * 2 + 1]) && at(j, 0) == ' ' && at(j, 1) == ' ') {
			// ����]
			// �]���̏ꍇ�̓X�L�b�v
			// B
			// A
			set_puyo(j, 0, nextPuyos[idx * 2]);
			set_puyo(j, 1, nextPuyos[idx * 2 + 1]);
			fall(j);
			if (idx + 1 < nextPuyoNum && isChain()) {
				pop_top(j);
				pop_top(j);
			}
			else {
				nazopuyo_single::nazoDFS(idx + 1);
				if (isAnswerFound) return;
				pop_top(j);
				pop_top(j);
			}
		
		
			if ((nextPuyos[idx * 2] != nextPuyos[idx * 2 + 1]) && j - 1 >= 0 && at(j, 0) == ' ' && at(j - 1, 0) == ' ') {
				// BA
				set_puyo(j, 0, nextPuyos[idx * 2]);
				set_puyo(j - 1, 0, nextPuyos[idx * 2 + 1]);
				fall(j);
				fall(j - 1);
				if (idx + 1 < nextPuyoNum && isChain()) {
					pop_top(j);
					pop_top(j - 1);
				}
				else {
					nazopuyo_single::nazoDFS(idx + 1);
					if (isAnswerFound) return;
					pop_top(j);
					pop_top(j - 1);
				}
			}
		}

		if (isAnswerFound) return;
	}

	/*for (int j = 0; j < FIELD_WIDTH; ++j) {
		for (int k = 0; k < 4; ++k) {
			if (isAnswerFound) return;
			int par_x = j + parPos[k].first;
			int par_y = parPos[k].second;
			int child_x = j + childPos[k].first;
			int child_y = childPos[k].second;
			if (0 <= child_x && child_x < FIELD_WIDTH &&
				at(par_x, par_y) == ' ' && at(child_x, child_y == ' ')) {
				set_puyo(par_x, par_y, nextPuyos[idx * 2]);
				set_puyo(child_x, child_y, nextPuyos[idx * 2 + 1]);
				fall(par_x);
				if (par_x != child_x) fall(child_x);
				if (idx + 1 < nextPuyoNum && isChain()) {
					pop_top(par_x);
					pop_top(child_x);
				} else {
					nazoDFS(idx + 1);
					if (isAnswerFound) return;
					pop_top(par_x);
					pop_top(child_x);
				}
			}
		}
	}*/




	if (idx == 0 && !isAnswerFound) {
		cout << "There is NO ANSWER!!!" << endl;
	}

	return;

}

void nazopuyo_single::solve_nazopuyo() {
	set_goalChainNum();
	set_nextPuyo();
	set_totalNodes();
	cout << "LETS SOLVE NAZO PUYO!" << endl;
	auto t_start = std::chrono::system_clock::now();
	nazopuyo_single::nazoDFS(0);


	auto t_end = std::chrono::system_clock::now();
	auto sec = std::chrono::duration_cast<std::chrono::seconds>(t_end - t_start).count();
	show(false);
	cout << "Answer Found!: " << (double)sec << "[s]" << endl;
	getchar();

}


// for���Ŏ������悤�Ƃ������ǖ���������
//for (int j = 0; j < FIELD_WIDTH; ++j) {
//	for (int k = 0; k < 4; ++k) {
//		// is_ok
//		int par_x = j + parPos[k].first;
//		int par_y = parPos[k].second;
//		int child_x = j + childPos[k].first;
//		int child_y = childPos[k].second;
//		if (0 <= child_x && child_x < FIELD_WIDTH &&
//			at(par_x, par_y) == ' ' && at(child_x, child_y == ' ')) {
//			cout << par_x << " ";
//			cout << par_y << " ";
//			cout << child_x << " ";
//			cout << child_y << " ";
//			Sleep(1000);
//			set_puyo(par_x, par_y, nextPuyos[idx * 2]);
//			set_puyo(child_x, child_y, nextPuyos[idx * 2 + 1]);
//			fall(par_x);
//			if (par_x != child_x) fall(child_x);
//			if (idx + 1 < nextPuyoNum && isChain()) {
//				pop_top(par_x);
//				pop_top(child_x);
//			}
//			this->show();
//			Sleep(500);
//			nazoDFS(idx + 1);
//			if (isAnswerFound) return;
//			pop_top(par_x);
//			pop_top(child_x);
//		}
//	}
//}
