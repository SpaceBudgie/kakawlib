#ifndef SYS_WIN_PROC_INCLUDED
#define SYS_WIN_PROC_INCLUDED

#include <Sys/SysPlatform.hpp>
#include <functional>

namespace Sys {
namespace Win {

typedef std::function<bool (HWND, UINT, WPARAM, LPARAM)> MessageHook;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

void AddWindowProcHandler(MessageHook msgHook);


} // namespace
} // namespace


#endif // include guard.