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

ということはパーサの魔法はFrontEnd.HsParser.parse関数の中で実現されていることになります。

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
以下はこのMonadic Parserの宣言です。

//list[ajhc_src_tree][Monadic Parserの宣言 (HsParser.yファイル)]{
%monad { P } { thenP } { returnP }
%lexer { lexer } { EOF }
%name parse module
%tokentype { Token }
//}

しかしこの宣言Haskellのソースコードではないため、実際の動作が想像できません。
まずはPモナドを見てみましょう。

//list[p_monad][Pモナド (ParseMonad.hsファイル)]{
instance Monad P where
	return a = P $ \_i _x _y _l s _m -> Ok s a
	P m >>= k = P $ \i x y l s mode ->
		case m i x y l s mode of
		    Failed loc msg -> Failed loc msg
		    Ok s' a -> runP (k a) i x y l s' mode
	fail s = P $ \_r _col _line loc _stk _m -> Failed loc s

returnP :: a -> P a
returnP = return
thenP :: P a -> (a -> P b) -> P b
thenP = (>>=)
//}

@<code>{returnP}と@<code>{thenP}はそのままモナドの定義に別名をつけているだけです。
@<code>{return}の定義は@<code>{Ok s a}を返す関数を@<code>{P}で包んでいます。
@<code>{>>=}の定義はつまりPモナドが内包している関数を取り出して、
外側に新しい関数を作りやはり@<code>{P}で包みます。
その新しい関数はさっき取り出しは関数を評価して@<code>{Ok}ならbindの右辺値のPモナドの中にある関数を実行します。
つまり接合されたPモナドを外側から順に評価するわけです。

次はlexer関数の型を見てみましょう。

//list[lexer_func][lexer関数の型 (Lexer.hsファイル)]{
lexer :: (Token -> P a) -> P a
lexer = runL topLexer

topLexer :: Lex a Token
//}



xxx LexerとParserの関係図が必要

== 内部表現

HsDecl
