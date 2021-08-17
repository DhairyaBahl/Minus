#include <gtkmm-3.0/gtkmm.h>
#include <iostream>

class Window : public Gtk::Window
{
    public:
    Window(const Glib::RefPtr<Gtk::Application>& app);
    virtual ~Window();

    public:
    void on_quit();

    Gtk::Box m_Box;

    Glib::RefPtr<Gtk::Builder> builder;
    Glib::RefPtr<Gio::SimpleActionGroup> simple_action_group;
    Glib::RefPtr<Gio::SimpleAction> action_quit;

    Glib::RefPtr<Gtk::UIManager> ui_manager;
    Glib::RefPtr<Gtk::ActionGroup> action_group;

};

Window::Window(const Glib::RefPtr<Gtk::Application>& app)
: m_Box(Gtk::ORIENTATION_VERTICAL) 
{
    
    set_title("Phishy");
    set_default_size(800, 600);

    add(m_Box);

    simple_action_group = Gio::SimpleActionGroup::create();
    simple_action_group->add_action("file-menu");
    simple_action_group->add_action("quit-now");

    insert_action_group("main", simple_action_group);

    builder = Gtk::Builder::create();

    const char* ui_info_builder =
        "<interface>"
        "  <menu id='menubar'>"
        "    <submenu>"
        "      <attribute name='label' translatable='yes'>_File</attribute>"
        "      <section>"
        "        <item>"
        "          <attribute name='action'>main.quit-now</attribute>"
        "          <attribute name='label' translatable='yes'>_Quit</attribute>"
        "        </item>"
        "      </section>"
        "    </submenu>"
        "  </menu>"
        "</interface>";

    try
    {
        builder->add_from_string(ui_info_builder);
    }
    catch(const std::exception& e)
    {
        std::cerr << "unable to build menus" << std::endl;
    }

    auto object = builder->get_object("menubar");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);

    if(!gmenu)
        g_warning("Gmenu not found");
    else
    {
        auto menuBar = Gtk::manage(new Gtk::MenuBar(gmenu));
        m_Box.pack_start(*menuBar, Gtk::PACK_SHRINK);
        // m_Box.append(*menuBar);
    }

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
        m_Box.add(*menu_bar);
    }
    else
    {
        std::cerr << "failed to create menubar" << std::endl;
    }

    show_all_children();

}

Window::~Window() {}

void Window::on_quit()
{
    std::cerr << "Quit request sent" << std::endl;
    hide();
    std::cerr << "Quit successfully" << std::endl;
}