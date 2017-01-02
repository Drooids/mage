#pragma once

#include <codecvt>

namespace Mage
{
	using U8toU16 = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>;
	using U16toU8 = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>;
}
