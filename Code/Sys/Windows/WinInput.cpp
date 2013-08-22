
#include <Sys/Windows/WinInput.hpp>
#include <Sys/Windows/Win32.hpp>
#include <Sys/System.hpp>
#include <bitset>

namespace
{
	const int MAX_KEYS(256);
	std::bitset<MAX_KEYS> keys(0);
	Sys::InputCallBack downCallBack;
	Sys::InputCallBack upCallBack;
}

namespace Sys {
namespace Win {

bool InitInput()
{
	return true;
}

bool UpdateKey(unsigned int param, KeyState::State const buttonState)
{
	if(param < MAX_KEYS)
	{
		//keys[param] = buttonState ? true : false;
		bool previous = keys[param];
		keys[param] = buttonState ? true : false;

		// Fire callback's
		if(previous != keys[param])
		{
			if(downCallBack && (buttonState == KeyState::BUTTON_DOWN)) {
				downCallBack(param);
			}

			if(upCallBack && (buttonState == KeyState::BUTTON_UP)) {
				upCallBack(param);
			}
		}

		return true;
	}

	return false;
}

bool IsButtonDown(unsigned int const button)
{
	if(button > MAX_KEYS) {
		ErrorMsg(L"Bad Key Request!");
		return false;
	}

	return keys[button] ? true : false;
}



void SetButtonDownCallback(InputCallBack cb)
{
	downCallBack = cb;
}

void SetButtonUpCallback(InputCallBack cb)
{
	upCallBack = cb;
}

} // namespace
} // namespace
