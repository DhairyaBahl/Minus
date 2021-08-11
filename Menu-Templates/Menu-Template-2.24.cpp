m_refActionGroup = Gtk::ActionGroup::create();

m_refActionGroup->add( Gtk::Action::create("MenuFile", "_File") );

m_refActionGroup->add( Gtk::Action::create("New", Gtk::Stock::NEW),sigc::mem_fun(*this, &ExampleWindow::on_action_file_new) );

m_refActionGroup->add( Gtk::Action::create("ExportData", "Export Data"),sigc::mem_fun(*this, &ExampleWindow::on_action_file_open) );

m_refActionGroup->add( Gtk::Action::create("Quit", Gtk::Stock::QUIT),sigc::mem_fun(*this, &ExampleWindow::on_action_file_quit) );

// inserting in the UI manager now

Glib::RefPtr<Gtk::UIManager> m_refUIManager = Gtk::UIManager::create();

m_refUIManager->insert_action_group(m_refActionGroup);

add_accel_group(m_refUIManager->get_accel_group());

// now providing the xml data

Glib::ustring ui_info =
    "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='MenuFile'>"
    "      <menuitem action='New'/>"
    "      <menuitem action='Open'/>"
    "      <separator/>"
    "      <menuitem action='Quit'/>"
    "    </menu>"
    "    <menu action='MenuEdit'>"
    "      <menuitem action='Cut'/>"
    "      <menuitem action='Copy'/>"
    "      <menuitem action='Paste'/>"
    "    </menu>"
    "  </menubar>"
    "  <toolbar  name='ToolBar'>"
    "    <toolitem action='Open'/>"
    "    <toolitem action='Quit'/>"
    "  </toolbar>"
    "</ui>";

m_refUIManager->add_ui_from_string(ui_info);

Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
pBox->add(*pMenuBar, Gtk::PACK_SHRINK);