= 可変長テンプレート

テンプレートパラメータを可変個受け取ることができる神機能。
C++の機能の中でも難しいと言われがちな機能であるが、ライブラリの設計やメタプログラミングには欠かせない。

//emlist[可変長テンプレート][cpp-example]{
template <class... Types> class X {};

template <class... Args>
void func(Args... args) {
    // ...
}
//}

@<code>{Args}や@<code>{args}などは@<b>{パラメータパック}と呼ばれ、型や値がまとまった状態になっている。
これを使用するためにはパラメータパックを@<b>{expansion (展開)}する必要がある。

//emlist[型パラメータパックの展開][cpp-example]{
template <class... Types> class X {
    // 型をtupleのテンプレート引数に展開
    std::tuple<Types...> values;
};
//}

//emlist[関数パラメータパックの展開][cpp-example]{
template <class Head, class... Tail>
void print(Head head, Tail... tail) {
    std::cout << head << "\n"; // 1つ目の引数を処理
    print(tail...); // 残りを再展開してheadとtailに分解
}
// パラメータパックが空になったら終了
void print() {}
//}

== 型リスト

メタプログラミングと言ったらこれでしょ。

型のリストを処理する。C++には可変長テンプレートがあるので簡単にできる。
まずは型リストの箱を作る。

//emlist[型リスト][cpp-example]{
template <class... Types> class type_list {};
//}

