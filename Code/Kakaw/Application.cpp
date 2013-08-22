// Application.cpp


#include <Kakaw/Application.hpp>
#include <Kakaw/Renderer.hpp>
#include <Kakaw/Window.hpp>
#include <Kakaw/Input.hpp>


namespace Kakaw {


Application::Application()
	: mWindowContext( new Window())
	, mRenderer(new Renderer())
	, mInput(new Input())
{

}


Application::~Application()
{

}


void Application::startFrame()
{
	mWindowContext->startFrame();
	mRenderer->startFrame();
	mInput->startFrame();
}


void Application::endFrame()
{
	mWindowContext->endFrame();
	mRenderer->endFrame();
	mInput->endFrame();
}



Window& Application::getWindow() const
{
	return *mWindowContext.get();
}



Input *	Application::getInput() const
{
	return mInput.get();
}



Renderer * Application::getRenderer() const
{
	return mRenderer.get();
}




} // namespace