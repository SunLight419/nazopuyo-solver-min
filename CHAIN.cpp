#include "CHAIN.h"
#include "FIELD_ARRAY.h"
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <Windows.h>

using namespace std;

void CHAIN::fall() {
	// 下から空白の数を数える、空白でないなら空白の数だけ下げる
	for (int j = 0; j < FIELD_WIDTH; ++j) {
		int blankNum = 0;
		for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
			if (this->at(j, i) == ' ') {
				blankNum++;
				continue;
			}
			else {
				if (blankNum == 0) continue;
				this->set_puyo(j, i + blankNum, this->at(j, i));
				this->set_puyo(j, i, ' ');
			}
		}
	}
}

void CHAIN::fall(int x) {
	// 下から空白の数を数える、空白でないなら空白の数だけ下げる
	int blankNum = 0;
	for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
		if (this->at(x, i) == ' ') {
			blankNum++;
			continue;
		}
		else {
			if (blankNum == 0) continue;
			this->set_puyo(x, i + blankNum, this->at(x, i));
			this->set_puyo(x, i, ' ');
		}
	}
}

void CHAIN::fall(int x, int y) {
	// 列ごとに連鎖が起こった最低のyを保存している場合
	int blankNum = 0;
	for (int i = y; i >= 0; --i) {
		if (this->at(x, i) == ' ') {
			blankNum++;
			continue;
		}
		else {
			if (blankNum == 0) continue;
			this->set_puyo(x, i + blankNum, this->at(x, i));
			this->set_puyo(x, i, ' ');
		}
	}
}



// 詳細は下記の chian_loop() を参照
bool CHAIN::chain(bool SHOW_CHAIN_SEQUENCE = false) {
	bool res = false;
	vector<bool> visited(FIELD_WIDTH * FIELD_HEIGHT, false);
	vector<pair<int, int>> dir{
		{1, 0}, {0, 1}, {-1, 0}, {0, -1}
	};
	int deleteX = 1 << 6; // 連鎖によってfallが生じる列
	//int lowestY = 1;
	;	for (int j = 0; j < FIELD_WIDTH; ++j) {
		for (int i = (FIELD_HEIGHT - 1); i > 0; --i) {
			// 下から見ていく方が効率が良い(はず)
			// 13段目(i = 0)は幽霊連鎖でカウントされない
			if (visited[i * FIELD_WIDTH + j]) continue;
			visited[i * FIELD_WIDTH + j] = true;
			char nowColor = this->at(j, i);
			if (nowColor == ' ') {
				i = -1;
				continue;
			}
			queue<pair<int, int>> que;
			set<pair<int, int>> kouho;
			que.emplace(j, i); // x, y
			kouho.emplace(j, i);
			while (!que.empty()) {
				int x = que.front().first;
				int y = que.front().second;
				que.pop();
				for (int k = 0; k < 4; ++k) {

					int nx = x + dir[k].first;
					int ny = y + dir[k].second;

					if (0 <= nx && nx < FIELD_WIDTH &&
						1 <= ny && ny < FIELD_HEIGHT &&
						!visited[ny * FIELD_WIDTH + nx] &&
						this->at(nx, ny) == nowColor) {
						kouho.emplace(nx, ny);
						que.emplace(nx, ny);
						visited[ny * FIELD_WIDTH + nx] = true;
					}
				}

			}

			if (kouho.size() >= 4) {
				res = true;
				for (auto pos : kouho) {
					this->set_puyo(pos.first, pos.second, ' ');
					deleteX |= 1 << pos.first;
					//lowestY = min(lowestY, pos.second);
				}
			}
		}
	}

	if (SHOW_CHAIN_SEQUENCE) {
		this->show();
		Sleep(500);
	}
	//if (res) { this->fall(); }
	for (int i = 0; i < FIELD_WIDTH; ++i) {
		if (deleteX >> i && 1) fall(i);
	}
	if (SHOW_CHAIN_SEQUENCE) {
		this->show();
		Sleep(250);
	}

	return res;
}

int CHAIN::chainSim(bool SHOW_CHAIN_SEQUENCE = false) {
	int chainCount = 0;
	bool res; // 連鎖が怒ったかどうか
	while (true) {
		res = chain(SHOW_CHAIN_SEQUENCE);
		if (res) {
			chainCount++;
			continue;
		}
		else {
			break;
		}
	}


	return chainCount;
}

int CHAIN::chain_loop(bool SHOW_CHAIN_SEQUENCE) {
	// 再帰呼び出しではなくwhileでループするver
	// Kenny式ベンチでは 0.1ms ぐらいはやそう
	int chainCount = 0;
	bool loopFlag = true; // ループが始まるタイミングで false になり、連鎖が発生すれば true になる

	// フィールドは fall 済みであってください
	while (loopFlag) {
		bool res = false; // ４つ以上連結しているぷよがあるかどうか
		vector<bool> visited(FIELD_WIDTH * FIELD_HEIGHT, false); // 探索済みのマスを記録 vectorじゃない方がいいかも
		vector<pair<int, int>> dir{
			{1, 0}, {0, 1}, {-1, 0}, {0, -1}
		};
		// dir: direction. これがあると BFS の実装が楽
		int deleteX = 1 << 6; // 連鎖によってfallが生じる列(bit演算)
		for (int j = 0; j < FIELD_WIDTH; ++j) {
			for (int i = (FIELD_HEIGHT - 1); i > 0; --i) {
				// 下から見ていく方が効率が良い(はず) (上のマスが空白なら、その上のマスも空白のはずなので)
				// 13段目(i = 0)は幽霊連鎖でカウントされない
				if (visited[i * FIELD_WIDTH + j]) continue; // すでに探索済みなら continue
				visited[i * FIELD_WIDTH + j] = true; // 探索済みにする
				char nowColor = this->at(j, i); // 今のマスのぷよの色
				if (nowColor == ' ') { // 空白ならば、右の列に移る
					i = -1;
					continue;
				}
				queue<pair<int, int>> que; // 探索する場所のqueue
				set<pair<int, int>> kouho; // 消す場所の候補 これの size() が4以上ならば、これの中身のぷよをフィールドから消す
				// 現在の場所を追加する
				que.emplace(j, i); // x, y
				kouho.emplace(j, i);

				// que が空になるまで(= 同じ色が続く限り)続ける
				while (!que.empty()) {
					// 現在の x, y 座標
					int x = que.front().first;
					int y = que.front().second;
					que.pop();
					for (int k = 0; k < 4; ++k) {
						// 現在のマスに対する上下左右のマスを探索する
						// dir があるとこれが楽
						int nx = x + dir[k].first; // new x
						int ny = y + dir[k].second; // new y

						if (0 <= nx && nx < FIELD_WIDTH &&
							1 <= ny && ny < FIELD_HEIGHT && // x, y がフィールドの外にはみ出していないか
							!visited[ny * FIELD_WIDTH + nx] && // すでに探索済みなら探索しない
							this->at(nx, ny) == nowColor) { // 同じ色でなければ探索しない
							kouho.emplace(nx, ny); // kouho, que に nx, ny を追加し、探索を続ける
							que.emplace(nx, ny);
							visited[ny * FIELD_WIDTH + nx] = true;
						}
					}

				}

				if (kouho.size() >= 4) { // 4連結以上ならばぷよを消す（空白を挿入）
					res = true;
					for (auto pos : kouho) {
						this->set_puyo(pos.first, pos.second, ' ');
						deleteX |= 1 << pos.first; // 落下が起こる列を記録
					}
				}
			}
		}
		if (!res) {
			loopFlag = false;
			break;
		}
		else {
			chainCount++;
		}

		if (SHOW_CHAIN_SEQUENCE) { // 途中結果表示用
			this->show();
			Sleep(500);
		}
		//if (res) { this->fall(); }
		for (int i = 0; i < FIELD_WIDTH; ++i) {
			if (deleteX >> i && 1) fall(i);
		}
		if (SHOW_CHAIN_SEQUENCE) {
			this->show();
			Sleep(250);
		}

	}

	return chainCount;

}

bool CHAIN::isChain() {
	bool res = false;
	vector<bool> visited(FIELD_WIDTH * FIELD_HEIGHT, false);
	vector<pair<int, int>> dir{
		{1, 0}, {0, 1}, {-1, 0}, {0, -1}
	};
	for (int j = 0; j < FIELD_WIDTH; ++j) {
		for (int i = (FIELD_HEIGHT - 1); i > 0; --i) {
			if (res) break; // 連鎖が発生するのならば探索を打ち切る
			// 下から見ていく方が効率が良い(はず)
			// 13段目(i = 0)は幽霊連鎖でカウントされない
			if (visited[i * FIELD_WIDTH + j]) continue;
			visited[i * FIELD_WIDTH + j] = true;
			char nowColor = this->at(j, i);
			if (nowColor == ' ') {
				i = -1;
				continue;
			}
			queue<pair<int, int>> que; // 候補は不要
			int kouho = 1;
			que.emplace(j, i); // x, y
			while (!que.empty()) {
				int x = que.front().first;
				int y = que.front().second;
				que.pop();
				for (int k = 0; k < 4; ++k) {

					int nx = x + dir[k].first;
					int ny = y + dir[k].second;

					if (0 <= nx && nx < FIELD_WIDTH &&
						1 <= ny && ny < FIELD_HEIGHT &&
						!visited[ny * FIELD_WIDTH + nx] &&
						this->at(nx, ny) == nowColor) {
						que.emplace(nx, ny);
						kouho++;
						if (kouho >= 4) {
							res = true;
							return true;
						}
						visited[ny * FIELD_WIDTH + nx] = true;
					}
				}

			}

			if (kouho >= 4) {
				res = true;
				return true;
				break;
			}
		}
	}

	return res;
}
