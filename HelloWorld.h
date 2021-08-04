#include<gtkmm-3.0/gtkmm/button.h>
#include<gtkmm-3.0/gtkmm/window.h>
#include<iostream>

class HelloWorld : public Gtk::Window
{
	public:
		HelloWorld();

		// use of virtual keyword is to make sure that on execution of destructor of this class,
		// destructors of all the derived classes are also executed

		virtual ~HelloWorld();

	protected:
		// signal handlers
		void on_button_clicked()
		{
			std::cout << "Hello Bhai" << std::endl ;
		}

		// member widgets
		Gtk::Button m_button;
};

HelloWorld::HelloWorld() : m_button("Hello World")
{

	set_border_width(10);

	m_button.signal_clicked().connect(sigc::mem_fun(*this,&HelloWorld::on_button_clicked));

	add(m_button);

	m_button.show();

}

HelloWorld::~HelloWorld()
{

}