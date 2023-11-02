
#include <iostream>

#include "BlockArea.hh"

#include <gtkmm/droptarget.h>

BlockArea::BlockArea()
{
    m_test_rect.set_width(100);
    m_test_rect.set_height(100);
    m_test_rect.set_x(0);
    m_test_rect.set_y(0);

    set_draw_func(sigc::mem_fun(*this, &BlockArea::on_draw));

    Glib::RefPtr<Gtk::GestureClick> gesture = Gtk::GestureClick::create();
    gesture->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
    gesture->signal_pressed().connect(sigc::mem_fun(*this, &BlockArea::on_button_press), false);
    gesture->signal_released().connect(sigc::mem_fun(*this, &BlockArea::on_button_released), false);

    Glib::RefPtr<Gtk::GestureDrag> gesture_drag = Gtk::GestureDrag::create();
    gesture_drag->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
    gesture_drag->signal_drag_begin().connect(sigc::mem_fun(*this, &BlockArea::on_drag_start), false);
    gesture_drag->signal_drag_end().connect(sigc::mem_fun(*this, &BlockArea::on_drag_end), false);
    gesture_drag->signal_drag_update().connect(sigc::mem_fun(*this, &BlockArea::on_drag_update), false);

    const GType ustring_type = Glib::Value<Glib::ustring>::value_type();
    Glib::RefPtr<Gtk::DropTarget> drop_target = Gtk::DropTarget::create(ustring_type, Gdk::DragAction::COPY);
    drop_target->signal_drop().connect(sigc::mem_fun(*this, &BlockArea::on_drop_data), false);

    add_controller(drop_target);
    add_controller(gesture);
    add_controller(gesture_drag);
}

BlockArea::~BlockArea()
{

}

bool
BlockArea::on_drop_data([[maybe_unused]]const Glib::ValueBase& value, [[maybe_unused]] double x, [[maybe_unused]] double y)
{
    if (G_VALUE_HOLDS(value.gobj(), Glib::Value<Glib::ustring>::value_type()))
    {
        // We got the value type that we expected.
        Glib::Value<Glib::ustring> ustring_value;
        ustring_value.init(value.gobj());
        const Glib::ustring dropped_string = ustring_value.get();

        std::cout << "Received \"" << dropped_string << "\" in button " << std::endl;
        return true;
    }
    else
    {
        std::cout << "Received unexpected data type \""
            << G_VALUE_TYPE_NAME(value.gobj()) << "\" in button " << std::endl;
        return false;
    }
}

void
BlockArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, [[maybe_unused]] int width, [[maybe_unused]] int height)
{
    // Set line width to 1 and color to dark grey
    cr->set_line_width(1);
    cr->set_source_rgba(0.1, 0.1, 0.1, 1.0);

    double block_x_position = m_test_rect.get_x();
    double block_y_position = m_test_rect.get_y();
    double block_width = m_test_rect.get_width();
    double block_height = m_test_rect.get_height();
    cr->rectangle(block_x_position, block_y_position, block_width, block_height);

    cr->stroke();

}

void
BlockArea::on_button_press(int n_press, double x, double y)
{
    std::cout << n_press << " " << x << " " << y << std::endl;
    queue_draw();
}

void
BlockArea::on_button_released(int n_press, double x, double y)
{
    if (n_press > 1) {
        double block_x_position = x - m_test_rect.get_width()/2;
        double block_y_position = y - m_test_rect.get_height()/2;

        m_test_rect.set_x(block_x_position);
        m_test_rect.set_y(block_y_position);
    }
    //std::cout << n_press << " " << x << " " << y << std::endl;
    queue_draw();
}

void
BlockArea::on_drag_start(double x, double y)
{
    if (m_test_rect.contains_point(x, y)) {
        double block_x_position = x;
        double block_y_position = y;

        double block_x_drag_start_offset = (m_test_rect.get_x() - x);
        double block_y_drag_start_offset = (m_test_rect.get_y() - y);

        m_drag_start_position.set_x(block_x_position + block_x_drag_start_offset);
        m_drag_start_position.set_y(block_y_position + block_y_drag_start_offset);
        m_in_drag_operation = true;
    }

    //std::cout << x << " " << y << std::endl;
    queue_draw();
}

void
BlockArea::on_drag_end([[maybe_unused]] double x, [[maybe_unused]] double y)
{
    m_in_drag_operation = false;
    //std::cout << x << " " << y << std::endl;
    queue_draw();
}

void
BlockArea::on_drag_update(double x, double y)
{
    if (m_in_drag_operation) {
        m_test_rect.set_x(m_drag_start_position.get_x() + x);
        m_test_rect.set_y(m_drag_start_position.get_y() + y);
        std::cout << x << " " << y << std::endl;
    }
    queue_draw();
}