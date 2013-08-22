#ifndef KAKAW_INPUT_INCLUDED
#define KAKAW_INPUT_INCLUDED

#include <Kakaw/Utils/NonCopyable.hpp>
#include <sys/System.hpp>

namespace Kakaw {

class Input : private NonCopyable
{
	friend class Application;

	Sys::InputCallBack	buttonDownCallback;
	Sys::InputCallBack	buttonUpCallback;

	bool				mIsMouseHeld;
	bool				mIsMouseVisible;
	unsigned int		mMouseX, mMouseY;
	unsigned int		mMouseDeltaX, mMouseDeltaY;


public:

	explicit 			Input();
						~Input();

	// Keyboard
	bool				isButtonDown(const unsigned int buttonID) const;
	void				onButtonDown(const unsigned int button);
	void				onButtonUp(const unsigned int button);


	// Mouse
	unsigned int		mouseX() const;
	unsigned int		mouseY() const;
	unsigned int		mouseDeltaX() const;
	unsigned int		mouseDeltaY() const;

	bool				isMouseHeld() const;
	bool				setMouseHold(bool const isHeld) const;
	bool				isMouseVisible() const;
	bool				setMouseVisible(bool const isVisible) const;


	// Gamepad	- unsure atm
	// Touch	- unsure atm


private:

	// Platform hooks
	void 				startFrame();
	void 				endFrame();
	
}; // class


} // namespace


#endif // include guard