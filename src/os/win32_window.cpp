#include <codecvt>

#include <mage/os/win32_exception.hpp>
#include <mage/os/win32_window.hpp>

#define MAGE_WINDOW_CLASSNAME L"MageWindowClass"

Mage::OS::Win32Window::Win32Window(HINSTANCE hInstance)
{
	WNDCLASSEXW wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEXW));

	// Check if the class exists.
	if (!GetClassInfoExW(hInstance, MAGE_WINDOW_CLASSNAME, &wc)) {
		// The window class does not yet exist, so we should write it.
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = windowProcInternal;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
		wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = MAGE_WINDOW_CLASSNAME;
		wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

		if (!RegisterClassExW(&wc))
		{
			throw Win32Exception("Could not register window class", GetLastError());
		}
	}

	// Create our window.
	m_handle = CreateWindowExW(
		WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW,
		MAGE_WINDOW_CLASSNAME,
		L"Mage",
		WS_OVERLAPPEDWINDOW,
		50,
		50,
		m_width,
		m_height,
		nullptr,
		nullptr,
		hInstance,
		this
	);

	if (!m_handle) {
		throw Win32Exception("Could not create window", GetLastError());
	}
}

LRESULT CALLBACK Mage::OS::Win32Window::windowProcInternal(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

void Mage::OS::Win32Window::setTitle(const std::string& title)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	SetWindowTextW(m_handle, converter.from_bytes(title).c_str());
	m_title = title;
}

void Mage::OS::Win32Window::setVisibility(bool visible)
{
	if (ShowWindow(m_handle, visible))
	{
		m_visible = visible;
	}
}

void Mage::OS::Win32Window::handleMessages() const
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	UpdateWindow(m_handle);

	while (PeekMessageW(&msg, m_handle, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
