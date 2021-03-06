= ランタイム(GCを除く)

Ajhcは他の言語処理系と同様にランタイムを持っています。
Ajhcのコンパイラパイプラインから吐き出されたC言語コードは、このランタイムと協調して動きます。
ただし、他の処理系と異なりAjhcのランタイムはC言語のみで記述されており、
しかもコメント込み3000行程度ととても小さなものです。

ランタイムはGCの機能も含んでいますが、この章ではGC以外のランタイムの設計を解説します。