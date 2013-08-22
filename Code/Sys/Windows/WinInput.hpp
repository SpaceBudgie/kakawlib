#ifndef SYS_WIN_INPUT_INCLUDED
#define SYS_WIN_INPUT_INCLUDED

#include <Sys/SysPlatform.hpp>
#include <Sys/System.hpp>

namespace Sys {
namespace Win {

namespace KeyState
{
	enum State
	{
		BUTTON_UP		= 0,
		BUTTON_DOWN		= 1,
	};
}

bool InitInput();
bool UpdateKey(unsigned int param, KeyState::State const buttonState);
bool IsButtonDown(unsigned int const button);
void SetButtonDownCallback(InputCallBack cb);
void SetButtonUpCallback(InputCallBack cb);

} // namespace
} // namespace

#endif // include guard