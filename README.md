# nazopuyo-solver-min
nazopuyo-solver-min is a strong tool to confronts nazopuyo harassment

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
