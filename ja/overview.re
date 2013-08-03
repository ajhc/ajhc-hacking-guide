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
$ sudo apt-get install haskell-platform libncurses5-dev libwww-perl gcc m4
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

== コンパイラパイプライン

Ajhcの主な役割はHaskellソースコードをC言語ソースコードに変換することだとわかりました。
ではその変換の手順はどのようなものなのでしょうか？
Ajhcの吐き出すC言語ソースコードを見てみましょう。
-Cオプションを使えばGCCにかける前のHaskellから変換されたC言語ソースコードを見ることができます。

//cmd{
$ cat Hoge.hs
main = putStrLn "hoge"
$ ajhc -C -o Hoge.c Hoge.hs
//}

//listnum[csource_fromhs][Hoge.c (Haskellから変換されたC言語ソースコード)]{
char jhc_c_compile[] = "gcc /tmp/jhc_6116/rts/profile.c /tmp/jhc_6116/rts/rts_su...
char jhc_command[] = "ajhc -C -o Hoge.c Hoge.hs";
char jhc_version[] = "ajhc 0.8.0.8 (f6c3f4b070acad8a5012682810f0f4d7b7b9ed44)";

#include "jhc_rts_header.h"
struct s_caches_pub {
};
#include <stdio.h>

enum {
    CJhc_Prim_Prim_$BE = 1,
    CJhc_Prim_Prim_$LR = 0,
    CJhc_Prim_Prim_$x3a = 0,
    CJhc_Type_Basic_Char = 0
};
struct sCJhc_Prim_Prim_$x3a A_ALIGNED;

struct sCJhc_Prim_Prim_$x3a {
    sptr_t a1;
    sptr_t a2;
};
void jhc_hs_init(gc_t gc,arena_t arena) ;
void _amain(void) ;
static void b__main(gc_t gc,arena_t arena) A_STD;
static void ftheMain(gc_t gc,arena_t arena) A_STD;
/* CAFS */
/* (HcNode CJhc.Prim.Prim.: [Left &("CJhc.Type.Basic.Char" 101),Left &("CJhc.Prim...
static const struct sCJhc_Prim_Prim_$x3a _c1 = {.a1 = (sptr_t)RAW_SET_UF('e'),
                                   .a2 = (sptr_t)SET_RAW_TAG(CJhc_Prim_Prim_$BE)};
#define c1 (TO_SPTR_C(P_WHNF, (sptr_t)&_c1))
/* (HcNode CJhc.Prim.Prim.: [Left &("CJhc.Type.Basic.Char" 103),Right 1],2) */
static const struct sCJhc_Prim_Prim_$x3a _c2 = {.a1 = (sptr_t)RAW_SET_UF('g'),
                                                                        .a2 = c1};
#define c2 (TO_SPTR_C(P_WHNF, (sptr_t)&_c2))
/* (HcNode CJhc.Prim.Prim.: [Left &("CJhc.Type.Basic.Char" 111),Right 2],3) */
static const struct sCJhc_Prim_Prim_$x3a _c3 = {.a1 = (sptr_t)RAW_SET_UF('o'),
                                                                        .a2 = c2};
#define c3 (TO_SPTR_C(P_WHNF, (sptr_t)&_c3))
/* (HcNode CJhc.Prim.Prim.: [Left &("CJhc.Type.Basic.Char" 104),Right 3],4) */
static const struct sCJhc_Prim_Prim_$x3a _c4 = {.a1 = (sptr_t)RAW_SET_UF('h'),
                                                                        .a2 = c3};
#define c4 (TO_SPTR_C(P_WHNF, (sptr_t)&_c4))

const void * const nh_stuff[] = {
&_c1, &_c2, &_c3, &_c4, NULL
};


void 
jhc_hs_init(gc_t gc,arena_t arena)
{
        alloc_public_caches(arena,sizeof(struct s_caches_pub));
}

void 
_amain(void)
{
        arena_t arena;
        gc_t gc;
        gc = NULL;
        arena = NULL;
        jhc_alloc_init(&gc,&arena);
        jhc_hs_init(gc,arena);
        b__main(gc,arena);
        jhc_alloc_fini(gc,arena);
}

static void A_STD
b__main(gc_t gc,arena_t arena)
{
        return ftheMain(gc,arena);
}

static void A_STD
ftheMain(gc_t gc,arena_t arena)
{
        sptr_t v10;
        v10 = c4;
        fJhc_Monad_72__go__3:;
        {   wptr_t v100000 = eval(gc,arena,v10);
            if (SET_RAW_TAG(CJhc_Prim_Prim_$BE) == v100000) {
                SET_RAW_TAG(CJhc_Prim_Prim_$LR);
            } else {
                sptr_t v115160440;
                sptr_t v12;
                /* ("CJhc.Prim.Prim.:" ni12 ni115160440) */
                v12 = ((struct sCJhc_Prim_Prim_$x3a*)v100000)->a1;
                v115160440 = ((struct sCJhc_Prim_Prim_$x3a*)v100000)->a2;
                {   uint32_t v216085086;
                    gc_frame0(gc,1,v115160440);
                    wptr_t v100002 = eval(gc,arena,v12);
                    v216085086 = ((uint32_t)RAW_GET_UF(v100002));
                    uint32_t v135303430 = v216085086;
                    (void)jhc_utf8_putchar((int)v135303430);
                    v10 = v115160440;
                    goto fJhc_Monad_72__go__3;
                }
            }
        }
        return (void)jhc_utf8_putchar((int)10);
}
//}

得られたC言語ソースコード (@<list>{csource_fromhs}) の行でわかりやすい部分を解説します。

 * 1行目: このソースコードをGCCでコンパイルするためのオプションが示されている
 * 50行目: このソースコードに関する初期化。ランタイムから呼び出される
 * 56行目: Haskellコードのエントリポイント
 * 75行目: Haskellのmain関数本体

ではHoge.hsからHoge.cを生成するコンパイラパイプラインはどのようなしくみなのでしょうか。

xxx 概要を追記すること

== ランタイムの概要

AjhcのランタイムはC言語によって書かれています。
また多くの処理系のようにCPUアーキティクチャ依存のコードは含まれていません。
インラインアセンブラも含みません。
これはAjhcランタイムの移植性が高いことを示しています。
しかしアーキティクチャ依存のコードはAjhcランタイムとは別に用意する必要があるということでもあります。

Ajhcランタイムの内部は以下の要素を含んでいます。

 * GC
 * WHNFの評価器
 * StablePtr実装
 * 並列実行プリミィティブ
 * ランタイム初期化

上記の要素はある程度POSIX APIに依存しています。
これらの依存APIを自前で用意することで、
Ajhcの吐き出すバイナリをPOSIXではない独自のアーキティクチャに移植できます。
例えば先の@<code>{print "hoge"}するだけのHaskellプログラムはどの程度POSIXに依存しているのでしょうか。

//cmd{
$ cat Hoge.hs
main = print "hoge"
$ ajhc Hoge.hs
$ size hs.out
   text    data     bss     dec     hex filename
  20544    1357     552   22453    57b5 hs.out
$ ldd hs.out
        linux-vdso.so.1 (0x00007fff217d7000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f4df2d10000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f4df30fc000)
$ nm hs.out | grep -c "U "
20
$ nm hs.out | grep "U "
                 U _IO_putc@@GLIBC_2.2.5
                 U __libc_start_main@@GLIBC_2.2.5
                 U _setjmp@@GLIBC_2.2.5
                 U abort@@GLIBC_2.2.5
                 U ctime@@GLIBC_2.2.5
                 U exit@@GLIBC_2.2.5
                 U fflush@@GLIBC_2.2.5
                 U fprintf@@GLIBC_2.2.5
                 U fputc@@GLIBC_2.2.5
                 U fputs@@GLIBC_2.2.5
                 U free@@GLIBC_2.2.5
                 U fwrite@@GLIBC_2.2.5
                 U getenv@@GLIBC_2.2.5
                 U malloc@@GLIBC_2.2.5
                 U memset@@GLIBC_2.2.5
                 U posix_memalign@@GLIBC_2.2.5
                 U realloc@@GLIBC_2.2.5
                 U setlocale@@GLIBC_2.2.5
                 U sysconf@@GLIBC_2.2.5
                 U times@@GLIBC_2.2.5
//}

実行プログラムのサイズは20kB程度しかなく、依存するライブラリはlibcのみ。
そして未解決シンボルは20個しかありません。
極論するとこの20個のシンボルに対応する実装をAjhcランタイムの下に配置できれば、
Ajhcの吐き出すバイナリの移植は完了したことになります。

実はマイコンなどへの移植はもっと簡単にでき、シリアルコンソール対応を考えなければ以下のシンボルのみ実装すれば良いことがわかっています。

 * abort
 * free
 * malloc
 * memset
 * realloc

つまりAjhcランタイムの主な依存はmalloc機構のみ、ということになります。
マイコンへのAjhcバイナリの移植例は
@<href>{https://github.com/ajhc/demo-cortex-m3}
を参考にしてください。

== ソースコード配置

@<list>{ajhc_src_tree} はAjhcのソースコード
@<href>{https://github.com/ajhc/ajhc}
の構造です。

//list[ajhc_src_tree][Ajhcソースコードツリー]{
ajhc
|-- ac-macros (configure用マクロ)
|-- bugs (原作者Johnのまとめたバグレポート)
|-- docs (Ajhcユーザーズマニュアル生成用markdown)
|   |-- announce (jhcのリリースノート置き場)
|   `-- announce_ajhc (Ajhcのリリースノート置き場)
|-- examples
|-- lib (hlファイルのソースコード)
|   |-- applicative
|   |-- ext
|   |-- flat-foreign
|   |-- haskell-extras
|   |-- haskell2010
|   |-- haskell98
|   |-- jhc
|   `-- jhc-prim
|-- po (Ajhcユーザーズマニュアル翻訳用poファイル)
|   `-- ja.po
|-- regress (回帰テスト置き場)
|   |-- regress.prl
|   `-- tests
|-- rts
|   |-- lib
|   |-- rts (Ajhcランタイムソースコード)
|   |-- sys
|   `-- test (Ajhcランタイム単体テスト)
|-- selftest (Ajhcコンパイラパイプライン単体テスト)
|-- src (Ajhcコンパイラパイプラインソースコード)
|   |-- C
|   |-- Cmm
|   |-- DerivingDrift
|   |-- Doc
|   |-- E
|   |-- Fixer
|   |-- FrontEnd
|   |-- Grin
|   |-- Ho
|   |-- Info
|   |-- Name
|   |-- StringTable
|   |-- Support
|   |-- Util
|   |-- Version
|   |-- cbits
|   `-- data
|-- src_jahm (パッケージマネージャソースコード)
|-- src_main (ajhcコマンドソースコード)
`-- utils
//}

この本で取り扱う範囲で注目すべきは以下のディレクトリでしょう。

 * ajhc/lib (hlファイルのソースコード)
 * ajhc/rts/rts (Ajhcランタイムソースコード)
 * ajhc/src (Ajhcコンパイラパイプラインソースコード)
