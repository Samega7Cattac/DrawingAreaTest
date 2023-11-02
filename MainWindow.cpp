// PROJECT headers
#include "MainWindow.hh"

// GTKMM headers
#include <gtkmm/box.h>

constexpr const char WINDOW_TITLE_NAME[] = "Drawing Area Test";

constexpr const int WINDOW_WIDTH = 800;

constexpr const int WINDOW_HEIGHT = 600;

MainWindow::MainWindow ()
{
    // Set base default window properties and add icon
    set_title(WINDOW_TITLE_NAME);
    set_default_size(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create Main box that will contain both the menu and drawing area
    Gtk::Box* main_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    set_child(*main_box);
    
    m_node_selector.set_vexpand(false);
    main_box->append(m_node_selector);
    

    m_draw_area.set_expand(true);
    m_draw_area.set_valign(Gtk::Align::FILL);
    main_box->append(m_draw_area);
}


MainWindow::~MainWindow()
{
}
