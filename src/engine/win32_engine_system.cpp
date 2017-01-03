#include <mage/engine/win32/render_system.hpp>
#include <mage/os/win32_exception.hpp>
#include <mage/os/win32_window.hpp>

#include <GL/glew.h>

Mage::Win32::RenderSystem::RenderSystem(HINSTANCE hInstance) : 
m_instance(hInstance)
{
	// We must create a fake context first, so we create a hidden window.
	OS::Win32Window fakeWindow(m_instance);
	auto fakeDC = GetDC(fakeWindow.get_handle());
	
	// Create PFD and set the fields we need; the rest are zeroed out.
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	auto pf = ChoosePixelFormat(fakeDC, &pfd);
	if (!pf)
	{
		throw OS::Win32Exception("Could not choose pixel format", GetLastError());
	}

	if (!SetPixelFormat(fakeDC, pf, &pfd))
	{
		throw OS::Win32Exception("Could not set pixel format", GetLastError());
	}

	auto fakeContext = wglCreateContext(fakeDC);
	if (!fakeContext)
	{
		throw OS::Win32Exception("Could not create priming context", GetLastError());
	}

	if (!wglMakeCurrent(fakeDC, fakeContext))
	{
		throw OS::Win32Exception("Could not prime OpenGL for initialization", GetLastError());
	}

	// Now the last step is to prime OpenGL with GLEW.
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		throw Mage::Exception("Could not initialize OpenGL");
	}

	// We are done, destroy the context.
	if (!wglMakeCurrent(fakeDC, nullptr))
	{
		throw OS::Win32Exception("Could not deactivate fake context", GetLastError());
	}

	if (!wglDeleteContext(fakeContext))
	{
		throw OS::Win32Exception("Could not destroy fake context", GetLastError());
	}
}

Mage::RenderingCanvas& Mage::Win32::RenderSystem::create_canvas()
{
	auto ctx = std::make_unique<Win32::RenderingContext>(m_instance);
	m_canvases.emplace_back(std::make_unique<Mage::RenderingCanvas>(std::move(ctx)));
	return *m_canvases.back();
}
