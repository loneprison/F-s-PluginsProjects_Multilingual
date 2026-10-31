**English** | [简体中文](_docs/README.zh-CN.md) | [日本語](_docs/README.ja.md)

# F's Plugins Multilingual Edition

This edition continues from
[`47a9d2c`](https://github.com/bryful/F-s-PluginsProjects/commit/47a9d2c7a322e5ed0ea09c77bbd90cf5a54cb7bf)
of [bryful/F-s-PluginsProjects](https://github.com/bryful/F-s-PluginsProjects). Its suite version starts
at `v1.0.0`.

- **Translation and code maintenance:** loneprison
- **Proofreading:** 光学核心

This repository maintains F's Plugins on the default `master` branch and NF Plugins on the
[`nf` branch](https://github.com/loneprison/F-s-PluginsProjects_Multilingual/tree/nf).
This README covers F's Plugins.

[Development](_docs/DEVELOPMENT.en.md) · [Translation review](_localization/README.md) · [Original README](_docs/README.original.md)

A maintained Windows x64 edition of F's Plugins for Adobe After Effects, with original Japanese,
Simplified Chinese, and English interfaces. Plugin names and Match Names remain unchanged.

> [!IMPORTANT]
> `v1.0.0` is still in preparation. Use the final GitHub Release package when it becomes available.

## Install

Download `Fs-Plugins-Multilingual-v1.0.0-win.zip` from GitHub Releases, close After Effects, and copy
the extracted `Fs_Plugins` directory to an After Effects plugin directory. Keep its directory
structure, then restart After Effects.

The archive includes user guides in Simplified Chinese, English, and Japanese, plus `LICENSE`.
macOS is not supported.

## Language

Open **Options** from any F's effect to use `F's Language Settings`.

- Automatic
- English
- Original Japanese
- Simplified Chinese
- Original Japanese represented for a Simplified Chinese encoding environment

Automatic mode uses the After Effects UI language on AE 23 and later: Simplified Chinese selects
Chinese, Japanese selects the original Japanese, and other languages select English. AE 22 and earlier
use the Windows ANSI code page: CP936 selects Chinese, CP932 selects Japanese, and other or unknown
code pages select English.

Restart After Effects for saved changes to take effect. If Language Settings is missing or unavailable,
effects default to the original Japanese text.

## Release contents

The planned release includes 105 effects and one Language Settings component. Tests, templates,
and the following effects are excluded:

- `ChannelBlur`
- `Extract_Edge`
- `FsSSFrame`
- `ShineParallel`
- `VideoLine2nd`

## Changelog

### v1.0.0

- **Bit depth:** Corrected inconsistent rendering calculations across 8/16/32 bpc in the following plugins:
  `ChannelNoise`, `colorThreshold`, `Extract-Hi`, `grayToColorize`, `IroToreAdjacent`,
  `Max`, `MaxBlur`, `MaxFast`, `Max_Kasumi`, `Mosaic`,
  `OpticalDiffusion`, `OutLine`, `PixelSelector`, `RandomMosaic`, `RandomMosaic2nd`,
  `Spark`, `SparkGrand`, `SparkMult`, `SparkRing`, `SparkStorm`,
  `Thin`, `TouchDraw`, `TouchDrawStraght`, `YuvControl`.
- **Other rendering:** Fixed color processing, random block distribution, block-count calculation,
  and downsampling issues in the following plugins:
  `LineTrace`, `Max`, `Max_Kasumi`, `OpticalDiffusion`, `TouchDraw`,
  `TouchDrawStraght`.
- **Stability:** Fixed issues that could cause AE to crash unexpectedly in the following plugins:
  `Max`, `OpticalDiffusion`, `OutLine`, `smokeThreshold`.
- **Interface:** Hid `GuideFrame`'s unused `Smooth` control and fixed `PixelSelector`'s control states.
- **Language support:** Added Simplified Chinese and English interfaces and language settings across effects,
  and adapted parameter text encoding for AE 26.2 and later.
- **Text:** Corrected parameter label errors from the original versions of `RandomShift` and `smokeThreshold`,
  and added numbers 0–7 to `SelectedBlur`'s enable parameters.
- **About:** Added some missing description text.

## Compatibility with older versions

After parameter text changed to UTF-8 in AE 26.2 and later, some property names in the following
plugins exceeded the SDK's length limit and have been changed in a way that breaks compatibility:

- `AnimatedNoise`
- `Mosaic`
- `PaintMultPoint`
- `Scanline`

`SelectedBlur`'s enable parameters have also been numbered 0–7. Expressions or scripts that reference
these parameters by their old names need to be updated.

For compatibility with older projects, the following plugins provide a **Legacy** checkbox to retain
the original rendering behavior:

- `LineTrace`
- `Max`
- `OpticalDiffusion`
- `TouchDraw`
- `TouchDrawStraght`

## Source and development

This edition reorganizes the original repository's directories and files, removes some historical
backups, generated files, and old binary packages, and preserves selected original-author materials
in archives. Removed content remains available in Git history.

For source builds and development, see the [developer guide](_docs/DEVELOPMENT.en.md).

## License

Licensed under the repository's [MIT License](LICENSE), with the original copyright notice retained.
