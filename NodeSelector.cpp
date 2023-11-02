#include "NodeSelector.hh"

// IMAGES headers
#include "images/cloudflare.imgh"
#include "images/dyndns.imgh"
#include "images/ioxhost.imgh"
#include "images/maxcdn.imgh"
#include "images/mybatis.imgh"
#include "images/plesk.imgh"

// GTKMM headers
#include <gtkmm/dragsource.h>
#include <gtkmm/signallistitemfactory.h>

NodeSelector::NodeSelector() :
    Gtk::Box(Gtk::Orientation::VERTICAL),
    m_data_model(Gio::ListStore<IconModel>::create())
{
    m_selection_model = Gtk::SingleSelection::create(m_data_model);
    m_selection_model->set_autoselect(false);

    Glib::RefPtr<Gtk::SignalListItemFactory> grid_factory = Gtk::SignalListItemFactory::create();
    grid_factory->signal_setup().connect(
        sigc::mem_fun(*this, &NodeSelector::OnImageSetup));
    grid_factory->signal_bind().connect(
        sigc::mem_fun(*this, &NodeSelector::OnImageBind));

    m_nodes.set_model(m_selection_model);
    m_nodes.set_factory(grid_factory);
    append(m_nodes);

    Glib::RefPtr<Gtk::DragSource> drag_source = Gtk::DragSource::create();
    drag_source->set_actions(Gdk::DragAction::COPY);
    drag_source->signal_prepare().connect(sigc::mem_fun(*this, &NodeSelector::PrepareDataToDrag), false);
    drag_source->signal_end().connect(sigc::mem_fun(*this, &NodeSelector::OnEndDrag));
    m_nodes.add_controller(drag_source);

    m_nodes.set_single_click_activate(true);

    LoadIcons();
}

NodeSelector::~NodeSelector()
{
    
}

Glib::RefPtr<NodeSelector::IconModel>
NodeSelector::IconModel::create(Glib::RefPtr<Gdk::Texture> image,
                                const std::string& name)
{
    return Glib::make_refptr_for_instance<IconModel>(
                new IconModel(image, name));
}

Glib::RefPtr<Gdk::Texture>
NodeSelector::IconModel::GetImage() const
{
    return m_image;
}

std::string
NodeSelector::IconModel::GetName() const
{
    return m_name;
}

NodeSelector::IconModel::IconModel(Glib::RefPtr<Gdk::Texture> image,
                                   const std::string& name) :
    m_image(image),
    m_name(name)
{

}

void NodeSelector::OnImageSetup(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    Gtk::Picture* image = Gtk::make_managed<Gtk::Picture>();
    image->set_can_shrink(false);
    list_item->set_child(*image);
}

void NodeSelector::OnImageBind(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    Glib::RefPtr<IconModel> col = std::dynamic_pointer_cast<IconModel>(list_item->get_item());
    if (col == nullptr)
    {
        return;
    }
    Gtk::Picture* picture = dynamic_cast<Gtk::Picture*>(list_item->get_child());
    if (picture == nullptr)
    {
        return;
    }
    picture->set_paintable(col->GetImage());
}

void
NodeSelector::LoadIcons()
{
    Glib::RefPtr<Gdk::Pixbuf> cloudflare =
        Gdk::Pixbuf::create_from_data(CLOUDFLARE_PIXEL_DATA,
                                    Gdk::Colorspace::RGB,
                                    true,
                                    8,
                                    CLOUDFLARE_WIDTH,
                                    CLOUDFLARE_HEIGHT,
                                    CLOUDFLARE_ROWSTRIDE);
    m_data_model->append(IconModel::create(Gdk::Texture::create_for_pixbuf(cloudflare), "cloudflare"));

    Glib::RefPtr<Gdk::Pixbuf> dyndns =
        Gdk::Pixbuf::create_from_data(DYNDNS_PIXEL_DATA,
                                    Gdk::Colorspace::RGB,
                                    true,
                                    8,
                                    DYNDNS_WIDTH,
                                    DYNDNS_HEIGHT,
                                    DYNDNS_ROWSTRIDE);
    m_data_model->append(IconModel::create(Gdk::Texture::create_for_pixbuf(dyndns), "dyndns"));

    Glib::RefPtr<Gdk::Pixbuf> ioxhost =
        Gdk::Pixbuf::create_from_data(IOXHOST_PIXEL_DATA,
                                    Gdk::Colorspace::RGB,
                                    true,
                                    8,
                                    IOXHOST_WIDTH,
                                    IOXHOST_HEIGHT,
                                    IOXHOST_ROWSTRIDE);
    m_data_model->append(IconModel::create(Gdk::Texture::create_for_pixbuf(ioxhost), "ioxhost"));

    Glib::RefPtr<Gdk::Pixbuf> maxcdn =
        Gdk::Pixbuf::create_from_data(MAXCDN_PIXEL_DATA,
                                    Gdk::Colorspace::RGB,
                                    true,
                                    8,
                                    MAXCDN_WIDTH,
                                    MAXCDN_HEIGHT,
                                    MAXCDN_ROWSTRIDE);
    m_data_model->append(IconModel::create(Gdk::Texture::create_for_pixbuf(maxcdn), "maxcdn"));

    Glib::RefPtr<Gdk::Pixbuf> mybatis =
        Gdk::Pixbuf::create_from_data(MYBATIS_PIXEL_DATA,
                                    Gdk::Colorspace::RGB,
                                    true,
                                    8,
                                    MYBATIS_WIDTH,
                                    MYBATIS_HEIGHT,
                                    MYBATIS_ROWSTRIDE);
    m_data_model->append(IconModel::create(Gdk::Texture::create_for_pixbuf(mybatis), "mybatis"));

    Glib::RefPtr<Gdk::Pixbuf> plesk =
        Gdk::Pixbuf::create_from_data(PLESK_PIXEL_DATA,
                                    Gdk::Colorspace::RGB,
                                    true,
                                    8,
                                    PLESK_WIDTH,
                                    PLESK_HEIGHT,
                                    PLESK_ROWSTRIDE);
    m_data_model->append(IconModel::create(Gdk::Texture::create_for_pixbuf(plesk), "plesk"));
}

Glib::RefPtr<Gdk::ContentProvider>
NodeSelector::PrepareDataToDrag(double, double)
{
    Glib::RefPtr<Glib::ObjectBase> obj = m_selection_model->get_selected_item();
    Glib::RefPtr<IconModel> col = std::dynamic_pointer_cast<IconModel>(obj);

    Glib::Value<Glib::ustring> ustring_value;
    ustring_value.init(ustring_value.value_type());
    ustring_value.set(col->GetName());
    return Gdk::ContentProvider::create(ustring_value);
}

void
NodeSelector::OnEndDrag(Gdk::EventSequence*)
{
    // TODO: The point of this is to deselect when the drag is finished but it's still selected
    m_selection_model->unselect_all();
}
