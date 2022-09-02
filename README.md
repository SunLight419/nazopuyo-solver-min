# nazopuyo-solver-min
nazopuyo-solver-min is a strong(wish) tool to confronts nazopuyo harassment

## 諸注意
- 全体的に例外処理をしていないので配列外参照とか起こりまくるかもしれません
- Windows10, Visual Studio 2022 で動作確認済み

## 各ソースコードの説明
- main.cpp
  - メイン
- FIELD_ARRAY.cpp/h
  - フィールドの状態を std::array で実装したもの
  - もともとは2次元 std::vector で実装していたが、5手の探索で速度が10倍(50分台→5分以下)ぐらいになった
- CHAIN.cpp/h
  - 連鎖に関するあれこれ
- nazopuyo_single.cpp/h
  - 謎ぷよを解くためのあれこれ
- main_loop.cpp/h
  - CUI のためのあれこれ
