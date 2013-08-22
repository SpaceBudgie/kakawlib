#include <Kakaw/Kakaw.hpp>

class TestApp : public Kakaw::Application
{
public:

	explicit TestApp()
		: Kakaw::Application()
	{

	}


	void think()
	{}


	void render()
	{}

};


int main()
{
	TestApp app;
	
	while(app.getWindow().isVisible())
	{
		app.startFrame();

		app.think();
		app.render();

		app.endFrame();
	}


	return 0;
}