#include <gtkmm-3.0/gtkmm.h>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    
    auto app = Gtk::Application::create("New App");
    
    MainWindow window(app);

    return app->run(window);

}