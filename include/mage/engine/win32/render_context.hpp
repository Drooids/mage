#pragma once

#include <Windows.h>

#include <mage/engine/render_canvas.hpp>
#include <mage/os/win32_window.hpp>

namespace Mage
{
	namespace Win32
	{
		class RenderingContext final : public OS::Win32Window, public Mage::RenderingContext
		{
		protected:
			HDC m_dc;
			HGLRC m_rc;

		public:
			RenderingContext(HINSTANCE hInstance);
			~RenderingContext();
			
			void swap_buffers() override;
			uint64_t get_client_width() override;
			uint64_t get_client_height() override;
		};
	}
}