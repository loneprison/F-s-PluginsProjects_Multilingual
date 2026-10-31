#pragma once

#include <Windows.h>

#include <array>
#include <vector>

#pragma comment(lib, "Version.lib")

namespace AeText::detail {

inline const VS_FIXEDFILEINFO &HostFileVersion() noexcept
{
    static const VS_FIXEDFILEINFO version = []() noexcept {
        try {
            std::array<wchar_t, 32768> path{};
            const DWORD length = GetModuleFileNameW(nullptr, path.data(), static_cast<DWORD>(path.size()));
            if (length == 0 || length >= path.size()) {
                return VS_FIXEDFILEINFO{};
            }
            DWORD ignored = 0;
            const DWORD size = GetFileVersionInfoSizeW(path.data(), &ignored);
            if (size == 0) {
                return VS_FIXEDFILEINFO{};
            }
            std::vector<unsigned char> data(size);
            if (!GetFileVersionInfoW(path.data(), 0, size, data.data())) {
                return VS_FIXEDFILEINFO{};
            }
            VS_FIXEDFILEINFO *info = nullptr;
            UINT info_size = 0;
            if (!VerQueryValueW(data.data(), L"\\", reinterpret_cast<void **>(&info), &info_size)) {
                return VS_FIXEDFILEINFO{};
            }
            return *info;
        } catch (...) {
            return VS_FIXEDFILEINFO{};
        }
    }();
    return version;
}

inline bool HostUsesUtf8Parameters() noexcept
{
    return HostFileVersion().dwProductVersionMS >= ((26u << 16) | 2u);
}

} // namespace AeText::detail
