#include "bancos.h"

Bancos::Bancos()
{
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
        builder->add_from_resource("/org/gtkmm/gefin/bancos.glade");
    }
    catch(const Glib::Error& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return;
    }

    this->store_bancos = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_banco"));

    builder->get_widget("win_bancos", win_bancos);
    builder->get_widget("cmb_banco", this->cmb_banco);

    builder->get_widget("calendar_dataini", calendar_dataini);
    builder->get_widget("calendar_datafin", calendar_datafin);

    builder->get_widget("entry_data_ini", entry_data_ini);
    entry_data_ini->signal_button_release_event().connect(sigc::mem_fun(*this, &Bancos::on_entry_dataini_release_event));

    builder->get_widget("entry_data_fin", entry_data_fin);
    entry_data_fin->signal_button_release_event().connect(sigc::mem_fun(*this, &Bancos::on_entry_datafin_release_event));

    builder->get_widget("itm_fechar", itm_fechar);
    itm_fechar->signal_activate().connect(sigc::mem_fun(*this, &Bancos::quit));

    builder->get_widget("itm_novo_banco", itm_novo_banco);
    itm_novo_banco->signal_activate().connect(sigc::mem_fun(*this, &Bancos::on_itm_novo_banco_activate));

    builder->get_widget("itm_extrato", itm_extrato);
    itm_extrato->signal_activate().connect(sigc::mem_fun(*this, &Bancos::on_itm_extrato_mensal_activate));

    time(&data_current);
    timeinfo = std::localtime(&data_current);

    calendar_dataini->select_day(1);
    calendar_dataini->select_month(timeinfo->tm_mon, timeinfo->tm_year+1900);

    calendar_datafin->select_day(Glib::Date::get_days_in_month((Glib::Date::Month)(timeinfo->tm_mon+1), (timeinfo->tm_year + 1900)));
    calendar_datafin->select_month(timeinfo->tm_mon, timeinfo->tm_year+1900);
    
    calendar_dataini->signal_day_selected().connect(sigc::mem_fun(*this, &Bancos::on_calendar_dataini_day_selected));
    calendar_datafin->signal_day_selected().connect(sigc::mem_fun(*this, &Bancos::on_calendar_datafin_day_selected));

    builder->get_widget("pp_dataini", pp_dataini);
    builder->get_widget("pp_datafin", pp_datafin);

    auto signal = cmb_banco->signal_changed().connect(sigc::mem_fun(*this, &Bancos::on_cmb_banco_changed));

    Bancos::getBancos();

}

Bancos::~Bancos(){}

Gtk::Window *Bancos::getWindow()
{
    return win_bancos;
}

void Bancos::getBancos()
{
    QueryBanco *query_banco = new QueryBanco();

    listBancos = new std::list<Banco>;

    this->store_bancos->clear();

    listBancos = query_banco->get_bancos();

    for (auto list_banco = listBancos->begin(); list_banco != listBancos->end(); ++list_banco)
    {
        Gtk::TreeModel::iterator iter = this->store_bancos->append();
        Gtk::TreeModel::Row row = *iter;
        
        row[m_Columns_Bancos.idbanco] = list_banco->get_idbanco();
        row[m_Columns_Bancos.banco] = list_banco->get_banco();
        row[m_Columns_Bancos.conta] = list_banco->get_conta();
        row[m_Columns_Bancos.agencia] = list_banco->get_agencia();
    }

    this->cmb_banco->set_active(0);

}

void Bancos::on_cmb_banco_changed()
{
    Gtk::Label *lbl_conta;
    Glib::ustring conta;
    listBanco = new std::list<Banco>;
    
    builder->get_widget("lbl_conta", lbl_conta);
    
    Gtk::TreeModel::iterator iter_banco = this->cmb_banco->get_active();

    if(iter_banco)
    {
        Gtk::TreeModel::Row row = *iter_banco;
    
        conta.append("Conta ");
        conta.append(row[m_Columns_Bancos.conta]);
        conta.append(" Agência ");
        conta.append(row[m_Columns_Bancos.agencia]);

        lbl_conta->set_text(conta);

        Banco banco;
        banco.set_idbanco(row[m_Columns_Bancos.idbanco]);
        banco.set_banco(row[m_Columns_Bancos.banco]);
        banco.set_conta(row[m_Columns_Bancos.conta]);
        banco.set_agencia(row[m_Columns_Bancos.agencia]);

        listBanco->push_back(banco);
        
        Bancos::getItens();
    }
    
}

void Bancos::on_itm_novo_banco_activate()
{
    this->idbanco = this->selected_idbanco;
    auto novo_banco = new NovoBanco();
    Gtk::Window * win_novo_banco = novo_banco->getWindow();
    win_novo_banco->signal_delete_event().connect(sigc::mem_fun(*this, &Bancos::novo_banco));
    win_novo_banco->show();
}

bool Bancos::novo_banco(GdkEventAny * ea)
{
    Bancos::getBancos();

    Gtk::TreeModel::Children children_bancos =  this->store_bancos->children();
    Gtk::TreeModel::iterator iter_banco = this->cmb_banco->get_active();
    Gtk::TreeModel::Row row_banco;

    for (unsigned int i = 0; i < children_bancos.size(); i++)
    {
        this->cmb_banco->set_active(i);
        iter_banco = this->cmb_banco->get_active();
        row_banco = *iter_banco;
        
        if (row_banco[m_Columns_Bancos.idbanco] == this->idbanco)
        {
            this->cmb_banco->set_active(i);
            break;
        }
    }

    return false;
}

void Bancos::getItens()
{
    std::list<Item> *list_itens;
    QueryItem *query_item = new QueryItem();
    
    guint year, month, day;
    char dataini[100], datafin[100], params[100];
    const char *credito, *debito;

    builder->get_widget("cmb_banco", cmb_banco);

    Gtk::TreeModel::iterator iter_banco = cmb_banco->get_active();
    Gtk::TreeModel::Row row_banco = *iter_banco;
    selected_idbanco = row_banco[m_Columns_Bancos.idbanco];

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
    
    list_itens = query_item->GetItens(dataini, datafin, selected_idbanco.c_str());

    for (auto it = list_itens->begin(); it != list_itens->end(); ++it)
    {
        Gtk::TreeModel::iterator iter = store_itens->append();
        Gtk::TreeModel::Row row = *iter;

        row[m_Columns_Itens.iditem] = it->get_iditem();
        row[m_Columns_Itens.data] = it->get_data();
        row[m_Columns_Itens.tipo] = it->get_tpbanc();
        row[m_Columns_Itens.valor] = it->get_valor();
        row[m_Columns_Itens.historico] = it->get_item();
        row[m_Columns_Itens.tipo] = it->get_tpbanc();
    }

    Bancos::getTotais();
}

void Bancos::getTotais()
{
    std::list<Item> *list_itens;
    QueryItem *query_item = new QueryItem();
    
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    Gtk::Entry *entry_creditos, *entry_debitos, *entry_saldo;
    char sql_totais[1000] = "", dataini[100], datafin[100], params[100];

    unsigned int year, month, day;
    
    builder->get_widget("calendar_dataini", calendar_dataini);
    calendar_dataini->get_date(year, month, day);
    sprintf(dataini, "%d-%02d-%02d", year, month + 1, day);
    
    builder->get_widget("calendar_datafin", calendar_datafin);
    calendar_datafin->get_date(year, month, day);
    sprintf(datafin, "%d-%02d-%02d", year, month + 1, day);

    builder->get_widget("entry_creditos", entry_creditos);
    builder->get_widget("entry_debitos", entry_debitos);
    builder->get_widget("entry_saldo", entry_saldo);

    list_itens = query_item->GetTotaisItens(dataini, datafin, selected_idbanco.c_str());

    for (auto it = list_itens->begin(); it != list_itens->end(); ++it)
    {
        entry_creditos->set_text(it->get_creditos());
        entry_debitos->set_text(it->get_debitos());
        entry_saldo->set_text(it->get_saldo());
    }
        
}

void Bancos::quit()
{
    win_bancos->close();
}
bool Bancos::on_entry_dataini_release_event(GdkEventButton* release_event)
{
    Gtk::Popover * pp_dataini;

    builder->get_widget("pp_dataini", pp_dataini);
    pp_dataini->popup();

    return true;
}

bool Bancos::on_entry_datafin_release_event(GdkEventButton* release_event)
{
    Gtk::Popover *pp_datafin;

    builder->get_widget("pp_datafin", pp_datafin);
    pp_datafin->popup();

    return true;
}

void Bancos::on_calendar_dataini_day_selected()
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

    Bancos::getItens();
}

void Bancos::on_calendar_datafin_day_selected ()
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
    
    Bancos::getItens();
}

void Bancos::on_itm_extrato_mensal_activate()
{
    Gtk::Calendar *calendar_dataini, *calendar_datafin;
    unsigned int year, month, day;
    
    builder->get_widget("calendar_dataini", calendar_dataini);
    calendar_dataini->get_date(year, month, day);
    Glib::ustring dataini = Glib::ustring::sprintf("%d-%02d-%02d", year, month + 1, day);
    
    builder->get_widget("calendar_datafin", calendar_datafin);
    calendar_datafin->get_date(year, month, day);
    Glib::ustring datafin = Glib::ustring::sprintf("%d-%02d-%02d", year, month + 1, day);
    
    ExtratoMensal *extmensal = new ExtratoMensal();
    extmensal->set_job_name("Extrato Mensal");
    extmensal->list_itens(dataini, datafin, selected_idbanco, listBanco);

}

void Bancos::on_itm_extrato_anual_activate()
{
    /*Gtk::Calendar *calendar_dataini;
    unsigned int year, month, day;
    char ano[4];
    
    builder->get_widget("calendar_dataini", calendar_dataini);
    calendar_dataini->get_date(year, month, day);
    sprintf(ano, "%d", year);

    ExtratoAnual *extanual = new ExtratoAnual();
    extanual->init(year, selected_idbanco.c_str());*/
}
