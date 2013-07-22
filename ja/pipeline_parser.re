= コンパイラパイプライン: パーサ

AjhcコンパイラはまずHaskellソースコード文字列を受け取り、内部表現になおします。
この処理はパーサ(構文解析器)と呼ばれます。

== パーサに届くまで

ajhcコマンドの開始は
@<href>{https://github.com/ajhc/ajhc/blob/arafura/src/Ho/Build.hs}
にあるloadModules関数です。
loadModules関数から呼び出される関数を順に辿ってみましょう。

 * @<code>{Ho.Build.loadModules :: Opt -> [FilePath] -> [String] -> SrcLoc -> [Either Module FilePath] -> IO (Map.Map SourceHash (Module, [(Module, SrcLoc)]), HoHash, CompUnitGraph)}
 * @<code>{Ho.Build.fetchSource :: Opt -> IORef Done -> [FilePath] -> Maybe (Module,SrcLoc) -> IO Module}
 * @<code>{Ho.ReadSource.parseHsSource :: Opt -> FilePath -> LBS.ByteString -> IO (HsModule,LBS.ByteString)}
 * @<code>{FrontEnd.ParseMonad.runParserWithMode :: ParseMode -> P a -> String -> ([Warning],ParseResult a)}
 * @<code>{FrontEnd.HsParser.parse :: P HsModule}

いきなり型がやたら長いですがあまり気にする必要はありません。
ここでは
@<href>{https://github.com/ajhc/ajhc/blob/arafura/src/FrontEnd/ParseMonad.hs}
にあるparseHsSource関数がパーサの最上位にいることがわかれば十分です。

== パーサの構造



== 内部表現
