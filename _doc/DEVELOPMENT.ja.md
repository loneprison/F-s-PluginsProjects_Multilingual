[English](DEVELOPMENT.en.md) | [简体中文](DEVELOPMENT.md) | **日本語**

# ソースのビルドと開発

[使用ガイド](README.ja.md) · [翻訳レビュー](../_localization/README.ja.md) · [原作者の README](README.upstream.md)

## ソースと環境の準備

1. After Effects SDK 25.6 を展開し、本リポジトリのソースを SDK 内の `Examples\NF-PluginsProjects_Multilingual` に配置します。SDK の構造は保持してください。`Headers`、`Resources`、`Util`、`Examples` は同じ階層にあります。
2. Visual Studio 2026 の「C++ によるデスクトップ開発」をインストールし、MSVC v145 と Windows SDK を含めます。
3. `uv` をインストールします。ローカライズツールは Python 3.12 を使用し、初回実行時に uv がロックファイルに基づく依存環境を準備します。

uv が未インストールの場合は、PowerShell で実行します。

```powershell
powershell -ExecutionPolicy ByPass -c "irm https://astral.sh/uv/install.ps1 | iex"
```

PowerShell を開き直し、本リポジトリのルートディレクトリで確認します。

```powershell
uv --version
.\BuildPlugins.bat --help
```

## 正式な多言語ビルド

ルートの `BuildPlugins.bat` は `_tools/BuildPlugins.ps1` を呼び出します。正式ビルドは `NF-PluginsProjects.slnx` を基準とし、名前が丸括弧で囲まれたソリューションフォルダー（現在は `(_SDK)`）を除外します。固定のプロジェクト一覧は別途管理しません。

```powershell
.\BuildPlugins.bat publication
```

45 個の NF メインラインエフェクトと言語サポートコンポーネントを Release x64 でリビルドし、翻訳と有効なレビュー状態を検証します。エフェクトには作者の原文と簡体中国語が含まれ、標準のフォールバックは原文です。開発用の `_checkout`、`_Skeleton`、`_Test` はソースに残しますが、正式ビルドには含めません。

プラグインは次のディレクトリに直接コンパイルされます。

```text
_build\publication\NF-Plugins\
```

このディレクトリには 46 個の AEX のみが含まれ、正式ビルドのたびに再生成されます。バージョン付きディレクトリへのコピーは行いません。配布時のバージョン名の設定、`_doc/INSTALL.txt` の追加、圧縮は手動で行います。これらはビルド処理に含めません。

ビルドに Git checkout、事前のコミット、クリーンな作業ツリーは必要ありません。ビルドメッセージはコンソールに表示され、ログファイルは自動保存されません。`publication` と `custom` は、ビルド前に現在のモードの `NF-Plugins` 出力ディレクトリを、読み取り専用・隠しファイルも含めて削除します。保存が必要なファイルはこのディレクトリに置かないでください。

## カスタム言語ビルド

```powershell
.\BuildPlugins.bat custom --default-language zh
.\BuildPlugins.bat custom --default-language zh --single-language
.\BuildPlugins.bat custom --default-language source --single-language
```

`--default-language` には `source`（作者の原文）または `zh`（簡体中国語）を指定します。

- `--single-language` なし：多言語機能と言語サポートコンポーネントを含めます。言語サービスが利用できない場合は指定言語を使用し、利用できる場合は NF の言語設定に従います。
- `--single-language` あり：指定言語の 45 個のエフェクトのみをビルドし、言語サポートコンポーネントは含めません。プロジェクト側のルールでビルドモードを検証してから、このコンポーネントのビルドをスキップします。ホストに言語サポートコンポーネントがインストールされていても、常に指定言語を使用します。

出力先は `_build\custom\multilingual-<言語>` または `_build\custom\single-<言語>` で、分類済みの `NF-Plugins` ディレクトリ内のプラグインのみを含みます。カスタム版は個人利用向けです。正式な多言語版には `publication` を使用してください。

## 通常の開発ビルド

手動でコンパイルするユーザー向けに、標準の Debug/Release x64 構成を保持しています。Visual Studio で `NF-PluginsProjects.slnx` を開いて構成を選択するか、Visual Studio の開発者用ターミナルで MSBuild を使用してください。

```powershell
MSBuild NF-PluginsProjects.slnx /p:Configuration=Release /p:Platform=x64
MSBuild NF-PluginsProjects.slnx /p:Configuration=Debug /p:Platform=x64
```

先に次節の説明に従って出力先を設定してください。通常のビルドは `AE_PLUGIN_BUILD_DIR` 配下の `NF-Plugins\<分類>` に出力します。Debug のファイル名には `NF-AlphaFill_d.aex` のように `_d` が付きます。ルートの BAT は `publication/custom` のみを提供します。リンク成功後、同じ出力ディレクトリにある同一プラグインの別構成の AEX を削除します。Release では対応する `_d.aex` を、Debug では `_d` のない対応する AEX を削除します。

中間ファイルは各プロジェクトの `Win\x64\<構成>` に、生成されたテキストヘッダーはその中の `Localization` に置かれます。

## Visual Studio とローカルパス

Visual Studio を使用する場合は、次の Windows ユーザー環境変数を設定します。

- `AE_PLUGIN_BUILD_DIR`：プラグインの出力ルート。各プロジェクトが `NF-Plugins\<分類>` を追加します。
- `AE_DEBUG_HOST_EXE`：Debug/F5 で使用する `AfterFX.exe` のパス。

PowerShell での設定例です。ホストのパスは実際のインストール先に置き換えてください。

```powershell
New-Item -ItemType Directory -Force 'D:\AePluginBuild'
[Environment]::SetEnvironmentVariable('AE_PLUGIN_BUILD_DIR', 'D:\AePluginBuild', 'User')
[Environment]::SetEnvironmentVariable(
    'AE_DEBUG_HOST_EXE',
    'C:\Program Files\Adobe\Adobe After Effects 2024\Support Files\AfterFX.exe',
    'User'
)
```

Visual Studio とターミナルを開き直します。`NF-PluginsProjects.slnx` を開き、Debug または Release / x64 を選択してください。`BuildPlugins.bat` のみを使う場合、この 2 つの変数の設定は不要です。

別の方法として、ルートの `Directory.Build.props` の最初の属性グループ内で、`NfRawOutDir` より前にローカルの既定値を設定できます。

```xml
<AE_PLUGIN_BUILD_DIR Condition="'$(AE_PLUGIN_BUILD_DIR)'==''">D:\AePluginBuild</AE_PLUGIN_BUILD_DIR>
<AE_DEBUG_HOST_EXE Condition="'$(AE_DEBUG_HOST_EXE)'==''">C:\Program Files\Adobe\Adobe After Effects 2024\Support Files\AfterFX.exe</AE_DEBUG_HOST_EXE>
```

Visual Studio から直接ビルドすると、設定した出力ディレクトリに書き込みます。3 つの `(_SDK)` 開発プロジェクトは既定のビルド対象外ですが、必要に応じて個別にビルドできます。

## 分類と翻訳ディレクトリ

メインラインエフェクトでは、PiPL の `Category`、`Directory.Build.PluginMap.props` の出力カテゴリ、ソリューションフォルダー、翻訳ディレクトリを一致させます。例えば AlphaFill は `_localization/catalog/NF-Channel/AlphaFill.json` と `_localization/review-state/NF-Channel/AlphaFill.json` を使用します。

3 つの開発プロジェクトの翻訳とレビュー状態は、それぞれの `(_SDK)` サブディレクトリに置きます。ソリューションと出力のグループも `(_SDK)` のまま、既定ではビルドしません。ソース内のエフェクトカテゴリ名は保持します。Language Settings のソリューションフォルダーとプラグイン出力は `_Support` ですが、`Settings.json` は `catalog` と `review-state` の各ルート直下に置き、通常のエフェクトカテゴリでは分類しません。

実際のビルド準備時に、翻訳ファイル、ソースカテゴリ、出力設定、ソリューションフォルダーの整合性を読み取り専用で検査します。通常の Debug/Release、publication、custom に適用し、Visual Studio のデザイン時評価では省略します。単一言語 custom でコンパイルを省略する Settings には、引き続きビルドモードの規則が適用されます。検査に失敗すると対象プロジェクトのビルドを停止し、ディレクトリや分類を自動変更することはありません。

コンパイルせずに 1 つのプロジェクトを検査するには、リポジトリのルートで実行します。

```powershell
uv run --locked --no-dev --project .\_localization\tools aetext check-classification --repository . --project .\AlphaFill\Win\AlphaFill.vcxproj
```

カテゴリを変更する場合は、上記のパスと設定、およびプロジェクトの翻訳ファイル参照を同時に更新してください。`review-state` は `catalog` と同じ相対パスを使います。ディレクトリ移動ではファイル内容をそのまま保持し、その後レビューツールで対象プロジェクトを再スキャンします。

## ローカライズコードの書き方

原文は `L10N_*` マクロで定義し、表示時には対応する `AETEXT_*` ラッパーを使用します。文字列を使う関数やコールバックごとに、対象エフェクトの `Strings(in_data)` を 1 つ作成し、同じスコープ内で共有します。AlphaFill の例：

```cpp
const AlphaFillText::Strings strings(in_data);
const char* label = AETEXT_PARAM(strings, L10N_PARAM_MODE);
```

以下の ID は記述形式の例です。既存プロジェクトの安定 ID と原文は保持してください。

| ラッパーの形式 | 用途 |
| --- | --- |
| `AETEXT_PARAM(strings, L10N_PARAM_<NAME>)` | パラメーター名 |
| `AETEXT_LABEL(strings, L10N_LABEL_<NAME>)` | コントロールの文字 |
| `AETEXT_POPUP(strings, L10N_POPUP_<NAME>)` | ドロップダウン項目 |
| `AETEXT_TOPIC(strings, L10N_<NAME>_TOPIC)` | グループ見出し |
| `AETEXT_ABOUT(strings, L10N_PLUGIN_<NAME>)` | プラグイン説明 |
| `AETEXT_ERROR(strings, L10N_ERR_<NAME>)` | エラーメッセージ |
| `AETEXT_VERBATIM_PARAM(strings, L10N_PARAM_<NAME>)` | 原文のパラメーター名 |
| `AETEXT_VERBATIM_LABEL(strings, L10N_LABEL_<NAME>)` | 原文のコントロール文字 |
| `AETEXT_VERBATIM_POPUP(strings, L10N_POPUP_<NAME>)` | 原文のドロップダウン項目 |
| `AETEXT_VERBATIM_TOPIC(strings, L10N_<NAME>_TOPIC)` | 原文のグループ見出し |
| `AETEXT_VERBATIM_ABOUT(strings, L10N_PLUGIN_<NAME>)` | 原文のプラグイン説明 |
| `AETEXT_VERBATIM_ERROR(strings, L10N_ERR_<NAME>)` | 原文のエラーメッセージ |

`AETEXT_VERBATIM_*` は翻訳処理の対象外です。原文マクロを追加・削除・変更した場合や文字列ラッパーを変更した場合は、レビューツールで該当プラグインを再スキャンします。パラメーター ID、ドロップダウンの項目順、プラグインの Match Name は保持してください。

## 翻訳への貢献

翻訳を変更または提供する場合は、[翻訳レビューガイド](../_localization/README.ja.md)をご覧ください。

## コードへの貢献

コードの変更は Pull Request で提出してください。
