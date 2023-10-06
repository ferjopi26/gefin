#include "classes.h"

Classes::Classes()
{
    Gtk::MenuItem *itm_fechar, *itm_nova_classe;
    Gtk::TreeView *listClasses;
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    Gtk::Entry *entry_data_ini, *entry_data_fin;
    Gtk::Popover *pp_dataini, *pp_datafin;
    Glib::DateTime localtime = Glib::DateTime::create_now_local();
    Glib::Date date;
    int year, month, day;
    time_t data_current;
    struct tm * timeinfo;

    localtime.to_local().get_ymd(year, month, day);
    localtime.get_ymd(year, month, day);

    builder = Gtk::Builder::create();

    try
    {
        builder->add_from_resource("/org/gtkmm/gefin/classes.glade");
    }
    catch(const Glib::Error& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return;
    }

    builder->get_widget("win_classes", win_classes);
    builder->get_widget("cmb_classes", cmb_classes);

    store_classes = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_classes"));

    builder->get_widget("calendar_dataini", calendar_dataini);
    builder->get_widget("calendar_datafin", calendar_datafin);

    builder->get_widget("entry_data_ini", entry_data_ini);
    entry_data_ini->signal_button_release_event().connect(sigc::mem_fun(*this, &Classes::on_entry_dataini_release_event));

    builder->get_widget("entry_data_fin", entry_data_fin);
    entry_data_fin->signal_button_release_event().connect(sigc::mem_fun(*this, &Classes::on_entry_datafin_release_event));

    builder->get_widget("itm_fechar", itm_fechar);
    itm_fechar->signal_activate().connect(sigc::mem_fun(*this, &Classes::quit));

    builder->get_widget("itm_nova_classe", itm_nova_classe);
    itm_nova_classe->signal_activate().connect(sigc::mem_fun(*this, &Classes::on_itm_nova_classe_activate_cb));

    time(&data_current);
    timeinfo = std::localtime(&data_current);

    calendar_dataini->select_day(1);
    calendar_dataini->select_month(timeinfo->tm_mon, timeinfo->tm_year+1900);

    calendar_datafin->select_day(Glib::Date::get_days_in_month((Glib::Date::Month)(timeinfo->tm_mon+1), (timeinfo->tm_year + 1900)));
    calendar_datafin->select_month(timeinfo->tm_mon, timeinfo->tm_year+1900);
    
    calendar_dataini->signal_day_selected().connect(sigc::mem_fun(*this, &Classes::on_calendar_dataini_day_selected));
    calendar_datafin->signal_day_selected().connect(sigc::mem_fun(*this, &Classes::on_calendar_datafin_day_selected));

    builder->get_widget("pp_dataini", pp_dataini);
    builder->get_widget("pp_datafin", pp_datafin);

    cmb_classes->signal_changed().connect(sigc::mem_fun(*this, &Classes::on_cmb_classes_changed));

    Classes::getClasses();

}

Classes::~Classes(){}

Gtk::Window *Classes::getWindow()
{
    return win_classes;
}

void Classes::getClasses()
{
    Gtk::ComboBox *cmb_classes;
    QueryClasse *query_classe = new QueryClasse();
    std::list<Classe> *listClasses;
    
    listClasses = query_classe->GetClasses();
    
    store_classes->clear();

    for (auto list_classes = listClasses->begin(); list_classes != listClasses->end(); ++list_classes)
    {
        Gtk::TreeModel::iterator iter = store_classes->append();
        Gtk::TreeModel::Row row = *iter;

        row[m_Columns_Classes.idclasse] = list_classes->get_idclasse();
        row[m_Columns_Classes.classe] = list_classes->get_classe();
    }

    builder->get_widget("cmb_classes", cmb_classes);
    cmb_classes->set_active(0);

}

void Classes::on_cmb_classes_changed()
{
    Gtk::ComboBox *cmb_classes;

    builder->get_widget("cmb_classes", cmb_classes);

    Gtk::TreeModel::iterator iter_classes = cmb_classes->get_active();

    if (iter_classes)
    {
        Classes::getItens();
    }   
    
}

void Classes::getItens()
{
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    Gtk::ComboBox *cmb_classes;
    Glib::Date date;
    Gtk::Entry *entry_data_ini, *entry_data_fin, *entry_total_classe;
    guint year, month, day;
    char sql [1000], dataini[100], datafin[100];

    QueryClasse *query_classe = new QueryClasse();
    std::list<Item> *list_itens = new std::list<Item>;

    builder->get_widget("cmb_classes", cmb_classes);
    builder->get_widget("entry_total_classe", entry_total_classe);

    Gtk::TreeModel::iterator iter_classes = cmb_classes->get_active();
    Gtk::TreeModel::Row row_classes = *iter_classes;
    selected_idclasse = row_classes[m_Columns_Classes.idclasse];
    
    builder->get_widget("calendar_dataini", calendar_dataini);
    builder->get_widget("calendar_datafin", calendar_datafin);

    calendar_dataini->get_date(date);
    builder->get_widget("entry_data_ini", entry_data_ini);
    entry_data_ini->set_text(date.format_string("%d/%m/%Y"));
    
    calendar_dataini->get_date(year, month, day);
    sprintf(dataini, "%d-%02d-%02d", year, month + 1, day);

    calendar_datafin->get_date(year, month, day);
    sprintf(datafin, "%d-%02d-%02d", year, month + 1, day);

    calendar_datafin->get_date(date);
    builder->get_widget("entry_data_fin", entry_data_fin);
    entry_data_fin->set_text(date.format_string("%d/%m/%Y"));

    calendar_datafin->get_date(year, month, day);
    sprintf(datafin, "%d-%02d-%02d", year, month + 1, day);

    calendar_datafin->get_date(date);
    builder->get_widget("entry_data_fin", entry_data_fin);
    entry_data_fin->set_text(date.format_string("%d/%m/%Y"));
    
    auto store_itens = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_itens"));
    store_itens->clear();

    list_itens = query_classe->GetItens(dataini, datafin, selected_idclasse.c_str());

    for (auto itens = list_itens->begin(); itens != list_itens->end(); ++itens)
    {
        Gtk::TreeModel::iterator iter = store_itens->append();
        Gtk::TreeModel::Row row = *iter;

        row[m_Columns_Itens.iditem] = itens->get_iditem();
        row[m_Columns_Itens.item] = itens->get_item();
        row[m_Columns_Itens.valor] = itens->get_valor();
        row[m_Columns_Itens.data] = itens->get_data();
    }

    Classes::getTotais();
}

void Classes::getTotais()
{
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    Gtk::ComboBox *cmb_classes;
    Glib::Date date;
    Gtk::Entry *entry_data_ini, *entry_data_fin, *entry_total_classe;
    guint year, month, day;
    char sql [1000], dataini[100], datafin[100];

    QueryClasse *query_classe = new QueryClasse();
    std::list<Item> *list_total_classe = new std::list<Item>;

    builder->get_widget("cmb_classes", cmb_classes);

    Gtk::TreeModel::iterator iter_classes = cmb_classes->get_active();
    Gtk::TreeModel::Row row_classes = *iter_classes;
    selected_idclasse = row_classes[m_Columns_Classes.idclasse];
    
    builder->get_widget("calendar_dataini", calendar_dataini);
    builder->get_widget("calendar_datafin", calendar_datafin);

    builder->get_widget("entry_total_classe", entry_total_classe);

    calendar_dataini->get_date(date);
    builder->get_widget("entry_data_ini", entry_data_ini);
    entry_data_ini->set_text(date.format_string("%d/%m/%Y"));
    
    calendar_dataini->get_date(year, month, day);
    sprintf(dataini, "%d-%02d-%02d", year, month + 1, day);

    calendar_datafin->get_date(year, month, day);
    sprintf(datafin, "%d-%02d-%02d", year, month + 1, day);

    calendar_datafin->get_date(date);
    builder->get_widget("entry_data_fin", entry_data_fin);
    entry_data_fin->set_text(date.format_string("%d/%m/%Y"));

    calendar_datafin->get_date(year, month, day);
    sprintf(datafin, "%d-%02d-%02d", year, month + 1, day);

    calendar_datafin->get_date(date);
    builder->get_widget("entry_data_fin", entry_data_fin);
    entry_data_fin->set_text(date.format_string("%d/%m/%Y"));
    
    list_total_classe = query_classe->GetTotaisItens(dataini, datafin, selected_idclasse.c_str());

    for (auto total_classe = list_total_classe->begin(); total_classe != list_total_classe->end(); ++total_classe)
    {
        entry_total_classe->set_text(total_classe->get_total_classe());
    }

}

void Classes::quit()
{
    win_classes->close();
}
bool Classes::on_entry_dataini_release_event(GdkEventButton* release_event)
{
    Gtk::Popover * pp_dataini;

    builder->get_widget("pp_dataini", pp_dataini);
    pp_dataini->popup();

    return true;
}

bool Classes::on_entry_datafin_release_event(GdkEventButton* release_event)
{
    Gtk::Popover *pp_datafin;

    builder->get_widget("pp_datafin", pp_datafin);
    pp_datafin->popup();

    return true;
}

void Classes::on_calendar_dataini_day_selected()
{
    Glib::Date startdate;
    Gtk::Entry *entry_data_ini;
    Gtk::Popover *pp_dataini;
    Gtk::Calendar *calendar_dataini;

    builder->get_widget("calendar_dataini", calendar_dataini);
    
    builder->get_widget("entry_data_ini", entry_data_ini);
    
    builder->get_widget("pp_dataini", pp_dataini);
    
    calendar_dataini->get_date(startdate);
    
    entry_data_ini->set_text(startdate.format_string("%d/%m/%Y"));

    pp_dataini->popdown();

    Classes::getItens();
}

void Classes::on_calendar_datafin_day_selected ()
{
    Glib::Date enddate;
    Gtk::Entry *entry_data_fin;
    Gtk::Popover *pp_datafin;
    Gtk::Calendar *calendar_datafin;

    builder->get_widget("calendar_datafin", calendar_datafin);

    builder->get_widget("entry_data_fin", entry_data_fin);
    
    builder->get_widget("pp_datafin", pp_datafin);
    
    calendar_datafin->get_date(enddate);

    entry_data_fin->set_text(enddate.format_string("%d/%m/%Y"));

    pp_datafin->popdown();
    
    Classes::getItens();
}

void Classes::on_itm_nova_classe_activate_cb()
{
    idclasse = selected_idclasse;
    auto nova_classe = new NovaClasse();
    Gtk::Window * win_nova_classe = nova_classe->getWindow();
    win_nova_classe->signal_delete_event().connect(sigc::mem_fun(*this, &Classes::novaClasse));
    win_nova_classe->show();
}

bool Classes::novaClasse(GdkEventAny * ea)
{
    Classes::getClasses();

    Gtk::TreeModel::Children children_classes =  store_classes->children();
    Gtk::TreeModel::iterator iter_classe = cmb_classes->get_active();
    Gtk::TreeModel::Row row_classe;

    for (unsigned int i = 0; i < children_classes.size(); i++)
    {
        cmb_classes->set_active(i);
        iter_classe = cmb_classes->get_active();
        row_classe = *iter_classe;
        
        if (row_classe[m_Columns_Classes.idclasse] == idclasse)
        {
            cmb_classes->set_active(i);
            break;
        }
    }

    return false;
}
