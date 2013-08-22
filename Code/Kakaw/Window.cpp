// Window.cpp

#include <Kakaw/Window.hpp>
#include <Sys/System.hpp>
#include <sys/Windows/Win32.hpp>

namespace Kakaw {


Window::Window(const unsigned int width, const unsigned int height, const bool isFullscreen, const std::wstring title)
	: mWidth(0)
	, mHeight(0)
	, mIsFullscreen(false)
	, mTitle(title)
{
	if(!Sys::CreateAppWindow()) {
		throw "Couldn't create window context!";
	}

	if(!setWindowSize(width, height)) {
		throw "Couldn't set resolution of window context!";
	}
		
	if(!setFullscreen(isFullscreen)) {
		throw "Failed setting fullscreen mode!";
	}

	setWindowTitle(title);
}



Window::~Window() {
	Sys::CloseAppWindow();
}



// Client dimentions

unsigned int Window::getWindowWidth() const		{ return mWidth; }
unsigned int Window::getWindowHeight() const	{ return mHeight; }

bool Window::setWindowSize(const unsigned int width, const unsigned int height)
{
	if(Sys::ResizeAppWindow(width, height))
	{
		mWidth  = width;
		mHeight = height;

		return true;
	}

	return false;
}


// Client fullscreen

bool Window::isFullscreen() const { return mIsFullscreen; }

bool Window::setFullscreen(const bool isFullscreen)
{
	if(Sys::MakeFullscreen(isFullscreen))
	{
		mIsFullscreen = isFullscreen;

		return true;
	}

	return false;
}


//  Client Title
std::wstring Window::getWindowTitle() const { return mTitle; }

bool Window::setWindowTitle(const std::wstring setTitle)
{
	if (Sys::SetAppTitle(setTitle))
	{
		mTitle = setTitle;
		return true;
	}

	return false;
}


// Window State
bool Window::isVisible() const		{ return Sys::IsAppVisible();	}
bool Window::closeWindow() const	{ return Sys::CloseAppWindow(); }


// System platform hooks
void Window::startFrame() { Sys::Win::PumpMessages(); }
void Window::endFrame() {}



} // namespace