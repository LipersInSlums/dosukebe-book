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
docker run --mount type=bind,source=/absolute/path/to/dosukebe-book,target=/book --rm -it vvakame/review:4.0 /bin/sh -c "cd /book && ./build.sh"
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
