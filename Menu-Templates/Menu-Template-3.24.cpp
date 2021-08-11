m_refActionGroup = Gio::SimpleActionGroup::create();

m_refActionGroup->add_action("new", sigc::mem_fun(*this, &ExampleWindow::on_action_file_new));
m_refActionGroup->add_action("open", sigc::mem_fun(*this, &ExampleWindow::on_action_file_open));
m_refActionGroup->add_action("quit", sigc::mem_fun(*this, &ExampleWindow::on_action_file_quit));

insert_action_group("example", m_refActionGroup);

// creating Gtk::Builder 

Glib::RefPtr<Gtk::Builder> m_refBuilder = Gtk::Builder::create();

app->set_accel_for_action("example.new", "<Primary>n");
app->set_accel_for_action("example.quit", "<Primary>q");
app->set_accel_for_action("example.copy", "<Primary>c");
app->set_accel_for_action("example.paste", "<Primary>v");

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

m_refBuilder->add_from_string(ui_info);
m_refBuilder->add_from_resource("/toolbar/toolbar.glade");

// This is the final code to add it in the window 
// and we are also getting the objects from the builder over here.

Glib::RefPtr<Glib::Object> object = m_refBuilder->get_object("menubar");
Glib::RefPtr<Gio::Menu> gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
Gtk::MenuBar* pMenuBar = Gtk::make_managed<Gtk::MenuBar>(gmenu);
m_Box.pack_start(*pMenuBar, Gtk::PACK_SHRINK);

Gtk::Toolbar* toolbar = nullptr;
m_refBuilder->get_widget("toolbar", toolbar);
m_Box.pack_start(*toolbar, Gtk::PACK_SHRINK);