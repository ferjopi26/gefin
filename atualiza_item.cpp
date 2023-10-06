#include "atualiza_item.h"

AtualizaItem::AtualizaItem()
{
    Glib::DateTime localtime = Glib::DateTime::create_now_local();
    Glib::Date date;
    int year, month, day;
    time_t data_current;
    struct tm * timeinfo;

    builder = Gtk::Builder::create();

    try
    {
        builder->add_from_resource("/org/gtkmm/gefin/atualiza_item.glade");
    }
    catch(const Glib::Error& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return;
    }

    builder->get_widget("win_atualiza_item", win_atualiza_item);
    builder->get_widget("calendar_data", calendar_data);
    builder->get_widget("entry_data", entry_data);
    builder->get_widget("entry_item", entry_item);
    builder->get_widget("entry_valor", entry_valor);
    builder->get_widget("cmb_bancos", cmb_bancos);
    builder->get_widget("btn_fechar", btn_fechar);
    builder->get_widget("btn_salvar", btn_salvar);
    builder->get_widget("btn_excluir", btn_excluir);

    builder->get_widget("pp_data", pp_data);

    btn_fechar->signal_clicked().connect(sigc::mem_fun(*this, &AtualizaItem::close));
    btn_salvar->signal_clicked().connect(sigc::mem_fun(*this, &AtualizaItem::salvar));
    btn_excluir->signal_clicked().connect(sigc::mem_fun(*this, &AtualizaItem::excluir));
    entry_data->signal_button_release_event().connect(sigc::mem_fun(*this, &AtualizaItem::on_entry_dataini_release_event));
    calendar_data->signal_day_selected().connect(sigc::mem_fun(*this, &AtualizaItem::on_calendar_data_day_selected));
    cmb_bancos->signal_changed().connect(sigc::mem_fun(*this, &AtualizaItem::on_cmb_banco_changed));
    
    time(&data_current);
    timeinfo = std::localtime(&data_current);

    calendar_data->select_day(timeinfo->tm_mday);
    calendar_data->select_month(timeinfo->tm_mon, timeinfo->tm_year+1900);   

    AtualizaItem::getClasses();
    AtualizaItem::getBancos();
    AtualizaItem::getTpOrc();
    AtualizaItem::getTpBanc();
}

AtualizaItem::~AtualizaItem(){}

Gtk::Window *AtualizaItem::getWindow()
{
    return win_atualiza_item;
}

void AtualizaItem::atualizaItem(Gtk::TreeRow row)
{
    Gtk::ComboBox *cmb_classes, *cmb_bancos, *cmb_tporc, *cmb_tpbanc;
    Gtk::Entry *entry_item, *entry_valor, *entry_data;
    Gtk::Calendar *calendar_data;
    Gtk::TreeModel::iterator iter_classe, iter_banco, iter_tporc, iter_tpbanc;
    Gtk::TreeModel::Row row_classe, row_banco, row_tporc, row_tpbanc, row_item;
    Glib::ustring classe, banco, tporc, tpbanc;

    row_item = row;

    builder->get_widget("cmb_classes", cmb_classes);
    builder->get_widget("cmb_bancos", cmb_bancos);
    builder->get_widget("cmb_tporc", cmb_tporc);
    builder->get_widget("cmb_tpbanc", cmb_tpbanc);

    builder->get_widget("entry_item", entry_item);
    builder->get_widget("entry_valor", entry_valor);
    builder->get_widget("entry_data",entry_data);

    builder->get_widget("calendar_data", calendar_data);

    iditem = row_item[m_Columns_Itens.iditem];
    entry_item->set_text(row_item[m_Columns_Itens.item]);
    entry_valor->set_text(row_item[m_Columns_Itens.valor]);
    entry_data->set_text(row_item[m_Columns_Itens.data]);

    Glib::ustring date = row[m_Columns_Itens.data];
    Glib::ustring day = date.substr(0, 2);
    Glib::ustring month = date.substr(3, 2);
    Glib::ustring year = date.substr(6, 4);
    calendar_data->select_day(atoi(day.c_str()));
    calendar_data->select_month(atoi(month.c_str()) - 1, atoi(year.c_str()));

    auto store_classes = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_classes"));
    Gtk::TreeModel::Children children_classes =  store_classes->children();

    for (unsigned int i = 0; i < children_classes.size(); i++)
    {
        cmb_classes->set_active(i);
        iter_classe = cmb_classes->get_active();
        row_classe = *iter_classe;
        
        if (row_item[m_Columns_Itens.classe] == row_classe[m_Columns_Classes.classe])
        {
            cmb_classes->set_active(i);
            break;
        }
    }
    
    auto store_bancos = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_bancos"));
    Gtk::TreeModel::Children children_bancos =  store_bancos->children();

    for (unsigned int i = 0; i < children_bancos.size(); i++)
    {
        cmb_bancos->set_active(i);
        iter_banco = cmb_bancos->get_active();
        row_banco = *iter_banco;
        
        if (row_item[m_Columns_Itens.banco] == row_banco[m_Columns_Bancos.idbanco])
        {
            cmb_bancos->set_active(i);
            break;
        }
    }

    auto store_tporc = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_tporc"));
    Gtk::TreeModel::Children children_tporc =  store_tporc->children();

    for (unsigned int i = 0; i < children_tporc.size(); i++)
    {
        cmb_tporc->set_active(i);
        iter_tporc = cmb_tporc->get_active();
        row_tporc = *iter_tporc;
        
        if (row_item[m_Columns_Itens.tporc] == row_tporc[m_Columns_TpOrc.idtipo])
        {
            cmb_tporc->set_active(i);
            break;
        }
    }

    auto store_tpbanc = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_tpbanc"));
    Gtk::TreeModel::Children children_tpbanc =  store_tpbanc->children();

    for (unsigned int i = 0; i < children_tpbanc.size(); i++)
    {
        cmb_tpbanc->set_active(i);
        iter_tpbanc = cmb_tpbanc->get_active();
        row_tpbanc = *iter_tpbanc;
        
        if (row_item[m_Columns_Itens.tpbanc] == row_tpbanc[m_Columns_TpBanc.idtipo])
        {
            cmb_tpbanc->set_active(i);
            break;
        }
    }

}

void AtualizaItem::getClasses()
{
    Gtk::ComboBox *cmb_classes;
    
    QueryClasse *query_classe = new QueryClasse();

    listClasses = new std::list<Classe>;

    auto store_classes = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_classes"));
    store_classes->clear();

    listClasses = query_classe->GetClasses();

    for (auto list_classe = listClasses->begin(); list_classe != listClasses->end(); ++list_classe)
    {
        Gtk::TreeModel::iterator iter = store_classes->append();
        Gtk::TreeModel::Row row = *iter;

        row[m_Columns_Classes.idclasse] = list_classe->get_idclasse();
        row[m_Columns_Classes.classe] = list_classe->get_classe();
    }
}

void AtualizaItem::getBancos()
{
    Gtk::ComboBox *cmb_bancos;
    
    QueryBanco *query_banco = new QueryBanco();

    listBancos = new std::list<Banco>;

    auto store_bancos = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_bancos"));
    store_bancos->clear();

    listBancos = query_banco->get_bancos();

    for (auto list_banco = listBancos->begin(); list_banco != listBancos->end(); ++list_banco)
    {
        Gtk::TreeModel::iterator iter = store_bancos->append();
        Gtk::TreeModel::Row row = *iter;

        row[m_Columns_Bancos.idbanco] = list_banco->get_idbanco();
        row[m_Columns_Bancos.banco] = list_banco->get_banco();
        row[m_Columns_Bancos.conta] = list_banco->get_conta();
        row[m_Columns_Bancos.agencia] = list_banco->get_agencia();
    }
}

void AtualizaItem::getTpOrc()
{
    Gtk::ComboBox *cmb_tporc;
    
    QueryTpOrc *query_tporc = new QueryTpOrc();

    listTporc = new std::list<TpOrc>;

    auto store_tporc = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_tporc"));
    store_tporc->clear();

    listTporc = query_tporc->GetTpOrc();

    for (auto list_tporc = listTporc->begin(); list_tporc != listTporc->end(); ++list_tporc)
    {
        Gtk::TreeModel::iterator iter = store_tporc->append();
        Gtk::TreeModel::Row row = *iter;

        row[m_Columns_TpOrc.idtipo] = list_tporc->get_idtipo();
        row[m_Columns_TpOrc.tipo] = list_tporc->get_tipo();
    }
    
}

void AtualizaItem::getTpBanc()
{
    Gtk::ComboBox *cmb_tpbanc;
    
    QueryTpBanc *query_tpbanc = new QueryTpBanc();

    listTpbanc = new std::list<TpBanc>;

    auto store_tpbanc = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_tpbanc"));
    store_tpbanc->clear();

    listTpbanc = query_tpbanc->GetTpBanc();

    for (auto list_tpbanc = listTpbanc->begin(); list_tpbanc != listTpbanc->end(); ++list_tpbanc)
    {
        Gtk::TreeModel::iterator iter = store_tpbanc->append();
        Gtk::TreeModel::Row row = *iter;

        row[m_Columns_TpOrc.idtipo] = list_tpbanc->get_idtipo();
        row[m_Columns_TpOrc.tipo] = list_tpbanc->get_tipo();
    }
    
}

void AtualizaItem::close()
{
    win_atualiza_item->close();
}

void AtualizaItem::on_calendar_data_day_selected()
{
    Glib::Date startdate;
    
    calendar_data->get_date(startdate);
    
    entry_data->set_text(startdate.format_string("%d/%m/%Y"));

    pp_data->popdown();

}

bool AtualizaItem::on_entry_dataini_release_event(GdkEventButton* release_event)
{
    Gtk::Popover *pp_data;

    builder->get_widget("pp_data", pp_data);
    pp_data->popup();

    return true;
}

void AtualizaItem::on_cmb_banco_changed()
{
    Gtk::Label *lbl_conta, selected_conta, selected_agencia;
    Gtk::ComboBox *cmb_bancos;
    Glib::ustring conta;

    builder->get_widget("lbl_conta", lbl_conta);
    builder->get_widget("cmb_bancos", cmb_bancos);

    Gtk::TreeModel::iterator iter_banco = cmb_bancos->get_active();
    Gtk::TreeModel::Row row_banco = *iter_banco;
    
    conta.append("Conta ");
    conta.append(row_banco[m_Columns_Bancos.conta]);
    conta.append(" Agência ");
    conta.append(row_banco[m_Columns_Bancos.agencia]);

    lbl_conta->set_text(conta);
}

void AtualizaItem::salvar()
{
    Glib::ustring item, valor, selected_idclasse, selected_idbanco, selected_idtporc, selected_idtpbanc;
    unsigned int year, month, day;
    char sql[1000], data[100], mensagem[100];

    std::list<Item> *listItem = new std::list<Item>;
    QueryItem *query_item = new QueryItem();
    Item *new_item = new Item();
    
    calendar_data->get_date(year, month, day);

    item = this->entry_item->get_text();
    valor = entry_valor->get_text();
    sprintf(data, "%02d-%02d-%02d", year, month + 1, day);
    
    auto store_classes = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_classes"));
    builder->get_widget("cmb_classes", cmb_classes);
    Gtk::TreeModel::iterator iter_classe = cmb_classes->get_active();
    Gtk::TreeModel::Row row_classe = *iter_classe;
    selected_idclasse = row_classe[m_Columns_Classes.idclasse];

    auto store_bancos = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_bancos"));
    builder->get_widget("cmb_bancos", cmb_bancos);
    Gtk::TreeModel::iterator iter_banco = cmb_bancos->get_active();
    Gtk::TreeModel::Row row_banco = *iter_banco;
    selected_idbanco = row_banco[m_Columns_Bancos.idbanco];

    auto store_tporc = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_tporc"));
    builder->get_widget("cmb_tporc", cmb_tporc);
    Gtk::TreeModel::iterator iter_tporc = cmb_tporc->get_active();
    Gtk::TreeModel::Row row_tporc = *iter_tporc;
    selected_idtporc = row_tporc[m_Columns_TpOrc.idtipo];

    auto store_tpbanc = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object("store_tpbanc"));
    builder->get_widget("cmb_tpbanc", cmb_tpbanc);
    Gtk::TreeModel::iterator iter_tpbanc = cmb_tpbanc->get_active();
    Gtk::TreeModel::Row row_tpbanc = *iter_tpbanc;
    selected_idtpbanc = row_tpbanc[m_Columns_TpBanc.idtipo];

    new_item->set_iditem(iditem);
    new_item->set_item(item);
    new_item->set_data(data);
    new_item->set_valor(valor);
    new_item->set_classe(selected_idclasse);
    new_item->set_banco(selected_idbanco);
    new_item->set_tporc(selected_idtporc);
    new_item->set_tpbanc(selected_idtpbanc);
    
    int affectedRows = query_item->UpdateItem(new_item);

    sprintf(mensagem, "Atualizado %d registro na Tabela itens", affectedRows);

    Gtk::MessageDialog dialog(*win_atualiza_item, "Atualiza Item", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);

    dialog.set_secondary_text(mensagem);

    dialog.run();
    
    win_atualiza_item->close();

}

void AtualizaItem::excluir()
{
    MYSQL *conn;
    char sql[1000], mensagem[100];

    Gtk::MessageDialog dialog(*win_atualiza_item, "Gestão Financeira", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_NONE);
    Gtk::Button * button = dialog.add_button("Excluir", Gtk::RESPONSE_OK);
    Glib::RefPtr<Gtk::StyleContext> stContext = button->get_style_context();
    stContext->add_class("destructive-action");
    button = dialog.add_button("Cancelar", Gtk::RESPONSE_CANCEL);
    stContext = button->get_style_context();
    stContext->add_class("suggested-action");
    
    dialog.set_secondary_text("O item será excluído");

    int result = dialog.run();
    std::cout << iditem << std::endl;
    switch(result)
    {
        case(Gtk::RESPONSE_OK):
        {
            QueryItem *query_item = new QueryItem();

            int affectedRows = query_item->DeleteItem(iditem);
            
            sprintf(mensagem, "Excluído %d registro na Tabela itens", affectedRows);

            Gtk::MessageDialog dialog(*win_atualiza_item, "Atualiza Item", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);

            dialog.set_secondary_text(mensagem);

            dialog.run();

            win_atualiza_item->close();

            break;
        }
        case(Gtk::RESPONSE_CANCEL):
        {
            win_atualiza_item->close();
            break;
        }
        default:
        {
            break;
        }
    }
}
