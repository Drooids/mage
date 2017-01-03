#include <exception>

#include <Windows.h>

#include <mage/engine/win32/render_system.hpp>
#include <mage/engine/win32/render_context.hpp>
#include <mage/engine/buffer.hpp>
#include <mage/math/matrix.hpp>
#include <mage/ui/frame.hpp>


int WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nShow) {
	try {
		Mage::Win32::RenderSystem rs(hInstance);
		auto& canvas = rs.create_canvas();
		auto& rendering_context = static_cast<Mage::Win32::RenderingContext&>(canvas.get_context());

		rendering_context.set_visibility(true);

		auto& ui = canvas.get_ui_layer();
		auto& frame = ui.create_element<Mage::UI::Frame>("TestFrame");

		while (true)
		{
			canvas.render_next_frame(0);
		}
	}
	catch (std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "An error has occured!", MB_ICONEXCLAMATION | MB_OK);
	}
}