#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

// PROJECT headers
#include "BlockArea.hh"
#include "NodeSelector.hh"

// GTKMM headers
#include <gtkmm/applicationwindow.h>
#include <gtkmm/drawingarea.h>

//! @brief This is the main window, it constructs the window widgets and childs
//!
//! The main window contain all the base resources which will appear on screen.
//! The derived objects will be contained inside the base classes, and forward.
//!
class MainWindow : public Gtk::ApplicationWindow
{
public:

    //! @brief Windows constructor with
    //!
    MainWindow();

    //! @brief Windows destructor
    //!
    //! This class is designed no to be derived
    //!
    ~MainWindow();

protected:

private:
    NodeSelector m_node_selector;

    BlockArea m_draw_area;
};

#endif // MAINWINDOW_HH
