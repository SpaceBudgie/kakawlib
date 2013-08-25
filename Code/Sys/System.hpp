#ifndef SYS_INCLUDED
#define SYS_INCLUDED

#include <string>
#include <functional>

namespace Sys {


// *** WINDOW CONTEXT CONTROL *** //

bool			CreateAppWindow();
bool			ResizeAppWindow(unsigned int const width, unsigned int const height);
bool			MakeFullscreen(bool const isFullscreen);
bool			SetAppTitle(std::wstring const title);
bool			IsAppVisible();
bool			CloseAppWindow();



// *** INPUT CONTROL *** //

typedef std::function<void(unsigned int)> InputCallBack;

bool			InitInput();
bool			IsButtonDown(unsigned int const button);
void			ButtonDownEventCallback(InputCallBack callback);
void			ButtonUpEventCallback(InputCallBack callback);
unsigned int	MouseXPosition();
unsigned int	MouseYPosition();
unsigned int	MouseXDelta();
unsigned int	MouseYDelta();
void			CloseInput();



// *** ERROR HANDLING *** //

void ErrorMsg(std::wstring const msg);
void ErrorMsg(std::string const msg);


// Displays an error for zero check.
template<class T>
T ErrorCheckMsg(T const check, std::wstring const msg)
{
	if(!check) {
		ErrorMsg(msg);
	}

	return check;
}


// Displays an error for non-zero check.
template<class T>
T ErrorNotCheckMsg(T const check, std::wstring const msg)
{
	if(check) {
		ErrorMsg(msg);
	}

	return check;
}



} // namespace

#endif // include guard