#ifndef NOVO_ITEM_H
#define NOVO_ITEM_H

#include <gtkmm.h>
#include <mysql.h>
#include <iostream>
#include <list>
#include "item.h"
#include "query_item.h"
#include "classe.h"
#include "query_classe.h"
#include "banco.h"
#include "query_banco.h"
#include "tp_orc.h"
#include "query_tp_orc.h"
#include "tp_banc.h"
#include "query_tp_banc.h"

class NovoItem{
    protected:
        Gtk::Window* win_novo_item;
        Glib::ustring selected_idclasse;
        Glib::ustring selected_idbanco;
        Glib::ustring selected_idtporc;
        Glib::ustring selected_idtpbanc;

        std::list<Classe> *listClasses;
        std::list<Banco> *listBancos;
        std::list<TpOrc> *listTporc;
        std::list<TpBanc> *listTpbanc;
    
    public:
        NovoItem();
        virtual ~NovoItem();
        Gtk::Window *getWindow();
        void getClasses();
        void getBancos();
        void getTpOrc();
        void getTpBanc();
        void close();
        void salvar();
        void limpar();

        void on_calendar_data_day_selected();
        bool on_entry_dataini_release_event(GdkEventButton* release_event);
        void on_cmb_banco_changed();
    
        class ModelColumnsClasses : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsClasses()
                {
                    add(idclasse);
                    add(classe);
                }

                Gtk::TreeModelColumn<Glib::ustring> idclasse;
                Gtk::TreeModelColumn<Glib::ustring> classe;
        };

        class ModelColumnsBancos : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsBancos()
                {
                    add(idbanco);
                    add(banco);
                    add(conta);
                    add(agencia);
                }

                Gtk::TreeModelColumn<Glib::ustring> idbanco;
                Gtk::TreeModelColumn<Glib::ustring> banco;
                Gtk::TreeModelColumn<Glib::ustring> conta;
                Gtk::TreeModelColumn<Glib::ustring> agencia;
        };

        class ModelColumnsTpOrc : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsTpOrc()
                {
                    add(idtipo);
                    add(tipo);
                }

                Gtk::TreeModelColumn<Glib::ustring> idtipo;
                Gtk::TreeModelColumn<Glib::ustring> tipo;
        };

        class ModelColumnsTpBanc : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsTpBanc()
                {
                    add(idtipo);
                    add(tipo);
                }

                Gtk::TreeModelColumn<Glib::ustring> idtipo;
                Gtk::TreeModelColumn<Glib::ustring> tipo;
        };

        ModelColumnsClasses m_Columns_Classes;
        ModelColumnsBancos m_Columns_Bancos;
        ModelColumnsTpOrc m_Columns_TpOrc;
        ModelColumnsTpBanc m_Columns_TpBanc;

        Glib::RefPtr<Gtk::Builder> builder;
};

#endif
