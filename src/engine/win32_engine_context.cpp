#include <GL/glew.h>
#include <GL/wglew.h>

#include <mage/engine/win32/render_context.hpp>
#include <mage/os/win32_exception.hpp>

Mage::Win32::RenderingContext::RenderingContext(HINSTANCE hInstance) :
OS::Win32Window(hInstance), m_dc(GetDC(m_handle))
{
	const int pfAttribList[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
		WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,     32,
		WGL_DEPTH_BITS_ARB,     24,
		WGL_STENCIL_BITS_ARB,   8,
		0,
	};

	int pf;
	UINT numFormats;

	if (!wglChoosePixelFormatARB(m_dc, pfAttribList, nullptr, 1, &pf, &numFormats))
	{
		throw OS::Win32Exception("Could not choose pixel format", GetLastError());
	}

	if (!SetPixelFormat(m_dc, pf, nullptr))
	{
		throw OS::Win32Exception("Could not set pixel format", GetLastError());
	}

	// Now we must create the OpenGL 4.5 context.
	const int ctxAttribList[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 5,
		WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifdef _DEBUG
		WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
		0,
	};

	m_rc = wglCreateContextAttribsARB(m_dc, nullptr, ctxAttribList);
	if (!m_rc)
	{
		throw OS::Win32Exception("Could not create context", GetLastError());
	}

	if (!wglMakeCurrent(m_dc, m_rc))
	{
		throw OS::Win32Exception("Could not set context", GetLastError());
	}
}

Mage::Win32::RenderingContext::~RenderingContext()
{
	wglMakeCurrent(m_dc, nullptr);
	wglDeleteContext(m_rc);
}

void Mage::Win32::RenderingContext::swapBuffers()
{
	if (!SwapBuffers(m_dc))
	{
		throw OS::Win32Exception("Swap buffers failed", GetLastError());
	}

	handleMessages();
}
