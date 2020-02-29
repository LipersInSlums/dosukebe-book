= 新たなる希望、constexpr

そもそもの問題として、テンプレートを駆使したメタプログラミングはわかりにくい。
通常のプログラミングとかけ離れすぎている。
コンパイル時にも普通のプログラミングがしたい。

C++11からこの要望を満たすため、@<code>{constexpr}指定子が登場した。
@<code>{constexpr}指定された変数はコンパイル時に初期化され、
@<code>{constexpr}指定された関数はコンパイル時に呼び出すことができる。
ただし、C++11では制限が多く、通常のプログラミングができるとは言いがたかった。

C++14で状況は一変し、
制限が緩和され変数宣言やローカル変数の書き換え、
制御分などがすべてconstexpr関数で行えるようになった。

テンプレートの特殊化を条件分岐に使うという言語機能の悪用とも言えるメタプログラミングから、
わかりやすい方法で記述できるメタプログラミングへと舵を切ったのだ。

この機能を使用することで、

 * コンパイル時に値が決定する定数
 * コンパイル時に実行される関数
 * コンパイル時にリテラルとして振る舞うクラス

を定義できるようになった。

== constexpr関数

C++11から導入された言語機能。
@<b>{コンパイル時にも計算可能}な関数を書くことができる。

C++03ではconstexprがないため、Non-type template parameterに整数を埋め込むという荒業を行うことで実現される。

//emlist[階乗を求めるコンパイル時関数（C++03）][cpp-example]{
template <unsigned long N>
struct factorial { enum { value = N*factorial<N-1>::value }; };

template <>
struct factorial<0> { enum { value = 1 }; };

int main() {
    const unsigned long fact6 = factorial<6>::value; // 720
}
//}

C++11ではconstexprが導入されたが、return文1つ以外に何も書くことができない。
条件分岐は条件演算子、ループは再帰を使って実現される。

//emlist[階乗を求めるコンパイル時関数（C++11）][cpp-example]{
constexpr int factorial (int n) {
    return n > 0 ? n * factorial( n - 1 ) : 1;
}
int main() {
    constexpr auto fact6 = factorial(6); // 720
}
//}

C++14でconstexprが宣言緩和されやや神機能となり、
ローカル変数宣言や制御構文が利用できるようになった。
普段書いている関数にconstexprをつけるだけで簡単にコンパイル時関数として利用できるようになった。

//emlist[階乗を求めるコンパイル時関数（C++14）][cpp-example]{
constexpr int factorial (int n) {
    int res = n;
    while (n --> 1) res *= n;
    return res;
}
int main() {
    constexpr auto fact6 = factorial(6); // 720
}
//}

