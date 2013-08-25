#ifndef KAKAW_APPLICATION_INCLUDED
#define KAKAW_APPLICATION_INCLUDED


#include <Kakaw/Fwd.hpp>
#include <Kakaw/Utils/NonCopyable.hpp>
#include <memory>


namespace Kakaw {

class Application : private NonCopyable
{

	std::unique_ptr<Window>		mWindowContext;
	std::unique_ptr<Renderer>	mRenderer;
	std::unique_ptr<Input>		mInput;	

public:


	explicit 					Application();
	virtual 					~Application();


	// Application start and end frame
	void						startFrame();
	void						endFrame();


	// Application components.
	Window&						getWindow() const;
	Input *						getInput() const;
	Renderer *					getRenderer() const;

}; // class


} // namespace

#endif // include guard