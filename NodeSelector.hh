#ifndef NODE_SELECTOR_HH
#define NODE_SELECTOR_HH

// GTKMM headers
#include <gtkmm/box.h>
#include <gtkmm/gridview.h>
#include <gtkmm/singleselection.h>
#include <giomm/liststore.h>
#include <gtkmm/picture.h>
#include <gtkmm/listitem.h>

class NodeSelector : public Gtk::Box
{
public:
    NodeSelector();
    ~NodeSelector();

private:
    class IconModel : public Glib::Object
    {
    public:
        // TODO: Removing this triggers a compile error for no reason
        IconModel() = default;

        static Glib::RefPtr<IconModel> create(Glib::RefPtr<Gdk::Texture> image,
                                              const std::string& name);

        Glib::RefPtr<Gdk::Texture> GetImage() const;

        std::string GetName() const;

    protected:
        IconModel(Glib::RefPtr<Gdk::Texture> image,
                  const std::string& name);

    private:
        Glib::RefPtr<Gdk::Texture> m_image;

        std::string m_name;
    };

    Glib::RefPtr<Gio::ListStore<IconModel>> m_data_model;
    Glib::RefPtr<Gtk::SingleSelection> m_selection_model;

    IconModel m_columns;

    Gtk::GridView m_nodes;

    void OnImageSetup(const Glib::RefPtr<Gtk::ListItem>& list_item);

    void OnImageBind(const Glib::RefPtr<Gtk::ListItem>& list_item);

    void LoadIcons();

    Glib::RefPtr<Gdk::ContentProvider> PrepareDataToDrag(double, double);

    void OnEndDrag(Gdk::EventSequence*);
};

#endif // NODE_SELECTOR_HH