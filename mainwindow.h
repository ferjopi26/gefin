#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include <mysql.h>
#include <iostream>
#include "item.h"
#include "query_item.h"
#include "novo_item.h"
#include "atualiza_item.h"
#include "bancos.h"
#include "classes.h"
#include "nova_classe.h"
#include "especie.h"
#include "relatorio_mensal.h"

class MainWindow
{
    protected:
        Gtk::Window* mainwindow;
        char sql[1000] = "";
    
    public:
        MainWindow();
        virtual ~MainWindow();
        Gtk::Window *getWindow();
        void getItens();
        void getTotais();
        
        void quit();
        void on_calendar_dataini_day_selected();
        void on_calendar_datafin_day_selected();
        bool on_entry_dataini_release_event(GdkEventButton* release_event);
        bool on_entry_datafin_release_event(GdkEventButton* release_event);
        void on_startday_selected(Glib::ustring data);
        void on_endday_selected(Glib::ustring data);
        bool novoItem(GdkEventAny * ea);
        bool get_itens(GdkEventAny * ea);

        void on_itm_novo_item_activate_cb();
        void listItensRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        void on_itm_bancos_activate_cb();
        void on_itm_classes_activate_cb();
        void on_itm_especie_activate_cb();
        void on_itm_relatorio_mensal_activate_cb();
        //void on_itm_relatorio_anual_activate_cb();
        
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

        Glib::RefPtr<Gtk::Builder> builder;
};

#endif
