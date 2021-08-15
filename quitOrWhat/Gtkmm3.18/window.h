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
    Glib::RefPtr<Gio::SimpleActionGroup> action_group;
    Glib::RefPtr<Gio::SimpleAction> action_quit;

};

Window::Window(const Glib::RefPtr<Gtk::Application>& app)
: m_Box(Gtk::ORIENTATION_VERTICAL) 
{
    
    set_title("Phishy");
    set_default_size(800, 600);

    add(m_Box);

    action_group = Gio::SimpleActionGroup::create();
    action_group->add_action("file-menu");
    action_group->add_action("quit", sigc::mem_fun(*this, &Window::on_quit));

    insert_action_group("main", action_group);

    builder = Gtk::Builder::create();

    const char* ui_info =
        "<interface>"
        "  <menu id='menubar'>"
        "    <submenu>"
        "      <attribute name='label' translatable='yes'>_File</attribute>"
        "      <section>"
        "        <item>"
        "          <attribute name='action'>main.quit</attribute>"
        "          <attribute name='label' translatable='yes'>_Quit</attribute>"
        "        </item>"
        "      </section>"
        "    </submenu>"
        "  </menu>"
        "</interface>";

    try
    {
        builder->add_from_string(ui_info);
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