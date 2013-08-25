#include <Kakaw/Kakaw.hpp>

#include <Sys/System.hpp>
#include <exception>

class TestApp : public Kakaw::Application
{
public:

	explicit TestApp()
		: Kakaw::Application()
	{

	}


	void think()
	{
	}


	void render()
	{
		float color[] = {0.2f,0.2f,0.2f,1};
		getRenderer()->clear(true, &color[0]);
	}

};


int main()
{
	try
	{
		TestApp app;
		app.getWindow().setWindowSize(1200, 720);
		app.getRenderer()->setDefaultBufferSize(1200, 720);
	
		while(app.getWindow().isVisible())
		{
			app.startFrame();

			app.think();
			app.render();

			app.endFrame();
		}
	}

	catch(std::exception& e)
	{
		Sys::ErrorMsg(e.what());
	}


	return 0;
}