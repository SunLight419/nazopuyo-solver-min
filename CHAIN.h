#pragma once
#include "FIELD_ARRAY.h"

// 連鎖に関するもの

class CHAIN : public FIELD_ARRAY
{
public:
	// ぷよを落下させる関数
	// 実行速度の面では fall(x) <= fall() っぽい気がする
	// fall(x, y)は 落下させる x, y を記録するのがボトルネックになって多分遅い
	// 
	// フィールドすべてのぷよを落下させる
	// 連鎖開始前などに使用
	void fall();

	// ある列x ( 0 <= x < 6)に対してのみ落下を行う
	void fall(int x);

	// ある列xの下からy段目"以上"のぷよに対して落下を行う
	// 構造的には左上が0段目としていることに注意(y以下に処理を行う)
	void fall(int x, int y);

	// 連鎖が発生するかどうか
	// なぞぷよ探索の際、最終手でない場合に連鎖が起これば、その枝の探索を打ち切る
	bool isChain();

	// 1連鎖を行う
	bool chain(bool SHOW_CHAIN_SEQUENCE);

	// 連鎖が起こらなくなるまで chain() を繰り返す関数
	// 戻り値は連鎖数
	// SHOW_CHAIN_SEQUENCE: 連鎖の過程を表示するかどうか
	// 一般のシミュレーションでは TRUE だが、なぞぷよ探索では FALSE を指定する
	// Kenny19chain benchmark では 3ms/kenny ほど
	int chainSim(bool SHOW_CHAIN_SEQUENCE);

	// 関数のオーバーヘッドを嫌って、上記の chainSim() を while ループで実装したもの
	// こっちのほうがちょっと早いかも 2.95ms/kenny ほど
	int chain_loop(bool SHOW_CHAIN_SEQUENCE);
};

