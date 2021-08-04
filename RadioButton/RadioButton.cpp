#include "RadioButton1.h"
#include<gtkmm-3.0/gtkmm/application.h>

int main()
{
    auto app = Gtk::Application::create();

    RadioButton button ;

    return app->run(button);
}