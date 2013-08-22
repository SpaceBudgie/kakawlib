
#include <Sys/Windows/Win32.hpp>


namespace
{
		Sys::Win::Win32		win32;
} // namespace



namespace Sys {
namespace Win {

Win32&				GetWin32()			{ return win32;				}
HDC					GetHDC()			{ return win32.hdc;			}
HWND				GetHWND()			{ return win32.hwnd;		}
HINSTANCE			GetInstance()		{ return win32.instance;	}

void				PumpMessages()
{
	MSG messages;
	if (::PeekMessage(&messages, 0, 0, 0, PM_REMOVE))
    {
		::TranslateMessage(&messages);
		::DispatchMessage(&messages);
    }
}

} // namespace
} // namespace
