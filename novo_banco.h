#ifndef NOVO_BANCO_H
#define NOVO_BANCO_H

#include <gtkmm.h>
#include <mysql.h>
#include <iostream>
#include "banco.h"
#include "query_banco.h"

class NovoBanco{
    Gtk::Window* win_novo_banco;
    std::list<Banco> *listBancos;
    
    public:
        NovoBanco();
        virtual ~NovoBanco();
        Gtk::Window *getWindow();

        void on_btn_fechar_clicked();
        void on_btn_salvar_clicked();
        void on_btn_limpar_clicked();
        
        Glib::RefPtr<Gtk::Builder> builder;
};

#endif
