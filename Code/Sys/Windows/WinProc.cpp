
#include <Sys/Windows/WinProc.hpp>
#include <Sys/Windows/WinInput.hpp>
#include <vector>


namespace
{
	std::vector<Sys::Win::MessageHook > procHandlers;
}


namespace Sys {
namespace Win {

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case(WM_KEYUP):
	case(WM_SYSKEYUP):
		UpdateKey((unsigned int)wparam, KeyState::BUTTON_UP);
		return 0;

	case(WM_KEYDOWN):
	case(WM_SYSKEYDOWN):
		UpdateKey((unsigned int)wparam, KeyState::BUTTON_DOWN);
		return 0;

	case(WM_LBUTTONDOWN):
		UpdateKey(0x01, KeyState::BUTTON_DOWN);
		return 0;

	case(WM_LBUTTONUP):
		UpdateKey(0x01, KeyState::BUTTON_UP);
		return 0;

	case(WM_MBUTTONDOWN):
		UpdateKey(0x04, KeyState::BUTTON_DOWN);
		return 0;

	case(WM_MBUTTONUP):
		UpdateKey(0x04, KeyState::BUTTON_UP);
		return 0;

	case(WM_RBUTTONDOWN):
		UpdateKey(0x02, KeyState::BUTTON_DOWN);
		return 0;

	case(WM_RBUTTONUP):
		UpdateKey(0x02, KeyState::BUTTON_UP);
		return 0;
	};

	// Process any hooks.
	std::vector<MessageHook>::iterator msgIt = procHandlers.begin();

	for(; msgIt != procHandlers.end(); msgIt++) {
		bool swallowed = (*msgIt)(hwnd, msg, wparam, lparam);
				
		if(swallowed) {
			break;
		}
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}


void AddWindowProcHandler(MessageHook msgHook) {
	procHandlers.push_back(msgHook);
}


} // namespace
} // namespace