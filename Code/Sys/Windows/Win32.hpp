#ifndef SYS_WIN32_INCLUDED
#define SYS_WIN32_INCLUDED

#include <Sys/SysPlatform.hpp>

namespace Sys {
namespace Win {

struct Win32
{
	HWND			hwnd;
	HDC				hdc;
	HINSTANCE		instance;

	DWORD			style;
	DWORD			styleEx;
}; // struct


Win32&				GetWin32();
HWND				GetHWND();
HINSTANCE			GetInstance();
void				PumpMessages();

}
} //namespace

#endif // include guard