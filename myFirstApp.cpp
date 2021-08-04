#include<iostream>
#include<gtkmm-3.0/gtkmm.h>

using namespace std;

int main()
{
	auto myApp = Gtk::Application::create("org.baktech.Demo");

	Gtk::Window mainWindow ;

	mainWindow.set_size_request(800,800);

	mainWindow.set_title("This is the header");

	return myApp->run(mainWindow);

}
