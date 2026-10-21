# NF Plugins 中文维护版 · 本地候选包

> 此文件为早期随包说明草稿，保留作开发参考，已不用于打包。当前安装说明为 [INSTALL.txt](INSTALL.txt)，项目说明见 [中文 README](README.zh-CN.md)。以下包内文件描述属于旧方案。

本包尚未正式发布。包含 Windows x64 的 45 个 NF 主线效果和 1 个语言支持组件，共 46 个 Release AEX。
三个开发工程 `_checkout`、`_Skeleton`、`_Test` 不在包内。构建来源与逐插件校验值见 `BUILD-INFO.json`，文件校验清单为 `SHA256SUMS.txt`。

## 安装与回退

1. 关闭 After Effects 及正在使用 NF 插件的 Adobe 应用。
2. 已安装 NF 时，先将旧 `NF-Plugins` 文件夹备份到插件扫描目录之外。不要混装旧版、Debug/Release 或重复的 NF 语言支持组件。旧 F’s 是独立系列，无需因安装 NF 而移除。
3. 将本包的 `NF-Plugins` 文件夹完整复制到插件目录，例如：

   ```text
   C:\Program Files\Adobe\Common\Plug-ins\7.0\MediaCore\
   ```

   保留分类子目录和 `_Support/NF-Language Settings.aex`。
4. 重新启动 After Effects，在“效果”菜单的 NF 分类中添加效果。

卸载时先关闭宿主，再将本版 `NF-Plugins` 移出插件目录；回退时放回旧版备份，避免两版并存。无需修改其他插件系列。

## 语言设置

默认跟随 After Effects：简体中文界面使用简中，其他语言或语言信息不可用时使用作者原文。作者原文不统一为英语或日语。

在任意本版 NF 效果的“效果控件”面板点击“选项…”，选择“自动”“原文”或“简体中文”，保存后退出并重新启动 After Effects。
这是整套 NF 共用的设置，当前会话保持原语言，新添加的效果也要等重启才切换。“设置界面语言”只改变这个窗口的中、英、日显示，不会增加效果的翻译语言。

缺少 NF 语言支持组件时，效果回退自身原文，“选项…”无法打开设置。遇到这一情况，检查 `_Support` 及重复安装，再重启。
NF 配置保存在 `%LOCALAPPDATA%\NF-Plugins-Localization\language.json`，独立于旧 F’s 和效果预设。恢复默认可选择“自动”并保存、重启。

## 来源与许可

原作者为 bryful，基于 [bryful/F-s-PluginsProjects](https://github.com/bryful/F-s-PluginsProjects) 的 `db6dad3959522cfcd593dfe12a9fa4ad022d31e3` 主线继续本地化维护。
遵循随包提供的 `LICENSE`（MIT License），保留原作者版权声明。旧 F’s Legacy 项目不包含在本包中。
