#ifndef BLOCKAREA_HH
#define BLOCKAREA_HH

// GTKMM headers
#include <gtkmm/drawingarea.h>
#include <gtkmm/eventcontroller.h>
#include <cairomm/cairomm.h>
#include <gtkmm/gestureclick.h>
#include <gtkmm/gesturedrag.h>


class BlockArea : public Gtk::DrawingArea
{

    public:
        BlockArea();
        virtual ~BlockArea();

    private:
        Gdk::Rectangle m_test_rect;

        Gdk::Rectangle m_drag_start_position;

        bool m_in_drag_operation = false;

        void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
        void on_button_press(int n_press, double x, double y);
        void on_button_released(int n_press, double x, double y);


        void on_drag_start(double x, double y);
        void on_drag_end(double x, double y);
        void on_drag_update(double x, double y);

        bool on_drop_data(const Glib::ValueBase& value, double x, double y);


};

#endif