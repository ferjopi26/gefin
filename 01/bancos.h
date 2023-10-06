#ifndef BANCOS_H
#define BANCOS_H

#include <gtkmm.h>
#include <mysql.h>
#include <iostream>
#include "query_item.h"
#include "banco.h"
#include "novo_banco.h"

class Bancos
{
    protected:
        Gtk::Window* win_bancos;
        Glib::ustring selected_idbanco;
        Gtk::Calendar *calendar_dataini, *calendar_datafin;
        Gtk::ComboBox *cmb_banco;
        Glib::Date date;
        Gtk::Entry *entry_data_ini, *entry_data_fin;
        std::list<Banco> *listBancos;
    
    public:
        Bancos();
        virtual ~Bancos();
        Gtk::Window *getWindow();
        void getBancos();
        void getItens();
        void getTotais();

        void on_cmb_banco_changed();
        void on_itm_novo_banco_activate();
        void on_itm_extrato_mensal_activate();
        void on_itm_extrato_anual_activate();
        void quit();
        bool on_entry_dataini_release_event(GdkEventButton* release_event);
        bool on_entry_datafin_release_event(GdkEventButton* release_event);
        void on_calendar_dataini_day_selected();
        void on_calendar_datafin_day_selected();
        bool novo_banco(GdkEventAny * ea);
    
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

        class ModelColumnsItens : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsItens()
                {
                    add(iditem);
                    add(data);
                    add(tipo);
                    add(valor);
                    add(historico);
                }

                Gtk::TreeModelColumn<Glib::ustring> iditem;
                Gtk::TreeModelColumn<Glib::ustring> data;
                Gtk::TreeModelColumn<Glib::ustring> tipo;
                Gtk::TreeModelColumn<Glib::ustring> valor;
                Gtk::TreeModelColumn<Glib::ustring> historico;
        };

        ModelColumnsBancos m_Columns_Bancos;
        ModelColumnsItens m_Columns_Itens;

        Glib::RefPtr<Gtk::Builder> builder;
};

#endif
