#include "novo_banco.h"

NovoBanco::NovoBanco(){
    Gtk::Button *btn_fechar, *btn_salvar, *btn_limpar;

    builder = Gtk::Builder::create();

    try
    {
        builder->add_from_resource("/org/gtkmm/gefin/novo_banco.glade");
    }
    catch(const Glib::Error& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return;
    }

    builder->get_widget("win_novo_banco", win_novo_banco);
    builder->get_widget("btn_fechar", btn_fechar);
    builder->get_widget("btn_salvar", btn_salvar);
    builder->get_widget("btn_limpar", btn_limpar);

    btn_fechar->signal_clicked().connect(sigc::mem_fun(*this, &NovoBanco::on_btn_fechar_clicked));
    btn_salvar->signal_clicked().connect(sigc::mem_fun(*this, &NovoBanco::on_btn_salvar_clicked));
    btn_limpar->signal_clicked().connect(sigc::mem_fun(*this, &NovoBanco::on_btn_limpar_clicked));

}

NovoBanco::~NovoBanco(){}

Gtk::Window *NovoBanco::getWindow(){
    return win_novo_banco;
}

void NovoBanco::on_btn_fechar_clicked(){
    win_novo_banco->close();
}

void NovoBanco::on_btn_salvar_clicked(){
    Gtk::Entry *entry_banco, *entry_conta, *entry_agencia;
    Glib::ustring banco, conta, agencia;
   // MYSQL *conn;
    char /*sql[1000],*/ mensagem[100];

    QueryBanco *query_banco = new QueryBanco();
    listBancos = new std::list<Banco>;
    Banco new_banco;

    builder->get_widget("entry_banco", entry_banco);
    banco = entry_banco->get_text();

    builder->get_widget("entry_conta", entry_conta);
    conta = entry_conta->get_text();

    builder->get_widget("entry_agencia", entry_agencia);
    agencia = entry_agencia->get_text();

    new_banco.set_banco(banco);
    new_banco.set_conta(conta);
    new_banco.set_agencia(agencia);

    listBancos->push_back(new_banco);

    int newInsertId = query_banco->insert_banco(listBancos);

    /*sprintf(sql, "INSERT INTO bancos(banco, conta, agencia) VALUES('%s', '%s', '%s')", banco.c_str(), conta.c_str(), agencia.c_str());

    conn = mysql_init(NULL);

    mysql_real_connect(conn, "localhost", "fernando", "ferjopi26", "gefin_sdbox", 0, NULL, 0);

    mysql_set_character_set(conn, "utf8");

    if (mysql_query(conn, sql))
    {
        printf("%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    int newInsertId = mysql_insert_id(conn);*/
    
    sprintf(mensagem, "Inserido 1 registro com Id %d na Tabela bancos", newInsertId);

    Gtk::MessageDialog dialog(*win_novo_banco, "Novo Banco", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);

    dialog.set_secondary_text(mensagem);

    dialog.run();

    /*mysql_close(conn);*/

}

void NovoBanco::on_btn_limpar_clicked(){
    Gtk::Entry *entry_banco, *entry_conta, *entry_agencia;

    builder->get_widget("entry_banco", entry_banco);
    builder->get_widget("entry_conta", entry_conta);
    builder->get_widget("entry_agencia", entry_agencia);

    entry_banco->set_text("");
    entry_conta->set_text("");
    entry_agencia->set_text("");

    entry_banco->grab_focus();
}
