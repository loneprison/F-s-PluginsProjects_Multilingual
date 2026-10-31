$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

function Write-Usage {
    [Console]::WriteLine(@'
Usage:
  BuildPlugins.bat publication
  BuildPlugins.bat custom [--default-language <en|source|zh|ja-for-zh>] [--single-language]

Modes:
  publication  Official multilingual Release x64 build
  custom       Custom build
'@)
}

try {
    $tokens = @($args)
    if ($tokens.Count -eq 1 -and $tokens[0] -in @('--help', '-h')) {
        Write-Usage
        exit 0
    }
    if ($tokens.Count -eq 0) {
        Write-Usage
        [Console]::WriteLine('Press any key to continue . . .')
        [Console]::ReadKey($true) | Out-Null
        exit 0
    }

    $mode = [string]$tokens[0]
    $defaultLanguage = $null
    $singleLanguage = $false

    switch ($mode) {
        'publication' {
            if ($tokens.Count -ne 1) {
                throw 'The publication mode does not accept language overrides.'
            }
        }
        'custom' {
            $index = 1
            while ($index -lt $tokens.Count) {
                $token = [string]$tokens[$index]
                switch ($token) {
                    '--default-language' {
                        if ($null -ne $defaultLanguage) {
                            throw '--default-language may be specified only once.'
                        }
                        $index++
                        if ($index -ge $tokens.Count) {
                            throw '--default-language requires a value.'
                        }
                        $defaultLanguage = [string]$tokens[$index]
                    }
                    '--single-language' {
                        if ($singleLanguage) {
                            throw '--single-language may be specified only once.'
                        }
                        $singleLanguage = $true
                    }
                    default {
                        throw "Unknown custom-build option: $token"
                    }
                }
                $index++
            }
            if ($null -eq $defaultLanguage) {
                $defaultLanguage = 'source'
            }
        }
        default {
            throw "Unknown build mode: $mode"
        }
    }

    $languageMap = @{
        'en' = 'en'
        'source' = 'source'
        'zh' = 'zh'
        'ja-for-zh' = 'source-cp936-compatible'
    }
    if ($mode -eq 'custom' -and -not $languageMap.ContainsKey($defaultLanguage)) {
        throw "Unsupported default language: $defaultLanguage"
    }

    $repositoryRoot = [System.IO.Path]::GetFullPath((Split-Path -Parent $PSScriptRoot))
    $solutionPath = Join-Path $repositoryRoot "F's PluginsProjects.slnx"
    if (-not [System.IO.File]::Exists($solutionPath)) {
        throw "Solution was not found: $solutionPath"
    }

    $uv = Get-Command 'uv.exe' -ErrorAction SilentlyContinue
    if ($null -eq $uv) {
        throw 'uv.exe was not found on PATH.'
    }

    $programFilesX86 = [Environment]::GetFolderPath('ProgramFilesX86')
    $vswhere = Join-Path $programFilesX86 'Microsoft Visual Studio\Installer\vswhere.exe'
    if (-not [System.IO.File]::Exists($vswhere)) {
        throw "Visual Studio Installer vswhere.exe was not found: $vswhere"
    }
    $installationOutput = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    $installation = [string]($installationOutput | Select-Object -First 1)
    if ([string]::IsNullOrWhiteSpace($installation)) {
        throw 'A Visual Studio installation with the x64 C++ tools was not found.'
    }
    $msbuild = Join-Path $installation.Trim() 'MSBuild\Current\Bin\MSBuild.exe'
    if (-not [System.IO.File]::Exists($msbuild)) {
        throw "MSBuild was not found: $msbuild"
    }

    if ($mode -eq 'publication') {
        $outputRoot = Join-Path $repositoryRoot '_build\publication'
        $target = 'Rebuild'
        $variantId = 'source'
        $customBuildValue = 'false'
        $singleLanguageValue = 'false'
        $publicationValue = 'true'
    } else {
        $variantId = [string]$languageMap[$defaultLanguage]
        $variantMode = if ($singleLanguage) { 'single' } else { 'multilingual' }
        $outputRoot = Join-Path $repositoryRoot "_build\custom\$variantMode-$defaultLanguage"
        $target = 'Build'
        $customBuildValue = 'true'
        $singleLanguageValue = $singleLanguage.ToString().ToLowerInvariant()
        $publicationValue = 'false'
    }

    $outputRoot = [System.IO.Path]::GetFullPath($outputRoot)
    [System.IO.Directory]::CreateDirectory($outputRoot) | Out-Null

    $pluginOutput = Join-Path $outputRoot 'Fs_Plugins'
    if ([System.IO.Directory]::Exists($pluginOutput)) {
        Remove-Item -LiteralPath $pluginOutput -Recurse -Force
    }

    $processPath = $env:Path
    Remove-Item Env:PATH -ErrorAction SilentlyContinue
    [Environment]::SetEnvironmentVariable('Path', $processPath, 'Process')

    $buildSolutionPath = $solutionPath
    $temporarySolutionPath = $null
    if ($mode -eq 'publication') {
        [xml]$publicationSolution = [System.IO.File]::ReadAllText($solutionPath)
        $excludedFolders = @(
            $publicationSolution.Solution.Folder |
                Where-Object { [string]$_.Name -match '^/\([^/]+\)/$' }
        )
        if ($excludedFolders.Count -gt 0) {
            $excludedProjectCount = @($excludedFolders | ForEach-Object { $_.Project }).Count
            $excludedFolderNames = @($excludedFolders | ForEach-Object { [string]$_.Name })
            foreach ($folder in $excludedFolders) {
                $publicationSolution.Solution.RemoveChild($folder) | Out-Null
            }
            $temporarySolutionPath = Join-Path $repositoryRoot (
                '.publication-{0}.slnx' -f [Guid]::NewGuid().ToString('N'))
            [System.IO.File]::WriteAllText(
                $temporarySolutionPath,
                $publicationSolution.OuterXml,
                [System.Text.UTF8Encoding]::new($false))
            $buildSolutionPath = $temporarySolutionPath
            [Console]::WriteLine(
                "Skipping $excludedProjectCount projects in solution folders: $($excludedFolderNames -join ', ')")
        }
    }

    $msbuildArguments = @(
        $buildSolutionPath
        '-nologo'
        "-target:$target"
        '-maxCpuCount'
        '-property:Configuration=Release'
        '-property:Platform=x64'
        "-property:AE_PLUGIN_BUILD_DIR=$outputRoot"
        "-property:AeTextCustomBuild=$customBuildValue"
        "-property:AeTextDefaultVariantId=$variantId"
        "-property:AeTextSingleLanguage=$singleLanguageValue"
        "-property:FsTextPublicationValidation=$publicationValue"
        "-property:AeTextPublicationValidation=$publicationValue"
        '-verbosity:minimal'
    )

    [Console]::WriteLine("Building $mode output in $outputRoot")
    try {
        & $msbuild @msbuildArguments
        $buildExitCode = $LASTEXITCODE
    } finally {
        if ($null -ne $temporarySolutionPath -and [System.IO.File]::Exists($temporarySolutionPath)) {
            Remove-Item -LiteralPath $temporarySolutionPath -Force
        }
    }
    if ($buildExitCode -ne 0) {
        exit $buildExitCode
    }

    [Console]::WriteLine("Build completed: $pluginOutput")
    exit 0
} catch {
    [Console]::Error.WriteLine("BuildPlugins: $($_.Exception.Message)")
    Write-Usage
    exit 1
}
