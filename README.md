**English** | [简体中文](_doc/README.zh-CN.md) | [日本語](_doc/README.ja.md)

# NF Plugins Multilingual Edition

This repository maintains two plugin families: [F’s Plugins on `master`](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/tree/master) and [NF Plugins on `nf`](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/tree/nf). This page describes NF Plugins.

[Development](_doc/DEVELOPMENT.en.md) · [Translation review](_localization/README.md) · [Original README](_doc/README.upstream.md)

A Windows x64 localization of bryful's NF Plugins for Adobe After Effects, with the author's original
text and a Simplified Chinese interface. Original plugin names, Match Names, and rendering behavior are preserved.

> This maintenance edition follows upstream `v1.1.0`. A local package is ready; it has not been published.

## Install

Close After Effects and copy the extracted `NF-Plugins` folder to:

```text
C:\Program Files\Adobe\Common\Plug-ins\7.0\MediaCore\
```

Keep all subfolders, including `_Support`, then restart After Effects. When upgrading, move the old
NF folder out of the plugin directories first and keep a backup. Avoid duplicate installations.
Existing F's Plugins installations can remain alongside NF.

The formal build writes plugin files directly to `_build/publication/NF-Plugins`. When packaging a release,
choose the versioned package name, add `_doc/INSTALL.txt`, and compress the files manually.
Installation is by copying the files on Windows x64; no macOS build is provided.

## Language

Open **Options** from any NF effect in the Effect Controls panel to choose:

- **Automatic**: use Simplified Chinese when the After Effects UI is Simplified Chinese; otherwise use the author's original text.
- **Original text**: use each effect's source text, which may include English and Japanese.
- **Simplified Chinese**: use the Chinese translation.

Save and restart After Effects to apply the change to all NF effects. The current session keeps its
language. If the language support component is missing, effects use their own original text.

The settings window's English, Chinese, and Japanese display languages are separate from effect
translations. NF language preferences are independent of F's Plugins.

## Package contents

The package includes **45 NF effects and one NF Language Settings component**, totaling 46 Release AEX files.
The three development projects (`_checkout`, `_Skeleton`, and `_Test`) remain in the source repository
and are excluded from the package.

For the localized edition of F's Plugins, see [F's Plugins Multilingual](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/tree/master).

## Source and license

Based on [bryful/F-s-PluginsProjects](https://github.com/bryful/F-s-PluginsProjects) at
[`v1.1.0`](https://github.com/bryful/F-s-PluginsProjects/releases/tag/v1.1.0) (`db6dad3`).
Package versions follow upstream. The [original README](_doc/README.upstream.md) is preserved separately.

This maintenance edition reorganizes the original repository, removing some older projects and historical
plugin binary packages while retaining or archiving the author's examples, documentation, and backups.
Removed upstream content remains available in Git history.

For source builds, see the [developer guide](_doc/DEVELOPMENT.en.md).
The repository retains the [MIT License](LICENSE) and the author's copyright notice.
