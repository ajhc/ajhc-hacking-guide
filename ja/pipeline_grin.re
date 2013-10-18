= コンパイラパイプライン: Grinによる最適化

== GCルート制御の追加

Grinでの最適化の(ほぼ)最後段には以下のようにtwiddleGrin関数を呼び出します。

//list[call_twiddleGrin][twiddleGrin呼び出し]{
compileToGrin prog = do
    stats <- Stats.new
    putProgressLn "Converting to Grin..."
    x <- Grin.FromE.compile prog
    -- snip --
    x <- return $ twiddleGrin x
//}

このtwiddleという処理は以下のようなクラスで型毎に実装されています。

//list[TwiddleClass][Twiddleクラス]{
class Twiddle a where
    twiddle :: a -> R a
    twiddle a = return a
//}

Twiddleクラスを継承しているのは以下の5つです。

 * data Exp
 * data Val
 * data Lam
 * data FuncDef
 * [a]

ここでExp型を辿る際にGCルートの制御を追加します。
