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

std::string nazopuyo_single::make_nowKey() {
	std::string nowString;
	for (int i = 0; i < 6; ++i) {
		nowString += howPut[i];
		nowString += "+";
	}
	return nowString;
}


// 解を DFS(深さ優先探索) で全探索する
void nazopuyo_single::nazoDFS(int idx) {
	// idx = 0 からスタートし、 idx = ネクストの数 になった時連鎖シミュを行う
	if (isAnswerFound) return;
	if (idx > nextPuyoNum) return;
	if (idx == nextPuyoNum) {
		// 途中経過表示用
		visitedNodes++;
		if (visitedNodes % 10000 == 0) {
			show();
			cout << "Now Solving ...   ";
			cout << ((double)visitedNodes / totalNodes * 100) << "[%] end" << endl;
			// 探索したノード/全ノード
			// 実際は枝狩りがあるのであくまで目安の割合
			// hash の処理を追加したのであんまり意味なくなったかも (実際の探索ノードと乖離が大きい)
			cout << (visitedNodes / 1000) << "k Nodes visited" << endl;
		}
		// copy
		std::array<char, FIELD_WIDTH* FIELD_HEIGHT> beforeCopy;
		nazopuyo_single::copy_field(field, beforeCopy);

		int nowChainNum = chain_loop(false);
		if (nowChainNum == goalChainNum) {
			// 連鎖数と目標連鎖数が一致すると終わります
			isAnswerFound = true;
			nazopuyo_single::copy_field(beforeCopy, field);
			//nazopuyo_single::copy_field(beforeCopy, ansField);
			return;
		}
		// 探索が続く場合、コピーをコピーします。
		// chain_loop(), chainSim() は破壊的な操作です。だからコピーを取っておく必要があったんですね。
		nazopuyo_single::copy_field(beforeCopy, field);


		return;
	}

	for (int j = 0; j < FIELD_WIDTH; ++j) {
		if (isAnswerFound) return;
		// for文にすべき?だけど上手くいかなかった
		if (at(j, 0) == ' ' && at(j, 1) == ' ') { // 直落下
			// A
			// B
			set_puyo(j, 0, nextPuyos[idx * 2]);
			set_puyo(j, 1, nextPuyos[idx * 2 + 1]);

			// hash 系の処理 (std::unordered_set は hash を用いて実装されている)
			howPut[j].push_back(nextPuyos[idx * 2]);
			howPut[j].push_back(nextPuyos[idx * 2 + 1]);
			string nowString = make_nowKey();
			bool usedKeyFlag = usedKey.count(nowString);
			// 空白があるかを確認し、ぷよをセットする
			// 各配列の一番上の非空白のインデックスを持っておく方法のほうがいいかもしれない
			fall(j);
			if (idx + 1 < nextPuyoNum && isChain() || usedKeyFlag) {
				// ADDIE式枝狩り
				// すべてのぷよを置いてない時に連鎖が発生するのは剪定事象
				pop_top(j); // j 列の一番上のぷよを取る
				pop_top(j);
				howPut[j].pop_back();
				howPut[j].pop_back();
			}
			else {
				// push して操作して pop するのが DFS の基本的な流れ
				usedKey.insert(nowString);
				nazopuyo_single::nazoDFS(idx + 1);
				if (isAnswerFound) return;
				// hash 系の処理
				pop_top(j);
				pop_top(j);
				howPut[j].pop_back();
				howPut[j].pop_back();
			}
		}

		if (j + 1 < FIELD_WIDTH && at(j, 0) == ' ' && at(j + 1, 0) == ' ') { // AB
			set_puyo(j, 0, nextPuyos[idx * 2]);
			set_puyo(j + 1, 0, nextPuyos[idx * 2 + 1]);
			fall(j);
			fall(j + 1);
			howPut[j].push_back(nextPuyos[idx * 2]);
			howPut[j + 1].push_back(nextPuyos[idx * 2 + 1]);
			string nowString = make_nowKey();
			bool usedKeyFlag = usedKey.count(nowString);
			if (idx + 1 < nextPuyoNum && isChain() || usedKeyFlag) {
				pop_top(j);
				pop_top(j + 1);
				howPut[j].pop_back();
				howPut[j + 1].pop_back();
			}
			else {
				usedKey.insert(nowString);
				nazopuyo_single::nazoDFS(idx + 1);
				if (isAnswerFound) return;
				pop_top(j);
				pop_top(j + 1);
				howPut[j].pop_back();
				howPut[j + 1].pop_back();
			}
		}

		if ((nextPuyos[idx * 2] != nextPuyos[idx * 2 + 1]) && at(j, 0) == ' ' && at(j, 1) == ' ') {
			// 反回転
			// ゾロの場合はスキップ
			// B
			// A
			set_puyo(j, 0, nextPuyos[idx * 2]);
			set_puyo(j, 1, nextPuyos[idx * 2 + 1]);
			fall(j);
			howPut[j].push_back(nextPuyos[idx * 2]);
			howPut[j].push_back(nextPuyos[idx * 2 + 1]);
			string nowString = make_nowKey();
			bool usedKeyFlag = usedKey.count(nowString);
			if (idx + 1 < nextPuyoNum && isChain() || usedKeyFlag) {
				pop_top(j);
				pop_top(j);
				howPut[j].pop_back();
				howPut[j].pop_back();
			}
			else {
				usedKey.insert(nowString);
				nazopuyo_single::nazoDFS(idx + 1);
				if (isAnswerFound) return;
				pop_top(j);
				pop_top(j);
				howPut[j].pop_back();
				howPut[j].pop_back();
			}
		}


		if ((nextPuyos[idx * 2] != nextPuyos[idx * 2 + 1]) && j - 1 >= 0 && at(j, 0) == ' ' && at(j - 1, 0) == ' ') {
			// BA
			set_puyo(j, 0, nextPuyos[idx * 2]);
			set_puyo(j - 1, 0, nextPuyos[idx * 2 + 1]);
			fall(j);
			fall(j - 1);
			howPut[j].push_back(nextPuyos[idx * 2]);
			howPut[j - 1].push_back(nextPuyos[idx * 2 + 1]);
			string nowString = make_nowKey();
			bool usedKeyFlag = usedKey.count(nowString);
			if (idx + 1 < nextPuyoNum && isChain() || usedKeyFlag) {
				pop_top(j);
				pop_top(j - 1);
				howPut[j].pop_back();
				howPut[j - 1].pop_back();
			}
			else {
				usedKey.insert(nowString);
				nazopuyo_single::nazoDFS(idx + 1);
				if (isAnswerFound) return;
				pop_top(j);
				pop_top(j - 1);
				howPut[j].pop_back();
				howPut[j - 1].pop_back();
			}
		}
	}

	if (isAnswerFound) return;

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
	cout << "usedKey.size(): " << usedKey.size() << endl;
	//cout << (sizeof(usedKey) * usedKey.size() / 8 / 1024 / 1024) << " MB" << endl;;
	getchar();

}


// for文で実装しようとしたけど無理だった
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
