= 可変長テンプレート

テンプレートパラメータを可変個受け取ることができる神機能。
C++の機能の中でも難しいと言われがちな機能であるが、ジェネリックライブラリの設計やメタプログラミングには欠かせない。

//emlist[可変長テンプレート][]{
template <class... Types> class X {};

template <class... Args>
void func(Args... args) {
    // ...
}
//}

@<code>{Args}や@<code>{args}などは@<b>{パラメータパック}と呼ばれ、型や値がまとまった状態になっている。
これを使用するためにはパラメータパックを@<b>{expansion (展開)}する必要がある。

//emlist[型パラメータパックの展開][cpp-example]{
#include <tuple>
template <class... Types> class X {
    // 型をtupleのテンプレート引数に展開
    std::tuple<Types...> values;
};

int main(){
    X<int, double, float> x;
}
//}

//emlist[関数パラメータパックの展開][cpp-example]{
#include <iostream>

// パラメータパックが空になったら終了
void print() {}

template <class Head, class... Tail>
void print(Head head, Tail... tail) {
    std::cout << head << "\n"; // 1つ目の引数を処理
    print(tail...); // 残りを再展開してheadとtailに分解
}


int main() {
    print(1, 2.0, "3");
}
//}

== 型リスト

メタプログラミングと言ったらこれでしょ。

型のリストを処理する。C++には可変長テンプレートがあるので簡単にできる。
まずは型リストの箱を作る。

//emlist[型リスト][]{
template <class... Types> class type_list {};
//}

== 型レベルアルゴリズム (線形再帰)

先程の型リストに対して、N個目の型を得ることができる型レベル関数を作ろう。
最も簡単であろう実装は、線形再帰である。
@<code>{list_element<N, Types...>}に対して、N回@<code>{Types...}の先頭を取り除いたあと、先頭がN番目の型である。

//emlist[線形再帰による探索][cpp-example]{
#include <tuple>
#include <type_traits>

template <std::size_t, class>
struct list_element;

template <std::size_t I,
          template <class...> class TList,
          class Head, class... Tail>
struct list_element<I, TList<Head, Tail...>>
    : list_element<I-1, TList<Tail...>> {};

template <template <class...> class TList,
          class Head, class... Tail>
struct list_element<0, TList<Head, Tail...>>
    { using type = Head; };

template <std::size_t N, class TList>
using list_element_t = typename list_element<N, TList>::type;

int main(){
    static_assert(std::is_same_v<float,
        list_element_t<2, std::tuple<int, short, float>>>);
}
//}

再帰的なクラスの実体化による継承の結果、目的の型をメンバ型として持つクラスが出来上がる。
@<code>{list_element_t<1, type_list<A, B, C>}は@<code>{B}となる。

@<code>{template <class...> class TList}という文法が登場した。
これはテンプレートテンプレートパラメータである。
テンプレート引数を可変個とる何らかの型をテンプレートパラメータにとることができる。
@<code>{list_element<N, type_list<Head, Tail...>>}のように、決め打ちで受け取ってもいいが、
型リストとみなせるものをまとめて受け取れるようになるのでこのほうがいいだろう。

このような型リストを操作する方法はメタプログラミングではよく行われる。
