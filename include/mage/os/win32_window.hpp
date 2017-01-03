#pragma once

#include <Windows.h>
#include <mage/os/window.hpp>

namespace Mage {
	namespace OS {
		class Win32Window : public Mage::OS::Window {
			static LRESULT CALLBACK window_proc_internal(HWND, UINT, WPARAM, LPARAM);

		protected:
			HWND m_handle;
			
		public:
			Win32Window(HINSTANCE hInstance);
			~Win32Window() = default;

			void set_visibility(bool visible);
			void set_title(const std::string& title) override;
			void handle_messages() const;

			HWND get_handle() const
			{
				return m_handle;
			}
		};
	}
}