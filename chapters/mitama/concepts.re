= コンセプトの帰還

200x年までにリリース予定のC++0xから削除され、C++0xのリリースを遅らせた伝説の機能。
結局2011年にコンセプトなしでC++11が出たが、その間「0xは16進数のこと」という冗談が流行っていたのは有名なこと。
C++20ではコンセプトが帰ってくる（軽量化されて）。
コンセプトがあれば玄人技だったSFINAEはほとんどがユーザーの目に留まるところから消えてコンパイラが勝手に置換してくれることになる。

最後に未来のC++、C++20の話をして締めくくりたい。

SFINAEを利用することとコンセプトを利用することの一番の違いは、オーバーヘッド解決である。
コンセプトには優先順位がつくため、複数のコンセプトにマッチしたとしても、オーバーヘッドが解決する。
これはSFINAEではできなかったことである。

== concept

コンセプトは型に対する要求を記述できる機能である。

//emlist[コンセプト][]{
template <class T>
concept Printable = requires (T& x) {
  x.print(); // 要求する操作をセミコロン区切りで列挙する。
            // これは、メンバ関数print()を呼び出せることを要求する。
};
//}

コンセプトに型を適用するとbool値を返す。

//emlist[][]{
#include <concepts>
static_assert(std::integral<int>);    // OK
static_assert(std::integral<double>); // ERROR
//}

テンプレート宣言の代わりに、制約つきのテンプレートとして使うことができる。
コンセプトの第一引数に関数の引数から推論された型が自動的に適用され、trueを返す場合、オーバーロード候補になる。

//emlist[][]{
#include <concepts>
template <std::integral T>
bool equal(T a, T b) {
  return a == b;
}
//}

実はC++20からは関数テンプレートの引数をautoで宣言できる。
便利すぎる。

//emlist[][]{
bool f(auto a, auto b);
// 以下と同様
// template <class T, class U>
// bool f(T a, U b);
//}

実はコンセプトはautoが書ける場所にはすべて書ける。
以下のように書く事ができる。

//emlist[][]{
bool f(std::integral auto a, std::integral auto b);
//}

変数宣言に制約を書ける。

//emlist[][]{
std::integral auto value = func();
//}

これを使えば例えば単位つきの型を使ったライブラリで

//emlist[][]{
units::length auto value = 12_mps * 3_sec;
//}

みたいな感じで利用できそう。

