#include "nova_classe.h"

NovaClasse::NovaClasse(){
    Gtk::Button *btn_fechar, *btn_salvar, *btn_limpar;

    builder = Gtk::Builder::create();

    try
    {
        builder->add_from_resource("/org/gtkmm/gefin/nova_classe.glade");
    }
    catch(const Glib::Error& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return;
    }

    builder->get_widget("win_nova_classe", win_nova_classe);
    builder->get_widget("btn_fechar", btn_fechar);
    builder->get_widget("btn_salvar", btn_salvar);
    builder->get_widget("btn_limpar", btn_limpar);

    btn_fechar->signal_clicked().connect(sigc::mem_fun(*this, &NovaClasse::on_btn_fechar_clicked));
    btn_salvar->signal_clicked().connect(sigc::mem_fun(*this, &NovaClasse::on_btn_salvar_clicked));
    btn_limpar->signal_clicked().connect(sigc::mem_fun(*this, &NovaClasse::on_btn_limpar_clicked));

}

NovaClasse::~NovaClasse(){}

Gtk::Window *NovaClasse::getWindow()
{
    return win_nova_classe;
}

void NovaClasse::on_btn_fechar_clicked(){
    win_nova_classe->close();
}

void NovaClasse::on_btn_salvar_clicked(){
    Gtk::Entry *entry_classe;
    Glib::ustring classe;
    char sql[1000], mensagem[100];

    QueryClasse *query_classe = new QueryClasse();

    builder->get_widget("entry_classe", entry_classe);
    classe = entry_classe->get_text();

    int newInsertId = query_classe->InsertClasse(classe.c_str());
    
    sprintf(mensagem, "Inserido 1 registro com Id %d na Tabela classes", newInsertId);

    Gtk::MessageDialog dialog(*win_nova_classe, "Nova Classe", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);

    dialog.set_secondary_text(mensagem);

    dialog.run();

}

void NovaClasse::on_btn_limpar_clicked(){
    Gtk::Entry *entry_classe;
    builder->get_widget("entry_classe", entry_classe);

    entry_classe->set_text("");
    entry_classe->grab_focus();
}
