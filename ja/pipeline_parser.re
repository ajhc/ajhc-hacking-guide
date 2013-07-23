= コンパイラパイプライン: パーサ

AjhcコンパイラはまずHaskellソースコード文字列を受け取り、内部表現になおします。
この処理はパーサ(構文解析器)と呼ばれます。

== パーサに届くまで

ajhcコマンドの開始は
@<href>{https://github.com/ajhc/ajhc/blob/arafura/src/Ho/Build.hs}
にあるloadModules関数です。
loadModules関数から呼び出される関数を順に辿ってみましょう。

 * @<code>{Ho.Build.loadModules :: Opt -> [FilePath] -> [String] -> SrcLoc -> [Either Module FilePath] -> IO (Map.Map SourceHash (Module, [(Module, SrcLoc)]), HoHash, CompUnitGraph)}
 * @<code>{Ho.Build.fetchSource :: Opt -> IORef Done -> [FilePath] -> Maybe (Module, SrcLoc) -> IO Module}
 * @<code>{Ho.ReadSource.parseHsSource :: Opt -> FilePath -> LBS.ByteString -> IO (HsModule, LBS.ByteString)}
 * @<code>{FrontEnd.ParseMonad.runParserWithMode :: ParseMode -> P a -> String -> ([Warning], ParseResult a)}
 * @<code>{FrontEnd.HsParser.parse :: P HsModule} xxx これ本当？

いきなり型がやたら長いですがあまり気にする必要はありません。
ここでは
@<href>{https://github.com/ajhc/ajhc/blob/arafura/src/FrontEnd/ParseMonad.hs}
にあるparseHsSource関数がパーサの最上位にいることがわかれば十分です。
parseHsSource関数の型はそれぞれ以下の意味をもっています。

 * 第一引数 "@<code>{Opt}": コマンドオプション
 * 第二引数 "@<code>{FilePath}": Haskellソースコードファイル名
 * 第三引数 "@<code>{LBS.ByteString}": Haskellソースコードの中身、文字列
 * 返値 "@<code>{(HsModule, LBS.ByteString)}": パース結果とHaskellソースコードファイル名

このparseHsSource関数とその近辺は何をやっているのでしょうか。

 * preprocess関数でCPPやm4のプリプロセッサを通す
 * collectFileOpts関数でHaskellソースのプラグマからコンパイルオプションを抽出
 * runParserWithMode関数呼び出し
 * FrontEnd.HsParser.parseの中のモナドを実行

xxx ここは図描くべき

== パーサの構造

FrontEnd.HsParser.parse関数は
@<href>{https://github.com/ajhc/ajhc/blob/arafura/src/FrontEnd/HsParser.y}
で定義されています。このファイルはHappy
@<href>{http://www.haskell.org/happy/}
というパーサジェネレータでHaskellコードに変換されてからコンパイルされます。

レキシカルアナライザ(字句解析器)は
FrontEnd.Lexer.lexer関数です。
@<href>{https://github.com/ajhc/ajhc/blob/arafura/src/FrontEnd/Lexer.hs}
で定義されています。
GHCのレキシカルアナライザはAlex
@<href>{http://www.haskell.org/alex/}
を使って書かれていましたが、Ajhcでは生のHaskellコードです。

HappyはパーサとレキシカルアナライザをMonadic Parser
@<href>{http://www.haskell.org/happy/doc/html/sec-monads.html}
という方法で接合します。

== 内部表現

HsDecl
