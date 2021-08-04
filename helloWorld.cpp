#include "HelloWorld.h"
#include<gtkmm-3.0/gtkmm/application.h>

int main()
{
	auto app = Gtk::Application::create("I dont know what the shit is this");

	HelloWorld helloworld ;

	// shows the window
	
	return app->run(helloworld);
}
