#include "FsParamText.h"

#ifdef AE_OS_WIN
#include <Windows.h>

#include <deque>
#include <new>
#include <string>
#include <vector>

#pragma comment(lib, "Version.lib")

namespace FsParamText {

bool HostUsesUtf8()
{
    static const bool utf8 = [] {
        wchar_t path[32768];
        const DWORD length = GetModuleFileNameW(nullptr, path, 32768);
        if (!length || length >= 32768) return false;

        DWORD ignored = 0;
        const DWORD size = GetFileVersionInfoSizeW(path, &ignored);
        if (!size) return false;

        std::vector<BYTE> data(size);
        if (!GetFileVersionInfoW(path, 0, size, data.data())) return false;

        VS_FIXEDFILEINFO* version = nullptr;
        UINT versionSize = 0;
        if (!VerQueryValueW(data.data(), L"\\", reinterpret_cast<void**>(&version), &versionSize)) return false;
        return version->dwProductVersionMS >= ((26u << 16) | 2u);
    }();
    return utf8;
}

std::string ToUtf8(const char* text)
{
    const int wideSize = MultiByteToWideChar(_MSVC_EXECUTION_CHARACTER_SET, 0, text, -1, nullptr, 0);
    if (!wideSize) throw PF_Err(PF_Err_BAD_CALLBACK_PARAM);
    std::wstring wide(wideSize, L'\0');
    if (!MultiByteToWideChar(_MSVC_EXECUTION_CHARACTER_SET, 0, text, -1, &wide[0], wideSize)) throw PF_Err(PF_Err_BAD_CALLBACK_PARAM);

    const int size = WideCharToMultiByte(CP_UTF8, 0, wide.data(), -1, nullptr, 0, nullptr, nullptr);
    if (!size) throw PF_Err(PF_Err_BAD_CALLBACK_PARAM);
    std::string utf8(size, '\0');
    if (!WideCharToMultiByte(CP_UTF8, 0, wide.data(), -1, &utf8[0], size, nullptr, nullptr)) throw PF_Err(PF_Err_BAD_CALLBACK_PARAM);
    utf8.pop_back();
    return utf8;
}

const char* KeepUtf8(const char* text)
{
    if (!text) return nullptr;
    static std::deque<std::string> strings;
    strings.push_back(ToUtf8(text));
    return strings.back().c_str();
}

// AE 26.2 以降の登録文字列を UTF-8 に変換する。
PF_Err AddParam(PF_InData* in_data, PF_ParamIndex index, PF_ParamDef* def)
{
    try {
        if (HostUsesUtf8() && _MSVC_EXECUTION_CHARACTER_SET != CP_UTF8) {
            const std::string name = ToUtf8(def->PF_DEF_NAME);
            PF_STRNNCPY(def->PF_DEF_NAME, name.c_str(), sizeof(def->PF_DEF_NAME));
            switch (def->param_type) {
            case PF_Param_CHECKBOX:
                def->u.bd.u.PF_DEF_NAMEPTR = KeepUtf8(def->u.bd.u.PF_DEF_NAMEPTR);
                break;
            case PF_Param_POPUP:
                def->u.pd.u.PF_DEF_NAMESPTR = KeepUtf8(def->u.pd.u.PF_DEF_NAMESPTR);
                break;
            case PF_Param_BUTTON:
                def->u.button_d.u.PF_DEF_NAMESPTR = KeepUtf8(def->u.button_d.u.PF_DEF_NAMESPTR);
                break;
            }
        }
        return (*in_data->inter.add_param)(in_data->effect_ref, index, def);
    } catch (PF_Err err) {
        return err;
    } catch (const std::bad_alloc&) {
        return PF_Err_OUT_OF_MEMORY;
    }
}

} // namespace FsParamText
#endif

