#pragma once
#include "FIELD_ARRAY.h"
#include "CHAIN.h"
#include <vector>
#include <unordered_set>
// なぞぷよを解くクラス(シングルスレッド)
// マルチスレッドはコードがごちゃごちゃしてのでとりあえず
// pthreadを用いていたがstd::threadで良い?
class nazopuyo_single : public CHAIN
{
public:
	int nextPuyoNum; // ネクストぷよの数 ５手６手ぐらいから爆発する
	int goalChainNum; // 目標連鎖数
	std::array<char, 20> nextPuyos; // とりあえず10手分確保

	long long visitedNodes = 0; // 探索した(n手すべて置いた)局面の数
	long long totalNodes = 1;
	bool isAnswerFound = false; // 解が見つかったかどうか

	// 探索済みのノードを記録する
	// ノードの記録の仕方は何列目に何のぷよを置いたか( howPut )
	// これを make_nowKey() で合成して usedKey にぶち込む
	std::unordered_set<std::string> usedKey;
	std::array<std::string, FIELD_WIDTH> howPut;
	std::string make_nowKey();

	//std::array<char, FIELD_WIDTH* FIELD_HEIGHT> ansField; // 答え用のフィールド

	void set_totalNodes();

	// field をコピーする関数
	// スマートにする方法わからん
	void copy_field(std::array<char, FIELD_WIDTH* FIELD_HEIGHT>& from, std::array<char, FIELD_WIDTH* FIELD_HEIGHT>& to);
	
	void show_nextPuyos();

	void set_nextPuyo();
	void set_goalChainNum();
	void solve_nazopuyo(); // 基本的にはこれを呼び出せば全部やってくれる

	std::vector<std::pair<int, int>> parPos = {
		{0, 0}, {0, 0}, {0, 1}, {0, 0},
	};

	std::vector<std::pair<int, int>> childPos = {
		{0, 1}, {-1, 0}, {0, 0}, {1, 0},
	};

	// 謎ぷよを深さ優先探索で解く
	// idx: 何手目の組みぷよか
	void nazoDFS(int idx);
};

