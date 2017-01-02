#pragma once

#include <sstream>
#include <string>

#include <Windows.h>

#include <mage/exception.hpp>
#include <mage/string_util.hpp>

namespace Mage {
	namespace OS {
		class Win32Exception : public Mage::Exception {
		protected:
			std::string m_what;

		public:
			explicit Win32Exception(const std::string& err, DWORD errCode = 0) {
				std::ostringstream ss;
				ss << err;
				
				if (errCode) {
					LPWSTR pBuffer = nullptr;
					Mage::U16toU8 converter;

					FormatMessageW(
						FORMAT_MESSAGE_ALLOCATE_BUFFER,
						nullptr,
						errCode,
						0,
						reinterpret_cast<LPWSTR>(&pBuffer),
						0,
						nullptr);

					std::string errMsg = converter.to_bytes(pBuffer);
					ss << ": " << errMsg;

					LocalFree(pBuffer);
				}

				m_what = ss.str();
			}

			const char* what() const {
				return m_what.c_str();
			}
		};
	}
}