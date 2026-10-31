[English](../README.md) | [简体中文](README.zh-CN.md) | **日本語**

# F's Plugins Multilingual Edition

このプロジェクトは [bryful/F-s-PluginsProjects](https://github.com/bryful/F-s-PluginsProjects) の
[`47a9d2c`](https://github.com/bryful/F-s-PluginsProjects/commit/47a9d2c7a322e5ed0ea09c77bbd90cf5a54cb7bf)
を基点としています。配布版は `v1.0.0` から始まります。

- **翻訳・プログラム保守**：loneprison
- **校正**：光学核心

このリポジトリでは、既定の `master` ブランチで F's Plugins を、
[`nf` ブランチ](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/tree/nf)で NF Plugins を保守しています。
この README は F's Plugins の説明です。

[開発ガイド](DEVELOPMENT.ja.md) · [翻訳レビュー](../_localization/README.ja.md) · [原作者の README](README.original.md)

Adobe After Effects 用 F's Plugins の Windows x64 多言語保守版です。日本語原文、簡体中国語、
英語の UI を提供し、元のプラグイン名と Match Name を維持します。

> [!IMPORTANT]
> `v1.0.0` は準備中です。正式公開後は GitHub Releases の配布パッケージを使用してください。

## インストール

GitHub Releases から `Fs-Plugins-Multilingual-v1.0.0-win.zip` をダウンロードします。After Effects を
終了し、展開した `Fs_Plugins` ディレクトリを構成を保ったままプラグインディレクトリへコピーして、
After Effects を再起動してください。

中・英・日のガイドと `LICENSE` を含みます。macOS はサポートしません。

## 言語

任意の F's エフェクトの **オプション／Options** から `F's Language Settings` を開きます。

- 自動
- English
- 日本語原文
- 簡体中国語
- 簡体中国語の文字コード環境向け日本語原文

AE 23 以降の自動モードは AE の UI 言語を使用し、簡体中国語では中国語、日本語では日本語原文、
その他では英語を選択します。AE 22 以前は Windows ANSI コードページを使用し、CP936 では中国語、
CP932 では日本語、その他または不明な場合は英語を選択します。

保存した設定を有効にするには After Effects を再起動してください。Language Settings がない、または
利用できない場合、各エフェクトは日本語原文を既定で使用します。

## 配布内容

配布予定は 105 個のエフェクトと 1 個の Language Settings コンポーネントです。
テスト、テンプレート、および次のエフェクトは含みません。

- `ChannelBlur`
- `Extract_Edge`
- `FsSSFrame`
- `ShineParallel`
- `VideoLine2nd`

## 更新履歴

### v1.0.0

- **ビット深度**：以下のプラグインで、8／16／32 bpc 間の描画計算の不一致を修正：
  `ChannelNoise`、`colorThreshold`、`Extract-Hi`、`grayToColorize`、`IroToreAdjacent`、
  `Max`、`MaxBlur`、`MaxFast`、`Max_Kasumi`、`Mosaic`、
  `OpticalDiffusion`、`OutLine`、`PixelSelector`、`RandomMosaic`、`RandomMosaic2nd`、
  `Spark`、`SparkGrand`、`SparkMult`、`SparkRing`、`SparkStorm`、
  `Thin`、`TouchDraw`、`TouchDrawStraght`、`YuvControl`。
- **その他の描画**：以下のプラグインで、色処理、ランダムなブロック分布、ブロック数計算、ダウンサンプリングの不具合を修正：
  `LineTrace`、`Max`、`Max_Kasumi`、`OpticalDiffusion`、`TouchDraw`、
  `TouchDrawStraght`。
- **安定性**：以下のプラグインで AE が予期せずクラッシュする可能性がある問題を修正：
  `Max`、`OpticalDiffusion`、`OutLine`、`smokeThreshold`。
- **UI**：`GuideFrame` の無効な `Smooth` コントロールを非表示にし、`PixelSelector` のコントロール状態を修正。
- **言語**：エフェクト全体に簡体中国語・英語の UI と言語設定を追加し、AE 26.2 以降のパラメーター文字コードに対応。
- **テキスト**：`RandomShift` と `smokeThreshold` の原版のパラメーターラベルの誤りを修正し、`SelectedBlur` の有効パラメーターに 0～7 の番号を追加。
- **About**：不足していた説明文の一部を補完。

## 旧バージョンとの互換性について

AE 26.2 以降のパラメーター文字列は UTF-8 になり、以下のプラグインの一部のプロパティ名が SDK の長さ制限を超えたため、互換性のない変更を行いました。

- `AnimatedNoise`
- `Mosaic`
- `PaintMultPoint`
- `Scanline`

`SelectedBlur` の有効パラメーターにも 0～7 の番号を追加しました。旧名でこれらのパラメーターを参照するエクスプレッションやスクリプトは修正が必要です。

旧プロジェクトとの互換性のため、以下のプラグインに「Legacy」チェックボックスを用意し、従来の描画方式を維持できるようにしています。

- `LineTrace`
- `Max`
- `OpticalDiffusion`
- `TouchDraw`
- `TouchDrawStraght`

## ソースと開発

本保守版では元のリポジトリのディレクトリとファイルを整理し、過去のバックアップ、生成ファイル、
旧バイナリパッケージの一部を削除するとともに、原作者の資料の一部をアーカイブとして保存しています。
削除した内容は Git の履歴から参照できます。

ソースビルドと開発については[開発ガイド](DEVELOPMENT.ja.md)を参照してください。

## ライセンス

リポジトリルートの [MIT License](../LICENSE) と原作者の著作権表示を維持します。
