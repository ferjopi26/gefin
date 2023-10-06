#ifndef NOVA_CLASSE_H
#define NOVA_CLASSE_H

#include <gtkmm.h>
#include <mysql.h>
#include <iostream>
#include "query_classe.h"

class NovaClasse{
    Gtk::Window* win_nova_classe;
    
    public:
        NovaClasse();
        virtual ~NovaClasse();
        Gtk::Window *getWindow();

        void on_btn_fechar_clicked();
        void on_btn_salvar_clicked();
        void on_btn_limpar_clicked();
        
        Glib::RefPtr<Gtk::Builder> builder;
};

#endif
