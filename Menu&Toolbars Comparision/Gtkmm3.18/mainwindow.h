#include <gtkmm-3.0/gtkmm.h>
#include <iostream>

class MainWindow : public Gtk::Window
{
    public:
        MainWindow(const Glib::RefPtr<Gtk::Application>& app);
        virtual ~MainWindow();

    private:
        //Signal handlers:
        void on_action_file_new();
        void on_action_quit();
        void on_action_others();
        void on_action_toggle();

        // child widgets
        Gtk::Box m_Box;

        Glib::RefPtr<Gtk::Builder> m_refBuilder;
        Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;
        Glib::RefPtr<Gio::SimpleAction> m_refActionRain;
};

MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application>& app)
: m_Box(Gtk::ORIENTATION_VERTICAL)
{
    
    set_title("main-menu");
    set_default_size(200, 200);

    add(m_Box);

    m_refActionGroup = Gio::SimpleActionGroup::create();

    m_refActionGroup->add_action("new", sigc::mem_fun(*this, &MainWindow::on_action_file_new));
    m_refActionGroup->add_action("open", sigc::mem_fun(*this, &MainWindow::on_action_others));

    m_refActionRain = m_refActionGroup->add_action("rain", sigc::mem_fun(*this, &MainWindow::on_action_toggle));

    m_refActionGroup->add_action("quit",sigc::mem_fun(*this, &MainWindow::on_action_quit));

    m_refActionGroup->add_action("cut",sigc::mem_fun(*this, &MainWindow::on_action_others) );
    m_refActionGroup->add_action("copy",sigc::mem_fun(*this, &MainWindow::on_action_others) );
    m_refActionGroup->add_action("paste",sigc::mem_fun(*this, &MainWindow::on_action_others) );

    insert_action_group("example", m_refActionGroup);

    //Define how the actions are presented in the menus and toolbars:
    m_refBuilder = Gtk::Builder::create();

    //Layout the actions in a menubar and toolbar:
  const char* ui_info =
    "<interface>"
    "  <menu id='menubar'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_New</attribute>"
    "          <attribute name='action'>example.new</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Open</attribute>"
    "          <attribute name='action'>example.open</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;o</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Rain</attribute>"
    "          <attribute name='action'>example.rain</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Quit</attribute>"
    "          <attribute name='action'>example.quit</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Edit</attribute>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Cut</attribute>"
    "        <attribute name='action'>example.cut</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;x</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Copy</attribute>"
    "        <attribute name='action'>example.copy</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;c</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Paste</attribute>"
    "        <attribute name='action'>example.paste</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;v</attribute>"
    "      </item>"
    "    </submenu>"
    "  </menu>"
    "</interface>";

    app->set_accel_for_action("example.new", "<Primary>n");
    app->set_accel_for_action("example.open", "<Primary>o");
    app->set_accel_for_action("example.quit", "<Primary>q");
    app->set_accel_for_action("example.cut", "<Primary>x");
    app->set_accel_for_action("example.copy", "<Primary>c");
    app->set_accel_for_action("example.paste", "<Primary>v");

    try
    {
    m_refBuilder->add_from_string(ui_info);
    m_refBuilder->add_from_resource("/toolbar/toolbar.glade");
    }
    catch(const Glib::Error& ex)
    {
    std::cerr << "Building menus and toolbar failed: " <<  ex.what();
    }

    //Get the menubar:
    auto object = m_refBuilder->get_object("menubar");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    if (!gmenu)
        g_warning("GMenu not found");
    else
    {
        auto pMenuBar = Gtk::make_managed<Gtk::MenuBar>(gmenu);

        //Add the MenuBar to the window:
        m_Box.pack_start(*pMenuBar, Gtk::PACK_SHRINK);
    }

    //Get the toolbar and add it to a container widget:
    Gtk::Toolbar* toolbar = nullptr;
    m_refBuilder->get_widget("toolbar", toolbar);
    if (!toolbar)
    g_warning("GtkToolbar not found");
    else
    m_Box.pack_start(*toolbar, Gtk::PACK_SHRINK);

    show_all_children();

}

MainWindow::~MainWindow()
{

}

void MainWindow::on_action_quit()
{
    hide();
}

void MainWindow::on_action_file_new()
{
    std::cout << "New File" << std::endl;
}

void MainWindow::on_action_others()
{
    std::cout << "Other File" << std::endl;
}

void MainWindow::on_action_toggle()
{

    std::cout << "The toggle menu item was selected." << std::endl;

    bool active = false;
    m_refActionRain->get_state(active);

    //The toggle action's state does not change automatically:
    active = !active;
    m_refActionRain->change_state(active);

    Glib::ustring message;
    if(active)
    message = "Toggle is active.";
    else
    message = "Toggle is not active";

    std::cout << message << std::endl;

}