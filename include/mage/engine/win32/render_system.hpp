#pragma once

#include <vector>
#include <memory>

#include <windows.h>

#include <mage/engine/render_system.hpp>
#include <mage/engine/render_canvas.hpp>
#include <mage/engine/win32/render_context.hpp>

namespace Mage
{
	namespace Win32
	{
		class RenderSystem : public Mage::RenderSystem
		{
		protected:
			HINSTANCE m_instance;
			std::vector<std::unique_ptr<RenderingCanvas>> m_canvases;
			
		public:
			RenderSystem(HINSTANCE hInstance);
			virtual ~RenderSystem() = default;

			Mage::RenderingCanvas& create_canvas() override;
		};
	}
}
