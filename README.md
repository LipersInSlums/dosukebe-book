# dosukebe-book

## 環境構築

## gitのインストールとリポジトリのクローン

まず、任意のパッケージマネージャでgitをインストール。
ssh鍵をgithubに登録することを強く推奨する。

任意のわかりやすい作業ディレクトリでクローンを実行すればよい。

```shell
$ git clone git@github.com:LipersInSlums/dosukebe-book.git
```

## docker を使う場合

- [docker intall](https://docs.docker.com/install/) にしたがってインストール。
- dockerユーザーグループにユーザーを追加する（任意だが、以下はやったものとして進める）
- `docker pull vvakame/review:4.0`で公式のDocker Imageをもってくる。

以下のコマンドでビルド可能。

```shell
docker run --mount type=bind,source=/absolute/path/to/dosukebe-book,target=/book --rm -it vvakame/review:4.0 /bin/sh -c "cd /book && ./build.sh"
```

