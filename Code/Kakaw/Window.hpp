#ifndef KAKAW_WINDOW_INCLUDED
#define KAKAW_WINDOW_INCLUDED


#include <Kakaw/Utils/NonCopyable.hpp>
#include <string>


namespace Kakaw {

class Window : private NonCopyable
{
	friend class Application;

	unsigned int		mWidth;
	unsigned int		mHeight;
	bool				mIsFullscreen;
	std::wstring		mTitle;

public:

	// Create the window context.
	explicit 			Window(const unsigned int width = 640, const unsigned int height = 480, const bool isFullscreen = false, const std::wstring title = L"KakawApp");
						~Window();
	


	// Client dimentions (if platform allows for it, not including chrome)
	unsigned int 		getWindowWidth() const;
	unsigned int		getWindowHeight() const;
	bool				setWindowSize(const unsigned int width, const unsigned int height);



	// Set fullscreen or not (if platform allows for it).
	bool 				isFullscreen() const;
	bool				setFullscreen(const bool isFullscreen);



	// Title at the top of the window (if platform allows for it).
	std::wstring		getWindowTitle() const;
	bool				setWindowTitle(const std::wstring title);



	// Window State
	bool				isVisible() const;
	bool				closeWindow() const;


private:

	// Sys platform hooks, if the platform needs a chance to do anything.
	void				startFrame();
	void				endFrame();

}; // class

}  // namespace



#endif // include guard