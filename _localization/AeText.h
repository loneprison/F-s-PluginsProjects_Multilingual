#pragma once

#include <cstdint>

#include <AE_Effect.h>
#include <SPTypes.h>

#if !defined(_WIN32) || !defined(_WIN64) || !defined(_MSC_VER)
#error AeText V1 is a Windows x64 MSVC ABI.
#endif

namespace AeText {

inline constexpr std::uint32_t kCatalogVersion = 1;
inline constexpr std::uint32_t kTextRoleCount = 6;
inline constexpr std::int32_t kTextResolved = 0;

enum class TextRole : std::uint32_t {
	Param = 0,
	Label = 1,
	Popup = 2,
	Topic = 3,
	About = 4,
	Error = 5,
};

#pragma pack(push, 8)

// V1 は Windows x64 MSVC 用の ABI。カタログ、バリアント、テーブルおよび各文字列は
// エフェクト AEX が所有する静的な読み取り専用データ。Runtime の Resolve() は呼び出し中のみ
// これらを参照でき、呼び出し後にポインターを保持してはならない。
struct TextToken {
	TextRole role;
	std::uint32_t index;
};

struct StringTable {
	const char *const *values;
	std::uint32_t count;
};

struct VariantView {
	std::uint32_t struct_size;
	std::uint32_t stable_id_size; // ASCII のバイト数。末尾に NUL があっても含めない。
	const char *stable_id;
	const StringTable *role_tables;
	std::uint32_t role_table_count;
	StringTable about_utf8;
	StringTable error_utf8;
};

struct CatalogView {
	std::uint32_t struct_size;
	std::uint32_t version;
	const VariantView *variants;
	std::uint32_t variant_count;
	std::uint32_t fallback_variant_index;
};

struct TextRequest {
	TextToken token;
};

struct TextResult {
	// 成功時のポインターはエフェクト AEX 内の静的な生成テーブルを参照し、
	// その AEX が読み込まれている間のみ有効。
	const char *legacy;
	const char *utf8;
};

struct TextSuite1 {
	SPAPI std::int32_t (*Resolve)(
		const CatalogView *catalog,
		const TextRequest *request,
		TextResult *result);

	SPAPI void (*ShowOptions)(
		std::uint64_t owner_window,
		const wchar_t *plugin_title); // plugin_title はこの呼び出し中のみ有効。
};

#pragma pack(pop)

namespace detail {
struct AboutTextAccess;
}

class AboutText final {
private:
	friend class Client;
	friend struct detail::AboutTextAccess;

	constexpr AboutText(const char *script_utf8, const char *legacy) noexcept
		: script_utf8_(script_utf8), legacy_(legacy)
	{}

	const char *script_utf8_;
	const char *legacy_;
};

namespace detail {
struct AboutTextAccess final {
	static constexpr const char *ScriptUtf8(const AboutText &text) noexcept
	{
		return text.script_utf8_;
	}

	static constexpr const char *Legacy(const AboutText &text) noexcept
	{
		return text.legacy_;
	}
};
}

// エフェクト側で短期間だけ使用するクライアント。渡される Suite の識別情報は製品ファミリーが所有する。
class Client final {
public:
	Client(
		PF_InData *in_data,
		const CatalogView &catalog,
		const char *suite_name,
		std::int32_t suite_version) noexcept;
	~Client() noexcept;

	Client(const Client &) = delete;
	Client &operator=(const Client &) = delete;
	Client(Client &&) = delete;
	Client &operator=(Client &&) = delete;

	const char *Static(TextToken token) const noexcept;
	const char *Error(TextToken token) const noexcept;
	AboutText About(TextToken token) const noexcept;
	void OpenSettings(const wchar_t *plugin_title) const noexcept;

private:
	bool Resolve(const TextRequest &request, TextResult &result) const noexcept;

	PF_InData *in_data_;
	SPBasicSuite *pica_basic_;
	const CatalogView *catalog_;
	const char *suite_name_;
	std::int32_t suite_version_;
	const TextSuite1 *suite_;
	mutable char error_legacy_[PF_MAX_EFFECT_MSG_LEN + 1];
};

} // namespace AeText
