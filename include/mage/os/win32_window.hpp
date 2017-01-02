#pragma once

#include <Windows.h>
#include <mage/os/window.hpp>

namespace Mage {
	namespace OS {
		class Win32Window : public Mage::OS::Window {
			static LRESULT CALLBACK windowProcInternal(HWND, UINT, WPARAM, LPARAM);

		protected:
			HWND m_handle;
			
		public:
			Win32Window(HINSTANCE hInstance);
			~Win32Window() = default;

			void setVisibility(bool visible);
			void setTitle(const std::string& title) override;
			void handleMessages() const;

			HWND getHandle() const
			{
				return m_handle;
			}
		};
	}
}