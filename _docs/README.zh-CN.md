[English](../README.md) | **简体中文** | [日本語](README.ja.md)

# F's Plugins Multilingual Edition

本项目基于 [bryful/F-s-PluginsProjects](https://github.com/bryful/F-s-PluginsProjects) 的
[`47a9d2c`](https://github.com/bryful/F-s-PluginsProjects/commit/47a9d2c7a322e5ed0ea09c77bbd90cf5a54cb7bf)
继续维护。整套发行版本从 `v1.0.0` 开始。

- **翻译与程序维护**：loneprison
- **校对**：光学核心

本仓库的默认分支 `master` 维护 F's Plugins，[`nf` 分支](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/tree/nf)
维护 NF Plugins。本页介绍 F's Plugins。

[开发文档](DEVELOPMENT.zh-CN.md) · [翻译审校](../_localization/README.zh-CN.md) · [原作者 README](README.original.md)

F's Plugins 的 Windows x64 多语言维护版，面向 Adobe After Effects，提供日文原文、简体中文和英文
界面，并保留原插件名称与 Match Name。

> [!IMPORTANT]
> `v1.0.0` 仍在准备中。正式发布后请使用 GitHub Releases 中的发行包。

## 安装

从 GitHub Releases 下载 `Fs-Plugins-Multilingual-v1.0.0-win.zip`。关闭 After Effects，将解压后的
`Fs_Plugins` 完整复制到 After Effects 插件目录，保留原目录结构，然后重新启动 After Effects。

包内包含中、英、日三语说明及 `LICENSE`。不支持 macOS。

## 语言

从任一 F's 效果的“选项／Options”打开 `F's Language Settings`。

- 自动
- English
- 日文原文
- 简体中文
- 适用于简体中文编码环境的日文原文表示

AE 23 及以上的“自动”模式按 AE 界面语言选择：简体中文使用中文，日文使用日文原文，其他语言使用英文。
AE 22 及以下按 Windows ANSI 代码页选择：CP936 使用中文，CP932 使用日文，其他或未知代码页使用英文。

保存后需要重新启动 After Effects 才可生效。如果 Language Settings 缺失或不可用，各效果会默认使用
日文原文。

## 发行内容

计划发行 105 个效果和 1 个语言设置组件，不包含测试、模板及以下效果：

- `ChannelBlur`
- `Extract_Edge`
- `FsSSFrame`
- `ShineParallel`
- `VideoLine2nd`

## 更新日志

### v1.0.0

- **位深**：修复以下插件在 8／16／32 bpc 下的渲染计算不一致问题：
  `ChannelNoise`、`colorThreshold`、`Extract-Hi`、`grayToColorize`、`IroToreAdjacent`、
  `Max`、`MaxBlur`、`MaxFast`、`Max_Kasumi`、`Mosaic`、
  `OpticalDiffusion`、`OutLine`、`PixelSelector`、`RandomMosaic`、`RandomMosaic2nd`、
  `Spark`、`SparkGrand`、`SparkMult`、`SparkRing`、`SparkStorm`、
  `Thin`、`TouchDraw`、`TouchDrawStraght`、`YuvControl`。
- **其他渲染**：修复以下插件的颜色处理、随机块分布、块数量计算和下采样处理异常：
  `LineTrace`、`Max`、`Max_Kasumi`、`OpticalDiffusion`、`TouchDraw`、
  `TouchDrawStraght`。
- **稳定性**：修复以下插件可能导致 AE 意外崩溃的问题：
  `Max`、`OpticalDiffusion`、`OutLine`、`smokeThreshold`。
- **界面**：隐藏 `GuideFrame` 无效的 `Smooth` 控件，修复 `PixelSelector` 控件状态异常。
- **语言**：为效果插件新增简体中文、英文界面和语言设置，适配 AE 26.2 及以上版本的参数文字编码。
- **文本**：修正 `RandomShift` 和 `smokeThreshold` 原版中的参数标签错误，为 `SelectedBlur` 的启用参数补充 0～7 编号。
- **About**：补充部分缺失的说明文本。

## 关于旧版兼容

AE 26.2 及以上版本的参数文字改用 UTF-8 编码后，以下插件的部分属性名超出 SDK 长度限制，因此进行了不兼容调整：

- `AnimatedNoise`
- `Mosaic`
- `PaintMultPoint`
- `Scanline`

`SelectedBlur` 的启用参数另补充了 0～7 编号，按旧名称引用这些参数的表达式或脚本需相应调整。

为兼容旧版工程，以下插件提供“旧版”复选框，可保留原有的渲染方式：

- `LineTrace`
- `Max`
- `OpticalDiffusion`
- `TouchDraw`
- `TouchDrawStraght`

## 源码与开发

本维护版整理了原仓库的目录与文件，移除了部分历史备份、生成文件和旧二进制包，并归档保留部分
原作者资料；被移除的内容仍可从 Git 历史查阅。

源码构建与开发见[开发文档](DEVELOPMENT.zh-CN.md)。

## 许可

项目沿用仓库根目录的 [MIT License](../LICENSE)，并保留原作者版权声明。
