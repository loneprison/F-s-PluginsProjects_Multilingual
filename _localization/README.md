**English** | [简体中文](README.zh-CN.md) | [日本語](README.ja.md)

# Translation review Web tool

[User guide](../README.md) · [Developer guide](../_doc/DEVELOPMENT.en.md)

Use the local Web workspace for translation and review. Do not edit translation or review JSON by hand.

## Start

Prepare the SDK, Visual Studio, and uv as described in the [developer guide](../_doc/DEVELOPMENT.en.md), then run from the repository root:

```powershell
uv run --project .\_localization\tools --locked aetext review
```

The first run prepares the Python environment. Keep the terminal running while using the tool. If the browser does not open automatically, open the local URL printed after `AeText review:`.

**Interface language** controls the Web UI. **Translation language** selects the text being edited. NF mainline effects have Simplified Chinese translations. Settings uses Chinese source text, with English and Japanese window text available for review.

## Scan

- On first opening this repository, choose **Scan > Scan all plugin sources**.
- For one effect, select it and choose **Scan > Scan current plugin source**.
- After changing source text or wrappers, or when source data is reported as stale, scan the affected plugin again.

The **NF mainline effects** group on the left lists effects by NF category. Templates / tests and Settings are listed separately.

## File locations

Effect translations are stored in `_localization/catalog/<category>/<project>.json`, with review states at the same relative paths under `_localization/review-state/`. Mainline effects use NF categories; the three development projects use `(_SDK)`. Both Settings files remain as `Settings.json` directly under their respective roots, while its solution folder and plugin output use `_Support`.

Directory migrations move translations and review states together without changing their contents. If catalog paths change after updating the source tree, rescan the affected projects to refresh the source cache. Review remains valid for entries whose source text, translation, and review context are unchanged.

## Edit and review

1. Select a plugin and translation language.
2. Enter text in **Translation**, or enable **Use source** to retain the source text.
3. Change dropdown text through **Edit popup items…**, preserving item count and order.
4. After checking the text, set **Status** to **Reviewed**.

Changes to source text or translations may require an earlier review to be renewed. Check the current content before marking it reviewed.

## Save and reload

`*` marks unsaved changes. Use **Save this plugin** or **Save all changes** to save them.

If another window or tool updates the files, preserve any drafts you need, then use **Reload translation files** and check the latest content before saving.

## Check publication review

After saving, select an effect or Settings and choose **Scan > Check current plugin publication review**. Resolve any reported missing translations, invalid content, or pending reviews.

This checks the current plugin. Use `BuildPlugins.bat publication` for the formal suite build, which performs the checks across the build.

## Stop or reopen

Save your changes, then press `Ctrl+C` in the terminal to stop the service. Run the start command again to reopen it.
