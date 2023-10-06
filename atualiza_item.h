#ifndef ATUALIZA_ITEM_H
#define ATUALIZA_ITEM_H

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

class AtualizaItem{
    protected:
        Gtk::Window* win_atualiza_item;
        Glib::ustring selected_idclasse;
        Glib::ustring selected_idbanco;
        Glib::ustring selected_idtporc;
        Glib::ustring selected_idtpbanc;
        Glib::ustring iditem;
    
        std::list<Classe> *listClasses;
        std::list<Banco> *listBancos;
        std::list<TpOrc> *listTporc;
        std::list<TpBanc> *listTpbanc;

        Gtk::Popover *pp_data;

        Gtk::Calendar *calendar_data;
        Gtk::Entry *entry_data, *entry_item, *entry_valor;
        Gtk::ComboBox *cmb_classes, *cmb_bancos, *cmb_tporc, *cmb_tpbanc;
        Gtk::Button *btn_fechar, *btn_salvar, *btn_excluir;
    
    public:
        AtualizaItem();
        virtual ~AtualizaItem();
        Gtk::Window *getWindow();
        void atualizaItem(Gtk::TreeRow row);
        void getClasses();
        void getBancos();
        void getTpOrc();
        void getTpBanc();
        void close();
        void salvar();
        void excluir();
        
        void on_calendar_data_day_selected();
        bool on_entry_dataini_release_event(GdkEventButton* release_event);
        void on_cmb_banco_changed();

        class ModelColumnsClasses : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsClasses()
                { add(idclasse); add(classe);}

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

        class ModelColumnsItens : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsItens()
                {
                    add(iditem);
                    add(item);
                    add(valor);
                    add(data);
                    add(classe);
                    add(tpbanc);
                    add(tporc);
                    add(banco);
                }

                Gtk::TreeModelColumn<Glib::ustring> iditem;
                Gtk::TreeModelColumn<Glib::ustring> item;
                Gtk::TreeModelColumn<Glib::ustring> valor;
                Gtk::TreeModelColumn<Glib::ustring> data;
                Gtk::TreeModelColumn<Glib::ustring> classe;
                Gtk::TreeModelColumn<Glib::ustring> tpbanc;
                Gtk::TreeModelColumn<Glib::ustring> tporc;
                Gtk::TreeModelColumn<Glib::ustring> banco;
        };

        ModelColumnsItens m_Columns_Itens;
        ModelColumnsClasses m_Columns_Classes;
        ModelColumnsBancos m_Columns_Bancos;
        ModelColumnsTpOrc m_Columns_TpOrc;
        ModelColumnsTpBanc m_Columns_TpBanc;

        Glib::RefPtr<Gtk::Builder> builder;
};

#endif
