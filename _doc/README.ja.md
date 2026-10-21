[English](../README.md) | [简体中文](README.zh-CN.md) | **日本語**

# NF Plugins Multilingual Edition

このリポジトリでは、[master ブランチで F’s Plugins](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/blob/master/_docs/README.ja.md)、[nf ブランチで NF Plugins](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/blob/nf/_doc/README.ja.md) を保守しています。このページは NF Plugins の説明です。

[開発ガイド](DEVELOPMENT.ja.md) · [翻訳レビュー](../_localization/README.ja.md) · [原作者の README](README.upstream.md)

bryful 氏の NF Plugins を基にした、Adobe After Effects 用の Windows x64 ローカライズ版です。
作者の原文と簡体中国語の UI を提供し、元のプラグイン名、Match Name、描画処理を維持します。

> 本保守版のバージョンは原作者の `v1.1.0` に合わせています。ローカルパッケージは作成済みですが、未公開です。

## インストール

After Effects を終了し、展開した `NF-Plugins` フォルダーを次の場所へコピーしてください。

```text
C:\Program Files\Adobe\Common\Plug-ins\7.0\MediaCore\
```

`_Support` を含むすべてのサブフォルダーを保持し、After Effects を再起動します。
更新時は、旧 NF フォルダーをプラグインディレクトリの外へ移してバックアップし、重複を避けてください。
既存の F's Plugins は NF と併用できます。

正式ビルドは `_build/publication/NF-Plugins` にプラグイン本体を直接出力します。
配布時のバージョン名の設定、`_doc/INSTALL.txt` の追加、圧縮は手動で行います。これらはビルド処理に含めません。
Windows x64 向けにファイルをコピーしてインストールします。macOS 版はありません。

## 言語

エフェクトコントロールパネルで任意の NF エフェクトの **オプション／Options** を開き、次から選びます。

- **自動**：After Effects の UI が簡体中国語なら中国語を、それ以外の場合は作者の原文を使用します。
- **原文**：各エフェクトの原文を使用します。英語と日本語が含まれる場合があります。
- **簡体中国語**：中国語訳を使用します。

保存後に After Effects を再起動すると、すべての NF エフェクトに適用されます。
現在のセッションでは言語は変わりません。言語サポートコンポーネントがない場合、各エフェクトは自身の原文を使用します。

設定ウィンドウ自体の英語・中国語・日本語表示は、エフェクトの翻訳言語とは別です。
NF の言語設定は F's Plugins から独立しています。

## パッケージ内容

**45 個の NF エフェクトと 1 個の NF Language Settings、計 46 個の Release AEX** を含みます。
開発用の `_checkout`、`_Skeleton`、`_Test` はソースに残し、パッケージには含めません。

F's Plugins のローカライズ版については、[F's Plugins Multilingual プロジェクト](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/blob/master/_docs/README.ja.md)をご覧ください。

## ソースとライセンス

[bryful/F-s-PluginsProjects](https://github.com/bryful/F-s-PluginsProjects) の
[`v1.1.0`](https://github.com/bryful/F-s-PluginsProjects/releases/tag/v1.1.0)（`db6dad3`）を基に保守しています。
パッケージのバージョンは原作者に合わせます。[原作者の README](README.upstream.md) は別に保存しています。

本保守版では元のリポジトリのディレクトリとファイルを整理し、一部の旧プロジェクトと過去の
プラグインバイナリパッケージを削除しています。作者のサンプル、文書、バックアップ資料は
保持またはアーカイブしています。削除した元の内容は Git の履歴から参照できます。

ソースビルドについては[開発ガイド](DEVELOPMENT.ja.md)を参照してください。
リポジトリの [MIT License](../LICENSE) と原作者の著作権表示を維持しています。
