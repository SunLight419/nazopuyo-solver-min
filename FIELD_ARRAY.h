#pragma once
#include <array>
#include <string>

// フィールドの状況を表す
// vector 型で実装していたのを array 型で実装してみた
// 78通りしかないので i*FIELD_WIDTH+j とするよりも配列を事前に作成した方が速いかも
class FIELD_ARRAY
{
public:
	std::array<char, FIELD_WIDTH * FIELD_HEIGHT> field;
	// char 型1次元配列
	// 左上から下に向かって 0, 1, 2, ..., 77( = 13 * 6 - 1)
	// とした方が都合が良いが、右に走査するようになったりなってなかったりしてるので要修正
	FIELD_ARRAY();									// コンストラクタ
	char at(int x, int y);							// ぷよの色を返す
	void showColor(char c);							// 色付きでターミナルにフィールドの状況を描画するための下準備
	void show();
	void show(bool isFlush);						// 色付きでターミナルにフィールドの状況を描画する
	void show_with_cursol(int x, int y);			// x, y にカーソルを表示するver
	void set_puyo(int x, int y, char puyoColor);	// x, y にぷよをセットする
	void set_template(std::string key);				// 既存のテンプレートフィールドをセットする(Kenny式19連鎖など)
	void pop_top(int x);							// 列 x の最上位ぷよを取る


};

