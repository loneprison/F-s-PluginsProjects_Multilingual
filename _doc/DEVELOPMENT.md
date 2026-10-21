[English](DEVELOPMENT.en.md) | **简体中文** | [日本語](DEVELOPMENT.ja.md)

# 源码构建与开发

[使用说明](README.zh-CN.md) · [翻译审校](../_localization/README.zh-CN.md) · [原作者 README](README.upstream.md)

## 准备源码与环境

1. 解压 After Effects SDK 25.6，将本仓库源码放在 SDK 的 `Examples\NF-PluginsProjects_Multilingual` 目录下。保留 SDK 的目录结构，`Headers`、`Resources`、`Util` 与 `Examples` 同级。
2. 安装 Visual Studio 2026，选择“使用 C++ 的桌面开发”，包含 MSVC v145 和 Windows SDK。
3. 安装 `uv`。本地化工具使用 Python 3.12，首次运行时由 uv 准备锁定的依赖环境。

如果尚未安装 uv，在 PowerShell 中运行：

```powershell
powershell -ExecutionPolicy ByPass -c "irm https://astral.sh/uv/install.ps1 | iex"
```

重新打开 PowerShell，进入本仓库根目录，然后检查：

```powershell
uv --version
.\BuildPlugins.bat --help
```

## 正式多语言构建

根目录 `BuildPlugins.bat` 调用 `_tools/BuildPlugins.ps1`；正式构建以 `NF-PluginsProjects.slnx` 为准，排除名称用圆括号包围的解决方案分组（当前为 `(_SDK)`），不另维护固定项目清单。

```powershell
.\BuildPlugins.bat publication
```

该命令对 45 个 NF 主线效果和语言支持组件执行 Release x64 重建，并检查译文及有效审校状态。效果包含作者原文和简体中文，默认回退作者原文。三个开发工程 `_checkout`、`_Skeleton`、`_Test` 保留源码，不参与正式构建。

正式插件直接编译到：

```text
_build\publication\NF-Plugins\
```

该目录仅包含 46 个 AEX，再次正式构建会重新生成此插件目录。构建不复制到版本目录。制作安装包时自行按版本命名、放入 `_doc/INSTALL.txt` 并压缩；这些步骤不参与构建流程。

构建不要求 Git 仓库、预先提交或干净工作区。构建信息输出到控制台，不自动保存日志文件。`publication` 和 `custom` 构建前都会清理当前模式的 `NF-Plugins` 输出目录，包括其中的只读、隐藏文件；请勿在成品目录存放需要保留的文件。

## 自定义语言构建

```powershell
.\BuildPlugins.bat custom --default-language zh
.\BuildPlugins.bat custom --default-language zh --single-language
.\BuildPlugins.bat custom --default-language source --single-language
```

`--default-language` 接受 `source`（作者原文）或 `zh`（简体中文）。

- 不带 `--single-language`：保留多语言和支持组件；语言服务不可用时使用指定语言，服务可用时服从 NF 语言设置。
- 带 `--single-language`：只构建指定语言的 45 个效果，支持组件由工程规则先检查构建模式，再跳过编译。即使宿主安装了语言支持组件，效果也始终使用指定语言。

输出位于 `_build\custom\multilingual-<语言>` 或 `_build\custom\single-<语言>`，仅包含 `NF-Plugins` 分类目录中的插件。自定义版本供个人使用，正式多语言版本使用 `publication`。

## 日常开发构建

工程保留标准的 Debug/Release x64 配置，供需要自行编译的用户使用。在 Visual Studio 中打开 `NF-PluginsProjects.slnx` 并选择配置，或在 Visual Studio 开发者终端中使用 MSBuild：

```powershell
MSBuild NF-PluginsProjects.slnx /p:Configuration=Release /p:Platform=x64
MSBuild NF-PluginsProjects.slnx /p:Configuration=Debug /p:Platform=x64
```

先按下节配置输出路径。普通构建输出到 `AE_PLUGIN_BUILD_DIR` 下的 `NF-Plugins\<类别>`；Debug 文件名带 `_d` 后缀，例如 `NF-AlphaFill_d.aex`。根 BAT 仅提供 `publication/custom` 两种模式。成功链接后，会删除同一输出目录中同插件另一配置的 AEX：Release 清理对应的 `_d.aex`，Debug 清理对应的不带 `_d` 的 AEX。

中间文件位于各工程 `Win\x64\<配置>`，生成的文本头文件位于其中的 `Localization` 目录。

## Visual Studio 与本机路径

使用 Visual Studio 时，配置以下 Windows 用户环境变量：

- `AE_PLUGIN_BUILD_DIR`：插件输出根目录，工程会追加 `NF-Plugins\<类别>`。
- `AE_DEBUG_HOST_EXE`：Debug/F5 使用的 `AfterFX.exe` 路径。

例如，在 PowerShell 中运行，按实际安装位置替换宿主路径：

```powershell
New-Item -ItemType Directory -Force 'D:\AePluginBuild'
[Environment]::SetEnvironmentVariable('AE_PLUGIN_BUILD_DIR', 'D:\AePluginBuild', 'User')
[Environment]::SetEnvironmentVariable(
    'AE_DEBUG_HOST_EXE',
    'C:\Program Files\Adobe\Adobe After Effects 2024\Support Files\AfterFX.exe',
    'User'
)
```

重新打开 Visual Studio 和终端。打开 `NF-PluginsProjects.slnx`，选择 Debug 或 Release / x64。只使用 `BuildPlugins.bat` 时无需配置这两个变量。

也可以在根 `Directory.Build.props` 的第一个属性组内、`NfRawOutDir` 之前填写本机默认值：

```xml
<AE_PLUGIN_BUILD_DIR Condition="'$(AE_PLUGIN_BUILD_DIR)'==''">D:\AePluginBuild</AE_PLUGIN_BUILD_DIR>
<AE_DEBUG_HOST_EXE Condition="'$(AE_DEBUG_HOST_EXE)'==''">C:\Program Files\Adobe\Adobe After Effects 2024\Support Files\AfterFX.exe</AE_DEBUG_HOST_EXE>
```

直接 Visual Studio 构建会写入配置的输出目录。三个 `(_SDK)` 开发工程默认不编译，需要时可单独构建。

## 分类与翻译目录

主线效果的 PiPL `Category`、`Directory.Build.PluginMap.props` 输出类别、解决方案分组和翻译目录保持一致。例如 AlphaFill 的翻译位于 `_localization/catalog/NF-Channel/AlphaFill.json`，审校状态位于 `_localization/review-state/NF-Channel/AlphaFill.json`。

三个开发工程的翻译与审校文件放在各自的 `(_SDK)` 子目录，工程与输出也保留 `(_SDK)`，默认不构建；其源码中的效果类别保留原名。Language Settings 的工程与插件输出使用 `_Support`，但 `Settings.json` 直接放在 `catalog` 和 `review-state` 根目录，不按普通效果类别归类。

实际构建准备阶段会执行只读分类检查，核对翻译文件、源类别、输出映射和解决方案分组。普通 Debug/Release、publication 和 custom 均使用此检查，Visual Studio 设计时跳过；单语言 custom 中跳过编译的 Settings 仍按构建模式规则处理。检查失败会停止对应工程构建，不会自动改写目录或分类。

可从仓库根目录单独检查一个工程，无需编译：

```powershell
uv run --locked --no-dev --project .\_localization\tools aetext check-classification --repository . --project .\AlphaFill\Win\AlphaFill.vcxproj
```

调整类别时，同步以上路径与配置以及工程的翻译文件引用；`review-state` 使用与 `catalog` 相同的相对路径。目录迁移应原样保留文件内容，再在审校工具中重新扫描受影响工程。

## 本地化代码写法

原文由 `L10N_*` 宏定义，显示文字时使用对应的 `AETEXT_*` 包装宏。在每个使用文字的函数或回调中建立一个该效果的 `Strings(in_data)`，供同一作用域内的文字调用共用。例如 AlphaFill：

```cpp
const AlphaFillText::Strings strings(in_data);
const char* label = AETEXT_PARAM(strings, L10N_PARAM_MODE);
```

下表中的 ID 写法是示例模式；现有工程保留自己的稳定 ID 和原文。

| 包装写法 | 用途 |
| --- | --- |
| `AETEXT_PARAM(strings, L10N_PARAM_<NAME>)` | 参数名称 |
| `AETEXT_LABEL(strings, L10N_LABEL_<NAME>)` | 控件文字 |
| `AETEXT_POPUP(strings, L10N_POPUP_<NAME>)` | 下拉选项 |
| `AETEXT_TOPIC(strings, L10N_<NAME>_TOPIC)` | 分组标题 |
| `AETEXT_ABOUT(strings, L10N_PLUGIN_<NAME>)` | 插件说明 |
| `AETEXT_ERROR(strings, L10N_ERR_<NAME>)` | 错误消息 |
| `AETEXT_VERBATIM_PARAM(strings, L10N_PARAM_<NAME>)` | 保留原文参数名称 |
| `AETEXT_VERBATIM_LABEL(strings, L10N_LABEL_<NAME>)` | 保留原文控件文字 |
| `AETEXT_VERBATIM_POPUP(strings, L10N_POPUP_<NAME>)` | 保留原文下拉选项 |
| `AETEXT_VERBATIM_TOPIC(strings, L10N_<NAME>_TOPIC)` | 保留原文分组标题 |
| `AETEXT_VERBATIM_ABOUT(strings, L10N_PLUGIN_<NAME>)` | 保留原文插件说明 |
| `AETEXT_VERBATIM_ERROR(strings, L10N_ERR_<NAME>)` | 保留原文错误消息 |

`AETEXT_VERBATIM_*` 跳过翻译流程。新增、删除或修改原文宏，或更换文字包装宏后，在审校工具中重新扫描对应插件。保留原参数 ID、下拉选项顺序和插件 Match Name。

## 贡献翻译

修改或贡献翻译，请查看[翻译审校指南](../_localization/README.zh-CN.md)。

## 贡献代码

贡献代码请提交 Pull Request。
