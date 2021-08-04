#include<gtkmm-3.0/gtkmm/radiobutton.h>
#include<gtkmm-3.0/gtkmm/window.h>
#include<gtkmm-3.0/gtkmm/button.h>
#include<gtkmm-3.0/gtkmm/box.h>
#include<gtkmm-3.0/gtkmm/separator.h>

class RadioButton : public Gtk::Window
{
    public:
    RadioButton();
    virtual ~RadioButton();

    protected:
    
    // signal handlers
    void on_button_clicked();

    //child widgets
    Gtk::Box m_Box_top, m_Box1 , m_Box2;

    Gtk::RadioButton m_RadioButton1, m_RadioButton2 , m_RadioButton3 ;

    Gtk::Separator m_separator ;

    Gtk::Button m_button_close ;

};

// what we are doing here is we are first creating a group for button1 and then
// we want the other two's to share that as well

RadioButton::RadioButton() : m_Box_top(Gtk::ORIENTATION_VERTICAL),
m_Box1(Gtk::ORIENTATION_HORIZONTAL , 10),
m_Box2(Gtk::ORIENTATION_HORIZONTAL , 10),
m_RadioButton1("Button1"),
m_RadioButton2("Button2"),
m_RadioButton3("Button3"),
m_button_close("close")
{

    // set title and border of the window
    set_title("This is the title");
    set_border_width(0);

    // put radio button 2 and 3 same as in the group 1 
    Gtk::RadioButton::Group group = m_RadioButton1.get_group();
    m_RadioButton2.set_group(group);
    m_RadioButton3.set_group(group);
    m_RadioButton1.set_active();

    // add outer box to the window 
    // because the window can only contain a single widget
    add(m_Box_top);

    // put inner boxes and separators in the outer box
    m_Box_top.pack_start(m_Box1);
    m_Box_top.pack_start(m_separator);
    m_Box_top.pack_start(m_Box2);

    // set inner boxes borders
    m_Box2.set_border_width(10);
    m_Box1.set_border_width(10);

    // putting radio buttons in the box1 
    m_Box1.pack_start(m_RadioButton1);
    m_Box1.pack_start(m_RadioButton2);
    m_Box1.pack_start(m_RadioButton3);

    // setting the second radio button active
    m_RadioButton2.set_active();

    // put the close button in the box2 
    m_Box2.pack_start(m_button_close);

    // make the button the default widget
    m_button_close.set_can_default();
    m_button_close.grab_default();

    // connect the clicked signal to the radio buttons
    // RadioButtons::on_button_clicked()
    m_button_close.signal_clicked().connect(sigc::mem_fun(*this,&RadioButton::on_button_clicked));

    // show all children of the window
    show_all_children();

}

RadioButton::~RadioButton()
{

}

void RadioButton::on_button_clicked()
{
    // to close the application
    hide();
}