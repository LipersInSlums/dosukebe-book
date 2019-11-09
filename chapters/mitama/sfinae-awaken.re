= SFINAEの覚醒

C++11の時代に突入してメタプログラミングは現代のC++を構成する大きな機能を手にした。

「任意の式によるSFINAE（Substitution Failure Is Not An Error）」である。

== SFINAE

SFINAE（Substitution Failure Is Not An Error）とは、
（テンプレートの）実体化の失敗はエラーではないという意味である。

テンプレートの実体化に失敗しても即座にはエラーにならず、他の実体化できるテンプレートを探すという言語仕様のことを指す。
この機能を利用することによって、テンプレートの実体化を任意にコントロールすることが可能となる。
C++11ではこれを補助するため、標準ライブラリに@<code>{<type_traits>}ヘッダが登場した。

== Associated Type

C++のクラスはメンバに型を持つことができる。

//emlist[Associated Type][cpp]{
template <class T>
struct MyClass { using value_type = T; };
//}

このとき、@<code>{value_type}は@<code>{MyClass<T>}のAssociated Typeであると言う。
テンプレートメタプログラミングではAssociated Typeを多用する。

@<code>{typename MyClass<int>::value_type}のようにしてAssociated Typeを取り出し、型名として利用できる。

== enable_if

次の関数は引数の型Tがvalue_typeというAssociated Typeを持っていない場合オーバーロードの候補から除外される。

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

