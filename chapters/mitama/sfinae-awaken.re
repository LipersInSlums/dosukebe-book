= SFINAEの覚醒

C++11の時代に突入してメタプログラミングは現代のC++を構成する大きな機能を手にした。

「任意の式によるSFINAE（Substitution Failure Is Not An Error）」である。

== SFINAE

SFINAE（Substitution Failure Is Not An Error）とは、
（テンプレートの）実体化の失敗はエラーではないという意味である。

テンプレートの実体化に失敗しても即座にはエラーにならず、他の実体化できるテンプレートを探すという言語仕様のことを指す。
この機能を利用することによって、テンプレートの実体化を任意にコントロールすることが可能となる。
C++11ではこれを補助するため、標準ライブラリに@<code>{<type_traits>}ヘッダが登場した。

== 関連型

C++のクラスはメンバに型を持つことができる。

//emlist[関連型][cpp]{
template <class T>
struct MyClass { using value_type = T; };
//}

このとき、@<code>{value_type}は@<code>{MyClass<T>}の関連型であると言う。
テンプレートメタプログラミングでは関連型を多用する。

@<code>{typename MyClass<int>::value_type}のようにして関連型を取り出し、型名として利用できる。

== enable_if

次の関数#1は引数の型Tがvalue_typeという関連型を持っていない場合オーバーロードの候補から除外される。

//emlist[][cpp-example]{
template <class T>
struct MyClass { using value_type = T; };

template <class T>
typename T::value_type func(T const&) { return {}; } // #1

void func(...) {} // #2

int main() {
    func(MyClass<int>{});   // #1
    func(1);                // #2
}
//}

@<code>{func(1)}の呼び出しでは#1はオーバーロードの候補から外され、#2が呼び出される。
これがSFINAEの効果である。

これを便利にするために@<code>{std::enable_if}を使う。

第一テンプレートパラメータがboolを受け取り、
第二テンプレートパラメータが型を受け取る（省略するとvoid型になる）。

@<code>{std::enable_if}は受け取ったbool値がtrueであるときのみ関連型typeを持つ。

//emlist[][]{
namespace std {
    template <bool, class T = void>
    struct enable_if { type = T; };

    template <class T>
    struct enable_if<false, T> {};

    template <bool B, class T = void>
    using enable_if_t = typename enable_if<B, T>::type;
}
//}

これを用いて、次のようにすることで任意の判定によってテンプレートをオーバーロードの候補から外すことができる。
判定結果が@<code>{false}の場合には@<code>{enable_if}が関連型を持たないため実体化に失敗するからである。

//emlist[][]{
template <class T>
std::enable_if_t<{Tに関して何かを判定する}, {戻り値型}>
func(T const&) { return ...; }
//}

== メタ述語

{Tに関して何かを判定する}のところには型を受け取ってbool値を返すものを書く必要がある。
型を受け取ってなにか結果を返すようなものはC++ではメタ述語（メタ関数）と呼ばれている。

標準ライブラリ@<code>{<type_traits>}にはメタ関数が100個以上用意されている。
メタ関数は大きく分けて、型を受け取り型を返すものと、型を受け取って加工された型を返すものがある。

@<code>{enable_if_t}も@<code>{<type_traits>}に存在する。

