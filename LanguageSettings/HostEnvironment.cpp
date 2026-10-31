#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "HostEnvironment.h"
#include "../_localization/core/AeTextHost.h"

#include "AEConfig.h"
#include "AEGP_SuiteHandler.h"

#include <Windows.h>

#include <cwctype>
#include <sstream>
#include <string>

namespace FsLanguage {
namespace {

std::wstring NormalizeLanguageTag(std::wstring value)
{
	for (wchar_t &character : value) {
		character = static_cast<wchar_t>(std::towlower(character));
		if (character == L'-') {
			character = L'_';
		}
	}
	return value;
}

AeLanguage ClassifyAeLanguage(const std::wstring &language_tag)
{
	const std::wstring normalized = NormalizeLanguageTag(language_tag);
	if (normalized == L"zh_cn" || normalized == L"zh_sg") {
		return AeLanguage::SimplifiedChinese;
	}
	if (normalized.rfind(L"ja", 0) == 0) {
		return AeLanguage::Japanese;
	}
	if (normalized.rfind(L"en", 0) == 0) {
		return AeLanguage::English;
	}
	return AeLanguage::Other;
}

bool TryGetAeLanguageTag(SPBasicSuite *pica_basic, std::wstring &language_tag)
{
	if (!pica_basic) {
		return false;
	}

	try {
		AEGP_SuiteHandler suites(pica_basic);
		A_char tag[PF_APP_LANG_TAG_SIZE] = {};
		if (suites.AppSuite6()->PF_AppGetLanguage(tag)) {
			return false;
		}

		for (const unsigned char value : std::string(tag)) {
			language_tag.push_back(static_cast<wchar_t>(value));
		}
		return !language_tag.empty();
	} catch (...) {
		return false;
	}
}

WindowsCodePage ClassifyWindowsCodePage(UINT code_page)
{
	if (code_page == 932) {
		return WindowsCodePage::Japanese932;
	}
	if (code_page == 936) {
		return WindowsCodePage::SimplifiedChinese936;
	}
	return WindowsCodePage::OtherOrUnknown;
}

std::wstring WindowsLanguageName(UINT code_page)
{
	wchar_t locale_name[LOCALE_NAME_MAX_LENGTH] = {};
	wchar_t display_name[256] = {};
	std::wstring result;
	if (GetSystemDefaultLocaleName(locale_name, LOCALE_NAME_MAX_LENGTH)) {
		if (GetLocaleInfoEx(
				locale_name,
				LOCALE_SLOCALIZEDDISPLAYNAME,
				display_name,
				static_cast<int>(sizeof(display_name) / sizeof(display_name[0])))) {
			result = display_name;
		} else {
			result = locale_name;
		}
	}
	if (result.empty()) {
		result = L"unknown";
	}
	result += L" (CP" + std::to_wstring(code_page) + L')';
	return result;
}

} // namespace

HostEnvironment DetectHostEnvironment(SPBasicSuite *pica_basic)
{
	HostEnvironment result;
	if (TryGetAeLanguageTag(pica_basic, result.ae_language_tag)) {
		result.language.ae_language = ClassifyAeLanguage(result.ae_language_tag);
	}

	const auto &version = AeText::detail::HostFileVersion();
	const unsigned int major_version = HIWORD(version.dwProductVersionMS);
	if (major_version != 0) {
		result.language.host_version = major_version <= 22
			? HostVersion::AtMost22
			: HostVersion::AtLeast23OrUnknown;
		std::wostringstream text;
		text << major_version << L'.' << LOWORD(version.dwProductVersionMS) << L'.'
			 << HIWORD(version.dwProductVersionLS) << L'.' << LOWORD(version.dwProductVersionLS);
		result.version_text = text.str();
	}
	result.language.utf8_parameters = AeText::detail::HostUsesUtf8Parameters();

	const UINT code_page = GetACP();
	result.language.windows_code_page = ClassifyWindowsCodePage(code_page);
	result.windows_language = WindowsLanguageName(code_page);
	return result;
}

SettingsUiLanguage DefaultSettingsUiLanguage(AeLanguage language)
{
	switch (language) {
	case AeLanguage::SimplifiedChinese: return SettingsUiLanguage::SimplifiedChinese;
	case AeLanguage::Japanese: return SettingsUiLanguage::Japanese;
	case AeLanguage::English:
	case AeLanguage::Other:
	case AeLanguage::Unavailable:
	default: return SettingsUiLanguage::English;
	}
}

} // namespace FsLanguage
