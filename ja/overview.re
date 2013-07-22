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

AjhcコンパイラはHoge.hsというファイル名のHaskellソースコードを、
hs.outという実行バイナリに変換したようです。
このhs.outというファイルはどのようにしてAjhcが生成したのでしょう？

//image[ajhc_compile][Ajhcによるコンパイルの流れ][width=10cm]

@<img>{ajhc_compile}のようにAjhcコマンドはHaskellソースコードをC言語ソースコードに変換します。
変換されたC言語ソースコードを実行バイナリにコンパイルするのはGCCコンパイラの役目です。
この時、Haskellソースコードから変換されたC言語ソースコードだけでなく、
Ajhcのために専用に作られたランタイムソースコードも一緒にコンパイルします。

ところで、hlファイルというのは一体なんなのでしょう。
hlファイルはAjhcをインストールすると.cabalディレクトリの下に生成されます。

//cmd{
$ ls ~/.cabal/share/ajhc-0.8.0.8/lib
Diff-0.2.0.hl          flat-foreign-1.0.hl      parsec-2.1.0.1.hl
HUnit-1.2.5.1.hl       haskell-extras-0.8.1.hl  pretty-1.0.1.2.hl
QuickCheck-1.2.0.1.hl  haskell2010-0.8.1.hl     safe-0.3.3.hl
applicative-1.0.hl     haskell98-1.0.hl         smallcheck-0.6.1.hl
containers-0.3.0.0.hl  html-1.0.1.2.hl          transformers-0.2.1.0.hl
deepseq-1.2.0.1.hl     jhc-1.0.hl               xhtml-3000.2.1.hl
filepath-1.3.0.1.hl    jhc-prim-1.0.hl
//}

これらのhlファイルはAjhcにおけるHaskellライブラリです。
具体的にはHaskellコードを途中までコンパイルした結果を固めたもので、
ファイルフォーマットはAjhc独自のものです。
hlファイルを使うときは-pオプションを使ってライブラリ名を指定してあげる必要があります。

== コンパイルパイプライン

Ajhcの主な役割はHaskellソースコードをC言語ソースコードに変換することだとわかりました。
ではその変換の手順はどのようなものなのでしょうか？

xxx

== ランタイムの概要

xxx

== ソースコード配置

xxx

== ライセンス

Ajhcのライセンスはjhcに従い、GPL2もしくはそれ以降です。
ただしコンパイルパイプライン以外のソースコードにはGPLは適用されません。

 * hlファイルに対応するHaskellソースコード
 * Ajhcランタイムに対応するC言語ソースコード

このGPL例外条項はまだAjhcのソースコードツリーには反映されていません。
jhcの原作者であるJohn Meachamの修正待ちになっています。
