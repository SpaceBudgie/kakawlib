// Input.cpp

#include <Kakaw/Input.hpp>

namespace Kakaw {


Input::Input()
	: mIsMouseHeld(true)
	, mIsMouseVisible(true)
	, mMouseX(0)
	, mMouseY(0)
	, mMouseDeltaX(0)
	, mMouseDeltaY(0)
{
	Sys::InitInput();

	//buttonDownCallback = std::bind(&Input::onButtonDown, this, std::placeholders::_1);
	//Sys::ButtonDownEventCallback(buttonDownCallback);

	//buttonUpCallback = std::bind(&Input::onButtonUp, this, std::placeholders::_1);
	//Sys::ButtonUpEventCallback(buttonUpCallback);
}


Input::~Input()
{
}



// System platform hooks
void Input::startFrame() {}
void Input::endFrame() {}

} // namespace