= Ajhcって何？

AjhcはHaskellコンパイラです。
Haskellコンパイラとして有名なのはGHCですが、AjhcはGHCとはまた別のHaskellコンパイラなのです。

AjhcはjhcというHaskellコンパイラに独自の改造をほどこしたものです。
Ajhcの運営方針は「Ajhcにおける意義ある改変は本家jhcにマージすること」です。
そのためjhcとAjhcは少し違うところはあれども、同じ道を歩むことになるでしょう。
Ajhcはjhcにまだマージされていない実験的な機能が入っているとも言えるかもしれません。

== どうして新しいHaskellコンパイラを作るの？

なぜGHCの開発に参加するのではなく、あまり人気のないコンパイラであるjhcの開発に参加するのでしょうか？
それはGHCではまだ開拓できないコンピューターアーキティクチャの領域にHaskellプログラミングを適用するためです。
例えば以下のような領域ではGHCを使ったHaskellプログラミングは困難です。

 * Linux kernelモジュール
 * POSIXではないOS上のアプリケーション
 * メモリの少ない組み込みマイコンチップ内ファームウェア
 * OS本体

このような領域においてもHaskellプログラミングの恩恵を受けられるようにするために、Ajhcは開発が続けられています。

また、AjhcはMetasepiというOSを作るプロジェクトの一部でもあります。
Metasepiは最終的にLinuxやNetBSDのようなフリーUNIXのkernel部分をC言語より強い型によって再設計することを目指しています。
Metasepiプロジェクトの道ははてしなく遠くへ続いています。
Ajhcはその最初の一歩です。
もちろんAjhcはMetasepiプロジェクトのためだけのものではありません。
フリーUNIXのkernelを書く力を持つHaskellコンパイラが手に入れば、
コンピューターアーキティクチャのほとんど全ての領域に強い型をつけることが可能になるでしょう。
そんな未来を私達は夢みています。

== 使い方は？

jhcのユーザーズマニュアルを日本語訳し、Ajhcで追加した機能を加筆したドキュメントがあります。

 * Ajhcユーザーズマニュアル @<href>{http://ajhc.metasepi.org/manual_ja.html}

Ajhcコンパイラの使い方は上記のマニュアルで一応説明されています。
そのためこの本では使い方ではなく、Ajhcの内部を解説します。
もしAjhcユーザーズマニュアルに書かれているべきことが書かれていない場合には、
Metasepiチームまで連絡をいただけると助かります。

== 連絡先を教えてください

2つの方法があります。

 * メーリングリスト: @<href>{http://groups.google.com/group/metasepi}
 * バグ報告: @<href>{https://github.com/ajhc/ajhc/issues}

ただし上記どちらも公用語は英語になります。

== ライセンス

Ajhcのライセンスはjhcに従い、GPL2もしくはそれ以降です。
ただしコンパイラパイプライン以外のソースコードにはGPLは適用されません。
つまり以下のソースコードはGPL適用から除外されています。

 * hlファイルに対応するHaskellソースコード
 * Ajhcランタイムに対応するC言語ソースコード

このGPL例外条項はまだAjhcのソースコードツリーには反映されていません。
jhcの原作者であるJohn Meachamの修正待ちになっています。

いま目にしているこの本は
Creative Commons Attribution-ShareAlike 3.0 Unported License
@<href>{http://creativecommons.org/licenses/by-sa/3.0/}
で配布されています。

この本表紙のイカさん写真はSilke Baronさんのものです。
@<href>{http://www.flickr.com/photos/silkebaron/931381358/}
この写真に限り Creative Commons Attribution 2.0 Generic License
@<href>{http://creativecommons.org/licenses/by/2.0/deed.en}
で配布されています。
