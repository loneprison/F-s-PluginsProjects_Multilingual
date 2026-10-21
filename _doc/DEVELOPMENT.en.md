**English** | [简体中文](DEVELOPMENT.md) | [日本語](DEVELOPMENT.ja.md)

# Source build and development

[User guide](../README.md) · [Translation review](../_localization/README.md) · [Original README](README.upstream.md)

## Prepare the source and environment

1. Extract After Effects SDK 25.6 and place this repository's source in `Examples\NF-PluginsProjects_Multilingual` inside the SDK. Preserve the SDK layout: `Headers`, `Resources`, `Util`, and `Examples` are sibling directories.
2. Install Visual Studio 2026 with **Desktop development with C++**, including MSVC v145 and the Windows SDK.
3. Install `uv`. The localization tools use Python 3.12; uv prepares the locked dependency environment on first use.

If uv is not installed, run in PowerShell:

```powershell
powershell -ExecutionPolicy ByPass -c "irm https://astral.sh/uv/install.ps1 | iex"
```

Open a new PowerShell window, enter this repository's root directory, and check:

```powershell
uv --version
.\BuildPlugins.bat --help
```

## Formal multilingual build

The root `BuildPlugins.bat` calls `_tools/BuildPlugins.ps1`. Formal builds use `NF-PluginsProjects.slnx`, excluding solution folders whose names are enclosed in parentheses (currently `(_SDK)`), without a separate fixed project list.

```powershell
.\BuildPlugins.bat publication
```

This rebuilds the 45 NF mainline effects and the language support component for Release x64, checking translations and effective review status. Effects include the author's source text and Simplified Chinese, with source text as the default fallback. The three development projects `_checkout`, `_Skeleton`, and `_Test` remain in the source but do not participate in this build.

Plugins are compiled directly to:

```text
_build\publication\NF-Plugins\
```

This directory contains only 46 AEX files and is recreated for each formal build. The build does not copy files into a versioned directory. When packaging a release, choose the versioned package name, add `_doc/INSTALL.txt`, and compress the files manually. These steps are separate from the build workflow.

Building does not require a Git checkout, a prior commit, or a clean working tree. Build messages are shown in the console; log files are not saved automatically. Both `publication` and `custom` clear the current mode’s `NF-Plugins` output directory before building, including read-only and hidden files. Do not store files you need to retain in that directory.

## Custom language builds

```powershell
.\BuildPlugins.bat custom --default-language zh
.\BuildPlugins.bat custom --default-language zh --single-language
.\BuildPlugins.bat custom --default-language source --single-language
```

`--default-language` accepts `source` (the author's original text) or `zh` (Simplified Chinese).

- Without `--single-language`: includes multilingual support and the support component. Effects use the selected language when the language service is unavailable, and follow NF language settings when it is available.
- With `--single-language`: builds only the 45 effects in the selected language, without the support component. Project rules validate the build mode before skipping that component. Effects always use that language, even if the host has a language support component installed.

Output is under `_build\custom\multilingual-<language>` or `_build\custom\single-<language>`, containing only plugins in the categorized `NF-Plugins` directory. Custom builds are for personal use; use `publication` for the formal multilingual version.

## Everyday development builds

The projects retain standard Debug/Release x64 configurations for users who wish to compile them manually. Open `NF-PluginsProjects.slnx` in Visual Studio and select a configuration, or use MSBuild from a Visual Studio developer terminal:

```powershell
MSBuild NF-PluginsProjects.slnx /p:Configuration=Release /p:Platform=x64
MSBuild NF-PluginsProjects.slnx /p:Configuration=Debug /p:Platform=x64
```

Configure the output path as described below first. Normal builds write to `NF-Plugins\<category>` under `AE_PLUGIN_BUILD_DIR`. Debug filenames have a `_d` suffix, such as `NF-AlphaFill_d.aex`. The root BAT provides only the `publication/custom` modes. After successful linking, the other configuration’s AEX for the same plugin is removed from the same output directory: Release removes the matching `_d.aex`, and Debug removes the matching AEX without `_d`.

Intermediate files are under each project's `Win\x64\<configuration>` directory; generated text headers are in its `Localization` subdirectory.

## Visual Studio and local paths

For Visual Studio, configure these Windows user environment variables:

- `AE_PLUGIN_BUILD_DIR`: plugin output root; projects append `NF-Plugins\<category>`.
- `AE_DEBUG_HOST_EXE`: path to `AfterFX.exe` for Debug/F5.

For example, run in PowerShell, replacing the host path with your actual installation:

```powershell
New-Item -ItemType Directory -Force 'D:\AePluginBuild'
[Environment]::SetEnvironmentVariable('AE_PLUGIN_BUILD_DIR', 'D:\AePluginBuild', 'User')
[Environment]::SetEnvironmentVariable(
    'AE_DEBUG_HOST_EXE',
    'C:\Program Files\Adobe\Adobe After Effects 2024\Support Files\AfterFX.exe',
    'User'
)
```

Reopen Visual Studio and terminals. Open `NF-PluginsProjects.slnx` and select Debug or Release / x64. These variables are not needed when using only `BuildPlugins.bat`.

Alternatively, add local defaults before `NfRawOutDir` in the first property group of the root `Directory.Build.props`:

```xml
<AE_PLUGIN_BUILD_DIR Condition="'$(AE_PLUGIN_BUILD_DIR)'==''">D:\AePluginBuild</AE_PLUGIN_BUILD_DIR>
<AE_DEBUG_HOST_EXE Condition="'$(AE_DEBUG_HOST_EXE)'==''">C:\Program Files\Adobe\Adobe After Effects 2024\Support Files\AfterFX.exe</AE_DEBUG_HOST_EXE>
```

Direct Visual Studio builds write to the configured output directory. The three `(_SDK)` development projects are excluded from the default build and can be built individually.

## Categories and translation directories

For mainline effects, the PiPL `Category`, output category in `Directory.Build.PluginMap.props`, solution folder, and catalog directory must match. For example, AlphaFill uses `_localization/catalog/NF-Channel/AlphaFill.json` and `_localization/review-state/NF-Channel/AlphaFill.json`.

The three development projects keep catalogs and review states in their respective `(_SDK)` subdirectories. Their solution and output group remains `(_SDK)`, with default builds disabled; their source effect categories retain their existing names. Language Settings uses `_Support` for its solution folder and plugin output, but its `Settings.json` files remain directly under the `catalog` and `review-state` roots. It is not classified by an effect category.

Actual build preparation runs a read-only classification check of catalogs, source categories, output mappings, and solution folders. This applies to ordinary Debug/Release, publication, and custom builds; Visual Studio design-time evaluation skips it. Settings skipped in single-language custom builds continues to use the build-mode rules. A failed check stops that project's build without rewriting directories or classifications.

To check one project from the repository root without compiling:

```powershell
uv run --locked --no-dev --project .\_localization\tools aetext check-classification --repository . --project .\AlphaFill\Win\AlphaFill.vcxproj
```

When changing a category, update these paths and settings together with the project's catalog reference. Review states mirror catalog-relative paths. Preserve file contents when moving directories, then rescan affected projects in the review tool.

## Localization code style

Define source text with `L10N_*` macros and display it through the appropriate `AETEXT_*` wrapper. Create one effect-specific `Strings(in_data)` in each text-using function or callback and share it within that scope. For example, in AlphaFill:

```cpp
const AlphaFillText::Strings strings(in_data);
const char* label = AETEXT_PARAM(strings, L10N_PARAM_MODE);
```

The ID forms below are examples; existing projects retain their stable IDs and source text.

| Wrapper form | Use |
| --- | --- |
| `AETEXT_PARAM(strings, L10N_PARAM_<NAME>)` | Parameter names |
| `AETEXT_LABEL(strings, L10N_LABEL_<NAME>)` | Control labels |
| `AETEXT_POPUP(strings, L10N_POPUP_<NAME>)` | Dropdown items |
| `AETEXT_TOPIC(strings, L10N_<NAME>_TOPIC)` | Group headings |
| `AETEXT_ABOUT(strings, L10N_PLUGIN_<NAME>)` | Plugin descriptions |
| `AETEXT_ERROR(strings, L10N_ERR_<NAME>)` | Error messages |
| `AETEXT_VERBATIM_PARAM(strings, L10N_PARAM_<NAME>)` | Source-text parameter names |
| `AETEXT_VERBATIM_LABEL(strings, L10N_LABEL_<NAME>)` | Source-text control labels |
| `AETEXT_VERBATIM_POPUP(strings, L10N_POPUP_<NAME>)` | Source-text dropdown items |
| `AETEXT_VERBATIM_TOPIC(strings, L10N_<NAME>_TOPIC)` | Source-text group headings |
| `AETEXT_VERBATIM_ABOUT(strings, L10N_PLUGIN_<NAME>)` | Source-text plugin descriptions |
| `AETEXT_VERBATIM_ERROR(strings, L10N_ERR_<NAME>)` | Source-text error messages |

`AETEXT_VERBATIM_*` bypasses translation. After adding, deleting, or changing a source-text macro, or changing a text wrapper, scan that plugin again in the review tool. Preserve parameter IDs, dropdown item order, and plugin Match Names.

## Contributing translations

To change or contribute translations, see the [translation review guide](../_localization/README.md).

## Contributing code

To contribute code, submit a pull request.
