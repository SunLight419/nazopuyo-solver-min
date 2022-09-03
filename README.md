# nazopuyo-solver-min
nazopuyo-solver-min is a strong(wish) tool to confronts nazopuyo harassment

## 諸注意
- 全体的に例外処理をしていないので配列外参照とか起こりまくるかもしれません
- Windows10, Visual Studio 2022 で動作確認済み
- 割とメモリを食います（6手の探索で2GBほど）
- 何かあれば twitter@mintisalive まで

## 使い方
- WASD で移動
- 1: フィールドエディットモード
  - {w, a, s, d} でカーソルを移動させ、{r, g, b, y, p, @(お邪魔), ' '(空白) } でぷよを挿入
- 2: 連鎖シミュレーション
- 3: 謎ぷよモード
  - おじゃま非対応
  - n連鎖のみ対応
## 各ソースコードの説明
- main.cpp
  - メイン
- FIELD_ARRAY.cpp/h
  - フィールドの状態を std::array で実装したもの
  - もともとは2次元 std::vector で実装していたが、5手の探索で速度が10倍(50分台→5分以下)ぐらいになった (他の部分も改良している)
- CHAIN.cpp/h
  - 連鎖に関するあれこれ
- nazopuyo_single.cpp/h
  - 謎ぷよを解くためのあれこれ
- main_loop.cpp/h
  - CUI のためのあれこれ

## 実行速度について
- ぷよぷよは重複を考えない1手2色のぷよの置き方が22通りある
  - そのため、n手のぷよを全探索する場合、探索するノードは 22^n となる
  - 22^3: 24万通り, 22^4: 52万通り, 22^5: 520万通り, 22^6: 1.2億通り, 22^7: 25億通り
  - 以上のように、手数が増えるにつれ爆発的にノード数が増加する
- ぷよぷよの連鎖数を求めるのは難しい(効率的なアルゴリズムが存在しない?)らしい
- kenny式(有名な19連鎖の形)を1回シミュレートするのに 3ms 程かかる
- Hash 機能の追加で速度が大幅に改善された
- 目安
  - 4手以下: 1秒
  - 5手: 1分
  - 6手: 25分
