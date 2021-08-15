#include <iostream>
#include <gtkmm-3.0/gtkmm.h>

class Window:public Gtk::Window
{
    public:

    Window();
    virtual ~Window();
    void on_quit();

    Gtk::VBox m_vbox;

    Glib::RefPtr<Gtk::UIManager> ui_manager;
    Glib::RefPtr<Gtk::ActionGroup> action_group;

};

Window::Window()
{
    
    set_title("Window");
    set_default_size(200, 200);

    add(m_vbox);

    action_group = Gtk::ActionGroup::create();

    action_group->add(Gtk::Action::create("quit", "_Quit"),sigc::mem_fun(*this, &Window::on_quit));

    action_group->add(Gtk::Action::create("file-menu","_File"));

    ui_manager = Gtk::UIManager::create();
    ui_manager->insert_action_group(action_group);

    Glib::ustring ui_info =
        "<ui>"
        "  <menubar name='menubar'>"
        "    <menu action='file-menu'>"
        "      <menuitem action='quit'/>"
        "    </menu>"
        "  </menubar>"
        "</ui>";
    
    try
    {
        ui_manager->add_ui_from_string(ui_info);
    }
    catch(const Glib::Error& ex)
    {
        std::cerr << "building menus failed" << std::endl;
    }

    Gtk::Widget* menu_bar = ui_manager->get_widget("/menubar");

    if(menu_bar)
    {
        m_vbox.pack_start(*menu_bar, Gtk::PACK_SHRINK);
    }
    else
    {
        std::cerr << "failed to create menubar" << std::endl;
    }

    show_all_children();

}

Window::~Window()
{

}

void Window::on_quit()
{
    std::cout << "Quit request sent" << std::endl;
    hide();
}