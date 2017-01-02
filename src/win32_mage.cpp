#include <exception>

#include <Windows.h>

#include <mage/engine/win32/render_system.hpp>
#include <mage/engine/win32/render_context.hpp>
#include <mage/engine/buffer.hpp>

#include <mage/math/matrix.hpp>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nShow) {
	try {
		Mage::Win32::RenderSystem rs(hInstance);
		auto& canvas = rs.createCanvas();
		auto& surface = static_cast<Mage::Win32::RenderingContext&>(canvas.getContext());

		std::vector<float> quad_vertex = {
			-1.0f,  1.0f,
			 1.0f,  1.0f,
			 1.0f, -1.0f,

			 1.0f, -1.0f,
			-1.0f, -1.0f,
			-1.0f,  1.0f
		};

		Mage::Buffer quad_buf(6 * 2 * sizeof(float));
		quad_buf.data(quad_vertex.begin(), quad_vertex.end());

		surface.setVisibility(true);
		while (true)
		{
			canvas.renderNextFrame(0);
		}
	}
	catch (std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "An error has occured!", MB_ICONEXCLAMATION | MB_OK);
	}
}