// WinMain.cpp

/*
	Windows starting point, this is abstracted to use int main() instead.
 */


#include <Sys/SysPlatform.hpp>
#include <Sys/Windows/Win32.hpp>

int main();

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE pHInstance, PSTR, int)
{
	::SetThreadAffinityMask(::GetCurrentThread(), 1);

	Sys::Win::Win32 win32;
	ZeroMemory(&win32, sizeof(Sys::Win::Win32));

	Sys::Win::GetWin32() = win32;
	Sys::Win::GetWin32().instance = hInstance;

	return main();
}