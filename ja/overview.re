= Ajhcコンパイラひとめぐり

探検のはじめる前には地図が必要です。
Ajhcコンパイラの外観をつかんでおきましょう。

== インストール

AjhcのインストールにはGHCが必要です。
Ajhcはセルフホスティングできておらず、GHCの独自拡張に頼って実装されています。

=== Linux

このインストール例はDebian系ディストリビューションのものです。
他のディストリビューションを使用されている方はapt-getによるパッケージ設定を読み替えてください。

//cmd{
$ sudo apt-get install haskell-platform libncurses5-dev gcc
$ cabal update
$ cabal install ajhc
$ export PATH=$HOME/.cabal/bin/:$PATH
//}

=== Windows

=== Mac OS X

== コンパイルの流れ

まずは簡単なプログラムをコンパイルしてみましょう。

//cmd{
$ echo 'main = print "hoge"' > Hoge.hs
$ ajhc Hoge.hs
$ ./hs.out
"hoge"
//}

このhs.outというファイルはどのようにしてAjhcが生成したのでしょう？

//image[ajhc_compile][Ajhcによるコンパイルの流れ][width=10cm]

@<img>{ajhc_compile}はAjhcがHaskellソースコードを実行バイナリにコンパイルする全体の流れです。

== コンパイルパイプライン
== ランタイムの概要
== ソースコード配置
