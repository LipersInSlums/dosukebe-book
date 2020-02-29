# dosukebe-book

## 環境構築

Re:VIEW 4.0を使う。

## gitのインストールとリポジトリのクローン

まず、任意のパッケージマネージャでgitをインストール。
ssh鍵をgithubに登録することを強く推奨する。

任意のわかりやすい作業ディレクトリでクローンを実行すればよい。

```shell
$ git clone git@github.com:LipersInSlums/dosukebe-book.git
```

## docker を使う場合

- [docker install](https://docs.docker.com/install/) にしたがってインストール。
- dockerユーザーグループにユーザーを追加する（任意だが、以下はやったものとして進める）
- `docker pull vvakame/review:4.0`で公式のDocker Imageをもってくる。

以下のコマンドでビルド可能。

```shell
docker-compose up
```

注意:
ubuntu 19.10はまだパッケージがないので

```shell
$ sudo add-apt-repository \
   "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
   $(lsb_release -cs) \
   stable"
```

を実行しないこと。

```shell
$ sudo add-apt-repository \
   "deb [arch=amd64] https://download.docker.com/linux/ubuntu disco stable"
```

として、無理やりDiscoのパッケージを利用することでなんとかなる。

## ローカル環境を作る場合

自分で頑張れ。
Debian系の場合、上記Docker imageを参考に必要物を入れていけばできるはずだ。

PDFを作るだけであれば、TeXLiveとreviewがあれば他にはなにもいらない。

## 執筆のルール

### reファイルを置く場所

`repository-root/chapters/{自分のディレクトリ}` 以下に配置すること。
1つのファイルが1章になる。

### catalog.ymlファイルの編集

以下のように章を2つ作った場合を考える。

```
chapters/
　├ mitama/
　 └ cp1.re
　 └ cp2.re
```

`book/catalog.yml`を次のように編集することでPDFに反映される。
`repository-root/chapters/{自分のディレクトリ}`における`{自分のディレクトリ}`を接頭辞としてハイフンに続いてファイル名を記述する必要がある。

```diff
CHAPS:
+  - mitama-cp1.re
+  - mitama-cp2.re
```
