#include<gtkmm-3.0/gtkmm.h>
using namespace std;

int main()
{
	auto app = Gtk::Application::create("org.gtkmm.examples.base");
	Gtk::Window window ;
	window.set_default_size(400,400);
	window.set_title("hello world");
	return app->run(window);
}
