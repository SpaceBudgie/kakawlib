

#include <Sys/SysPlatform.hpp>
#include <Sys/System.hpp>
#include <Sys/Windows/WinProc.hpp>
#include <Sys/Windows/Win32.hpp>
#include <Sys/Windows/WinInput.hpp>


namespace Sys {

bool CreateAppWindow()
{
	Sys::Win::Win32 win32 = Sys::Win::GetWin32();

	if(Sys::ErrorNotCheckMsg(Sys::Win::GetHWND(), L"A window has already been created, you can't create a second!")) {
		return false;
	}

	// Reg window.
	{
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize        = sizeof (wc);   
		wc.style         = CS_HREDRAW | CS_VREDRAW;//CS_OWNDC;
		wc.lpfnWndProc   = Sys::Win::WinProc;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = Sys::Win::GetInstance();
		wc.hIcon         = 0;
		wc.hCursor       = LoadCursor (0, IDC_ARROW); 
		wc.hbrBackground = CreateSolidBrush(0);
		wc.lpszMenuName  = 0;   
		wc.lpszClassName = L"App";
		wc.hIconSm       = 0;


		if(!Sys::ErrorCheckMsg(RegisterClassEx(&wc), L"Registering class failed!")) {
			return false;
		}
	}


	// Create Window.
	{
		DWORD style		= WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		DWORD styleEx	= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		HWND hwnd		= CreateWindowEx(styleEx, L"App", 0, style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, Sys::Win::GetInstance(), 0);

		if(!Sys::ErrorCheckMsg(hwnd, L"Can't create the window!")) {
			return false;
		}

		Sys::Win::GetWin32().hwnd		= hwnd;
		Sys::Win::GetWin32().hdc		= ::GetDC(hwnd);
		Sys::Win::GetWin32().style		= style;
		Sys::Win::GetWin32().styleEx	= styleEx;

		::SetFocus(hwnd);
	}


	return true;
}



bool ResizeAppWindow(unsigned int const width, unsigned int const height)
{
	// If Zero width can't make window.
	if(!Sys::ErrorCheckMsg(width, L"Can't resize a window with zero width!")) {
		return false;
	}

	// If Zero height can't make widow.
	if(!Sys::ErrorCheckMsg(height, L"Can't resize a window with zero height!")) {
		return false;
	}

	// Check if the window has been created.
	if(!Sys::ErrorCheckMsg(Sys::Win::GetHWND(), L"Can't resize window! Has it been created yet?")) {
		return false;
	}

		

	// Creates the window and centers it.	
	RECT rc = { 0, 0, width, height };

	::AdjustWindowRectEx(&rc, Sys::Win::GetWin32().style, false,  Sys::Win::GetWin32().styleEx);

	LONG actualWidth  = std::abs(rc.left) + std::abs(rc.right);
	LONG actualHeight = std::abs(rc.top)  + std::abs(rc.bottom);

	// Center the window.
	HWND desktopWindow = ::GetDesktopWindow();
	RECT desktopRect;

	::GetClientRect(desktopWindow, &(desktopRect));

	LONG desktopWidth  = desktopRect.right  - desktopRect.left;
	LONG desktopHeight = desktopRect.bottom - desktopRect.top;

	LONG wndPosX = (desktopWidth  - width)  / 2;
	LONG wndPosY = (desktopHeight - height) / 2;

	BOOL window = ::MoveWindow(Sys::Win::GetHWND(), wndPosX, wndPosY, actualWidth, actualHeight, false);

	if(window)
	{
		::ShowWindow(Sys::Win::GetHWND(), SW_SHOW);
		::UpdateWindow(Sys::Win::GetHWND());
		::SetFocus(Sys::Win::GetHWND());
	}

	return window ? true : false;
}



bool MakeFullscreen(bool const isFullscreen)
{
	// Check if the window has been created.
	if(!Sys::ErrorCheckMsg(Sys::Win::GetHWND(), L"Can't set fullscreen! Has the window been created yet?")) {
		return false;
	}

	return true;
}



bool SetAppTitle(std::wstring const title)
{
	// Check if the window has been created.
	if(!Sys::ErrorCheckMsg(Sys::Win::GetHWND(), L"Can't set app title! Has the window been created yet?")) {
		return false;
	}

	return ::SetWindowText(Sys::Win::GetHWND(), title.c_str()) ? true : false;
}




bool IsAppVisible()
{
	if(!Sys::Win::GetHWND()) {
		return false;
	}

	return ::IsWindowVisible(Sys::Win::GetHWND()) ? true : false;
}



bool CloseAppWindow()
{
	if(Sys::Win::GetHWND())
	{
		PostQuitMessage(0);

		::UnregisterClass(L"App", Sys::Win::GetInstance());

		Sys::Win::GetWin32().hwnd = 0;
		Sys::Win::GetWin32().hdc  = 0;

		Sys::Win::Win32 win32 = Sys::Win::GetWin32();

		return true;
	}

	return false;
}



// *** INPUT CONTROL *** //

bool			InitInput()									{ return Sys::Win::InitInput(); }
bool			IsButtonDown(unsigned int const button)		{ return Sys::Win::IsButtonDown(button); }
void			ButtonDownEventCallback(InputCallBack cb)	{ return Sys::Win::SetButtonDownCallback(cb); }
void			ButtonUpEventCallback(InputCallBack cb)		{ return Sys::Win::SetButtonUpCallback(cb); }
unsigned int	MouseXPosition()							{ return 0; }
unsigned int	MouseYPosition()							{ return 0; }
unsigned int	MouseXDelta()								{ return 0; }
unsigned int	MouseYDelta()								{ return 0; }
void			CloseInput()								{}

void ErrorMsg(std::wstring const msg) {
	::MessageBox(0, msg.c_str(), L"Error", MB_OK);
}

void ErrorMsg(std::string const msg) {
	std::wstring errMsg;
	errMsg.assign(msg.begin(), msg.end());
	ErrorMsg(errMsg);
}


} // namespace