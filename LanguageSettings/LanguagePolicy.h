#pragma once
#include <cstdint>
namespace NfLanguage {
enum class ConfiguredLanguage : std::uint8_t { Automatic, Original, SimplifiedChinese };
enum class SessionLanguage : std::uint8_t { Original, SimplifiedChinese };
enum class AeLanguage : std::uint8_t { SimplifiedChinese, Japanese, English, Other, Unavailable };
enum class HostVersion : std::uint8_t { AtMost22, AtLeast23OrUnknown };
enum class WindowsCodePage : std::uint8_t { Japanese932, SimplifiedChinese936, OtherOrUnknown };
enum class CompatibilityMessage : std::uint8_t { None, Incompatible };
struct LanguageEnvironment {
    AeLanguage ae_language;
    HostVersion host_version;
    WindowsCodePage windows_code_page;
};
constexpr SessionLanguage ResolveAutomatic(const LanguageEnvironment &environment)
{
    return environment.ae_language == AeLanguage::SimplifiedChinese
        ? SessionLanguage::SimplifiedChinese : SessionLanguage::Original;
}
constexpr SessionLanguage ResolveSelected(ConfiguredLanguage selected, const LanguageEnvironment &environment)
{
    switch (selected) {
    case ConfiguredLanguage::Automatic: return ResolveAutomatic(environment);
    case ConfiguredLanguage::SimplifiedChinese: return SessionLanguage::SimplifiedChinese;
    case ConfiguredLanguage::Original:
    default: return SessionLanguage::Original;
    }
}
constexpr CompatibilityMessage ResolveMessage(ConfiguredLanguage selected, const LanguageEnvironment &environment)
{
    return selected == ConfiguredLanguage::SimplifiedChinese &&
        environment.ae_language != AeLanguage::SimplifiedChinese
        ? CompatibilityMessage::Incompatible : CompatibilityMessage::None;
}
} // namespace NfLanguage
