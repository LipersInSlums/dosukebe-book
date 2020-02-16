= メタプログラミングの夜明け

== メタプログラミングとは

//quote{
メタプログラミング (metaprogramming) とはプログラミング技法の一種で、
ロジックを直接コーディングするのではなく、
あるパターンをもったロジックを生成する高位ロジックによってプログラミングを行う方法、
またその高位ロジックを定義する方法のこと。

主に対象言語に埋め込まれたマクロ言語によって行われる。
//}

-- Wikipediaより

== C++が持つマクロ機能

=== C言語から受け継いだマクロ

C++はC言語から存在するCプリプロセッサマクロが使える。
プリプロセッサマクロによってメタプログラミングができる。
ただし、プリプロセッサマクロは単なる文字列の置き換えにすぎない。
名前空間を汚染するし、意図しないマクロの展開のデバッグは果てしなく困難である。

C++にはテンプレートという機能がある。
テンプレートを使うことによって型システムに守られたメタプログラミングが可能になる。

=== テンプレート

テンプレートという名前からわかるように、
テンプレートの機能は雛形を定義しておくことによって少しずつ違う関数やクラスをコンパイラが自動生成できる機能である。
テンプレートには型や整数を渡すことができる。

例を見てみよう。

C++にはオーバーロードがあり、関数を引数の型で呼び分けることができるので次が可能。

//emlist[関数オーバーロード][cpp-example]{
int twice(int a, int b) { return a + b; }           // #1
double twice(double a, double b) { return a + b; }  // #2

int main() {
    twice(1, 2);     // #1
    twice(1.1, 2.2); // #2
}
//}

関数本体は全く同じであるので、こんなものをたくさん書きたくはない。
コンパイラに自動生成してほしい。

そこで関数テンプレートを使う。

//emlist[関数テンプレート][cpp-example]{
template <class T>
T twice(T a, T b) { return a + b; }

int main() {
    twice<int>(1, 2); // T = int
    twice(1.1, 2.2);  // T = double
    // twice(1.1, 2); // Error: T = int or double ???
}
//}

1つ目は明示的にテンプレートに型を渡す方法である。
2つ目は暗黙に引数から型を推論している (1.1と2.2はdouble型であることをコンパイラは知っているため@<code>{T = double}を導出可能)。
3つ目のように引数の型Tが異なる型に推論された場合、コンパイルエラーとなる（マクロと違って型がついていて安全）。

同様にクラステンプレートも可能である。

//emlist[クラステンプレート][]{
template <class T>
struct MyClass {
    T value_;
    T value() const { return value_; }
};

template <class T> MyClass(T) -> MyClass<T>;

int main() {
    MyClass<int> a{1};  // T = int
    MyClass b{1.2};     // T = double
}
//}

== テンプレートの特殊化

ここではクラステンプレートの明示的特殊化について述べる。
特定の型に対して特殊な実装に実体化させることができる機能である。

次の例ではMyClassのvoidに対する明示的特殊化を行っている。
最初に宣言されるMyClassをプライマリーテンプレートと呼ぶ。
@<code>{template <>}で始まり、
クラス名に対して@<code>{MyClass<void>}のように
明示的にテンプレートパラメータを指定したものをクラステンプレートの明示的特殊化と呼ぶ。

//emlist[クラステンプレートの明示的特殊化][cpp-example]{
#include <cassert>
#include <string>

template <class T>
struct MyClass { // プライマリーテンプレート
    static std::string func() { return "primary"; }
};

template <>
struct MyClass<void> { // テンプレートの明示的特殊化
    static std::string func() { return "specialization"; }
};

int main() {
    assert(MyClass<int>::func() == "primary");
    assert(MyClass<void>::func() == "specialization");
}
//}

== 原初のメタプログラミング

 * テンプレートには型だけではなく整数を渡せる
 * テンプレートを明示的に特殊化できる

以上の2点に加えてクラステンプレートが再帰的に実体化できるという事実により、
メタプログラミングが可能となった。

早速、コンパイル時に階乗を計算してみよう。

//emlist[enum hack][cpp-example]{
template <int N>
struct Factorial
{ enum { value = N * Factorial<N - 1>::value }; };

template <>
struct Factorial<0>
{ enum { value = 1 }; };

int main() {
    static_assert(Factorial<4>::value == 24);
}
//}

テンプレートの明示的特殊化が分岐として機能し、再帰的にクラステンプレートが実体化することにより計算が可能になる。

さらっと登場した@<code>{template <int N>}なる文法は@<b>{Non-Type Template Parameter (非型テンプレート引数)}という機能。
型ではないもの（C++17までは整数かenum値のみ）を渡すことができる機能である。
整数を直接テンプレートに埋め込めるため、ペアノ数などを型で表現する必要はない。

これが、原初に発見された（発明ではなく発見）テンプレートメタプログラミングのアイデアである。
最初にメタプログラミングが発見されたあと、次々とメタプログラミング技法が見出されることになる。
結果として、C++03からC++11にかけて、C++はメタプログラミング時代に突入した。
このメタプログラミングの波は他の言語にも大きな影響を与えたのではないかと思う。
C++11からはコンパイル時有理数算術などが標準で当たり前のようにサポートされている。
