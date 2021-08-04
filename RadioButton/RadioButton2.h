#include<iostream>
#include<gtkmm-3.0/gtkmm/radiobutton.h>
#include<gtkmm-3.0/gtkmm/window.h>

class RadioButton : public Gtk::Window
{

    public:
    
    RadioButton();

    virtual ~RadioButton();

}

RadioButton::RadioButton()
{

    Gtk::RadioButton::Group group ;

    Gtk::RadioButton *m_rb1 = Gtk::manage(new Gtk::RadioButton(group,"button1"));

    Gtk::RadioButton *m_rb2 = Gtk::manage(new Gtk::RadioButton(group,"button2"));

    Gtk::RadioButton *m_rb3 = Gtk::manage(new Gtk::RadioButton(group,"button3"));

    *m_rb1.set_active();

}

RadioButton::~RadioButton()
{

}