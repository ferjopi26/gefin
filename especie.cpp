#include "especie.h"

Especie::Especie(){
    Gtk::TreeView *list_especie;
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    Gtk::Entry *entry_dataini, *entry_datafin;
    Gtk::Button *btn_fechar;
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
        builder->add_from_resource("/org/gtkmm/gefin/especie.glade");
    }
    catch(const Glib::Error& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return;
    }

    builder->get_widget("win_especie", win_especie);

    builder->get_widget("calendar_dataini", calendar_dataini);
    builder->get_widget("calendar_datafin", calendar_datafin);
    builder->get_widget("btn_fechar", btn_fechar);

    btn_fechar->signal_clicked().connect(sigc::mem_fun(*this, &Especie::on_btn_fechar_clicked));

    time(&data_current);
    timeinfo = std::localtime(&data_current);

    calendar_dataini->select_day(1);
    calendar_dataini->select_month(timeinfo->tm_mon, timeinfo->tm_year+1900);

    calendar_datafin->select_day(Glib::Date::get_days_in_month((Glib::Date::Month)(timeinfo->tm_mon+1), (timeinfo->tm_year + 1900)));
    calendar_datafin->select_month(timeinfo->tm_mon, timeinfo->tm_year+1900);
    
    calendar_dataini->signal_day_selected().connect(sigc::mem_fun(*this, &Especie::on_calendar_dataini_day_selected));
    calendar_datafin->signal_day_selected().connect(sigc::mem_fun(*this, &Especie::on_calendar_datafin_day_selected));

    builder->get_widget("entry_dataini", entry_dataini);
    entry_dataini->signal_button_release_event().connect(sigc::mem_fun(*this, &Especie::on_entry_dataini_release_event));

    builder->get_widget("entry_datafin", entry_datafin);
    entry_datafin->signal_button_release_event().connect(sigc::mem_fun(*this, &Especie::on_entry_datafin_release_event));

    builder->get_widget("pp_dataini", pp_dataini);
    builder->get_widget("pp_datafin", pp_datafin);

    Especie::on_calendar_dataini_day_selected();
    Especie::on_calendar_datafin_day_selected();

    //Especie::getItens();
}

Especie::~Especie(){}

Gtk::Window *Especie::getWindow()
{
    return win_especie;
}

void Especie::on_calendar_dataini_day_selected(){
    Glib::Date startdate, enddate;
    Gtk::Entry *entry_dataini;
    Gtk::Popover *pp_dataini;
    Gtk::Calendar *calendar_dataini;

    builder->get_widget("calendar_dataini", calendar_dataini);
    
    builder->get_widget("entry_dataini", entry_dataini);
    
    builder->get_widget("pp_dataini", pp_dataini);
    
    calendar_dataini->get_date(startdate);
    
    entry_dataini->set_text(startdate.format_string("%d/%m/%Y"));

    pp_dataini->popdown();

    Especie::getItens();
}

void Especie::on_calendar_datafin_day_selected(){
    Glib::Date enddate;
    Gtk::Entry *entry_datafin;
    Gtk::Popover *pp_datafin;
    Gtk::Calendar *calendar_datafin;

    builder->get_widget("calendar_datafin", calendar_datafin);

    builder->get_widget("entry_datafin", entry_datafin);
    
    builder->get_widget("pp_datafin", pp_datafin);
    
    calendar_datafin->get_date(enddate);

    entry_datafin->set_text(enddate.format_string("%d/%m/%Y"));

    pp_datafin->popdown();
    
    Especie::getItens();
}

bool Especie::on_entry_dataini_release_event(GdkEventButton* release_event){
    Gtk::Popover * pp_dataini;
    
    builder->get_widget("pp_dataini", pp_dataini);
    pp_dataini->popup();

    return true;
}

bool Especie::on_entry_datafin_release_event(GdkEventButton* release_event){
    Gtk::Popover *pp_datafin;

    builder->get_widget("pp_datafin", pp_datafin);
    pp_datafin->popup();

    return true;
}

void Especie::on_btn_fechar_clicked()
{
    win_especie->close();
}

void Especie::getItens()
{
    std::list<Item> *listItens;
    QueryItem *query_item = new QueryItem();
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    char sql[1000] = "", dataini[100], datafin[100], params[100];
    
    unsigned int year, month, day;

    auto store_especie = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_especie"));
    store_especie->clear();

    builder->get_widget("calendar_dataini", calendar_dataini);
    calendar_dataini->get_date(year, month, day);
    sprintf(dataini, "%d-%02d-%02d", year, month + 1, day);
    
    builder->get_widget("calendar_datafin", calendar_datafin);
    calendar_datafin->get_date(year, month, day);
    sprintf(datafin, "%d-%02d-%02d", year, month + 1, day);

    listItens = query_item->GetItens(dataini, datafin, 3);

    for (auto item = listItens->begin(); item != listItens->end(); ++item)
    {
        Gtk::TreeModel::iterator iter = store_especie->append();
        Gtk::TreeModel::Row row = *iter;

        row[m_Columns_Especie.iditem] = item->get_iditem();
        row[m_Columns_Especie.item] = item->get_item();
        row[m_Columns_Especie.valor] = item->get_valor();
        row[m_Columns_Especie.data] = item->get_data();
    }

    Especie::getTotal();
}

void Especie::getTotal()
{
    QueryItem *query_item;
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    Gtk::Entry *entry_total;
    char *total, dataini[100], datafin[100], params[100];    
    unsigned int year, month, day;

    query_item = new QueryItem();

    builder->get_widget("calendar_dataini", calendar_dataini);
    builder->get_widget("entry_total", entry_total);
    
    calendar_dataini->get_date(year, month, day);
    sprintf(dataini, "%d-%02d-%02d", year, month + 1, day);
    
    builder->get_widget("calendar_datafin", calendar_datafin);
    calendar_datafin->get_date(year, month, day);
    sprintf(datafin, "%d-%02d-%02d", year, month + 1, day);

    total = query_item->GetTotaisItens(dataini, datafin, 3);

    entry_total->set_text(total);

}
