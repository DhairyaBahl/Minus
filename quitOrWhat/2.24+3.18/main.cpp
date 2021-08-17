#include <gtkmm-3.0/gtkmm.h>
#include "window.h"

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("sampleOrWot");

    Window window(app);

    return app->run(window);

}