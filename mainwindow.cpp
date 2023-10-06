#include "mainwindow.h"

MainWindow::MainWindow()
{
    Gtk::MenuItem *itm_sair, *itm_novo_item, *itm_bancos, *itm_classes, *itm_especie, *itm_relatorio;
    Gtk::TreeView *list_itens;
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    Gtk::Entry *entry_dataini, *entry_datafin;
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
        builder->add_from_resource("/org/gtkmm/gefin/main_window.glade");
    }
    catch(const Glib::Error& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return;
    }

    builder->get_widget("mainwindow", mainwindow);

    builder->get_widget("itm_sair", itm_sair);
    itm_sair->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::quit));

    builder->get_widget("itm_bancos", itm_bancos);
    itm_bancos->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_itm_bancos_activate_cb));

    builder->get_widget("itm_classes", itm_classes);
    itm_classes->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_itm_classes_activate_cb));

    builder->get_widget("itm_especie", itm_especie);
    itm_especie->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_itm_especie_activate_cb));

    builder->get_widget("itm_relatorio", itm_relatorio);
    itm_relatorio->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_itm_relatorio_mensal_activate_cb));

    builder->get_widget("calendar_dataini", calendar_dataini);
    builder->get_widget("calendar_datafin", calendar_datafin);

    time(&data_current);
    timeinfo = std::localtime(&data_current);

    calendar_dataini->select_day(1);
    calendar_dataini->select_month(timeinfo->tm_mon, timeinfo->tm_year+1900);

    calendar_datafin->select_day(Glib::Date::get_days_in_month((Glib::Date::Month)(timeinfo->tm_mon+1), (timeinfo->tm_year + 1900)));
    calendar_datafin->select_month(timeinfo->tm_mon, timeinfo->tm_year+1900);
    
    calendar_dataini->signal_day_selected().connect(sigc::mem_fun(*this, &MainWindow::on_calendar_dataini_day_selected));
    calendar_datafin->signal_day_selected().connect(sigc::mem_fun(*this, &MainWindow::on_calendar_datafin_day_selected));

    builder->get_widget("entry_dataini", entry_dataini);
    entry_dataini->signal_button_release_event().connect(sigc::mem_fun(*this, &MainWindow::on_entry_dataini_release_event));

    builder->get_widget("entry_datafin", entry_datafin);
    entry_datafin->signal_button_release_event().connect(sigc::mem_fun(*this, &MainWindow::on_entry_datafin_release_event));

    builder->get_widget("itm_novo_item", itm_novo_item);
    itm_novo_item->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_itm_novo_item_activate_cb));

    builder->get_widget("list_itens", list_itens);
    list_itens->signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::listItensRowActivated));

    Glib::RefPtr<Gdk::Screen> screen;
    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    Glib::RefPtr<Gtk::StyleContext> css_context = Gtk::StyleContext::create();
    
    css_provider->load_from_resource("/org/gtkmm/gefin/style.css");
    mainwindow->get_property("screen", screen);
    css_context->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    MainWindow::on_calendar_dataini_day_selected();
    MainWindow::on_calendar_datafin_day_selected();
    
}

MainWindow::~MainWindow()
{}

Gtk::Window *MainWindow::getWindow()
{
    return mainwindow;
}

void MainWindow::quit()
{
    mainwindow->close();
}

void MainWindow::on_calendar_dataini_day_selected ()
{
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

    MainWindow::getItens();
}

void MainWindow::on_calendar_datafin_day_selected ()
{
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
    
    MainWindow::getItens();
}

void MainWindow::getItens()
{
    std::list<Item> *list_itens;
    QueryItem *query_item = new QueryItem();
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    char dataini[100], datafin[100], params[100];
    unsigned int year, month, day;

    builder->get_widget("calendar_dataini", calendar_dataini);
    calendar_dataini->get_date(year, month, day);
    sprintf(dataini, "%d-%02d-%02d", year, month + 1, day);
    
    builder->get_widget("calendar_datafin", calendar_datafin);
    calendar_datafin->get_date(year, month, day);
    sprintf(datafin, "%d-%02d-%02d", year, month + 1, day);

    auto store_itens = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_itens"));
    store_itens->clear();

    list_itens = query_item->GetItens(dataini, datafin);

    for (auto it = list_itens->begin(); it != list_itens->end(); ++it)
    {
        Gtk::TreeModel::iterator iter = store_itens->append();
        Gtk::TreeModel::Row row = *iter;

        row[m_Columns_Itens.iditem] = it->get_iditem();
        row[m_Columns_Itens.item] = it->get_item();
        row[m_Columns_Itens.data] = it->get_data();
        row[m_Columns_Itens.valor] = it->get_valor();
        row[m_Columns_Itens.classe] = it->get_classe();
        row[m_Columns_Itens.banco] = it->get_banco();
        row[m_Columns_Itens.tporc] = it->get_tporc();
        row[m_Columns_Itens.tpbanc] = it->get_tpbanc();
    }

    MainWindow::getTotais();
}

void MainWindow::getTotais()
{
    std::list<Item> *list_itens;
    QueryItem *query_item = new QueryItem();
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    Gtk::Entry *entry_total_receitas, *entry_total_despesas, *entry_saldo;
    char dataini[100], datafin[100];
    
    unsigned int year, month, day;
    
    builder->get_widget("calendar_dataini", calendar_dataini);
    calendar_dataini->get_date(year, month, day);
    sprintf(dataini, "%d-%02d-%02d", year, month + 1, day);
    
    builder->get_widget("calendar_datafin", calendar_datafin);
    calendar_datafin->get_date(year, month, day);
    sprintf(datafin, "%d-%02d-%02d", year, month + 1, day);

    builder->get_widget("entry_total_receitas", entry_total_receitas);
    builder->get_widget("entry_total_despesas", entry_total_despesas);
    builder->get_widget("entry_saldo", entry_saldo);
    
    list_itens = query_item->GetTotaisItens(dataini, datafin);

    for (auto totais = list_itens->begin(); totais != list_itens->end(); ++totais)
    {
        entry_total_receitas->set_text(totais->get_receitas());
        entry_total_despesas->set_text(totais->get_despesas());
        entry_saldo->set_text(totais->get_saldo());
    }
}

bool MainWindow::on_entry_dataini_release_event(GdkEventButton* release_event)
{
    Gtk::Popover * pp_dataini;
    
    builder->get_widget("pp_dataini", pp_dataini);
    pp_dataini->popup();

    return true;
}

bool MainWindow::on_entry_datafin_release_event(GdkEventButton* release_event)
{
    Gtk::Popover *pp_datafin;

    builder->get_widget("pp_datafin", pp_datafin);
    pp_datafin->popup();

    return true;
}

void MainWindow::on_startday_selected(Glib::ustring data)
{
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
    
}

void MainWindow::on_endday_selected(Glib::ustring data)
{
    Glib::Date enddate;
    Gtk::Button *btnDataFinal;
    Gtk::Popover *ppDataFinal;
    Gtk::Calendar *data_final;

    builder->get_widget("data_final", data_final);

    builder->get_widget("btnDataFinal", btnDataFinal);
    
    builder->get_widget("ppDataFinal", ppDataFinal);
    
    data_final->get_date(enddate);
    
}

void MainWindow::on_itm_novo_item_activate_cb()
{
    auto novo_item = new NovoItem();
    Gtk::Window * win_novo_item = novo_item->getWindow();
    win_novo_item->signal_delete_event().connect(sigc::mem_fun(*this, &MainWindow::novoItem));
    win_novo_item->show();
}

bool MainWindow::novoItem(GdkEventAny * ea)
{
    MainWindow::getItens();
    return false;
}

void MainWindow::listItensRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
{
    Gtk::TreeView *list_itens;
    
    builder->get_widget("list_itens", list_itens);
    Glib::RefPtr<Gtk::TreeModel> store = list_itens->get_model();
    Glib::RefPtr<Gtk::TreeSelection> selection = list_itens->get_selection();
    Gtk::TreeModel::iterator iter = selection->get_selected();
    
    if (iter)
    {
        Gtk::TreeModel::Row row = *iter;

        auto atualizaitem = new AtualizaItem();
        Gtk::Window *win_atualiza_item = atualizaitem->getWindow();
        win_atualiza_item->signal_delete_event().connect(sigc::mem_fun(*this, &MainWindow::get_itens));
        atualizaitem->atualizaItem(row);
        win_atualiza_item->show();
    }
}

bool MainWindow::get_itens(GdkEventAny * ea)
{
    MainWindow::getItens();
    return false;
}

void MainWindow::on_itm_bancos_activate_cb()
{
    auto bancos = new Bancos();
    Gtk::Window * win_bancos = bancos->getWindow();
    win_bancos->show();
}

void MainWindow::on_itm_classes_activate_cb()
{
    auto classes = new Classes();
    Gtk::Window *win_classes = classes->getWindow();
    win_classes->show();
}

void MainWindow::on_itm_especie_activate_cb()
{
    auto especie = new Especie();
    Gtk::Window *win_especie = especie->getWindow();
    win_especie->show();
}

void MainWindow::on_itm_relatorio_mensal_activate_cb()
{
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    
    unsigned int iyear, imonth, iday, fyear, fmonth, fday;
    
    builder->get_widget("calendar_dataini", calendar_dataini);
    calendar_dataini->get_date(iyear, imonth, iday);
    const Glib::ustring dataini = Glib::ustring::sprintf("%d-%02d-%02d", iyear, imonth + 1, iday);
    
    builder->get_widget("calendar_datafin", calendar_datafin);
    calendar_datafin->get_date(fyear, fmonth, fday);
    const Glib::ustring datafin = Glib::ustring::sprintf("%d-%02d-%02d", fyear, fmonth+1, fday);

    const Glib::ustring period = Glib::ustring::sprintf("%02d/%02d/%d - %02d/%02d/%d", iday, imonth+1, iyear, fday, fmonth+1, fyear);
    
    RelatorioMensal *relmensal = new RelatorioMensal();
    relmensal->create();
    relmensal->set_job_name("Relatório Mensal");
    relmensal->list_itens(dataini, datafin, period);
}
