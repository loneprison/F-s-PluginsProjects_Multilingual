[English](../README.md) | **简体中文** | [日本語](README.ja.md)

# NF Plugins Multilingual Edition

本仓库分两个分支维护两套插件：[master 分支为 F’s Plugins](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/blob/master/_docs/README.zh-CN.md)，[nf 分支为 NF Plugins](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/blob/nf/_doc/README.zh-CN.md)。本页介绍 NF Plugins。

[开发文档](DEVELOPMENT.md) · [翻译审校](../_localization/README.zh-CN.md) · [原作者 README](README.upstream.md)

面向 Adobe After Effects 的 NF 插件 Windows x64 本地化维护版，基于 bryful 的 NF 主线，
提供作者原文和简体中文界面，保留原插件名称、Match Name 和渲染行为。

> 本维护版跟随作者 `v1.1.0`。本地安装包已整理完成，尚未发布。

## 安装

关闭 After Effects，将解压后的 `NF-Plugins` 文件夹完整复制到：

```text
C:\Program Files\Adobe\Common\Plug-ins\7.0\MediaCore\
```

保留全部子文件夹，包括 `_Support`，然后重新启动 After Effects。升级前先将旧 NF 文件夹
移出插件目录并备份，避免重复安装。已有的旧 F’s 插件可以与 NF 共存。

正式构建直接输出插件到 `_build/publication/NF-Plugins`。制作安装包时自行按版本命名、
放入 `_doc/INSTALL.txt` 安装说明并压缩；这些步骤不参与构建流程。采用手动复制安装，适用于 Windows x64，不提供 macOS 版本。

## 语言

在“效果控件”面板点击任意 NF 效果的“选项…”，选择：

- **自动**：After Effects 界面为简体中文时使用中文，其他情况使用作者原文。
- **原文**：使用各效果的作者原始文本，其中可能包含英语和日语。
- **简体中文**：使用中文译文。

保存后重新启动 After Effects，对全部 NF 效果生效；当前会话保持原语言。
缺少语言支持组件时，效果使用自身原文。

设置窗口自身的中、英、日显示语言与效果译文分开。NF 的语言设置独立于旧 F’s 插件。

## 包含内容

**45 个 NF 效果和 1 个 NF 语言支持组件，共 46 个 Release AEX。**
三个开发工程 `_checkout`、`_Skeleton`、`_Test` 保留在源码仓库，不进入安装包。

如果希望查看 F’s 插件的本地化版本，请前往 [F’s Plugins Multilingual 项目](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/blob/master/_docs/README.zh-CN.md)。

## 来源与许可

基于 [bryful/F-s-PluginsProjects](https://github.com/bryful/F-s-PluginsProjects) 的
[`v1.1.0`](https://github.com/bryful/F-s-PluginsProjects/releases/tag/v1.1.0)（`db6dad3`）继续维护，
安装包版本跟随作者。[原作者 README](README.upstream.md) 单独保留。

本维护版整理了原仓库的目录与文件，移除了部分旧工程和历史插件二进制包，
并保留或归档作者的示例、文档与备份资料。原仓库中被移除的内容仍可从 Git 历史查阅。

源码构建见[开发文档](DEVELOPMENT.md)。
仓库沿用 [MIT License](../LICENSE)，保留原作者版权声明。
